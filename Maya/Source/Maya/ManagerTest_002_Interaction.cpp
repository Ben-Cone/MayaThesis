// Fill out your copyright notice in the Description page of Project Settings.

#include "Maya.h"
#include "Engine.h"
#include "Cube.h"
#include "User.h"
#include "Kismet/KismetMathLibrary.h"
#include "ManagerTest_002_Interaction.h"
#include "Movement.h"


// Sets default values
AManagerTest_002_Interaction::AManagerTest_002_Interaction()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	currentAggro = 0.f;

	currentBeatProgress = 1;

}

// Called when the game starts or when spawned
void AManagerTest_002_Interaction::BeginPlay()
{
	Super::BeginPlay();

	SpawnDefaults();

	//Movement->NewPointBDiscrete();

}

// Called every frame
void AManagerTest_002_Interaction::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	SpectraMaster();
	baseCubeClass->SpawnTrail();

	cubeLocation = baseCubeClass->GetCurrentLoc();
	userLocation = userClass->GetActorLocation();

	baseCubeClass->CubeMovementDiscrete(userRotation, currentAggro);
	baseCubeClass->MoveCube();

}

void AManagerTest_002_Interaction::SpawnDefaults()
{

	int32 NumDefaultClasses = DefaultInventoryClasses.Num();

	for (int32 i = 0; i < NumDefaultClasses; i++)
	{
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		baseCubeClass = GetWorld()->SpawnActor<ACube>(DefaultInventoryClasses[i], SpawnInfo);

		Inventory.AddUnique(baseCubeClass);
	}

	//SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	//Movement = GetWorld()->SpawnActor<AMovement>(MovementSubClass, SpawnInfo);


	userClass = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

}

void AManagerTest_002_Interaction::SpectraMaster()
{

	userRadiusToCube = userLocation - cubeLocation;
	userRotation = UKismetMathLibrary::FindLookAtRotation(cubeLocation, userLocation);
	userRotation.Yaw += 180.f;
	DrawDebugSphere(GetWorld(), cubeLocation, 450, 32, FColor(255, 0, 0));
	DrawDebugSphere(GetWorld(), cubeLocation, 100, 32, FColor(160, 160, 0));



	currentTempAggro = InverseLerp(450, 0, (sqrt((pow(userRadiusToCube.X, 2)) + (pow(userRadiusToCube.Y, 2)))));

	currentAggro = FMath::Clamp(currentTempAggro, 0.f, 1.f);

	if (aggroCount < 1000)
	{
		aggroCount++;
	}
	else if (aggroCount == 1000)
	{
		aggroCount = 0;
		overwriteArray = true;
	}

	if (overwriteArray)
	{
		aggroHistory.RemoveAt(aggroCount - 1);
	}
	aggroHistory.Insert(currentAggro, aggroCount - 1);

	for (int i = 0; i < aggroHistory.Num(); i++)
	{
		aggroTempSum += aggroHistory[i];
	}

	aggroSum = aggroTempSum;

	avgAggro = aggroSum / aggroHistory.Num();

	aggroTempSum = 0;

	// -- spectra -- //

	SpectrumRoughness(currentAggro, avgAggro);
	SpectrumJitteriness(currentAggro, avgAggro);
	SpectrumCurviness(currentAggro, avgAggro);
	SpectrumMusic(currentAggro, avgAggro);

	baseCubeClass->Update(roughness, jitter, curviness, beatProgression);

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("current: %f "), currentAggro));
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("average: %f "), avgAggro));
}


float AManagerTest_002_Interaction::InverseLerp(float A, float B, float Value)
{
	if (FMath::IsNearlyEqual(A, B))
	{
		if (Value < A)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
	else
	{
		return ((Value - A) / (B - A));
	}
}

void AManagerTest_002_Interaction::SpectrumRoughness(float current, float avg)
{
	roughness = (current * .4f) + (avg * .7f);
	roughness = FMath::Clamp(roughness, 0.f, 1.f);
}

void AManagerTest_002_Interaction::SpectrumJitteriness(float current, float avg)
{
	jitter = (current * .6f) + (avg * .2f);
	jitter = FMath::Clamp(jitter, 0.f, 1.f);
}

void AManagerTest_002_Interaction::SpectrumCurviness(float current, float avg)
{
	curviness = (current * .1f) + (avg * .85f);
	curviness = FMath::Clamp(curviness, 0.f, 1.f);
}

void AManagerTest_002_Interaction::SpectrumMusic(float current, float avg)
{
	if (currentAggro > 0)
	{
		beatProgression += current * .9f;
		beatProgression = FMath::Clamp(beatProgression, 0.f, beatProgressionLimit);

	}

	
	if (beatProgression >= (beatProgressionLimit / 8) * currentBeatProgress && beatProgression < (beatProgressionLimit / 8) * (currentBeatProgress + 1))
	{

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT(" %d "), currentBeatProgress));
	}
	else if (beatProgression < beatProgressionLimit / 8)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT(" 001 ")));
	}
	else if (beatProgression >= (beatProgressionLimit / 8) * (currentBeatProgress + 1))
	{
		currentBeatProgress++;
	}


	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("%f"), beatProgression));
}