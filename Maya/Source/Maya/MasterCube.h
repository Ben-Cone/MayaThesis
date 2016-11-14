#pragma once

#include "Cube.h"
#include "ManagerTest_001_Movement.h"
#include "MasterTrail.h"
#include "MasterCube.generated.h"

UCLASS(Abstract)
class AMasterCube : public ACube
{
	GENERATED_UCLASS_BODY()

		void Print() override;

	// -- Derived class may not use non-base derived functions -- //

	void NonBaseFunc();

	// -- Derived class may override base class variables / functions -- //

	int Num;

	// -- Only Derived functions need to override base class functions -- // 
	// -- Derived class specific variables are allowed -- //

	int NumNonBaseVar;

	// -- Derived class functions must override Base virtual functions -- //

	int NumRet() override;

	// -- IMPLEMENT CUBE MOVEMENT

	float InterpSpeed;

	int DirectionToMoveXYZ;
	FVector Direction;

	// -- Location Picking -- // 

	FVector CurrentLocation;
	float StartLocation;
	FVector TargetLocation;

	UPROPERTY(EditAnywhere, Category = "Location Change")
		float MoveDistance;

	float Boundary;

	FVector GetCurrentLoc() override;
	FVector GetTargetLoc() override;

	void DrawDebugging() override;

	USphereComponent* RootNull;

	void MoveCube();
	void SpawnTrail();

	UPROPERTY(EditDefaultsOnly, Category = "Spawn Trail")
		TSubclassOf<AMasterTrail> SpawnedTrail;

	// -- Testing -- //
	void MoveAlongLine();
	int direction = 1;
	FVector previousDirection;
	int previousXYZ;

	float delay;

	UPROPERTY(EditAnywhere)
	float moveSpeed = 25;

	//

	void CubeMovementDiscrete(FRotator movementAngle, float currentAggro);
	void CubeMovementNewLocation(FRotator movementAngle, float currentAggro);
	TArray<FString> directionsXYZ;
	FVector currentAxisDirection;
	FVector nextAxisDirection;
	float distanceComplete;
	int currentDirectionXYZ;

};






