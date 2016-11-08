
#include "Maya.h"
#include "Engine.h"
#include "Polygon.h"
#include "Cube.h"
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
	SpawnDefaults();

	polygon->CreateCube(FVector(0.f, -2000.f, 400.f), 200.f);

	delayMax = 2;
	randomRepeater = 0;
	baseCubeClass->ManagerConnection();

}

// Called every frame
void AManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (int i = 0; i < shapes.Num(); i++)
	{
		shapes[i]->SetSquarePointLocations();
	}

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%d"), extraSquares));
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("%d"), delay));

	if (extraSquares < 5)
	{

		if (delay < spawningOffset)
		{
			delay++;
		}
		else if (delay == spawningOffset)
		{
			SpawnPolygon();
			delay = 0;
			extraSquares++;
		}
	}
	UpdateMovement();
	CurrentLocation = baseCubeClass->GetCurrentLoc();
	TargetLocation = baseCubeClass->GetTargetLoc();
	baseCubeClass->MoveCube();
	baseCubeClass->SpawnTrail();

}

void AManager::SpawnDefaults()
{

	int32 NumDefaultClasses = DefaultInventoryClasses.Num();

	for (int32 i = 0; i < NumDefaultClasses; i++)
	{
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		baseCubeClass = GetWorld()->SpawnActor<ACube>(DefaultInventoryClasses[i], SpawnInfo);

		Inventory.AddUnique(baseCubeClass);

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("%d"), NumDefaultClasses));


		//if (!baseCubeClass)
		//{
		//			}

		// -- Store Inventory items in variables -- // 
		//ABase* baseTemp = Inventory[0];
		//baseTemp->Print();

		
		// -- can flexibly choose directly from the inventory array -- //
		//Inventory[0]->Print();

		// -- can call directly from spawned actor -- //
		//newBase->Print();
	}
	
}


void AManager::UpdateMovement()
{
	CurrentLocation = baseCubeClass->GetCurrentLoc();
	TargetLocation = baseCubeClass->GetTargetLoc();

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, CurrentLocation.ToString());
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("-- Current Location --"));

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TargetLocation.ToString());
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("-- Target Location --"));

	// -- Set new target location -- //
	if (FVector::Dist(TargetLocation, CurrentLocation) < 1.f)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("%d"), randomRepeater));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("-- RandomRepeater --"));
		if (randomRepeater == 0)
		{
			MovementTypeRandomizer();
		}

		else if (randomRepeater > 0)
		{
			randomRepeater--;

			switch (movementType)
			{
			case Discrete:
				baseCubeClass->NewTargetLocationDiscrete();
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("-- DISCRETE --"));
				break;

			case Linear:
				baseCubeClass->NewTargetLocationLinear();
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("-- LINEAR --"));
				break;

			case Rotate:
				baseCubeClass->NewTargetLocationRotate();
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("-- ROTATE --"));
				break;
			}
		}
	}

	else if (FVector::Dist(TargetLocation, CurrentLocation) > 1.f)
	{
		switch (movementType)
		{
		case Discrete:
			baseCubeClass->MoveDiscrete();
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("-- Discrete --"));
			break;

		case Linear:
			baseCubeClass->MoveLinear();
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("-- Linear --"));
			break;

		case Rotate:
			baseCubeClass->MoveRotate();
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("-- Rotate --"));
			break;
		}
	}
}

void AManager::MovementTypeRandomizer()
{
	int MovementTypePicker = FMath::RandRange(0, 2);

	switch (MovementTypePicker)
	{
	case 0: movementType = MovementType::Discrete;
		randomRepeater = FMath::RandRange(4, 9);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("-- Discrete --"));
		break;

	case 1: movementType = MovementType::Linear;
		randomRepeater = FMath::RandRange(0, 2);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("-- Linear --"));
		break;

	case 2: movementType = MovementType::Rotate;
		randomRepeater = FMath::RandRange(1, 3);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("-- Rotate --"));
		break;
	}
}


void AManager::SpawnPolygon()
{

	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	polygon = GetWorld()->SpawnActor<APolygon>(APolygon::StaticClass(), SpawnLoc, SpawnRot, SpawnInfo);

	shapes.Add(polygon);
	polygon->CreateSquare(pointA, pointB, pointC, pointD);

}

FVector AManager::GetLocation()
{
	return CurrentLocation;
}


void AManager::CheckPolygonLife(APolygon* inputPoly)
{
}