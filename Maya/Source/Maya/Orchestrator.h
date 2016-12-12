
#pragma once

#include "GameFramework/Actor.h"
#include "Orchestrator.generated.h"

UCLASS()
class MAYA_API AOrchestrator : public AActor
{
	GENERATED_BODY()
	
public:	

	AOrchestrator();

	virtual void BeginPlay() override;
	
	virtual void Tick( float DeltaSeconds ) override;

	// -- Default Classes -- // 

	UPROPERTY(EditAnywhere, Category = "Default Classes")
	TArray<TSubclassOf<class AMaster> > MasterClass;

	AMaster* Master;

	UPROPERTY(EditAnywhere, Category = "Default Classes")
		TArray<TSubclassOf<class ABeats> > BeatsClass;

	ABeats* Beats;

	UPROPERTY(EditAnywhere, Category = "Default Classes")
		TArray<TSubclassOf<class AMovement> > MovementClass;

	AMovement* Movement;

	UPROPERTY(EditAnywhere, Category = "Default Classes")
		TArray<TSubclassOf<class AAnimationsPlanar> > AnimationsPlanarClass;

	AAnimationsPlanar* AnimationPlane;

	UPROPERTY(EditAnywhere, Category = "Default Classes")
		TArray<TSubclassOf<class AMusic> > MusicClass;

	AMusic* Music;

	UPROPERTY(EditAnywhere, Category = "Default Classes")
		TArray<TSubclassOf<class AEnvironment> > EnvironmentClass;

	AEnvironment* Environment;

	UPROPERTY(EditAnywhere, Category = "Default Classes")
		TArray<TSubclassOf<class ACurves> > CurvesClass;

	ACurves* Curve;

	void SpawnDefaultClasses();
	FActorSpawnParameters SpawnInfo;
	FVector SpawnLoc = FVector(0.f, 0.f, 0.f);
	FRotator SpawnRot;
	
	// -- User / Aggro -- //

	ACharacter* userClass;

	void AggroUpdate();

	FVector userLocation;
	FVector masterLocation;
	FVector userRadiusToCube;
	FRotator userRotation;
	TArray<float> aggroHistory;

	int aggroCount;
	void Spectra();

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

	void SpawnAnimPlane(/*FVector fVec, float fSpeed, int animType, int animCurve, float animSpeed, float lifetime*/);

	void AnimationPlaneControl();

	FVector masterCurrentLoc;
	FVector masterTargetLoc;
	int masterDirection;
	float masterInterpValue;

	// -- sections -- // 

	void SectionProgress();

	float userProgress;
	float timeLimit;

	int currentSection;

	// -- listeners -- // 




	void SetBeatValues();

	float wholeBeat;
	float halfBeat;
	float quarterBeat;
	float eighthBeat;

	UPROPERTY(EditAnywhere, Category = "Variables")
	float bpm;


};
