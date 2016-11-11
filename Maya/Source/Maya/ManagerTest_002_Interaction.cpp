// Fill out your copyright notice in the Description page of Project Settings.

#include "Maya.h"
#include "Engine.h"
#include "Cube.h"
#include "User.h"
#include "Kismet/KismetMathLibrary.h"
#include "ManagerTest_002_Interaction.h"


// Sets default values
AManagerTest_002_Interaction::AManagerTest_002_Interaction()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AManagerTest_002_Interaction::BeginPlay()
{
	Super::BeginPlay();

	SpawnDefaults();

	
}

// Called every frame
void AManagerTest_002_Interaction::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	Spectra();
	baseCubeClass->SpawnTrail();

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


	userClass = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

}

void AManagerTest_002_Interaction::Spectra()
{
	cubeLocation = baseCubeClass->GetCurrentLoc();
	userLocation = userClass->GetActorLocation();
	userRadiusToCube = userLocation - cubeLocation;
	userRotation = UKismetMathLibrary::FindLookAtRotation(cubeLocation, userLocation);
	userRotation.Yaw += 180.f;
	DrawDebugSphere(GetWorld(), cubeLocation, 450, 32, FColor(255, 0, 0));
	DrawDebugSphere(GetWorld(), cubeLocation, 100, 32, FColor(160, 160, 0));



	currentAggro = InverseLerp(450, 0, (sqrt((pow(userRadiusToCube.X, 2)) + (pow(userRadiusToCube.Y, 2)))));

	// currentAggro's stored in array
	// function adds to array, sets avgAggro
	// from there, use current/avgAggro's in other spectra
	//
	// > potentially break down further to (last 10 sec, last 5 sec, last 2 sec)
	// > > speed?  needs to be quick at avoiding user 


	// -- avoid user -- //

	if (currentAggro > 0)
	{
		if (aggroCount < 1000)
		{
			aggroCount++;
		}
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("%d"), aggroCount));

		avgAggro = avgAggro *  (aggroCount - 1) / aggroCount + currentAggro / aggroCount;
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%f"), avgAggro));

		baseCubeClass->AvoidanceDiscrete(userRotation, currentAggro);
		baseCubeClass->MoveCube();
		
		
		//baseCubeClass->AvoidUserBasic(userRotation, cubeLocation, currentAggro);
	}
	else if (currentAggro < 0)
	{
		if (aggroCount < 1000)
		{
			aggroCount++;
		}
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("%d"), aggroCount));

		avgAggro = avgAggro *  (aggroCount - 1) / aggroCount + 0 / aggroCount;
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%f"), avgAggro));

	}



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
