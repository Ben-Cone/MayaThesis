
#include "Maya.h"
#include "Engine.h"
#include "Master.h"
#include "Kismet/KismetMathLibrary.h"
#include "AnimationsPlanar.h"
#include "Beats.h"
#include "Movement.h"
#include "Music.h"
#include "Environment.h"
#include "Curves.h"
#include "Spectrum.h"
#include "Orchestrator.h"


AOrchestrator::AOrchestrator()
{

	previousBeat.Add(previousWholeBeat = 0);
	previousBeat.Add(previousHalfBeat = 0);
	previousBeat.Add(previousQuarterBeat = 0);
	previousBeat.Add(previousEighthBeat = 0);

	currentBeat.Add(wholeBeat = 0);
	currentBeat.Add(halfBeat = 0);
	currentBeat.Add(quarterBeat = 0);
	currentBeat.Add(eighthBeat = 0);

	PrimaryActorTick.bCanEverTick = true;

	decayingRepeater = 1;

	masterLocation.Z = 70.f;

}

void AOrchestrator::BeginPlay()
{
	Super::BeginPlay();
	SpawnDefaultClasses();

}

void AOrchestrator::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	timeDelta = DeltaTime;

	// master update current 
	Master->SpawnTrail();
	masterLocation = Movement->GetCurrentLocation();

	// user update 
	userLocation = userClass->GetActorLocation();
	AggroUpdate();

	// point tracking
	pointsNormalized = PointCurve->InverseLerp(0, maxPoints, points);
	PointCurve->InterpNotes(pointsNormalized);

	// beat driver
	BeatCalculator(DeltaTime);
	SectionController();

	// move master
	Master->MoveCube(masterLocation);
	interpValue = Movement->GetInterpValue();

	// debug

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT(" rotation: %f "), userRotation.Yaw));
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT(" location X: %f "), userLocation.X));
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT(" location Y: %f "), userLocation.Y));


}

void AOrchestrator::SpawnDefaultClasses()
{
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	Master = GetWorld()->SpawnActor<AMaster>(MasterClass[0], SpawnInfo);

	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	Beats = GetWorld()->SpawnActor<ABeats>(BeatsClass[0], SpawnInfo);

	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	Movement = GetWorld()->SpawnActor<AMovement>(MovementClass[0], SpawnInfo);

	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	Music = GetWorld()->SpawnActor<AMusic>(MusicClass[0], SpawnInfo);

	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	Environment = GetWorld()->SpawnActor<AEnvironment>(EnvironmentClass[0], SpawnInfo);

	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AggroCurve = GetWorld()->SpawnActor<ACurves>(CurvesClass[0], SpawnInfo);

	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	PointCurve = GetWorld()->SpawnActor<ACurves>(CurvesClass[0], SpawnInfo);

	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	Spectrum = GetWorld()->SpawnActor<ASpectrum>(SpectrumClass[0], SpawnInfo);

	userClass = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

}

void AOrchestrator::AggroUpdate()
{

	DrawDebugSphere(GetWorld(), masterLocation, 450, 32, FColor(255, 0, 0));
	DrawDebugSphere(GetWorld(), masterLocation, 100, 32, FColor(160, 160, 0));

	userRadiusToCube = masterLocation - userLocation;
	userRotation = UKismetMathLibrary::FindLookAtRotation(masterLocation, userLocation);
	userRotation.Yaw += 180.f;

	currentAggro = AggroCurve->InverseLerp(450, 0, (sqrt((pow(userRadiusToCube.X, 2)) + (pow(userRadiusToCube.Y, 2)))));
	currentAggro = FMath::Clamp(currentAggro, 0.f, 1.f);

	// add up to arbitrary amount for avg
	if (aggroCount < 1000)
	{
		aggroCount++;
	}

	// in range, add points / aggro, reset decay = 0
	if (currentAggro > 0) {
		points += currentAggro;
		AggroCurve->SetCurveStart(0.f);
		decay = 0;
		avgAggro = avgAggro *  (aggroCount - 1) / aggroCount + currentAggro / aggroCount;
	}

	// out of range, decay until 0, reset avgaggro
	else if (currentAggro == 0) { 
		avgAggro = avgAggro *  (aggroCount - 1) / aggroCount + 0 / aggroCount;
		decay = AggroCurve->InterpAlongCurve(decayRate, timeDelta, 0);
		points -= decay;

	}


	points = FMath::Clamp(points, 0.f, maxPoints);


	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT(" currentAggro: %f "), currentAggro));
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT(" avgAggro: %f "), avgAggro));
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT(" points: %f "), pointsNormalized));

}

void AOrchestrator::BeatCalculator(float deltaTime)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT(" current section -- %f"), currentSection));
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT(" current beat -- %f"), currentBeat[0]));
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT(" previous beat -- %f"), previousBeat[0]));
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT(" beat delay -- %f"), beatDelay));

	elapsedTime += deltaTime;

	currentBeat[0] = (elapsedTime * (bpm / 60)) - FMath::Fmod(elapsedTime * (bpm / 60), 1);
	currentBeat[1] = (elapsedTime * (bpm / 30)) - FMath::Fmod(elapsedTime * (bpm / 30), 1);
	currentBeat[2] = (elapsedTime * (bpm / 15)) - FMath::Fmod(elapsedTime * (bpm / 15), 1);
	currentBeat[3] = (elapsedTime * (bpm / 7.5)) - FMath::Fmod(elapsedTime * (bpm / 7.5), 1);

	// -- Beat Triggers

	// -- Time Triggers

}


void AOrchestrator::SectionController()
{
	currentSection = Spectrum->UserProgress(points, maxPoints);
	testSwitch = 1;

	switch (testSwitch) {
		
	case 0:

		directionXYZ = Movement->Movement_0_LinearPulse(userRotation.Yaw); 

		if (currentBeat[0] > previousBeat[0]) {

			if (beatDelay < 3) {
				beatDelay++;
			}
			else {
				beatDelay = 0;
				Section_Movement(currentSection);
				Section_Music(currentSection);
			}
			previousBeat[0] += 1.f;
		}
		
		Section_AnimationPlanes(currentSection);
		break;

	case 1:

		// for (currentAggro < i / x )
		// // for (currentBeat i)
		// // // SectionMovement(currentSection);
		// // // Section_Music(currentSection);

		directionXYZ = Movement->Movement_1_Discrete(userRotation.Yaw);
		if (currentBeat[0] > previousBeat[0]) {

			if (beatDelay < 3) {
				beatDelay++;
			}
			else {
				beatDelay = 0;
				Section_Movement(testSwitch);
				Section_Music(testSwitch);
			}
			previousBeat[0] += 1.f;
		}


		break;

	case 2:

		break;

	case 3:

		break;

	case 4:

		break;

	case 5:

		break;

	case 6:

		break;

	case 7:

		break;
	}

	for (int i = 0; i < currentBeat.Num(); i++) {

		if (currentBeat[i] > previousBeat[i]) {

			// -- TRIGGER -- //

			previousBeat[i] += 1.f;
		}
	}
}

// trigger sent from SectionController() -> Section_0X
// updates EACH beat IF given to it (whole / half / quarter / eighth) 
void AOrchestrator::Section_Movement(int currentSec)
{

	switch (testSwitch)
	{
	case 0:

		if (directionXYZ == 0)
		{
			masterForwardVector.Yaw = 90.f;
		}
		else if (directionXYZ == 1)
		{
			masterForwardVector.Yaw = 0.f;
		}

		if (directionXYZ == 0)
		{
			masterForwardVector.Yaw = 0.f;
		}
		else if (directionXYZ == 1)
		{
			masterForwardVector.Yaw = 90.f;
		}

		SpawnAnimPlane(masterForwardVector, 0, 0, 0, 0, 2);
		AnimationPlane->ScaleSquare(10.f, 80.f, 1.f);
		AnimationPlane->StrokeSquare(30.f, 1.f, 1.f);
		Movement->Movement_0_NewLocation();

		decayingRepeater = 0;

		break;

	case 1:
		Movement->Movement_1_NewLocation(userRotation.Yaw);
		break;

	}

}

void AOrchestrator::Section_Music(int currentSec)
{
	switch (testSwitch)
	{
	case 0:

		note_1_value = PointCurve->NoteProbability(1);
		Music->UpdateTrigger(note_1_value);
		break;

	case 1:

		note_1_value = PointCurve->NoteProbability(1);
		Music->UpdateTrigger(note_1_value);
		break;

	}

}


void AOrchestrator::Section_AnimationPlanes(int currentSec)
{
	switch (testSwitch)
	{
	case 0:
		if (interpValue > .1 * decayingRepeater && decayingRepeater < 4) {

			SpawnAnimPlane(masterForwardVector, 0, 0, 0, 0, 1.5);
			AnimationPlane->ScaleSquare(10.f, 40.f, 1.f);
			AnimationPlane->StrokeSquare(30.f / decayingRepeater, 1.f / decayingRepeater, 1.f);

			decayingRepeater++;
		}
		break;

	case 1:
		if (interpValue > .1 * decayingRepeater && decayingRepeater < 4) {

			SpawnAnimPlane(masterForwardVector, 0, 0, 0, 0, 1.5);
			AnimationPlane->ScaleSquare(10.f, 40.f, 1.f);
			AnimationPlane->StrokeSquare(30.f / decayingRepeater, 1.f / decayingRepeater, 1.f);

			decayingRepeater++;
		}
		break;

	}
}


void AOrchestrator::SpawnAnimPlane(FRotator fVec, float fSpeed, int animType, int animCurve, float animSpeed, float lifeTime)
{
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AnimationPlane = GetWorld()->SpawnActor<AAnimationsPlanar>(AnimationsPlanarClass[0], masterLocation, fVec, SpawnInfo);

	AnimationPlane->AnimationPicker(fSpeed, animType, animCurve, animSpeed, lifeTime);
}