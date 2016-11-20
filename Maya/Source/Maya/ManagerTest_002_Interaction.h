#pragma once

#include "GameFramework/Actor.h"
#include "ManagerTest_002_Interaction.generated.h"

UCLASS()
class MAYA_API AManagerTest_002_Interaction : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AManagerTest_002_Interaction();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	void SpawnDefaults();

	FActorSpawnParameters SpawnInfo;
	FVector SpawnLoc = FVector(0.f, 0.f, 0.f);
	FRotator SpawnRot;

	UPROPERTY(EditDefaultsOnly, Category = Inventory)
		TArray<TSubclassOf<class ACube> > DefaultInventoryClasses;

	UPROPERTY(EditDefaultsOnly, Category = Inventory)
		TArray<class ACube*> Inventory;

	ACube* baseCubeClass;
	ACharacter* userClass;

	FVector userLocation;
	FVector cubeLocation;
	FVector userRadiusToCube;
	FRotator userRotation;
	TArray<float> aggroHistory;

	int aggroCount;

	float currentAggro;
	float avgAggro;

	void Spectra();

	float InverseLerp(float A, float B, float Value);

};