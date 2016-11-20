// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Movement.generated.h"

UCLASS()
class MAYA_API AMovement : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovement();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

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

	
};
