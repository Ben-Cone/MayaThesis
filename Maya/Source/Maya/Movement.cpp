
#include "Maya.h"
#include "Curves.h"
#include "Movement.h"

AMovement::AMovement(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	
	PrimaryActorTick.bCanEverTick = true;

}

void AMovement::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnDefaults();
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
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("test")));
}

FVector AMovement::GetCubeLocation()
{
	return currentLocation;
}

void AMovement::Movement_A_LinearPulse(float userRotation)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("current: %f"), currentLocation[directionXYZ]));
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("target: %f"), targetLocation[directionXYZ]));

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("interp: %f"), interpolated));

	interpValue = Curve->DistanceBetweenFloats(currentLocation[directionXYZ], targetLocation[directionXYZ]);

	if (interpolated < 1.f) {
		interpolated = Curve->InterpAlongCurve(lengthSeconds, timeDelta, 0);
		currentLocation[directionXYZ] = startLocation[directionXYZ] + (interpolated * posNegDirection * distanceMultiplier);
	}
	else if (interpolated >= 1.f) {
		currentLocation[directionXYZ] = targetLocation[directionXYZ]; 
	}


}

void AMovement::Movement_0_NewLocation()
{

	lengthSeconds = FMath::RandRange(1.4f, 3.3f);
	distanceMultiplier = FMath::RandRange(50.f, 100.f);
	interpolated = 0;

	if (directionXYZ == 1) 
	{
		directionXYZ = 0;
	}
	else if (directionXYZ == 0)
	{
		directionXYZ = 1;
	}

	posNegSwitch = FMath::RandBool();
	if (posNegSwitch == 1)
	{
		posNegDirection = 1;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT(" 1 ")));
	}
	else if (posNegSwitch == 0)
	{
		posNegDirection = -1;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT(" -1 ")));
	}

	isMoving = true;
	Curve->SetCurveStart(0);

	startLocation[directionXYZ] = currentLocation[directionXYZ];
	targetLocation[directionXYZ] = startLocation[directionXYZ] + (distanceMultiplier * posNegDirection);

}

int AMovement::GetDirection()
{
	return directionXYZ;
}

float AMovement::GetInterpValue()
{
	return interpolated;
}






