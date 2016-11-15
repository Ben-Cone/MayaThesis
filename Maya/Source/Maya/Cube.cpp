
#include "Maya.h"
#include "Engine.h"
#include "Cube.h"

ACube::ACube(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void ACube::DrawDebugging()
{
	// -- Debugging calls -- //
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

void ACube::CubeMovementDiscrete(FRotator movementAngleDiscrete, float currentAggro)
{
}

void ACube::CubeMovementNewLocation(FRotator movementAngle, float currentAggro)
{
}

void ACube::Update(float roughness, float jitter, float curviness, float beatProgression)
{
}