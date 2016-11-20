#include "Maya.h"
#include "Engine.h"
#include "Polygon.h"
#include "Cube.h"
#include "ManagerTest_001_Movement.h"


// Sets default values
AManagerTest_001_Movement::AManagerTest_001_Movement()
{
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AManagerTest_001_Movement::BeginPlay()
{
	Super::BeginPlay();

	SpawnDefaults();
	SpawnPolygon();

	delayMax = 2;
	baseCubeClass->ManagerConnection();


}

// Called every frame
void AManagerTest_001_Movement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentLocation = baseCubeClass->GetCurrentLoc();
	TargetLocation = baseCubeClass->GetTargetLoc();

	baseCubeClass->SpawnTrail();
	baseCubeClass->MoveAlongLine();
	baseCubeClass->MoveCube();

	UpdateAnimations();

	if (CurrentLocation.X < 990 || CurrentLocation.X > 10)
	{
		SpawnTrailingAnimations();
	}
}

void AManagerTest_001_Movement::SpawnDefaults()
{

	int32 NumDefaultClasses = DefaultInventoryClasses.Num();

	for (int32 i = 0; i < NumDefaultClasses; i++)
	{
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		baseCubeClass = GetWorld()->SpawnActor<ACube>(DefaultInventoryClasses[i], SpawnInfo);

		Inventory.AddUnique(baseCubeClass);
	}

}

void AManagerTest_001_Movement::SpawnPolygon()
{

	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	polygon = GetWorld()->SpawnActor<APolygon>(APolygon::StaticClass(), SpawnLoc, SpawnRot, SpawnInfo);

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, CurrentLocation.ToString());

	shapes.Add(polygon);
	polygon->CreateSquareAtLoc(CurrentLocation);
	polygon->SquareScalePosition(CurrentLocation, 0, 0);

}

void AManagerTest_001_Movement::SpawnTrailingAnimations()
{
	spawningDelay;
	if (spawningDelay >= spawningOffset)
	{
		SpawnPolygon();
		spawningDelay = 0;
	}
	else
	{
		spawningDelay++;
	}

}

void AManagerTest_001_Movement::UpdateAnimations()
{
	for (int i = 0; i < shapes.Num(); i++)
	{
		shapes[i]->Update();
	}
}