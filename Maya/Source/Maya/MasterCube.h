#pragma once

#include "Cube.h"
#include "ManagerTest_001_Movement.h"
#include "MasterTrail.h"
#include "MasterCube.generated.h"

UCLASS(Abstract)
class AMasterCube : public ACube
{
	GENERATED_UCLASS_BODY()

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

	void Update(float roughness, float jitter, float curviness, float beatProgression);

	void CubeMovementDiscrete(FRotator movementAngle, float currentAggro);
	void CubeMovementNewLocation(FRotator movementAngle, float currentAggro);
	TArray<FString> directionsXYZ;
	FVector currentAxisDirection;
	FVector nextAxisDirection;
	float distanceComplete;
	int currentDirectionXYZ;

	// new movement

	void SpawnDefaults();
	FActorSpawnParameters SpawnInfo;
	UPROPERTY(EditDefaultsOnly, Category = Inventory)
		TSubclassOf<class AMovement> MovementSubClass;

	AMovement* Movement;

};






