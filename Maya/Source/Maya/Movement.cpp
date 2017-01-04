
#include "Maya.h"
#include "Curves.h"
#include "Movement.h"

AMovement::AMovement(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	
	PrimaryActorTick.bCanEverTick = true;

	xyz.Add("X");
	xyz.Add("Y");
	xyz.Add("Z");


}

void AMovement::BeginPlay()
{
	Super::BeginPlay();
	

	SpawnDefaults();
	currentLocation = FVector(0.f, 0.f, 150.f);
	Movement_0_NewLocation();
}

void AMovement::SpawnDefaults()
{
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	Curve = GetWorld()->SpawnActor<ACurves>(CurvesSubClass, SpawnInfo);
}

void AMovement::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	timeDelta = DeltaTime;



}

void AMovement::UpdateTrigger(int eventIndex)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("test")));


}

FVector AMovement::GetCurrentLocation()
{
	return currentLocation;
}

int AMovement::Movement_0_LinearPulse(float userRot)
{
	userRotation.Yaw = userRot;
	if (interpolated < 1.f) {
		interpolated = Curve->InterpAlongCurve(lengthSeconds, timeDelta, 0);
		currentLocation[directionXYZ] = startLocation[directionXYZ] + (interpolated * posNegDirection * distanceMultiplier);
	}
	else if (interpolated >= 1.f) {
		currentLocation[directionXYZ] = targetLocation[directionXYZ]; 
	}

	return directionXYZ;
}

int AMovement::Movement_1_Discrete(float userRot)
{
	userRotation.Yaw = userRot;
	if (interpolated < 1.f) {
		interpolated = Curve->InterpAlongCurve(lengthSeconds, timeDelta, 0);
		currentLocation[directionXYZ] = startLocation[directionXYZ] + (interpolated * posNegDirection * distanceMultiplier);
	}
	else if (interpolated >= 1.f) {
		currentLocation[directionXYZ] = targetLocation[directionXYZ];
	}

	if (userRotation.Yaw > 315 || userRotation.Yaw < 45) {
		rotationQuadrant = 0;
	}
	else if (userRotation.Yaw > 45 && userRotation.Yaw < 135) {
		rotationQuadrant = 1;
	}
	else if (userRotation.Yaw > 135 && userRotation.Yaw < 225) {
		rotationQuadrant = 2;
	}
	else if (userRotation.Yaw > 225 && userRotation.Yaw < 315) {
		rotationQuadrant = 3;
	}	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("X: %f"), currentLocation.X));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Y: %f"), currentLocation.Y));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT(" userRotation -- %f"), userRotation.Yaw));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("quadrant %d"), rotationQuadrant));

	return directionXYZ;
}

void AMovement::Movement_0_NewLocation()
{
	lengthSeconds = FMath::RandRange(1.4f, 3.3f);
	distanceMultiplier = FMath::RandRange(1,2) * 50;
	interpolated = 0;

	if (directionXYZ == 1) 
	{
		directionXYZ = 0;

		// X boundary driven wander
		if (FMath::Abs(startLocation.X) < boundary - (boundaryBuffer * 2)) {
			posNegDirection = FMath::RandBool();
			if (posNegDirection == 1) {
				posNegDirection = 1;
			}
			else if (posNegDirection == 0) {
				posNegDirection = -1;
			}
		}
		else if (startLocation.X > boundary - (boundaryBuffer * 2)) {
			posNegDirection = -1;
		}
		else if (startLocation.X < (boundary - (boundaryBuffer * 2)) * -1) {
			posNegDirection = 1;
		}
	}
	else if (directionXYZ == 0)
	{
		directionXYZ = 1;

		// Y boundary driven wander
		if (FMath::Abs(startLocation.Y) < boundary - (boundaryBuffer * 2)) {
			posNegDirection = FMath::RandBool();
			if (posNegDirection == 1) {
				posNegDirection = 1;
			}
			else if (posNegDirection == 0) {
				posNegDirection = -1;
			}
		}
		else if (startLocation.Y > boundary - (boundaryBuffer * 2)) {
			posNegDirection = -1;
		}
		else if (startLocation.Y < (boundary - (boundaryBuffer * 2)) * -1) {
			posNegDirection = 1;
		}
	}

	Curve->SetCurveStart(0);

	startLocation[directionXYZ] = currentLocation[directionXYZ];
	targetLocation[directionXYZ] = (startLocation[directionXYZ] + (distanceMultiplier * posNegDirection));

}

void AMovement::Movement_1_NewLocation(float userRot)
{
	interpolated = 0;
	distanceMultiplier = FMath::RandRange(3, 4) * 50;

	if (rotationQuadrant == 0) {
		if (currentLocation.X + distanceMultiplier < (boundary - boundaryBuffer)) {
			directionXYZ = 0;
			posNegDirection = 1;
		}
		else {
			directionXYZ = 1;
			if (currentLocation.Y >= 0) {
				posNegDirection = -1;
			}
			else if (currentLocation.Y < 0) {
				posNegDirection = 1;
			}
		}
	}
	else if (rotationQuadrant == 1) {
		if (currentLocation.Y + distanceMultiplier < (boundary - boundaryBuffer)) {
			directionXYZ = 1;
			posNegDirection = 1;
		}
		else {
			directionXYZ = 0;
			if (currentLocation.X >= 0) {
				posNegDirection = -1;
			}
			else if (currentLocation.X < 0) {
				posNegDirection = 1;
			}
		}
	}
	else if (rotationQuadrant == 2) {
		if (FMath::Abs(currentLocation.X) + distanceMultiplier < (boundary - boundaryBuffer)) {
			directionXYZ = 0;
			posNegDirection = -1;
		}
		else {
			directionXYZ = 1;
			if (currentLocation.Y >= 0) {
				posNegDirection = -1;
			}
			else if (currentLocation.Y < 0) {
				posNegDirection = 1;
			}
		}

	}
	else if (rotationQuadrant == 3) {
		if (FMath::Abs(currentLocation.Y) + distanceMultiplier < (boundary - boundaryBuffer)) {
			directionXYZ = 1;
			posNegDirection = -1;
		}
		else {
			directionXYZ = 0;
			if (currentLocation.X >= 0) {
				posNegDirection = -1;
			}
			else if (currentLocation.X < 0) {
				posNegDirection = 1;
			}
		}
	}

	startLocation = currentLocation;
	targetLocation[directionXYZ] = (startLocation[directionXYZ] + (distanceMultiplier * posNegDirection));

	Curve->SetCurveStart(0);

	// pick opposite from user 
	// // randomly left or right
	// // if boundary

	
}
















int AMovement::GetDirection()
{
	return directionXYZ;
}

float AMovement::GetInterpValue()
{
	return interpolated;
}