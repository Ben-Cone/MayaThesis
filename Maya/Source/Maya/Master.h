#pragma once

#include "GameFramework/Actor.h"
#include "MasterTrail.h"
#include "Master.generated.h"

UCLASS()
class MAYA_API AMaster : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMaster();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;


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

	// -- Spectrum -- //

	void SpectrumUpdate(FRotator movementAngle, int currentBeatProgress, float currentAggro, float avgAggro);
	void MoveCube();

	void Movement_A_LinearPulse();
	void Movement_B_Discrete();

	float interpValue;
	bool isMoving = false;
	int currentCurve;
	int posNegDirection;
	int directionXYZ;

	float spawningDelay;
	UPROPERTY(EditDefaultsOnly, Category = "Master Spawn")
	float spawningOffset;

	UPROPERTY(EditDefaultsOnly, Category = "Speed")
	float distanceMultiplier;
	UPROPERTY(EditDefaultsOnly, Category = "Speed")
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


