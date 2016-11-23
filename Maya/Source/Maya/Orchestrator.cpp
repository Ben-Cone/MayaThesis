// Fill out your copyright notice in the Description page of Project Settings.

#include "Maya.h"
#include "Engine.h"
#include "Master.h"
#include "Kismet/KismetMathLibrary.h"
#include "Orchestrator.h"


// Sets default values
AOrchestrator::AOrchestrator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AOrchestrator::BeginPlay()
{
	Super::BeginPlay();
	SpawnDefaultClasses();

}

// Called every frame
void AOrchestrator::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	Master->SpawnTrail();
	masterLocation = Master->GetCurrentLoc();
	userLocation = userClass->GetActorLocation();
	Spectra();
}

void AOrchestrator::SpawnDefaultClasses()
{
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	Master = GetWorld()->SpawnActor<AMaster>(MasterClass[0], SpawnInfo);

	userClass = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

}

void AOrchestrator::Spectra()
{


	userRadiusToCube = masterLocation - userLocation;
	userRotation = UKismetMathLibrary::FindLookAtRotation(masterLocation, userLocation);
	DrawDebugSphere(GetWorld(), masterLocation, 450, 32, FColor(255, 0, 0));
	DrawDebugSphere(GetWorld(), masterLocation, 100, 32, FColor(160, 160, 0));

	currentAggro = InverseLerp(450, 0, (sqrt((pow(userRadiusToCube.X, 2)) + (pow(userRadiusToCube.Y, 2)))));
	currentAggro = FMath::Clamp(currentAggro, 0.f, 1.f);

	if (currentAggro > 0)
	{

		if (aggroCount < 1000)
		{
			aggroCount++;
		}

		avgAggro = avgAggro *  (aggroCount - 1) / aggroCount + currentAggro / aggroCount;

	}
	else if (currentAggro < 0)
	{
		if (aggroCount < 1000)
		{
			aggroCount++;
		}

		avgAggro = avgAggro *  (aggroCount - 1) / aggroCount + 0 / aggroCount;

	}


	Master->SpectrumUpdate(userRotation, currentBeatProgress, currentAggro, avgAggro);
	Master->MoveCube();
	//SpectrumMusic(currentAggro, avgAggro);

}


float AOrchestrator::InverseLerp(float A, float B, float Value)
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


void AOrchestrator::SpectrumRoughness(float current, float avg)
{
	roughness = (current * .4f) + (avg * .7f);
	roughness = FMath::Clamp(roughness, 0.f, 1.f);
}

void AOrchestrator::SpectrumJitteriness(float current, float avg)
{
	jitter = (current * .6f) + (avg * .2f);
	jitter = FMath::Clamp(roughness, 0.f, 1.f);
}

void AOrchestrator::SpectrumCurviness(float current, float avg)
{
	curviness = (current * .1f) + (avg * .85f);
	curviness = FMath::Clamp(roughness, 0.f, 1.f);
}


void AOrchestrator::SpectrumMusic(float current, float avg)
{
	if (currentAggro > 0)
	{
		beatProgression += current * .9f;
		beatProgression = FMath::Clamp(beatProgression, 0.f, beatProgressionLimit);

	}


	if (beatProgression >= (beatProgressionLimit / 8) * currentBeatProgress && beatProgression < (beatProgressionLimit / 8) * (currentBeatProgress + 1))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT(" 000 ")));
	}
	else if (beatProgression < beatProgressionLimit / 8)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT(" 001 ")));
	}
	else if (beatProgression >= (beatProgressionLimit / 8) * (currentBeatProgress + 1))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT(" 002 ")));
		currentBeatProgress++;
	}

}