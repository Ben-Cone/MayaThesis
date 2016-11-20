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

void AMovement::SpawnDefaults()
{
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	Curves = GetWorld()->SpawnActor<ACurves>(CurvesSubClass, SpawnInfo);
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

	// which direction isn't 0, (0, 1, 0)
	// pointB = direction + moveDistance

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

FVector AMovement::DiscretePathing(FVector currentLoc, FVector endLocation)
{

	DirectionToMoveXYZ = FMath::RandRange(0, 2);
	
	directionAmplitude = FVector(0.f, 0.f, 0.f);

	switch (DirectionToMoveXYZ) {

	case 0:

		if (endLocation.X - currentLoc.X > 0)
		{
			directionAmplitude.X = 1.f;
		}
		else if (endLocation.X - currentLoc.X < 0)
		{
			directionAmplitude.X = -1.f;
		}

		if (currentLoc.X + moveDistance > endLocation.X)
		{
			NewPointBDiscrete(directionAmplitude, currentLoc);
		}
		else if (currentLoc.X + moveDistance <= endLocation.X)
		{
			NewPointBDiscrete(directionAmplitude, currentLoc);
		}

		break;

	case 1:

		if (endLocation.Y - currentLoc.Y > 0)
		{
			directionAmplitude.Y = 1.f;
		}
		else if (endLocation.Y - currentLoc.Y < 0)
		{
			directionAmplitude.Y = -1.f;
		}
			break;
	case 2:

		if (endLocation.Z - currentLoc.Z > 0)
		{
			directionAmplitude.Z = 1.f;
		}
		else if (endLocation.Z - currentLoc.Z < 0)
		{
			directionAmplitude.Z = -1.f;
		}

	}

	NewPointBDiscrete(directionAmplitude, currentLoc);


	return currentLoc;

}







