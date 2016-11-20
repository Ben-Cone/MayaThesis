#pragma once


#include "GameFramework/Actor.h"
#include "Manager.generated.h"

UCLASS()
class MAYA_API AManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AManager();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	FActorSpawnParameters SpawnInfo;
	FVector SpawnLoc = FVector(0.f, 0.f, 0.f);
	FRotator SpawnRot;

	// -- Shapes -- // 
	
	UPROPERTY(EditDefaultsOnly, Category = Spawn)
		TSubclassOf<class APolygon> polygonSubClass;

	APolygon* polygon;

	void SpawnPolygon();
	void CheckPolygonLife(APolygon* inputPoly);

	FVector pointA;
	FVector pointB;
	FVector pointC;
	FVector pointD;

	FVector tempPoint;
	int delay = 0;
	int delayMax;
	int randomRepeater;

	int extraSquares = 0;

	TArray<class APolygon*> shapes;

	// -- Movement -- //


	enum MovementType
	{
		Discrete,
		Linear,
		Rotate
	};

	MovementType movementType;


	float ManagerDeltaTime;

	// -- setup inventory system -- // 

	void SpawnDefaults();

	UPROPERTY(EditDefaultsOnly, Category = Inventory)
		TArray<TSubclassOf<class ACube> > DefaultInventoryClasses;

	UPROPERTY(EditDefaultsOnly, Category = Inventory)
		TArray<class ACube*> Inventory;

	ACube* baseCubeClass;

	void PrintOverridenBase();

	void UpdateMovement();
	void MovementTypeRandomizer();

	FVector CurrentLocation;
	FVector TargetLocation;
	FVector GetLocation();

	UPROPERTY(EditDefaultsOnly, Category = "Extra Animation")
		float spawningOffset = 10;

};
