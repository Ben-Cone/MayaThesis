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

	FVector NewPointBDiscrete(FVector directionXYZ, FVector currentLoc);
	FVector DiscretePathing(FVector currentLoc, FVector endLocation);

	FVector pointA;
	FVector pointB;


	UPROPERTY(EditAnywhere)
	float moveDistance;

	UPROPERTY(EditDefaultsOnly, Category = Curves)
	TSubclassOf<class ACurves> CurvesSubClass;
	
	ACurves* Curves;

	void SpawnDefaults();
	FActorSpawnParameters SpawnInfo;

	float returnTest;
	float movementAmount;
	int DirectionToMoveXYZ;
	FVector directionAmplitude;
	
};
