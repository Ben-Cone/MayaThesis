#pragma once

#include "Cube.h"
#include "ManagerTest_001_Movement.h"
#include "MasterTrail.h"
#include "MasterCube.generated.h"

UCLASS(Abstract)
class AMasterCube : public ACube
{
	GENERATED_UCLASS_BODY()

	// -- IMPLEMENT CUBE MOVEMENT

	float InterpSpeed;

	int DirectionToMoveXYZ;
	FVector Direction;

	// -- Location Picking -- // 

	FVector CurrentLocation;
	FVector TargetLocation;

	void NewTargetLocationDiscrete() override;
	void NewTargetLocationLinear() override;
	void NewTargetLocationRotate() override;

	// -- Movement -- //

	FVector MoveDiscrete() override;
	FVector MoveLinear() override;
	FVector MoveRotate() override;

	UPROPERTY(EditAnywhere, Category = "Location Change")
		float DiscreteMoveDistance;

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

	TArray<FString> directionsXYZ;
	
	FVector currentAxisDirection;
	FVector nextAxisDirection;
	
	float distanceComplete;
	int currentDirectionXYZ;
	float distanceMultiplier;

	//

	void AvoidUserBasic(FRotator movementAngleDiscrete, FVector currentLocation, float amplitude);



	// -- Spectrum Movement -- //

	int currentSection;
	int upOverDownOver;
	FVector StartLocation;
	float sin;
	float cos;

	void CubeMovementLinear(FRotator movementAngle, float currentAggro);
	void CubeMovementDiscrete(FRotator movementAngle, float currentAggro);
	void CubeMovementNewLocation(FRotator movementAngle, float currentAggro);
	void CubeMovementSquareWave(FRotator movementAngle, float currentAggro);
	void CubeMovementSinWave(FRotator movementAngle, float currentAggro);

	void SpectrumUpdate(FRotator movementAngle, int currentBeatProgress, float currentAggro, float avgAggro);

	void Movement_A_Linear(FRotator movementAngle, float currentAggro);
	void Movement_B_Discrete(FRotator movementAngle, float currentAggro);
	void Movement_C_SquareWave(FRotator movementAngle, float currentAggro);
	void Movement_D_SinWave(FRotator movementAngle, float currentAggro);
	void Movement_E_Spiral3D(FRotator movementAngle, float currentAggro);
	void Movement_F_Swimming(FRotator movementAngle, float currentAggro);
	void Movement_G_Bouncing(FRotator movementAngle, float currentAggro);
};


