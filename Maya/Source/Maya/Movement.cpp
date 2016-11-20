// Fill out your copyright notice in the Description page of Project Settings.

#include "Maya.h"
#include "Curves.h"
#include "Movement.h"


// Sets default values
AMovement::AMovement()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovement::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnDefaults();

}

// Called every frame
void AMovement::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

FVector AMovement::NewPointBDiscrete(FVector directionXYZ, FVector currentLoc)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("test")));

	pointA = currentLoc;
	pointB = pointA;

	if (directionXYZ.X != 0)
	{
		pointB.X = currentLoc.X + (moveDistance * directionXYZ.X);
	}
	else if (directionXYZ.Y != 0)
	{
		pointB.Y = currentLoc.Y + (moveDistance * directionXYZ.Y);
	}
	else if (directionXYZ.Z != 0)
	{
		pointB.Z = currentLoc.Z + (moveDistance * directionXYZ.Z);
	}

	return pointB;
}

void AMovement::SpawnDefaults()
{
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	Curves = GetWorld()->SpawnActor<ACurves>(CurvesSubClass, SpawnInfo);
}



FVector AMovement::DicretePathing(FVector currentLoc, FVector endLocation)
{
	float movementAmount;
	FVector pointB;
	// if currentLoc.X < pointB.X  movement++
	// if movement > moved, currentLoc =



	if (currentLoc.X < pointB.X)
	{
		
	}

	NewPointBDiscrete(currentLoc);


	return currentLoc;

}