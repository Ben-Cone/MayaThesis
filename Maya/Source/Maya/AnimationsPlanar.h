// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "AnimationsPlanar.generated.h"

UCLASS()
class MAYA_API AAnimationsPlanar : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAnimationsPlanar();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere, Category = Spawn)
		USphereComponent* RootNull;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* StaticMesh;

	FVector maskScale;

	UMaterialInstanceDynamic* Dynamic_Circle;
	UMaterialInstanceDynamic* Dynamic_001;
	UMaterialInstanceDynamic* Dynamic_002;
	UMaterialInstanceDynamic* Dynamic_003;
	UMaterialInstanceDynamic* Dynamic_004;
	UMaterialInstanceDynamic* Dynamic_005;
	UMaterialInstanceDynamic* Dynamic_006;
	UMaterialInstanceDynamic* Dynamic_007;
	UMaterialInstanceDynamic* Dynamic_008;
	UMaterialInstanceDynamic* Dynamic_009;


	void RotateShape(float rotationAngle);


	UPROPERTY(EditAnywhere, Category = "Master Spawn")
		TArray<TSubclassOf<class ACurves> > CurvesClass;
	FActorSpawnParameters SpawnInfo;
	float timeDelta;
	void SpawnDefaultClasses();

	float interpValue;
	float rotation;
	float rotator;
	UPROPERTY(EditDefaultsOnly, Category = "Speed")
		float distanceMultiplier;
	UPROPERTY(EditDefaultsOnly, Category = "Speed")
		float lengthSeconds;

	ACurves* Curve;
	
	TArray<ACurves*> CurveArray;

};
