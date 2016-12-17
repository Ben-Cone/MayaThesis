
#include "Maya.h"
#include "Engine.h"
#include "Environment.h"

AEnvironment::AEnvironment(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

	PrimaryActorTick.bCanEverTick = true;

}

void AEnvironment::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEnvironment::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AEnvironment::UpdateTrigger(int eventIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("test")));
}