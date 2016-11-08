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
	Radii();
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

void AManagerTest_002_Interaction::Radii()
{
	cubeLocation = baseCubeClass->GetCurrentLoc();
//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, cubeLocation.ToString());

	userLocation = userClass->GetActorLocation();
//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, userLocation.ToString());

	userRadius = userLocation - cubeLocation;
//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, userRadius.ToString());

	DrawDebugSphere(
		GetWorld(),
		cubeLocation,
		450,
		32,
		FColor(255, 0, 0));

	DrawDebugSphere(
		GetWorld(),
		cubeLocation,
		100,
		32,
		FColor(160, 160, 0));


	preNormalizedAggro = sqrt((pow(userRadius.X,2)) + (pow(userRadius.Y,2)));

	currentAggro = InverseLerp(450, 0, preNormalizedAggro);

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("%f"), currentAggro));

	userRotation = UKismetMathLibrary::FindLookAtRotation(cubeLocation, userLocation);

	userRotation.Yaw += 180.f;

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, userRotation.ToString());

	if (currentAggro > 0)
	{
		baseCubeClass->AvoidUserBasic(userRotation, cubeLocation, currentAggro);
		//baseCubeClass->MoveTo(cubeLocation);
	}

	//baseCubeClass->MoveTo(cubeLocation);

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
