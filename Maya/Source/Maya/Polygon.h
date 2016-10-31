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

	FActorSpawnParameters SpawnInfo;

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

	void CreateSquare(
		FVector squareA,
		FVector squareB,
		FVector squareC,
		FVector squareD);
	TArray<FVector> squarePoints;
	TArray<UParticleSystemComponent*> squareLines;

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

};

