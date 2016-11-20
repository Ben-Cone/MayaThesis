#pragma once

#include "GameFramework/Actor.h"
#include "MasterTrail.generated.h"

UCLASS()
class AMasterTrail : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMasterTrail();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category = Spawn)
		USphereComponent* RootNull;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* StaticMesh;

	float LifeTime;
	float Death;
	bool IsDynamic = false;

	void ColorOverLife();

	FVector OutColor;

	FVector RandomPanValue = FVector(0.f, FMath::FRandRange(0.f, 1.f), 0.f);

	FVector DensitySwitch = FVector(0.f, 0.f, 0.f);

	int GlitchReset;
	int GlitchCurrent;
	int TimeAdjust;

	float TextureSwitch_01;
	float TextureSwitch_02;
	float TextureSwitch_03;
};