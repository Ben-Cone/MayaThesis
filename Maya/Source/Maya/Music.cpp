
#include "Maya.h"
#include "Engine.h"
#include "Music.h"


AMusic::AMusic(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

	PrimaryActorTick.bCanEverTick = true;

}

void AMusic::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMusic::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AMusic::UpdateTrigger(int eventIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("test")));
}