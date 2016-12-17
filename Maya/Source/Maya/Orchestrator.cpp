
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

	Master->SpawnTrail();
	masterLocation = Movement->GetCubeLocation();
	userLocation = userClass->GetActorLocation();

	BeatCalculator(DeltaTime);

	AggroUpdate();

	pointsNormalized = PointCurve->InverseLerp(0, maxPoints, points);

	PointCurve->InterpNotes(pointsNormalized);

	Movement->Movement_A_LinearPulse(userAngleToCube);

	masterCurrentLocation = Movement->GetCubeLocation();

	Master->MoveCube(masterCurrentLocation);

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT(" points: %f "), pointsNormalized));

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
	AnimationPlane = GetWorld()->SpawnActor<AAnimationsPlanar>(AnimationsPlanarClass[0], SpawnLoc, SpawnRot, SpawnInfo);

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

	//DrawDebugSphere(GetWorld(), masterLocation, 450, 32, FColor(255, 0, 0));
	//DrawDebugSphere(GetWorld(), masterLocation, 100, 32, FColor(160, 160, 0));

	userRadiusToCube = masterLocation - userLocation;
	userRotation = UKismetMathLibrary::FindLookAtRotation(masterLocation, userLocation);
	userRotation.Yaw += 180.f;

	currentAggro = AggroCurve->InverseLerp(450, 0, (sqrt((pow(userRadiusToCube.X, 2)) + (pow(userRadiusToCube.Y, 2)))));
	currentAggro = FMath::Clamp(currentAggro, 0.f, 1.f);


	if (currentAggro > 0) {
		points += currentAggro;
		AggroCurve->SetCurveStart(0.f);
		decay = 0;
	}
	else if (currentAggro == 0 && points > 0) { 
		decay = AggroCurve->InterpAlongCurve(decayRate, timeDelta, 0);
		points -= decay;
	}
	points = FMath::Clamp(points, 0.f, maxPoints);

	currentSection = Spectrum->UserProgress(points, maxPoints);

}

void AOrchestrator::BeatCalculator(float deltaTime)
{

	elapsedTime += deltaTime;

	currentBeat[0] = (elapsedTime * (bpm / 60)) - FMath::Fmod(elapsedTime * (bpm / 60), 1);
	currentBeat[1] = (elapsedTime * (bpm / 30)) - FMath::Fmod(elapsedTime * (bpm / 30), 1);
	currentBeat[2] = (elapsedTime * (bpm / 15)) - FMath::Fmod(elapsedTime * (bpm / 15), 1);
	currentBeat[3] = (elapsedTime * (bpm / 7.5)) - FMath::Fmod(elapsedTime * (bpm / 7.5), 1);

	// -- iterate through each beat and trigger on beat

	for (int i = 0; i < currentBeat.Num(); i++) {

		if (currentBeat[0] > previousBeat[0]) {

			// -- TRIGGER -- //
			if (beatDelay < 3){
				beatDelay++;
			}
			else {

				Movement->Movement_0_NewLocation();

				note_1_value = PointCurve->NoteProbability(1);
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT(" note 1 -- %d"), note_1_value));
				Music->UpdateTrigger(note_1_value);
				beatDelay = 0;
			}


			Music->UpdateTrigger(3);


			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT(" note 1 -- %d"), note_1_value));

			previousBeat[0] += 1.f;
		}
	}
}

// points (total)
// currentAggro (delta)
// avgAggro

void AOrchestrator::PointProgress()
{
	// SECTION
	if (points < (maxPoints / 4)) {

		// SUBSECTION

	}

}

void AOrchestrator::NoteArpeggiator()
{

}