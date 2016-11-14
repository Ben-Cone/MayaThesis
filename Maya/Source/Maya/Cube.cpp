
#include "Maya.h"
#include "Engine.h"
#include "Cube.h"

ACube::ACube(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	Num = 5;
}

void ACube::Print()
{

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::FromInt(Num));

}

void ACube::Nothing()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("nothing"));

}

void ACube::DrawDebugging()
{
	// -- Debugging calls -- //
}

int ACube::NumRet()
{
	return Num;
}

void ACube::NewTargetLocationDiscrete()
{}

void ACube::NewTargetLocationLinear()
{}

void ACube::NewTargetLocationRotate()
{}

FVector ACube::MoveDiscrete()
{
	return FVector(0.f, 0.f, 0.f);
}

FVector ACube::MoveLinear()
{
	return FVector(0.f, 0.f, 0.f);
}

FVector ACube::MoveRotate()
{
	return FVector(0.f, 0.f, 0.f);
}

FVector ACube::GetCurrentLoc()
{
	return FVector(0.f, 0.f, 0.f);
}


FVector ACube::GetTargetLoc()
{
	return FVector(0.f, 0.f, 0.f);
}

void ACube::MoveCube()
{
}

void ACube::ManagerConnection()
{
}

void ACube::SpawnTrail()
{
}

void ACube::MoveAlongLine()
{
}

void ACube::AvoidUserBasic(FRotator movementAngle, FVector currentLocation, float amplitude)
{
}

void ACube::MoveTo(FVector inputCurrentLocation)
{
}

void ACube::AvoidanceDiscrete(FRotator movementAngleDiscrete, float currentAggro)
{
}

void ACube::AvoidanceNewLocation(FRotator movementAngleDiscrete, float currentAggro)
{
}

void ACube::CubeMovementDiscrete(FRotator movementAngleDiscrete, float currentAggro)
{
}

void ACube::CubeMovementNewLocation(FRotator movementAngle, float currentAggro)
{
}

