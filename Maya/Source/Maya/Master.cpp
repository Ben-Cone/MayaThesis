// Fill out your copyright notice in the Description page of Project Settings.

#include "Maya.h"
#include "Curves.h"
#include "Engine.h"
#include "Polygon.h"
#include "Kismet/KismetMathLibrary.h"
#include "Master.h"


// Sets default values
AMaster::AMaster()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	RootComponent = RootNull;


}

// Called when the game starts or when spawned
void AMaster::BeginPlay()
{
	Super::BeginPlay();
	SpawnDefaultClasses();

}

// Called every frame
void AMaster::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	timeDelta = DeltaTime;

	UpdatePolygonAnimations();

}

int AMaster::SpawnDefaultClasses()
{
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	Curve = GetWorld()->SpawnActor<ACurves>(CurvesClass[0], SpawnInfo);

	CurveArray.Add(Curve);
	return CurveArray.Num() - 1;
}


void AMaster::SpawnTrail()
{

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = Instigator;

	AMasterTrail* SpawnedTrailCube = GetWorld()->SpawnActor<AMasterTrail>(SpawnedTrail, currentLocation, SpawnRot, SpawnParams);

}

void AMaster::MoveCube()
{
	SetActorLocation(currentLocation, false);
}

FVector AMaster::GetCurrentLoc()
{
	return currentLocation;
}

FVector AMaster::GetTargetLoc()
{
	return targetLocation;
}

// -- Spectrum -- //

void AMaster::Movement_A_LinearPulse()
{
	targetLocation[directionXYZ] = startLocation[directionXYZ] + (distanceMultiplier * posNegDirection);

	interpValue = (CurveArray[currentCurve]->InterpAlongCurve(lengthSeconds, timeDelta) * distanceMultiplier);

	currentLocation[directionXYZ] = currentLocation[directionXYZ] + (interpValue * posNegDirection);
	if (interpValue >= distanceMultiplier)
	{

		isMoving = false;
	}

}

void AMaster::Movement_B_Discrete()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT(" Section 2 -- Discrete ")));
}

void AMaster::SpectrumUpdate(FRotator movementAngle, int currentBeatProgress, float currentA, float avgA)
{
	userAngleToCube.Yaw = movementAngle.Yaw + 180;
	currentSection = currentBeatProgress;
	currentAggro = currentA;
	avgAggro = avgA;

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT(" %f "), userAngleToCube.Yaw));

	switch (currentSection) {

	case 0:

		if (isMoving == true)
		{
			SpawnAlongTrail();
			Movement_A_LinearPulse();
		}
		else if (isMoving == false)
		{
			if (currentAggro > .3)
			{
				if (userAngleToCube.Yaw >= 315.f || userAngleToCube.Yaw < 45.f)
				{
					//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT(" 000 ")));
					directionXYZ = 0;
					posNegDirection = 1;
				}
				else if (userAngleToCube.Yaw >= 135.f && userAngleToCube.Yaw < 225.f)
				{
					//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT(" 001 ")));
					directionXYZ = 0;
					posNegDirection = -1;
				}
				else if (userAngleToCube.Yaw >= 225.f && userAngleToCube.Yaw < 315.f)
				{
					//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT(" 002 ")));
					directionXYZ = 1;
					posNegDirection = -1;
				}
				else if (userAngleToCube.Yaw <= 135.f && userAngleToCube.Yaw  >= 45.f)
				{
					//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT(" 003 ")));
					directionXYZ = 1;
					posNegDirection = 1;
				}

				currentCurve = SpawnDefaultClasses();
				startLocation = currentLocation;
				interpValue = 0;
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT(" %f "), interpValue));
				isMoving = true;

			}
		}

		break;

	case 1:
		Movement_B_Discrete();
		break;

	case 2:
		//Movement_C_SquareWave(movementAngle, currentAggro);
		break;

	case 3:
		//Movement_D_SinWave(movementAngle, currentAggro);
		break;

	case 4:
		//Movement_E_Spiral3D(movementAngle, currentAggro);
		break;

	case 5:
		//Movement_F_Swimming(movementAngle, currentAggro);
		break;

	case 6:
		//Movement_G_Bouncing(movementAngle, currentAggro);
		break;
	}


}

void AMaster::SpawnPolygon(int forwardVec)
{

	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	polygon = GetWorld()->SpawnActor<APolygon>(APolygon::StaticClass(), SpawnLoc, SpawnRot, SpawnInfo);

	shapes.Add(polygon);
	polygon->CreateSquareAtLoc(currentLocation, forwardVec);
	polygon->SquareScalePosition(currentLocation, 0);

}

void AMaster::SpawnAlongTrail()
{
	if (spawningDelay >= spawningOffset)
	{
		SpawnPolygon(directionXYZ);
		spawningDelay = 0;
	}
	else
	{
		spawningDelay++;
	}

}

void AMaster::UpdatePolygonAnimations()
{

	for (int i = 0; i < shapes.Num(); i++)
	{
		shapes[i]->Update();
	}
}