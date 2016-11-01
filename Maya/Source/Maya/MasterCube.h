#pragma once

#include "Cube.h"
#include "Manager.h"
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

	int DirectionToMove;
	FVector Direction;

	// -- Location Picking -- // 

	FVector CurrentLocation;
	FVector StartLocation;
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

	AManager* manager;

	USphereComponent* RootNull;

	void MoveCube();
	void ManagerConnection();
	void SpawnTrail();

	UPROPERTY(EditDefaultsOnly, Category = "Spawn Trail")
		TSubclassOf<AMasterTrail> SpawnedTrail;

};