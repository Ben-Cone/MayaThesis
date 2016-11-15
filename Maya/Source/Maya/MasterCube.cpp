
#include "Maya.h"
#include "Engine.h"
#include "Kismet/KismetMathLibrary.h"
#include "MasterCube.h"

AMasterCube::AMasterCube(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	RootComponent = RootNull;

	Direction = FVector(1.f, 1.f, 1.f);
	currentAxisDirection = FVector(1.f, 1.f, 1.f);
	nextAxisDirection = FVector(1.f, 1.f, 1.f);

	CurrentLocation = FVector(0.f, 0.f, 0.f);

	MoveDistance = 40.f;
	Boundary = 600.f;

	directionsXYZ.Add(TEXT("X"));
	directionsXYZ.Add(TEXT("Y"));
	directionsXYZ.Add(TEXT("Z"));

}

void AMasterCube::Update(float roughness, float jitter, float curviness, float beatProgression)
{

}

FVector AMasterCube::GetCurrentLoc()
{
	return CurrentLocation;
}

FVector AMasterCube::GetTargetLoc()
{
	return TargetLocation;
}

void AMasterCube::DrawDebugging()
{
	//DrawDebugLine(GWorld, RadiusCenter, CurrentLocation, FColor::Red, false, -1.f, 1, 3.f);
	//DrawDebugLine(GWorld, TargetLocation, StartLocation, FColor::Green, false, -1.f, 1, 8.f);
	//DrawDebugLine(GWorld, TargetLocation, CurrentLocation, FColor::Yellow, false, -1.f, 1, 10.f);
}

void AMasterCube::MoveCube()
{

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, masterLocation.ToString());
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("-- Current Location --"));

	SetActorLocation(CurrentLocation, false);
}

void AMasterCube::SpawnTrail()
{

	FRotator SpawnRot = FRotator(0.f, 0.f, 0.f);

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = Instigator;

	AMasterTrail* SpawnedTrailCube = GetWorld()->SpawnActor<AMasterTrail>(SpawnedTrail, CurrentLocation, SpawnRot, SpawnParams);

}

void AMasterCube::MoveAlongLine()
{

	if (delay == 0)
	{
		if (CurrentLocation.X < 1000 && direction == 1)
		{
			CurrentLocation.X += moveSpeed;
		}
		if (CurrentLocation.X > 0 && direction == -1)
		{
			CurrentLocation.X -= moveSpeed;
		}
		else if (CurrentLocation.X >= 1000 || CurrentLocation.X <= 0)
		{
			direction = direction * -1;
			delay = 300;
		}
	}
	else
	{
		delay--;
	}
}

void AMasterCube::CubeMovementDiscrete(FRotator movementAngle, float currentAggro)
{

	currentAxisDirection[DirectionToMoveXYZ] = nextAxisDirection[DirectionToMoveXYZ];
	currentDirectionXYZ = DirectionToMoveXYZ;

	if (distanceComplete < MoveDistance)
	{
		CurrentLocation[DirectionToMoveXYZ] += (12 * currentAggro * nextAxisDirection[DirectionToMoveXYZ]);
		distanceComplete += (12 * currentAggro);
	}
	else if (distanceComplete >= MoveDistance)
	{
		CurrentLocation = TargetLocation;
		CubeMovementNewLocation(movementAngle, currentAggro);
	}
	
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT(" %f "), distanceComplete));
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT(" %f "), MoveDistance));
}

void AMasterCube::CubeMovementNewLocation(FRotator movementAngle, float currentAggro)
{
	DirectionToMoveXYZ = FMath::RandRange(0, 2);

	distanceComplete = 0.f;

	// new X direction

	if (movementAngle.Yaw > 270 || movementAngle.Yaw < 90)
	{
		nextAxisDirection.X = 1;
	}
	else if (movementAngle.Yaw > 90 && movementAngle.Yaw < 270)
	{
		nextAxisDirection.X = -1;
	}

	// new y direction

	if (movementAngle.Yaw < 180 && movementAngle.Yaw > 0)
	{
		nextAxisDirection.Y = 1;
	}
	else if (movementAngle.Yaw > 180 && movementAngle.Yaw < 360)
	{
		nextAxisDirection.Y = -1;
	}

	// new z direction


	if (CurrentLocation.Z < 160 && CurrentLocation.Z > 0)
	{
		int zChoice = FMath::RandRange(0, 1);

		if (currentDirectionXYZ == DirectionToMoveXYZ)
		{
			switch (zChoice)
			{
			case 0:
				nextAxisDirection.Z = currentAxisDirection.Z;
				break;

			case 1:
				CubeMovementNewLocation(movementAngle, currentAggro);
				break;
			}
		}
		else
		{
			switch (zChoice)
			{
			case 0:
				nextAxisDirection.Z = 1;
				break;

			case 1:
				nextAxisDirection.Z = -1;
				break;
			}
		}
	}
	else if (CurrentLocation.Z >= 160)
	{
		nextAxisDirection.Z = -1;
	}
	else if (CurrentLocation.Z <= 0)
	{
		nextAxisDirection.Z = 1;
	}


	// new location

	TargetLocation[DirectionToMoveXYZ] = CurrentLocation[DirectionToMoveXYZ] + (MoveDistance * nextAxisDirection[DirectionToMoveXYZ]);
}

