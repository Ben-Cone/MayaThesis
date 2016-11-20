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

	void NewTargetLocationDiscrete() override;
	void NewTargetLocationLinear() override;
	void NewTargetLocationRotate() override;

	// -- Movement -- //

	FVector MoveDiscrete() override;
	FVector MoveLinear() override;
	FVector MoveRotate() override;

	UPROPERTY(EditAnywhere, Category = "Location Change")
		float MoveDistance;

	float Boundary;

	FVector RadiusCenter;
	float RotatorOffset;

	FVector InterpolationAlpha;

	FVector GetCurrentLoc() override;
	FVector GetTargetLoc() override;

	void DrawDebugging() override;

	AManagerTest_001_Movement* manager;

	USphereComponent* RootNull;

	void MoveCube();
	void ManagerConnection();
	void SpawnTrail();
	void MoveTo(FVector inputCurrentLocation);

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

	UPROPERTY(EditAnywhere)
		float avoidanceMultiplier;

	void AvoidanceDiscrete(FRotator movementAngle, float currentAggro);
	int avoidanceDirection;
	void AvoidanceNewLocation(FRotator movementAngle, float currentAggro);

	//

	void CubeMovementDiscrete(FRotator movementAngle, float currentAggro);
	void CubeMovementNewLocation(FRotator movementAngle, float currentAggro);
	TArray<FString> directionsXYZ;
	FVector currentAxisDirection;
	FVector nextAxisDirection;
	float distanceComplete;
	int currentDirectionXYZ;

	//

	void AvoidUserBasic(FRotator movementAngleDiscrete, FVector currentLocation, float amplitude);
};


