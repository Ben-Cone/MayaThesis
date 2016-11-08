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
	virtual void ManagerConnection();
	virtual void SpawnTrail();
	virtual void MoveTo(FVector inputCurrentLocation);

	// -- Testing -- //

	virtual void MoveAlongLine();
	virtual void AvoidUserBasic(FRotator movementAngle, FVector currentLocation, float amplitude);

};