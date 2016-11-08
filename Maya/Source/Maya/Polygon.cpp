
#include "Maya.h"
#include "Engine.h"
#include "Polygon.h"


// Sets default values
APolygon::APolygon(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = RootNull;

	ConstructorHelpers::FObjectFinder<UParticleSystem> line(TEXT("ParticleSystem'/Game/Shapes/BeamLine.BeamLine'"));
	lineComponent = ObjectInitializer.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("Line"));

	if (line.Succeeded())
	{
		lineComponent->Template = line.Object;
	}

	lineComponent->bAutoActivate = true;
	lineComponent->SetHiddenInGame(false);

}

void APolygon::Update()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%f"), shapeSpeed));


	if (shapeScaler < 200)
	{
		shapeScaler += shapeSpeed;
		SquareScalePosition(spawnLocation, shapeScaler, 0);
	}

	if (lifeTime < 200)
	{
		lifeTime++;
	}
	else if (lifeTime == 200)
	{
		DestroySelf();
		lifeTime++;
	}

	
}

void APolygon::CreateSquare(
	FVector squareA,
	FVector squareB,
	FVector squareC,
	FVector squareD)
{

	squarePoints.Add(squareA);
	squarePoints.Add(squareB);
	squarePoints.Add(squareC);
	squarePoints.Add(squareD);

	for (int i = 0; i < 4; i++)
	{
		newLine = UGameplayStatics::SpawnEmitterAtLocation
			(GetWorld(),
				lineComponent->Template,
				squareA,
				FRotator::ZeroRotator,
				false
				);

		squareLines.Add(newLine);
	}

	SetSquarePointLocations();

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%d"), Lines.Num()));

}

void APolygon::SetSquarePointLocations()
{

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("%d"), pointLocations.Num()));

	for (int i = 0; i < 4; i++)
	{

		if (squarePoints[i].X > -1000)
		{
			squarePoints[i].X -= 3.f;
		}
		else if (squarePoints[i].X <= -1000)
		{
			squarePoints[i].X = 0.f;
		}
		squareLines[i]->SetBeamSourcePoint(0, squarePoints[i], 0);

		if (i < 3)
		{
			squareLines[i]->SetBeamEndPoint(0, squarePoints[i + 1]);
		}
		else if (i == 3)
		{
			squareLines[i]->SetBeamEndPoint(0, squarePoints[0]);
		}
	}
}

FVector APolygon::GetPolyLocation()
{
	return cubePoints[0];
}

void APolygon::CreateCube(FVector cubeCen, float cubeLen)
{
	cubePoints.Init(tempA, 8);

	cubeCenter = cubeCen;
	cubeLength = cubeLen;

	for (int i = 0; i < 12; i++)
	{
		newLine = UGameplayStatics::SpawnEmitterAtLocation
			(GetWorld(),
				lineComponent->Template,
				tempA,
				FRotator::ZeroRotator,
				false
				);

		cubeLines.Add(newLine);
	}

	SetCubePointLocations();

}

void APolygon::SetCubePointLocations()
{


	cubePoints[0].X = cubeCenter.X + (cubeLength / 2);
	cubePoints[0].Y = cubeCenter.Y + (cubeLength / 2);
	cubePoints[0].Z = cubeCenter.Z + (cubeLength / 2);

	cubePoints[1].X = cubeCenter.X + (cubeLength / 2);
	cubePoints[1].Y = cubeCenter.Y + (cubeLength / -2);
	cubePoints[1].Z = cubeCenter.Z + (cubeLength / 2);

	cubePoints[2].X = cubeCenter.X + (cubeLength / 2);
	cubePoints[2].Y = cubeCenter.Y + (cubeLength / -2);
	cubePoints[2].Z = cubeCenter.Z + (cubeLength / -2);

	cubePoints[3].X = cubeCenter.X + (cubeLength / 2);
	cubePoints[3].Y = cubeCenter.Y + (cubeLength / 2);
	cubePoints[3].Z = cubeCenter.Z + (cubeLength / -2);

	cubePoints[4].X = cubeCenter.X + (cubeLength / -2);
	cubePoints[4].Y = cubeCenter.Y + (cubeLength / 2);
	cubePoints[4].Z = cubeCenter.Z + (cubeLength / 2);

	cubePoints[5].X = cubeCenter.X + (cubeLength / -2);
	cubePoints[5].Y = cubeCenter.Y + (cubeLength / -2);
	cubePoints[5].Z = cubeCenter.Z + (cubeLength / 2);

	cubePoints[6].X = cubeCenter.X + (cubeLength / -2);
	cubePoints[6].Y = cubeCenter.Y + (cubeLength / -2);
	cubePoints[6].Z = cubeCenter.Z + (cubeLength / -2);

	cubePoints[7].X = cubeCenter.X + (cubeLength / -2);
	cubePoints[7].Y = cubeCenter.Y + (cubeLength / 2);
	cubePoints[7].Z = cubeCenter.Z + (cubeLength / -2);

	for (int i = 0; i < 12; i++)
	{
		if (i < 3)
		{
			cubeLines[i]->SetBeamSourcePoint(0, cubePoints[i], 0);
			cubeLines[i]->SetBeamEndPoint(0, cubePoints[i + 1]);
		}
		else if (i == 3)
		{
			cubeLines[i]->SetBeamSourcePoint(0, cubePoints[i], 0);
			cubeLines[i]->SetBeamEndPoint(0, cubePoints[0]);
		}
		else if (i > 3 && i < 8)
		{
			cubeLines[i]->SetBeamSourcePoint(0, cubePoints[i - 4], 0);
			cubeLines[i]->SetBeamEndPoint(0, cubePoints[i]);
		}
		else if (i >= 8 && i < 11)
		{
			cubeLines[i]->SetBeamSourcePoint(0, cubePoints[i - 4], 0);
			cubeLines[i]->SetBeamEndPoint(0, cubePoints[i - 3]);
		}
		else if (i == 11)
		{
			cubeLines[i]->SetBeamSourcePoint(0, cubePoints[4], 0);
			cubeLines[i]->SetBeamEndPoint(0, cubePoints[7]);
		}
	}
}

void APolygon::CreateSquareAtLoc(FVector spawnLoc)
{

	for (int i = 0; i < 4; i++)
	{
		newLine = UGameplayStatics::SpawnEmitterAtLocation
			(GetWorld(),
				lineComponent->Template,
				tempA,
				FRotator::ZeroRotator,
				false
				);

		polyLines.Add(newLine);
	}

	polyPoints.Init(tempA, 4);
	spawnLocation = spawnLoc;


}

void APolygon::SquareScalePosition(FVector squareCen, float squareLen, int32 forwardVector)
{

//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("polyPoints: %d"), polyPoints.Num()));
//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("polyLines: %d"), polyLines.Num()));

	switch (forwardVector)
	{
	case 0: // x
		polyPoints[0].Z = squareCen.Z + (squareLen / 2);
		polyPoints[1].Z = squareCen.Z + (squareLen / 2);
		polyPoints[2].Z = squareCen.Z - (squareLen / 2);
		polyPoints[3].Z = squareCen.Z - (squareLen / 2);

		polyPoints[0].Y = squareCen.Y - (squareLen / 2);
		polyPoints[1].Y = squareCen.Y + (squareLen / 2);
		polyPoints[2].Y = squareCen.Y + (squareLen / 2);
		polyPoints[3].Y = squareCen.Y - (squareLen / 2);

		polyPoints[0].X = squareCen.X;
		polyPoints[1].X = squareCen.X;
		polyPoints[2].X = squareCen.X;
		polyPoints[3].X = squareCen.X;

		for (int i = 0; i < 4; i++)
		{
			polyLines[i]->SetBeamSourcePoint(0, polyPoints[i], 0);

			if (i < 3)
			{
				polyLines[i]->SetBeamEndPoint(0, polyPoints[i + 1]);
			}
			else if (i == 3)
			{
				polyLines[i]->SetBeamEndPoint(0, polyPoints[0]);
			}

		}
		break;

	case 1: // x
		polyPoints[0].Z = squareCen.Z + (squareLen / 2);
		polyPoints[1].Z = squareCen.Z + (squareLen / 2);
		polyPoints[2].Z = squareCen.Z - (squareLen / 2);
		polyPoints[3].Z = squareCen.Z - (squareLen / 2);

		polyPoints[0].X = squareCen.X - (squareLen / 2);
		polyPoints[1].X = squareCen.X + (squareLen / 2);
		polyPoints[2].X = squareCen.X + (squareLen / 2);
		polyPoints[3].X = squareCen.X - (squareLen / 2);

		polyPoints[0].Y = squareCen.Y;
		polyPoints[1].Y = squareCen.Y;
		polyPoints[2].Y = squareCen.Y;
		polyPoints[3].Y = squareCen.Y;

		for (int i = 0; i < 4; i++)
		{
			polyLines[i]->SetBeamSourcePoint(0, polyPoints[i], 0);

			if (i < 3)
			{
				polyLines[i]->SetBeamEndPoint(0, polyPoints[i + 1]);
			}
			else if (i == 3)
			{
				polyLines[i]->SetBeamEndPoint(0, polyPoints[0]);
			}

		}
		break;

	case 2: // x
		polyPoints[0].Y = squareCen.Y + (squareLen / 2);
		polyPoints[1].Y = squareCen.Y + (squareLen / 2);
		polyPoints[2].Y = squareCen.Y - (squareLen / 2);
		polyPoints[3].Y = squareCen.Y - (squareLen / 2);

		polyPoints[0].X = squareCen.X - (squareLen / 2);
		polyPoints[1].X = squareCen.X + (squareLen / 2);
		polyPoints[2].X = squareCen.X + (squareLen / 2);
		polyPoints[3].X = squareCen.X - (squareLen / 2);

		for (int i = 0; i < 4; i++)
		{
			polyLines[i]->SetBeamSourcePoint(0, polyPoints[i], 0);

			if (i < 3)
			{
				polyLines[i]->SetBeamEndPoint(0, polyPoints[i + 1]);
			}
			else if (i == 3)
			{
				polyLines[i]->SetBeamEndPoint(0, polyPoints[0]);
			}

		}
		break;
	}
}

void APolygon::DestroySelf()
{
	for (int i = 0; i < polyLines.Num(); i++)
	{
		polyLines[i]->Deactivate();
		Destroy();
	}
}

APolygon::~APolygon()
{
	//for (int i = 0; i < polyLines.Num(); i++)
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT(" destroy "));
	//	polyLines[i]->Deactivate();
	//}
}