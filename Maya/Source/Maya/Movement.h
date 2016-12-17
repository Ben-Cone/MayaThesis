// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Listener.h"
#include "Movement.generated.h"

UCLASS()
class MAYA_API AMovement : public AListener
{
	GENERATED_UCLASS_BODY()
	
public:	

	virtual void BeginPlay() override;
	
	virtual void Tick( float DeltaSeconds ) override;

	void UpdateTrigger(int eventIndex) override;

	float timeDelta;

	// -- defaults -- // 

	void SpawnDefaults();
	FActorSpawnParameters SpawnInfo;

	UPROPERTY(EditDefaultsOnly, Category = Curves)
		TSubclassOf<class ACurves> CurvesSubClass;

	ACurves* Curve;

	// -- variables -- //

	float distanceMultiplier;

	FVector startLocation;
	FVector targetLocation;
	FVector currentLocation;

	FVector GetCubeLocation();

	void Movement_A_LinearPulse(float userRotation);

	FVector directionDiscrete;
	
	int directionXYZ;
	int posNegDirection;

	// -- Movement -- //

	void Movement_0_NewLocation();

	int GetDirection();

	float GetInterpValue();
	
	// -- timing -- //

	float lengthSeconds;

	float interpValue;
	float interpolated;
	bool isMoving;
	bool posNegSwitch;

};
