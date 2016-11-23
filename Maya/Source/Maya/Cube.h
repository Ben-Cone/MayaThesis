#pragma once

#include "Cube.generated.h"

UCLASS(Abstract, Blueprintable)
class ACube : public AActor
{

	GENERATED_UCLASS_BODY()

		virtual void Print();

	int Num;

	// -- Base class may have members not used by ALL derived classes -- //

	virtual void Nothing();

	virtual int NumRet();

	// -- Movement -- //

	virtual void NewTargetLocationDiscrete();
	virtual void NewTargetLocationLinear();
	virtual void NewTargetLocationRotate();

	virtual FVector MoveDiscrete();
	virtual FVector MoveLinear();
	virtual FVector MoveRotate();

	virtual void MoveCube();

	virtual FVector GetCurrentLoc();
	virtual FVector GetTargetLoc();

	virtual void DrawDebugging();
	virtual void SpawnTrail();
	virtual void MoveTo(FVector inputCurrentLocation);

	// -- Testing -- //

	virtual void MoveAlongLine();
	virtual void AvoidUserBasic(FRotator movementAngle, FVector currentLocation, float amplitude);
	virtual void AvoidanceDiscrete(FRotator movementAngleDiscrete, float currentAggro);
	virtual void AvoidanceNewLocation(FRotator movementAngleDiscrete, float currentAggro);
	virtual void CubeMovementDiscrete(FRotator movementAngle, float currentAggro);
	virtual void CubeMovementNewLocation(FRotator movementAngle, float currentAggro);
	virtual void CubeMovementSquareWave(FRotator movementAngle, float currentAggro);
	virtual void CubeMovementSinWave(FRotator movementAngle, float currentAggro);

	// -- Movement -- //

	virtual void SpectrumUpdate(FRotator movementAngle, int currentBeatProgress, float currentAggro, float avgAggro);

	virtual void Movement_A_Linear(FRotator movementAngle, float currentAggro);
	virtual void Movement_B_Discrete(FRotator movementAngle, float currentAggro);
	virtual void Movement_C_SquareWave(FRotator movementAngle, float currentAggro);
	virtual void Movement_D_SinWave(FRotator movementAngle, float currentAggro);
	virtual void Movement_E_Spiral3D(FRotator movementAngle, float currentAggro);
	virtual void Movement_F_Swimming(FRotator movementAngle, float currentAggro);
	virtual void Movement_G_Bouncing(FRotator movementAngle, float currentAggro);

};