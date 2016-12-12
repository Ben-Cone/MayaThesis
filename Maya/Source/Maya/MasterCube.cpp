#include "Maya.h"
#include "Engine.h"
#include "Kismet/KismetMathLibrary.h"
#include "MasterCube.h"

AMasterCube::AMasterCube(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

	RootComponent = RootNull;

	CurrentLocation = FVector(0.f, 0.f, 0.f);

	Direction = FVector(1.f, 1.f, 1.f);
	currentAxisDirection = FVector(1.f, 1.f, 1.f);
	nextAxisDirection = FVector(1.f, 1.f, 1.f);

	CurrentLocation = FVector(0.f, 0.f, 0.f);

	Boundary = 600.f;
	InterpSpeed = .02f;
	RotatorOffset = 40.f;
	RadiusCenter = CurrentLocation;
	RadiusCenter.X += RotatorOffset;

	directionsXYZ.Add(TEXT("X"));
	directionsXYZ.Add(TEXT("Y"));
	directionsXYZ.Add(TEXT("Z"));

}


// -- Movement Functions -- //

void AMasterCube::NewTargetLocationDiscrete() // picks new direction / location in X || Y || Z, using boundary
{
	CurrentLocation = TargetLocation;

	DirectionToMoveXYZ = FMath::RandRange(0, 1);

	//StartLocation = CurrentLocation;

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("%d"), DirectionToMove));


	switch (DirectionToMoveXYZ) {

	case 0:

		if (CurrentLocation.X < Boundary && Direction.X == 1) {
			TargetLocation.X = (CurrentLocation.X + DiscreteMoveDistance * Direction.X);
		}

		else if (CurrentLocation.X >(Boundary * -1) && Direction.X == -1) {
			TargetLocation.X = (CurrentLocation.X + DiscreteMoveDistance * Direction.X);
		}

		else if (CurrentLocation.X == Boundary) {
			Direction.X = -1;
		}

		else if (CurrentLocation.X == (Boundary * -1)) {
			Direction.X = 1;
		}

		break;

	case 1:

		if (CurrentLocation.Y < Boundary && Direction.Y == 1) {
			TargetLocation.Y = (CurrentLocation.Y + DiscreteMoveDistance * Direction.Y);
		}

		else if (CurrentLocation.Y >(Boundary * -1) && Direction.Y == -1) {
			TargetLocation.Y = (CurrentLocation.Y + DiscreteMoveDistance * Direction.Y);
		}

		else if (CurrentLocation.Y == Boundary) {
			Direction.Y = -1;
		}

		else if (CurrentLocation.Y == (Boundary * -1)) {
			Direction.Y = 1;
		}


		break;

	case 2:

		if (CurrentLocation.Z < Boundary && Direction.Z == 1) {
			TargetLocation.Z = (CurrentLocation.Z + DiscreteMoveDistance * Direction.Z);
		}

		else if (CurrentLocation.Z >(Boundary * -1) && Direction.Z == -1) {
			TargetLocation.Z = (CurrentLocation.Z + DiscreteMoveDistance * Direction.Z);
		}

		else if (CurrentLocation.Z == Boundary) {
			Direction.Z = -1;
		}

		else if (CurrentLocation.Z <= 0) {
			Direction.Z = 1;
		}

		break;
	}

}

void AMasterCube::NewTargetLocationLinear()
{
	CurrentLocation = TargetLocation;

	TargetLocation.X = FMath::RandRange(Boundary * -1, Boundary);
	TargetLocation.Y = FMath::RandRange(Boundary * -1, Boundary);
	TargetLocation.Z = FMath::RandRange(Boundary * -1, Boundary);

	//StartLocation = CurrentLocation;
	//InterpolationAlpha = TargetLocation - StartLocation;

}

void AMasterCube::NewTargetLocationRotate()
{
	CurrentLocation = TargetLocation;

	DirectionToMoveXYZ = FMath::RandRange(0, 2);

	//StartLocation = CurrentLocation;
	InterpolationAlpha = FVector(0.f, 0.f, 0.f);

	switch (DirectionToMoveXYZ) {

	case 0:

		if (CurrentLocation.X < Boundary - RotatorOffset && Direction.X == 1)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("-- X 001 -------------------"));
			RadiusCenter = CurrentLocation;
			RadiusCenter.X += RotatorOffset;
			TargetLocation.Y = RadiusCenter.Y + RotatorOffset;
		}
		else if (CurrentLocation.X > Boundary - RotatorOffset && Direction.X == 1)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("-- X 002 -------------------"));
			RadiusCenter = CurrentLocation;
			RadiusCenter.X += RotatorOffset * -1;
			Direction.X = -1;
			TargetLocation.Y = RadiusCenter.Y - RotatorOffset;
		}
		else if (CurrentLocation.X > (Boundary * -1) + RotatorOffset && Direction.X == -1)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("-- X 003 -------------------"));
			RadiusCenter = CurrentLocation;
			RadiusCenter.X += RotatorOffset * -1;
			TargetLocation.Y = RadiusCenter.Y - RotatorOffset;
		}
		else if (CurrentLocation.X < (Boundary * -1) + RotatorOffset && Direction.X == -1)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("-- X 004 -------------------"));
			RadiusCenter = CurrentLocation;
			RadiusCenter.X += RotatorOffset;
			Direction.X = 1;
			TargetLocation.Y = RadiusCenter.Y + RotatorOffset;
		}

		TargetLocation.X = RadiusCenter.X;


		break;

	case 1:

		if (CurrentLocation.Y < Boundary - RotatorOffset && Direction.Y == 1)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("-- Y 001 -------------------"));
			RadiusCenter = CurrentLocation;
			RadiusCenter.Y += RotatorOffset;
			TargetLocation.X = RadiusCenter.X + RotatorOffset;
		}
		else if (CurrentLocation.Y > Boundary - RotatorOffset && Direction.Y == 1)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("-- Y 002 -------------------"));
			RadiusCenter = CurrentLocation;
			RadiusCenter.Y += RotatorOffset * -1;
			Direction.Y = -1;
			TargetLocation.X = RadiusCenter.X - RotatorOffset;
		}
		else if (CurrentLocation.Y > (Boundary * -1) + RotatorOffset && Direction.Y == -1)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("-- Y 003 -------------------"));
			RadiusCenter = CurrentLocation;
			RadiusCenter.Y += RotatorOffset * -1;
			TargetLocation.X = RadiusCenter.X - RotatorOffset;
		}
		else if (CurrentLocation.Y < (Boundary * -1) + RotatorOffset && Direction.Y == -1)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("-- Y 004 -------------------"));
			RadiusCenter = CurrentLocation;
			RadiusCenter.Y += RotatorOffset;
			Direction.Y = 1;
			TargetLocation.X = RadiusCenter.X + RotatorOffset;
		}

		TargetLocation.Y = RadiusCenter.Y;


		break;

	case 2:

		if (CurrentLocation.Z < Boundary - RotatorOffset && Direction.Z == 1)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("-- Z 001 -------------------"));
			RadiusCenter = CurrentLocation;
			RadiusCenter.Z += RotatorOffset;
			TargetLocation.X = RadiusCenter.X + RotatorOffset;
		}
		else if (CurrentLocation.Z > Boundary - RotatorOffset && Direction.Z == 1)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("-- Z 002 -------------------"));
			RadiusCenter = CurrentLocation;
			RadiusCenter.Z += RotatorOffset * -1;
			Direction.Z = -1;
			TargetLocation.X = RadiusCenter.X - RotatorOffset;
		}
		else if (CurrentLocation.Z > (Boundary * -1) + RotatorOffset && Direction.Z == -1)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("-- Z 003 -------------------"));
			RadiusCenter = CurrentLocation;
			RadiusCenter.Z += RotatorOffset * -1;
			TargetLocation.X = RadiusCenter.X - RotatorOffset;
		}
		else if (CurrentLocation.Z < (Boundary * -1) + RotatorOffset && Direction.Z == -1)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("-- Z 004 -------------------"));
			RadiusCenter = CurrentLocation;
			RadiusCenter.Z += RotatorOffset;
			Direction.Z = 1;
			TargetLocation.X = RadiusCenter.X + RotatorOffset;
		}

		TargetLocation.Z = RadiusCenter.Z;

		break;

	}

}

FVector AMasterCube::MoveDiscrete()
{
	//DrawDebugPoint(GWorld, CurrentLocation, 5, FColor::Orange, false, 10.f, 0.f);

	switch (DirectionToMoveXYZ) {

	case 0:

		CurrentLocation.X += (10 * Direction.X);

		break;

	case 1:

		CurrentLocation.Y += (10 * Direction.Y);

		break;

	case 2:

		CurrentLocation.Z += (10 * Direction.Z);

		break;
	}

	return CurrentLocation;
}

FVector AMasterCube::MoveLinear()
{
	//DrawDebugPoint(GWorld, CurrentLocation, 5, FColor::Blue, false, 10.f, 0.f);

	CurrentLocation.X += InterpolationAlpha.X * InterpSpeed;
	CurrentLocation.Y += InterpolationAlpha.Y * InterpSpeed;
	CurrentLocation.Z += InterpolationAlpha.Z * InterpSpeed;

	return CurrentLocation;

}

FVector AMasterCube::MoveRotate()
{

	switch (DirectionToMoveXYZ) {

	case 0:
		InterpolationAlpha.X += (1.57 * InterpSpeed);
		//CurrentLocation.X = (((StartLocation.X - RadiusCenter.X) * FMath::Cos(InterpolationAlpha.X)) - ((StartLocation.Y - RadiusCenter.Y) * FMath::Sin(InterpolationAlpha.X))) + RadiusCenter.X;
		//CurrentLocation.Y = (((StartLocation.Y - RadiusCenter.Y) * FMath::Cos(InterpolationAlpha.X)) - ((StartLocation.X - RadiusCenter.X) * FMath::Sin(InterpolationAlpha.X))) + RadiusCenter.Y;

		break;

	case 1:

		InterpolationAlpha.Y += (1.57 * InterpSpeed);
		//CurrentLocation.Y = (((StartLocation.Y - RadiusCenter.Y) * FMath::Cos(InterpolationAlpha.Y)) - ((StartLocation.X - RadiusCenter.X) * FMath::Sin(InterpolationAlpha.Y))) + RadiusCenter.Y;
		//CurrentLocation.X = (((StartLocation.X - RadiusCenter.X) * FMath::Cos(InterpolationAlpha.Y)) - ((StartLocation.Y - RadiusCenter.Y) * FMath::Sin(InterpolationAlpha.Y))) + RadiusCenter.X;

		break;

	case 2:

		InterpolationAlpha.Z += (1.57 * InterpSpeed);
		//CurrentLocation.Z = (((StartLocation.Z - RadiusCenter.Z) * FMath::Cos(InterpolationAlpha.Z)) - ((StartLocation.X - RadiusCenter.X) * FMath::Sin(InterpolationAlpha.Z))) + RadiusCenter.Z;
		//CurrentLocation.X = (((StartLocation.X - RadiusCenter.X) * FMath::Cos(InterpolationAlpha.Z)) - ((StartLocation.Z - RadiusCenter.Z) * FMath::Sin(InterpolationAlpha.Z))) + RadiusCenter.X;


		break;

	}

	return CurrentLocation;
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
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, CurrentLocation.ToString());
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT(" direction: %d "), direction));


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

void AMasterCube::AvoidUserBasic(FRotator movementAngle, FVector currentLocation, float amplitude)
{
	CurrentLocation = (UKismetMathLibrary::GetForwardVector(movementAngle) * (amplitude * avoidanceMultiplier)) + currentLocation;
	MoveCube();
}

void AMasterCube::MoveTo(FVector inputCurrentLocation)
{
	CurrentLocation = inputCurrentLocation;
}

void AMasterCube::AvoidanceDiscrete(FRotator movementAngleDiscrete, float currentAggro)
{

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, CurrentLocation.ToString());
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TargetLocation.ToString());

	if (Direction.X == 1 || Direction.Y == 1 || Direction.Z == 1)
	{

		switch (DirectionToMoveXYZ) {

		case 0:

			if (FMath::Abs(TargetLocation.X) - FMath::Abs(CurrentLocation.X) <= 0)
			{
				AvoidanceNewLocation(movementAngleDiscrete, currentAggro);
			}

			break;

		case 1:

			if (FMath::Abs(TargetLocation.Y) - FMath::Abs(CurrentLocation.Y) <= 0)
			{
				AvoidanceNewLocation(movementAngleDiscrete, currentAggro);
			}

			break;

		case 2:

			if (FMath::Abs(TargetLocation.Z) - FMath::Abs(CurrentLocation.Z) <= 0)
			{
				AvoidanceNewLocation(movementAngleDiscrete, currentAggro);
			}

			break;

		}
	}
	else if (Direction.X == -1 || Direction.Y == -1 || Direction.Z == -1)
	{

		switch (DirectionToMoveXYZ) {

		case 0:

			if (FMath::Abs(TargetLocation.X) - FMath::Abs(CurrentLocation.X) <= 0)
			{
				AvoidanceNewLocation(movementAngleDiscrete, currentAggro);
			}

			break;

		case 1:

			if (FMath::Abs(TargetLocation.Y) - FMath::Abs(CurrentLocation.Y) <= 0)
			{
				AvoidanceNewLocation(movementAngleDiscrete, currentAggro);
			}

			break;

		case 2:

			if (FMath::Abs(TargetLocation.Z) - FMath::Abs(CurrentLocation.Z) <= 0)
			{
				AvoidanceNewLocation(movementAngleDiscrete, currentAggro);
			}

			break;

		}
	}


	//if (FVector::Dist(TargetLocation, CurrentLocation) < 5.f)
	//{
	//	AvoidanceNewLocation(movementAngleDiscrete, currentAggro);
	//}


	switch (DirectionToMoveXYZ) {

	case 0:

		CurrentLocation.X += (12 * currentAggro * Direction.X);

		break;

	case 1:

		CurrentLocation.Y += (12 * currentAggro * Direction.Y);

		break;

	case 2:

		CurrentLocation.Z += (12 * currentAggro * Direction.Z);

		break;
	}

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT(" %d "), Direction.X));
}

void AMasterCube::AvoidanceNewLocation(FRotator movementAngleDiscrete, float currentAggro)
{
	DirectionToMoveXYZ = FMath::RandRange(0, 2);

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT(" %d "), DirectionToMove));

	//StartLocation = CurrentLocation;

	if (movementAngleDiscrete.Yaw < 180 && movementAngleDiscrete.Yaw > 0)
	{
		Direction.Y = 1;
	}
	else if (movementAngleDiscrete.Yaw > 180 && movementAngleDiscrete.Yaw < 360)
	{
		Direction.Y = -1;
	}

	if (movementAngleDiscrete.Yaw > 270 || movementAngleDiscrete.Yaw < 90)
	{
		Direction.X = 1;
	}
	else if (movementAngleDiscrete.Yaw > 90 && movementAngleDiscrete.Yaw < 270)
	{
		Direction.X = -1;
	}

	if (CurrentLocation.Z < 140 && CurrentLocation.Z > 10)
	{
		int32 randDirection = FMath::RandRange(0, 1);

		if (randDirection == 0)
		{
			Direction.Z = -1;
		}
		else if (randDirection == 1)
		{
			Direction.Z = 1;
		}

	}
	else if (CurrentLocation.Z > 140)
	{
		Direction.Z = -1;
	}
	else if (CurrentLocation.Z < 10)
	{
		Direction.Z = 1;
	}

	//

	switch (DirectionToMoveXYZ) {

	case 0:
		if (DirectionToMoveXYZ == previousXYZ && previousDirection.X == Direction.X)
		{
			TargetLocation.X = (CurrentLocation.X + DiscreteMoveDistance * Direction.X);
			previousDirection.X = -1;
			//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT(" 001")));
		}
		else if (DirectionToMoveXYZ == previousXYZ && previousDirection.X != Direction.X)
		{
			TargetLocation.X = (CurrentLocation.X + DiscreteMoveDistance * (Direction.X * -1));
			previousDirection.X = Direction.X * -1;
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT(" 002")));
		}
		else if (DirectionToMoveXYZ != previousXYZ)
		{
			if (Direction.X == -1) {
				TargetLocation.X = (CurrentLocation.X + DiscreteMoveDistance * Direction.X);
				previousDirection.X = -1;
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT(" 003")));
			}

			else if (Direction.X == 1) {
				TargetLocation.X = (CurrentLocation.X + DiscreteMoveDistance * Direction.X);
				previousDirection.X = 1;
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT(" 004")));
			}
		}

		previousXYZ = 0;

		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT(" case 0")));

		break;

	case 1:

		if (DirectionToMoveXYZ == previousXYZ && previousDirection.Y == Direction.Y)
		{
			TargetLocation.Y = (CurrentLocation.Y + DiscreteMoveDistance * Direction.Y);
			previousDirection.Y = -1;
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT(" 001")));
		}
		else if (DirectionToMoveXYZ == previousXYZ && previousDirection.Y != Direction.Y)
		{
			TargetLocation.Y = (CurrentLocation.Y + DiscreteMoveDistance * (Direction.Y * -1));
			previousDirection.Y = Direction.Y * -1;
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT(" 002")));
		}
		else if (DirectionToMoveXYZ != previousXYZ)
		{
			if (Direction.Y == -1) {
				TargetLocation.Y = (CurrentLocation.Y + DiscreteMoveDistance * Direction.Y);
				previousDirection.Y = -1;
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT(" 003")));
			}

			else if (Direction.Y == 1) {
				TargetLocation.Y = (CurrentLocation.Y + DiscreteMoveDistance * Direction.Y);
				previousDirection.Y = 1;
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT(" 004")));
			}
		}

		previousXYZ = 1;

		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT(" case 1")));

		break;

	case 2:

		if (DirectionToMoveXYZ == previousXYZ && previousDirection.Z == Direction.Z)
		{
			TargetLocation.Z = (CurrentLocation.Z + DiscreteMoveDistance * Direction.Z);
			previousDirection.Z = -1;
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT(" 001")));
		}
		else if (DirectionToMoveXYZ == previousXYZ && previousDirection.Z != Direction.Z)
		{
			TargetLocation.Z = (CurrentLocation.Z + DiscreteMoveDistance * (Direction.Z * -1));
			previousDirection.Z = Direction.Z * -1;
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT(" 002")));
		}
		else if (DirectionToMoveXYZ != previousXYZ)
		{
			if (Direction.Z == -1) {
				TargetLocation.Z = (CurrentLocation.Z + DiscreteMoveDistance * Direction.Z);
				previousDirection.Z = -1;
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT(" 003")));
			}

			else if (Direction.Z == 1) {
				TargetLocation.Z = (CurrentLocation.Z + DiscreteMoveDistance * Direction.Z);
				previousDirection.Z = 1;
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT(" 004")));
			}
		}

		previousXYZ = 2;
		break;
	}


}


// -- used -- //


void AMasterCube::CubeMovementLinear(FRotator movementAngle, float currentAggro)
{

	currentAxisDirection[DirectionToMoveXYZ] = nextAxisDirection[DirectionToMoveXYZ];
	currentDirectionXYZ = DirectionToMoveXYZ;



	if (distanceComplete < distanceMultiplier)
	{
		CurrentLocation[DirectionToMoveXYZ] += (12 * currentAggro * nextAxisDirection[DirectionToMoveXYZ]);
		distanceComplete += (12 * currentAggro);
	}
	else if (distanceComplete >= distanceMultiplier)
	{
		CurrentLocation = TargetLocation;
		CubeMovementNewLocation(movementAngle, currentAggro);
	}

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT(" %f "), distanceComplete));
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT(" %f "), MoveDistance));
}


void AMasterCube::CubeMovementNewLocation(FRotator movementAngle, float currentAggro)
{
	DirectionToMoveXYZ = FMath::RandRange(0, 1);

	distanceMultiplier = FMath::FloorToInt(currentAggro * 500);
	distanceComplete = 0.f;

	switch (DirectionToMoveXYZ) {

	case 0:

		// new X direction

		if (movementAngle.Yaw >= 315 || movementAngle.Yaw < 45)
		{
			nextAxisDirection.X = 1;
		}
		else if (movementAngle.Yaw >= 135 && movementAngle.Yaw < 225)
		{
			nextAxisDirection.X = -1;
		}

		break;

	case 1:

		// new y direction

		if (movementAngle.Yaw < 135 && movementAngle.Yaw >= 45)
		{
			nextAxisDirection.Y = 1;
		}
		else if (movementAngle.Yaw >= 225 && movementAngle.Yaw < 315)
		{
			nextAxisDirection.Y = -1;
		}

		break;
	}

	TargetLocation[DirectionToMoveXYZ] = CurrentLocation[DirectionToMoveXYZ] + (distanceMultiplier * nextAxisDirection[DirectionToMoveXYZ]);
}

void AMasterCube::Movement_A_Linear(FRotator movementAngle, float currentAggro)
{

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("section A ")));

	//CubeMovementSinWave(movementAngle, currentAggro);

	if (distanceComplete < distanceMultiplier)
	{
		CurrentLocation[DirectionToMoveXYZ] += (12 * currentAggro * nextAxisDirection[DirectionToMoveXYZ]);
		distanceComplete += (12 * currentAggro);
	}
	else if (distanceComplete >= distanceMultiplier)
	{
		CurrentLocation = TargetLocation;
		CubeMovementNewLocation(movementAngle, currentAggro);
	}

}








void AMasterCube::CubeMovementDiscrete(FRotator movementAngle, float currentAggro) 
{
	DirectionToMoveXYZ = FMath::RandRange(0, 2);
	distanceComplete = 0.f;


	switch (DirectionToMoveXYZ) {

	case 0:

		// new X direction

		if (movementAngle.Yaw >= 315 || movementAngle.Yaw < 45)
		{
			nextAxisDirection.X = 1;
		}
		else if (movementAngle.Yaw >= 135 && movementAngle.Yaw < 225)
		{
			nextAxisDirection.X = -1;
		}

		break;

	case 1:

		// new y direction

		if (movementAngle.Yaw < 135 && movementAngle.Yaw >= 45)
		{
			nextAxisDirection.Y = 1;
		}
		else if (movementAngle.Yaw >= 225 && movementAngle.Yaw < 315)
		{
			nextAxisDirection.Y = -1;
		}

		break;

	case 2:

		// new z direction

		if (CurrentLocation.Z >= 160)
		{
			nextAxisDirection.Z = -1;
		}
		else if (CurrentLocation.Z <= 0)
		{
			nextAxisDirection.Z = 1;
		}

	}

	TargetLocation[DirectionToMoveXYZ] = CurrentLocation[DirectionToMoveXYZ] + (DiscreteMoveDistance * nextAxisDirection[DirectionToMoveXYZ]);
}

void AMasterCube::Movement_B_Discrete(FRotator movementAngle, float currentAggro)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("section B ")));

	if (distanceComplete < DiscreteMoveDistance)
	{
		CurrentLocation[DirectionToMoveXYZ] += (12 * currentAggro * nextAxisDirection[DirectionToMoveXYZ]);
		distanceComplete += (12 * currentAggro);
	}
	else if (distanceComplete >= DiscreteMoveDistance)
	{
		CurrentLocation = TargetLocation;
		CubeMovementDiscrete(movementAngle, currentAggro);
	}
}

void AMasterCube::CubeMovementSquareWave(FRotator movementAngle, float currentAggro)
{

	// drive XY direction by DirectionXYZ , controlled by user position
	// more like a 90* turn, 3d, not just linear 2d

	switch (upOverDownOver) {

	case 0: 
		
		if (distanceComplete < DiscreteMoveDistance * 2)
		{
			TargetLocation.Z = CurrentLocation.Z + (DiscreteMoveDistance * 2);
			CurrentLocation.Z += (12 * currentAggro);
			distanceComplete += (12 * currentAggro);
		}
		else if (distanceComplete >= DiscreteMoveDistance * 2)
		{
			upOverDownOver++;
			distanceComplete = 0;
		}
//		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("------------------  0 ")));

		break;

	case 1:

		if (distanceComplete < DiscreteMoveDistance * 2)
		{
			TargetLocation.X = CurrentLocation.X + (DiscreteMoveDistance * 2);
			CurrentLocation.X += (12 * currentAggro);
			distanceComplete += (12 * currentAggro);
		}
		else if (distanceComplete >= DiscreteMoveDistance * 2)
		{
			upOverDownOver++;
			distanceComplete = 0;
		}
//		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("------------------  1 ")));
		break;

	case 2:
		
		if (distanceComplete < DiscreteMoveDistance * 2)
		{
			TargetLocation.Z = CurrentLocation.Z - (DiscreteMoveDistance * 2);
			CurrentLocation.Z -= (12 * currentAggro);
			distanceComplete += (12 * currentAggro);
		}
		else if (distanceComplete >= DiscreteMoveDistance * 2)
		{
			upOverDownOver++;
			distanceComplete = 0;
		}
//		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("------------------  2 ")));
		break; 

	case 3:

		if (distanceComplete < DiscreteMoveDistance * 2)
		{
			TargetLocation.X = CurrentLocation.X + (DiscreteMoveDistance * 2);
			CurrentLocation.X += (12 * currentAggro);
			distanceComplete += (12 * currentAggro);
		}
		else if (distanceComplete >= DiscreteMoveDistance * 2)
		{
			upOverDownOver = 0;
			distanceComplete = 0;
		}
//		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("------------------  3 ")));
		break;
	}
}


void AMasterCube::Movement_C_SquareWave(FRotator movementAngle, float currentAggro)
{
	CubeMovementSquareWave(movementAngle, currentAggro);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("section C ")));
}

void AMasterCube::CubeMovementSinWave(FRotator movementAngle, float currentAggro)
{
	sin = FMath::Sin(InterpolationAlpha.X);
	cos = FMath::Cos(InterpolationAlpha.X);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("sin: %f"), sin));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("cos: %f"), cos));


	switch (upOverDownOver) {

	case 0:

		if (sin >= 0 && sin < 1)
		{
			InterpolationAlpha.X += currentAggro;
			CurrentLocation.Z = (((StartLocation.Z - RadiusCenter.Z) * FMath::Cos(InterpolationAlpha.X)) - ((StartLocation.X - RadiusCenter.X) * FMath::Sin(InterpolationAlpha.X))) + RadiusCenter.Z;
			CurrentLocation.X = (((StartLocation.X - RadiusCenter.X) * FMath::Cos(InterpolationAlpha.X)) - ((StartLocation.Z - RadiusCenter.Z) * FMath::Sin(InterpolationAlpha.X))) + RadiusCenter.X;
		}
		else if (sin < 0 || sin >= 1)
		{
			upOverDownOver++;
		}
		 
		break;

	case 1:

		if (sin >= 0 && sin < 1)
		{
			InterpolationAlpha.X += currentAggro;
			CurrentLocation.Z = (((StartLocation.Z - RadiusCenter.Z) * FMath::Cos(InterpolationAlpha.X)) - ((StartLocation.X - RadiusCenter.X) * FMath::Sin(InterpolationAlpha.X))) + RadiusCenter.Z;
			CurrentLocation.X = (((StartLocation.X - RadiusCenter.X) * FMath::Cos(InterpolationAlpha.X)) - ((StartLocation.Z - RadiusCenter.Z) * FMath::Sin(InterpolationAlpha.X))) + RadiusCenter.X;
		}
		else if (sin < 0 || sin >= 1)
		{
			upOverDownOver++;
		}

		break;

	case 2:

		break;

	case 3:

		break;

	}

	//StartLocation = CurrentLocation;
	//InterpolationAlpha = FVector(0.f, 0.f, 0.f);

}

void AMasterCube::Movement_D_SinWave(FRotator movementAngle, float currentAggro)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("section D ")));
}

void AMasterCube::Movement_E_Spiral3D(FRotator movementAngle, float currentAggro)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("section E ")));
}

void AMasterCube::Movement_F_Swimming(FRotator movementAngle, float currentAggro)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("section F ")));
}

void AMasterCube::Movement_G_Bouncing(FRotator movementAngle, float currentAggro)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("section G ")));
}

void AMasterCube::SpectrumUpdate(FRotator movementAngle, int currentBeatProgress, float currentAggro, float avgAggro)
{

	currentSection = currentBeatProgress;

	switch (currentSection) {

	case 0:
		Movement_A_Linear(movementAngle, currentAggro);
		break;

	case 1:
		Movement_B_Discrete(movementAngle, currentAggro);
		break;

	case 2:
		Movement_C_SquareWave(movementAngle, currentAggro);
		break;

	case 3:
		Movement_D_SinWave(movementAngle, currentAggro);
		break;

	case 4:
		Movement_E_Spiral3D(movementAngle, currentAggro);
		break;

	case 5:
		Movement_F_Swimming(movementAngle, currentAggro);
		break;

	case 6:
		Movement_G_Bouncing(movementAngle, currentAggro);
		break;
	}


}