#pragma once

#include "GameFramework/Actor.h"
#include "OrchestratorOld.generated.h"

UCLASS()
class MAYA_API AOrchestratorOld : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AOrchestratorOld();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;


	// -- Spawning -- //

	UPROPERTY(EditAnywhere, Category = "Master Spawn")
		TArray<TSubclassOf<class AMaster> > MasterClass;

	FActorSpawnParameters SpawnInfo;
	FVector SpawnLoc = FVector(0.f, 0.f, 0.f);
	FRotator SpawnRot;

	void SpawnDefaultClasses();
	AMaster* Master;
	ACharacter* userClass;

	// -- User / Aggro -- //

	FVector userLocation;
	FVector masterLocation;
	FVector userRadiusToCube;
	FRotator userRotation;
	TArray<float> aggroHistory;

	int aggroCount;
	void Spectra();

	float InverseLerp(float A, float B, float Value);

	float currentTempAggro;
	float currentAggro;
	float aggroSum;
	float aggroTempSum;
	float avgAggro;
	bool overwriteArray = false;

	// -- spectra -- //

	void SpectraMaster();
	void SpectrumRoughness(float current, float avg);
	float roughness;
	void SpectrumJitteriness(float current, float avg);
	float jitter;
	void SpectrumCurviness(float current, float avg);
	float curviness;
	void SpectrumMusic(float current, float avg);
	float beatProgression;
	int currentBeatProgress;
	UPROPERTY(EditAnywhere, Category = "Variables")
		float beatProgressionLimit;

	// -- animation planes -- // 

	UPROPERTY(EditAnywhere, Category = "AnimationPlane Spawn")
		TArray<TSubclassOf<class AAnimationsPlanar> > AnimPlane;

	AAnimationsPlanar* AnimationPlane;

	void SpawnAnimPlane(/*FVector fVec, float fSpeed, int animType, int animCurve, float animSpeed, float lifetime*/);

	void AnimationPlaneControl();

	FVector masterCurrentLoc;
	FVector masterTargetLoc;
	int masterDirection;
	float masterInterpValue;

	// -- sections -- // 

	void SectionProgress();


};
