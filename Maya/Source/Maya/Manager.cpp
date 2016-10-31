
#include "Maya.h"
#include "Engine.h"
#include "Polygon.h"
#include "Manager.h"


// Sets default values
AManager::AManager()
{
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AManager::BeginPlay()
{
	Super::BeginPlay();

	pointA = FVector(0.f, 0.f, 0.f);
	pointB = FVector(0.f, 500.f, 0.f);
	pointC = FVector(0.f, 500.f, 500.f);
	pointD = FVector(0.f, 0.f, 500.f);

	SpawnPolygon();

	polygon->CreateCube(FVector(0.f, -2000.f, 400.f), 200.f);

}

// Called every frame
void AManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (int i = 0; i < shapes.Num(); i++)
	{
		shapes[i]->SetSquarePointLocations();
		CheckPolygonLife(shapes[i]);
	}

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%d"), extraSquares));
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("%d"), delay));

	if (extraSquares < 5)
	{

		if (delay < 50)
		{
			delay++;
		}
		else if (delay == 50)
		{
			SpawnPolygon();
			delay = 0;
			extraSquares++;
		}
	}

}

void AManager::SpawnPolygon()
{

	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	polygon = GetWorld()->SpawnActor<APolygon>(APolygon::StaticClass(), SpawnLoc, SpawnRot, SpawnInfo);

	shapes.Add(polygon);

	//polygon->CreateSquare(pointA, pointB, pointC, pointD);

	polygon->CreateSquare(pointA, pointB, pointC, pointD);

	//polygon->SpawnPoint(pointB);


	//if (polygon)
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Polygon = Valid"));
	//}

	//SpawnPointFromPoly();

	//SpawnLoc.X += 400.f;
}

void AManager::CheckPolygonLife(APolygon* inputPoly)
{

	//FVector tempLocation = inputPoly->GetPolyLocation();

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, tempLocation.ToString());

	//if (inputPoly)
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("alive"));
	//}
	//else if(!inputPoly)
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("dead"));
	//}

	//if (tempLocation.X < -1000)
	//{
	//	shapes[0]->Destroy();
	//}


}