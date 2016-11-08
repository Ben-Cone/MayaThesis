#pragma once

#include "GameFramework/Actor.h"
#include "ParticleDefinitions.h"
#include "Polygon.generated.h"


UCLASS()
class MAYA_API APolygon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APolygon(const FObjectInitializer& ObjectInitializer);
	~APolygon();

	void Update();
	FActorSpawnParameters SpawnInfo;
	USphereComponent* RootNull;

	// -- Spawn -- // 

	UPROPERTY(EditDefaultsOnly, Category = "Spawning Object")
		FVector SpawnLoc = FVector(0.f, 0.f, 0.f);

	UPROPERTY(EditDefaultsOnly, Category = "Spawning Object")
		FRotator SpawnRot;

	void SetSquarePointLocations();
	FVector GetPolyLocation();
	//void DestroyPoly();

	// -- Shapes -- //

	void Test();

	void CreateSquareAtLoc(FVector spawnLoc);

	void CreateSquare(
		FVector squareA,
		FVector squareB,
		FVector squareC,
		FVector squareD);
	TArray<FVector> squarePoints;
	TArray<UParticleSystemComponent*> squareLines;
	void SquareScalePosition(FVector squareCen, float squareLen, int32 forwardVector);

	void CreateCube(FVector cubeCen, float cubeLen);
	TArray<FVector> cubePoints;
	TArray<UParticleSystemComponent*> cubeLines;
	void SetCubePointLocations();

	FVector cubeCenter;
	float cubeLength;
	bool expandSwitch = true;

	//

	UPROPERTY(EditDefaultsOnly, Category = "Beam")
		UParticleSystem* lineType;
	UParticleSystemComponent* newLine;
	UParticleSystemComponent* lineComponent;
	FVector pointLocation;

	//

	FVector tempA = FVector(0.f, 0.f, 0.f);
	FVector tempB = FVector(100.f, 200.f, 0.f);

	TArray<FVector> polyPoints;
	TArray<UParticleSystemComponent*> polyLines;

	void DestroySelf();

//	int32 forwardVector = 0;
	FVector spawnLocation;
	float shapeScaler = 2;

	UPROPERTY(EditAnywhere, Category = "ShapeManip")
		float shapeSpeed = 1.5;

	int lifeTime;

};

