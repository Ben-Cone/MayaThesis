#include "Maya.h"
#include "Engine.h"
#include "Master.h"
#include "Kismet/KismetMathLibrary.h"
#include "AnimationsPlanar.h"
#include "OrchestratorOld.h"


// Sets default values
AOrchestratorOld::AOrchestratorOld()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AOrchestratorOld::BeginPlay()
{
	Super::BeginPlay();
	//SpawnDefaultClasses();

	//SpawnAnimPlane();

}

// Called every frame
void AOrchestratorOld::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Master->SpawnTrail();
	//masterLocation = Master->GetCurrentLoc();
	//userLocation = userClass->GetActorLocation();

	//AnimationPlaneControl();

	// -- BLOCKED FOR TESTING // Spectra();
}

//void AOrchestratorOld::SpawnDefaultClasses()
//{
//	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
//	Master = GetWorld()->SpawnActor<AMaster>(MasterClass[0], SpawnInfo);
//
//	userClass = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
//
//}
//
//void AOrchestratorOld::Spectra()
//{
//
//
//	userRadiusToCube = masterLocation - userLocation;
//	userRotation = UKismetMathLibrary::FindLookAtRotation(masterLocation, userLocation);
//	//DrawDebugSphere(GetWorld(), masterLocation, 450, 32, FColor(255, 0, 0));
//	//DrawDebugSphere(GetWorld(), masterLocation, 100, 32, FColor(160, 160, 0));
//
//	currentAggro = InverseLerp(450, 0, (sqrt((pow(userRadiusToCube.X, 2)) + (pow(userRadiusToCube.Y, 2)))));
//	currentAggro = FMath::Clamp(currentAggro, 0.f, 1.f);
//
//	if (currentAggro > 0)
//	{
//
//		if (aggroCount < 1000)
//		{
//			aggroCount++;
//		}
//
//		avgAggro = avgAggro *  (aggroCount - 1) / aggroCount + currentAggro / aggroCount;
//
//	}
//	else if (currentAggro < 0)
//	{
//		if (aggroCount < 1000)
//		{
//			aggroCount++;
//		}
//
//		avgAggro = avgAggro *  (aggroCount - 1) / aggroCount + 0 / aggroCount;
//
//	}
//
//
//	Master->SpectrumUpdate(userRotation, currentBeatProgress, currentAggro, avgAggro);
//	Master->MoveCube();
//	SpectrumMusic(currentAggro, avgAggro);
//
//}
//
//
//float AOrchestratorOld::InverseLerp(float A, float B, float Value)
//{
//	if (FMath::IsNearlyEqual(A, B))
//	{
//		if (Value < A)
//		{
//			return 0;
//		}
//		else
//		{
//			return 1;
//		}
//	}
//	else
//	{
//		return ((Value - A) / (B - A));
//	}
//}
//
//
//void AOrchestratorOld::SpectrumRoughness(float current, float avg)
//{
//	roughness = (current * .4f) + (avg * .7f);
//	roughness = FMath::Clamp(roughness, 0.f, 1.f);
//}
//
//void AOrchestratorOld::SpectrumJitteriness(float current, float avg)
//{
//	jitter = (current * .6f) + (avg * .2f);
//	jitter = FMath::Clamp(roughness, 0.f, 1.f);
//}
//
//void AOrchestratorOld::SpectrumCurviness(float current, float avg)
//{
//	curviness = (current * .1f) + (avg * .85f);
//	curviness = FMath::Clamp(roughness, 0.f, 1.f);
//}
//
//void AOrchestratorOld::SpectrumMusic(float current, float avg)
//{
//	if (currentAggro > 0)
//	{
//		beatProgression += current * .9f;
//		beatProgression = FMath::Clamp(beatProgression, 0.f, beatProgressionLimit);
//
//	}
//
//	if (beatProgression >= (beatProgressionLimit / 8) * (currentBeatProgress + 1))
//	{
//		currentBeatProgress++;
//	}
//
//}
//
//void AOrchestratorOld::SpawnAnimPlane(/*FVector fVec, float fSpeed, int animType, int animCurve, float animSpeed, float lifetime*/)
//{
//	SpawnLoc = masterCurrentLoc;
//
//	if (masterDirection == 0)
//	{
//		SpawnRot.Yaw = 0.f;
//	}
//	else if (masterDirection == 1)
//	{
//		SpawnRot.Yaw = 90.f;
//	}
//
//	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
//	AnimationPlane = GetWorld()->SpawnActor<AAnimationsPlanar>(AnimPlane[0], SpawnLoc, SpawnRot, SpawnInfo);
//
//	//AnimationPlane-> ;
//}
//
//void AOrchestratorOld::AnimationPlaneControl()
//{
//	masterCurrentLoc = Master->GetCurrentLoc();
//	masterTargetLoc = Master->GetTargetLoc();
//	masterDirection = Master->GetDirection();
//	masterInterpValue = Master->GetInterpValue();
//
//	if (FMath::Fmod(masterInterpValue, .1f) <= 0.01f)
//	{
//		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT(" interp : %f "), masterInterpValue));
//		SpawnAnimPlane();
//	}
//}
//
//void AOrchestratorOld::SectionProgress()
//{
//
//}