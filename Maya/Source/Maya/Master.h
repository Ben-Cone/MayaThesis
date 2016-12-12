#pragma once

#include "GameFramework/Actor.h"
#include "MasterTrail.h"
#include "Listener.h"
#include "Master.generated.h"

UCLASS()
class MAYA_API AMaster : public AListener
{
	GENERATED_UCLASS_BODY()
	
public:	

	virtual void BeginPlay() override;
	
	virtual void Tick( float DeltaSeconds ) override;

	void UpdateTrigger(int eventIndex) override;

	// -- Defaults -- //

	UPROPERTY(EditAnywhere, Category = "Master Spawn")
		TArray<TSubclassOf<class ACurves> > CurvesClass;
	FActorSpawnParameters SpawnInfo;
	float timeDelta;
	int SpawnDefaultClasses();

	ACurves* Curve;
	TArray<ACurves*> CurveArray;

	USphereComponent* RootNull;
	FVector SpawnLoc = FVector(0.f, 0.f, 0.f);
	FRotator SpawnRot;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn Trail")
		TSubclassOf<AMasterTrail> SpawnedTrail;
	void SpawnTrail();



	FVector currentLocation;
	FVector startLocation;
	FVector targetLocation;
	FVector GetCurrentLoc();
	FVector GetTargetLoc();
	int GetDirection();
	float GetInterpValue();

	// -- Spectrum -- //

	void SpectrumUpdate(FRotator movementAngle, int currentBeatProgress, float currentAggro, float avgAggro);
	void MoveCube();

	void RotateAroundPoint();

	void Movement_0_NewLocation();

	int bull;

	void Movement_0_Ambient();
	void Movement_A_LinearPulse();
	void Movement_B_Discrete();
	void Movement_C_SquareWave();
	void Movement_D_SinWave();
	void Movement_E_Spiral3D();
	void Movement_F_Swimming();
	void Movement_G_Bouncing();


	float interpValue;
	bool isMoving = false;
	int currentCurve;
	int posNegDirection;
	int directionXYZ;
	int upOverDownOver;
	FVector rotator;

	float throwAway;

	UPROPERTY(EditDefaultsOnly, Category = "Master Spawn")
	float interpSpeed;

	float spawningDelay;
	UPROPERTY(EditDefaultsOnly, Category = "Master Spawn")
	float spawningOffset;

	// -- set distanceMultiplier dynamically
	//UPROPERTY(EditDefaultsOnly, Category = "Speed")
	float distanceMultiplier;
	//UPROPERTY(EditDefaultsOnly, Category = "Speed")
	float lengthSeconds;



	FRotator userAngleToCube;
	int currentSection;
	float currentAggro;
	float avgAggro;

	// -- shapes -- //

	TArray<class APolygon*> shapes;
	UPROPERTY(EditDefaultsOnly, Category = Spawn)
	TSubclassOf<class APolygon> polygonSubClass;
	APolygon* polygon;

	void SpawnPolygon(int forwardVec);
	void UpdatePolygonAnimations();
	void SpawnAlongTrail();




};


