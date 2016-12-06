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

	if (isMoving)
	{
		Movement_0_Ambient();
	}
	else
	{
		Movement_0_NewLocation();
	}

	MoveCube();
	SpawnTrail();
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

	interpValue = (CurveArray[currentCurve]->InterpAlongCurve(lengthSeconds, timeDelta, 0) * distanceMultiplier);

	currentLocation[directionXYZ] = currentLocation[directionXYZ] + (interpValue * posNegDirection);
	if (interpValue >= distanceMultiplier)
	{
		isMoving = false;
	}

}

void AMaster::Movement_B_Discrete()
{
	
	if (interpValue < distanceMultiplier * 10)
	{
		currentLocation[directionXYZ] += (12 * currentAggro * posNegDirection);
		interpValue += (12 * currentAggro);
	}
	else if (interpValue >= distanceMultiplier * 10)
	{
		currentLocation = targetLocation;
		isMoving = false;
	}

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT(" Section 2 -- Discrete ")));
}

void AMaster::Movement_C_SquareWave()
{
	if (interpValue < distanceMultiplier * 10)
	{
		currentLocation[directionXYZ] += (12 * currentAggro * posNegDirection);
		interpValue += (12 * currentAggro);
	}
	else if (interpValue >= distanceMultiplier * 10)
	{
		//currentLocation = targetLocation;
		isMoving = false;

		switch (upOverDownOver) {

		case 0:
			directionXYZ = 2;
			posNegDirection = 1;
			upOverDownOver = 1;
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT(" 0 - up ")));
			break;

		case 1:
			// -- "OVER" param currently PERMANENTLY set to Y, should be driven by user
			directionXYZ = 1;
			posNegDirection = 1;
			upOverDownOver = 2;
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT(" 1 - over ")));
			break;

		case 2:
			directionXYZ = 2;
			posNegDirection = -1;
			upOverDownOver = 3;
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT(" 2 - down ")));
			break;

		case 3:
			// -- "OVER" param currently PERMANENTLY set to Y, should be driven by user
			directionXYZ = 1;
			posNegDirection = 1;
			upOverDownOver = 0;
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT(" current location : %f"), currentLocation.Z));
			break;
		}
	}
}

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT(" Section 3 -- Square Wave ")));

void AMaster::RotateAroundPoint()
{
	targetLocation[directionXYZ] = currentLocation[directionXYZ];
}

void AMaster::Movement_D_SinWave()
{
	interpValue += interpSpeed;

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT(" interpValue : %f"), interpValue));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT(" upOverDownOver : %d"), upOverDownOver));
	switch (upOverDownOver) {
	
	case 0: // -- up  + over
		if (interpValue < 90)
		{
			currentLocation.Z = (((startLocation.Z - rotator.Z) * FMath::Cos(interpValue * 0.0174553)) - ((startLocation.X - rotator.X) * FMath::Sin(interpValue * 0.0174553))) + rotator.Z;
			currentLocation.X = (((startLocation.X - rotator.X) * FMath::Cos(interpValue * 0.0174553)) - ((startLocation.Z - rotator.Z) * FMath::Sin(interpValue * 0.0174553))) + rotator.X;
		}
		else if (interpValue >= 90)
		{
			isMoving = false;
		}
		break;

	case 1: // -- over + down
		if (interpValue >= 90 && interpValue < 180)
		{
			currentLocation.Z = (((startLocation.Z - rotator.Z) * FMath::Cos(interpValue * 0.0174553)) - ((startLocation.X - rotator.X) * FMath::Sin(interpValue * 0.0174553))) + rotator.Z;
			currentLocation.X = (((startLocation.X - rotator.X) * FMath::Cos(interpValue * -0.0174553)) - ((startLocation.Z - rotator.Z) * FMath::Sin(interpValue * -0.0174553))) + rotator.X;
		}
		else if (interpValue >= 180)
		{
			isMoving = false;
		}
		break;


	case 2: // -- down + over
		if (interpValue >= 90 && interpValue < 180)
		{
			currentLocation.Z = (((startLocation.Z - rotator.Z) * FMath::Cos(interpValue * 0.0174553)) - ((startLocation.X - rotator.X) * FMath::Sin(interpValue * 0.0174553))) + rotator.Z;
			currentLocation.X = (((startLocation.X - rotator.X) * FMath::Cos(interpValue * -0.0174553)) - ((startLocation.Z - rotator.Z) * FMath::Sin(interpValue * -0.0174553))) + rotator.X;
		}
		else if (interpValue >= 180)
		{
			isMoving = false;
		}
		break;

	case 3: // -- over
		if (interpValue < 90)
		{
			currentLocation.Z = (((startLocation.Z - rotator.Z) * FMath::Cos(interpValue * 0.0174553)) - ((startLocation.X - rotator.X) * FMath::Sin(interpValue * 0.0174553))) + rotator.Z;
			currentLocation.X = (((startLocation.X - rotator.X) * FMath::Cos(interpValue * -0.0174553)) - ((startLocation.Z - rotator.Z) * FMath::Sin(interpValue * -0.0174553))) + rotator.X;
		}
		else if (interpValue >= 90)
		{
			isMoving = false;
		}

		break;

	}
}

void AMaster::Movement_E_Spiral3D()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT(" Section 5 -- Spiral ")));
}

void AMaster::Movement_F_Swimming()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT(" Section 6 -- Swimming ")));
}

void AMaster::Movement_G_Bouncing()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT(" Section 7 -- Bouncing ")));
}


void AMaster::SpectrumUpdate(FRotator movementAngle, int currentBeatProgress, float currentA, float avgA)
{
	userAngleToCube.Yaw = movementAngle.Yaw + 180;
	currentSection = currentBeatProgress;
	//currentSection = 3;
	currentAggro = currentA;
	avgAggro = avgA;

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT(" %f "), userAngleToCube.Yaw));

	switch (currentSection) {

	case 0: // -- Linear Pulse
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
					directionXYZ = 0;
					posNegDirection = 1;
				}
				else if (userAngleToCube.Yaw >= 135.f && userAngleToCube.Yaw < 225.f)
				{
					directionXYZ = 0;
					posNegDirection = -1;
				}
				else if (userAngleToCube.Yaw >= 225.f && userAngleToCube.Yaw < 315.f)
				{
					directionXYZ = 1;
					posNegDirection = -1;
				}
				else if (userAngleToCube.Yaw <= 135.f && userAngleToCube.Yaw  >= 45.f)
				{
					directionXYZ = 1;
					posNegDirection = 1;
				}

				currentCurve = SpawnDefaultClasses();
				startLocation = currentLocation;
				interpValue = 0;
				isMoving = true;

			}
		}

		break;

	case 1: // -- Discrete Steps
		if (isMoving == true)
		{
			Movement_B_Discrete();
		}
		else if (isMoving == false)
		{
			directionXYZ = FMath::RandRange(0, 2);
			interpValue = 0.f;


			switch (directionXYZ) {

			case 0:
				// new X direction

				if (userAngleToCube.Yaw >= 315 || userAngleToCube.Yaw < 45)
				{
					posNegDirection = 1;
				}
				else if (userAngleToCube.Yaw >= 135 && userAngleToCube.Yaw < 225)
				{
					posNegDirection = -1;
				}

				break;

			case 1:
				// new y direction

				if (userAngleToCube.Yaw < 135 && userAngleToCube.Yaw >= 45)
				{
					posNegDirection = 1;
				}
				else if (userAngleToCube.Yaw >= 225 && userAngleToCube.Yaw < 315)
				{
					posNegDirection = -1;
				}

				break;

			case 2:
				// new z direction

				if (currentLocation.Z >= 160)
				{
					posNegDirection = -1;
				}
				else if (currentLocation.Z <= 0)
				{
					posNegDirection = 1;
				}

			}

			targetLocation[directionXYZ] = currentLocation[directionXYZ] + (distanceMultiplier * 10 * posNegDirection);
		}

		isMoving = true;
		break;

	case 2: // -- Square Wave

		if (isMoving == true)
		{
			Movement_C_SquareWave();
		}
		else if (isMoving == false)
		{
			interpValue = 0;
			targetLocation[directionXYZ] = currentLocation[directionXYZ] + (distanceMultiplier * 10);

			isMoving = true;
		}
		break;

	case 3: // -- Sin Wave




		break;


		//if (isMoving == true)
		//{
		//	Movement_D_SinWave();
		//}
		//else if (isMoving == false)
		//{
		//	switch (upOverDownOver) {
		//	case 0:
		//		interpValue = 90;
		//		upOverDownOver = 1;

		//		break;

		//	case 1:
		//		interpValue = 180;
		//		upOverDownOver = 2;
		//		break;

		//	case 2:
		//		interpValue = 90;
		//		upOverDownOver = 3;
		//		break;

		//	case 3:
		//		interpValue = 0;
		//		upOverDownOver = 0;
		//		break;


		//	}

		//	rotator = FVector(0.f, 0.f, 100.f);
		//	startLocation = FVector(0.f, 0.f, 0.f);
		//	currentLocation = startLocation;

		//	//targetLocation.X = currentLocation.X + (distanceMultiplier * 10);
		//	//targetLocation.Z = currentLocation.Z + (distanceMultiplier * 10);

		//	isMoving = true;
		//}
		//break;

	case 4: // -- Spiral 3D
		Movement_E_Spiral3D();
		break;

	case 5: // -- Swimming
		Movement_F_Swimming();
		break;

	case 6: // -- Bouncing
		Movement_G_Bouncing();
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

void AMaster::Movement_0_Ambient()
{

	interpValue = (CurveArray[currentCurve]->InterpAlongCurve(lengthSeconds, timeDelta, 0));

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT(" interp : %f "), interpValue));
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT(" distance : %f "), distanceMultiplier));

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("  : %d "), posNegDirection));

	currentLocation[directionXYZ] = startLocation[directionXYZ] + (interpValue * posNegDirection * distanceMultiplier);
	if (interpValue >= 1)
	{
		isMoving = false;
	}

	// -- fill in animations planar -- //






	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT(" targetLocation : %f "), targetLocation[directionXYZ]));
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT(" currentLocation : %f "), currentLocation[directionXYZ]));
}

void AMaster::Movement_0_NewLocation()
{

	lengthSeconds = FMath::RandRange(1.4f, 2.3f);
	distanceMultiplier = FMath::RandRange(10.f, 100.f);
	interpValue = 0;

	if (directionXYZ == 1) 
	{
		directionXYZ = 0;
	}
	else if (directionXYZ == 0)
	{
		directionXYZ = 1;
	}

	bool posNegSwitch = FMath::RandBool();
	if (posNegSwitch == 1)
	{
		posNegDirection = 1;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT(" 1 ")));
	}
	else if (posNegSwitch == 0)
	{
		posNegDirection = -1;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT(" -1 ")));
	}

	isMoving = true;
	currentCurve = SpawnDefaultClasses();

	startLocation = currentLocation;
	targetLocation[directionXYZ] = startLocation[directionXYZ] + (distanceMultiplier * posNegDirection);

}