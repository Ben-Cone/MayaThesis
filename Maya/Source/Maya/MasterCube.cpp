
#include "Maya.h"
#include "Engine.h"
#include "MasterCube.h"

AMasterCube::AMasterCube(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NumNonBaseVar = 666;

	// -- Movement Initializaiton -- //

	RootComponent = RootNull;

	CurrentLocation = FVector(0.f, 0.f, 0.f);

	Direction = FVector(1.f, 1.f, 1.f);

	CurrentLocation = FVector(0.f, 0.f, 0.f);

	MoveDistance = 100.f;
	Boundary = 600.f;
	InterpSpeed = .02f;
	RotatorOffset = 200.f;
	RadiusCenter = CurrentLocation;
	RadiusCenter.X += RotatorOffset;

}

void AMasterCube::Print()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("overriden"));
}

void AMasterCube::NonBaseFunc()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Derived Function"));
}

int AMasterCube::NumRet()
{

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("-- NumRet executed --"));

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT(" %d "), NumNonBaseVar));
	return NumNonBaseVar;

}

// -- Movement Functions -- //

void AMasterCube::NewTargetLocationDiscrete() // picks new direction / location in X || Y || Z, using boundary
{
	CurrentLocation = TargetLocation;

	DirectionToMove = FMath::RandRange(0, 2);

	StartLocation = CurrentLocation;

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("%d"), DirectionToMove));


	switch (DirectionToMove) {

	case 0:

		if (CurrentLocation.X < Boundary && Direction.X == 1) {
			TargetLocation.X = (CurrentLocation.X + MoveDistance * Direction.X);
		}

		else if (CurrentLocation.X >(Boundary * -1) && Direction.X == -1) {
			TargetLocation.X = (CurrentLocation.X + MoveDistance * Direction.X);
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
			TargetLocation.Y = (CurrentLocation.Y + MoveDistance * Direction.Y);
		}

		else if (CurrentLocation.Y >(Boundary * -1) && Direction.Y == -1) {
			TargetLocation.Y = (CurrentLocation.Y + MoveDistance * Direction.Y);
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
			TargetLocation.Z = (CurrentLocation.Z + MoveDistance * Direction.Z);
		}

		else if (CurrentLocation.Z >(Boundary * -1) && Direction.Z == -1) {
			TargetLocation.Z = (CurrentLocation.Z + MoveDistance * Direction.Z);
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

	StartLocation = CurrentLocation;
	InterpolationAlpha = TargetLocation - StartLocation;

}

void AMasterCube::NewTargetLocationRotate()
{
	CurrentLocation = TargetLocation;

	DirectionToMove = FMath::RandRange(0, 2);

	StartLocation = CurrentLocation;
	InterpolationAlpha = FVector(0.f, 0.f, 0.f);

	switch (DirectionToMove) {

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



	//switch (DirectionToMove) {

	//case 0:

	//	if (CurrentLocation.X < Boundary - RotatorOffset)
	//	{
	//		RadiusCenter = CurrentLocation;
	//		RadiusCenter.X = RotatorOffset;
	//	}


	//	break;

	//case 1:

	//	break;

	//case 2:

	//	break;
	//}

}

FVector AMasterCube::MoveDiscrete()
{
	//DrawDebugPoint(GWorld, CurrentLocation, 5, FColor::Orange, false, 10.f, 0.f);

	switch (DirectionToMove) {

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

	switch (DirectionToMove) {

	case 0:
		InterpolationAlpha.X += (1.57 * InterpSpeed);
		CurrentLocation.X = (((StartLocation.X - RadiusCenter.X) * FMath::Cos(InterpolationAlpha.X)) - ((StartLocation.Y - RadiusCenter.Y) * FMath::Sin(InterpolationAlpha.X))) + RadiusCenter.X;
		CurrentLocation.Y = (((StartLocation.Y - RadiusCenter.Y) * FMath::Cos(InterpolationAlpha.X)) - ((StartLocation.X - RadiusCenter.X) * FMath::Sin(InterpolationAlpha.X))) + RadiusCenter.Y;

		break;

	case 1:

		InterpolationAlpha.Y += (1.57 * InterpSpeed);
		CurrentLocation.Y = (((StartLocation.Y - RadiusCenter.Y) * FMath::Cos(InterpolationAlpha.Y)) - ((StartLocation.X - RadiusCenter.X) * FMath::Sin(InterpolationAlpha.Y))) + RadiusCenter.Y;
		CurrentLocation.X = (((StartLocation.X - RadiusCenter.X) * FMath::Cos(InterpolationAlpha.Y)) - ((StartLocation.Y - RadiusCenter.Y) * FMath::Sin(InterpolationAlpha.Y))) + RadiusCenter.X;

		break;

	case 2:

		InterpolationAlpha.Z += (1.57 * InterpSpeed);
		CurrentLocation.Z = (((StartLocation.Z - RadiusCenter.Z) * FMath::Cos(InterpolationAlpha.Z)) - ((StartLocation.X - RadiusCenter.X) * FMath::Sin(InterpolationAlpha.Z))) + RadiusCenter.Z;
		CurrentLocation.X = (((StartLocation.X - RadiusCenter.X) * FMath::Cos(InterpolationAlpha.Z)) - ((StartLocation.Z - RadiusCenter.Z) * FMath::Sin(InterpolationAlpha.Z))) + RadiusCenter.X;


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

void AMasterCube::ManagerConnection()
{
	for (TActorIterator<AManager> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		manager = *ActorItr;
	}
}

void AMasterCube::MoveCube()
{
	FVector masterLocation = manager->GetLocation();

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, masterLocation.ToString());
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("-- Current Location --"));

	SetActorLocation(masterLocation, false);
}

void AMasterCube::SpawnTrail()
{

	FRotator SpawnRot = FRotator(0.f, 0.f, 0.f);

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = Instigator;

	AMasterTrail* SpawnedTrailCube = GetWorld()->SpawnActor<AMasterTrail>(SpawnedTrail, CurrentLocation, SpawnRot, SpawnParams);

}