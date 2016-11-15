#pragma once

#include "Cube.generated.h"

UCLASS(Abstract, Blueprintable)
class ACube : public AActor
{

	GENERATED_UCLASS_BODY()

	// -- Movement -- //

	virtual void MoveCube();

	virtual FVector GetCurrentLoc();
	virtual FVector GetTargetLoc();

	virtual void DrawDebugging();
	virtual void ManagerConnection();
	virtual void SpawnTrail();

	// -- Testing -- //

	virtual void MoveAlongLine();
	virtual void CubeMovementDiscrete(FRotator movementAngle, float currentAggro);
	virtual void CubeMovementNewLocation(FRotator movementAngle, float currentAggro);
};