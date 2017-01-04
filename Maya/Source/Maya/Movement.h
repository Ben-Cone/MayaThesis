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
	UPROPERTY(EditDefaultsOnly, Category = Variables)
	float boundary;
	UPROPERTY(EditDefaultsOnly, Category = Variables)
	float boundaryBuffer;
	
	float distanceMultiplier;

	FVector startLocation;
	FVector targetLocation;
	FVector currentLocation;

	FVector GetCurrentLocation();

	FRotator userRotation;
	int rotationQuadrant;

	FVector directionDiscrete;
	
	int directionXYZ;
	int posNegDirection;

	// -- Movement -- //
	int Movement_0_LinearPulse(float userRot);
	int Movement_1_Discrete(float userRot);


	void Movement_0_NewLocation();
	void Movement_1_NewLocation(float userRot);

	int GetDirection();

	float GetInterpValue();

	FRotator forwardAngle;

	
	// -- timing -- //

	float lengthSeconds;

	float interpValue;
	float interpolated;
	bool isMoving;
	bool posNegSwitch;

	TArray<FString> xyz;
	FString direction;

};
