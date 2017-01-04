
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

	float timeDelta;

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
	ACurves* AggroCurve;
	ACurves* PointCurve;
	UPROPERTY(EditAnywhere, Category = "Default Classes")
		TArray<TSubclassOf<class ASpectrum> > SpectrumClass;
	ASpectrum* Spectrum;

	// -- spawning defaults -- //
	
	void SpawnDefaultClasses();

	FActorSpawnParameters SpawnInfo;
	FVector SpawnLoc = FVector(0.f, 0.f, 0.f);
	FRotator SpawnRot;

	// -- master / user -- //

	ACharacter* userClass;
	FVector masterLocation;
	FVector userLocation;
	
	// -- User / Aggro -- //

	void AggroUpdate();
	TArray<float> aggroHistory;
	int aggroCount;
	FVector userRadiusToCube;
	FRotator userRotation;
	int testSwitch;

	float currentTempAggro;
	float currentAggro;
	float aggroSum;
	float aggroTempSum;
	float avgAggro;
	//bool overwriteArray = false;
	

	// -- sections -- // 
	void SectionController();

	float userProgress;
	float timeLimit;
	float interpValue;

	void Section_Movement(int currentSec);
	void Section_Music(int currentSec);
	void Section_AnimationPlanes(int currentSec);

	// -- spectra -- //

	void SpectraMaster();
	void SpectrumRoughness(float current, float avg);
	float roughness;
	void SpectrumJitteriness(float current, float avg);
	float jitter;
	void SpectrumCurviness(float current, float avg);
	float curviness;
	void SpectrumMusic(float current, float avg);

	// -- points -- //
	float points;
	float pointsNormalized;
	UPROPERTY(EditAnywhere, Category = "Variables")
	float maxPoints;
	UPROPERTY(EditAnywhere, Category = "Variables")
	float decayRate;
	float decay;

	int currentSection;

	// -- beats -- //
	void BeatCalculator(float deltaTime);

	TArray<float> currentBeat;
	float wholeBeat;
	float halfBeat;
	float quarterBeat;
	float eighthBeat;
	TArray<float> previousBeat;
	float previousWholeBeat;
	float previousHalfBeat;
	float previousQuarterBeat;
	float previousEighthBeat;

	int wholeNote;
	int halfNote;
	int quarterNote;
	int eighthNote;

	int note_1_value;
	int note_2_value;
	int note_3_value;
	int note_4_value;

	int beatDelay;
	float beatProgression;
	int currentBeatProgress;
	UPROPERTY(EditAnywhere, Category = "Variables")
	float beatProgressionLimit;
	UPROPERTY(EditAnywhere, Category = "Variables")
	float bpm;

	float elapsedTime;

	// -- animation planes -- // 

	void SpawnAnimPlane(FRotator fVec, float fSpeed, int animType, int animCurve, float animSpeed, float lifetime);
	void AnimationPlaneControl();

	FVector masterCurrentLocation;
	FVector masterTargetLoc;
	int directionXYZ;
	float masterInterpValue;
	FRotator masterForwardVector;

	float decayingRepeater;

};
