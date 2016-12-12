
#include "Maya.h"
#include "Engine.h"
#include "Master.h"
#include "Kismet/KismetMathLibrary.h"
#include "AnimationsPlanar.h"
#include "Beats.h"
#include "Movement.h"
#include "Music.h"
#include "Environment.h"
#include "Curves.h"
#include "Orchestrator.h"


AOrchestrator::AOrchestrator()
{

	PrimaryActorTick.bCanEverTick = true;

}

void AOrchestrator::BeginPlay()
{
	Super::BeginPlay();
	SpawnDefaultClasses();

}

void AOrchestrator::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	Master->SpawnTrail();
	masterLocation = Master->GetCurrentLoc();
	userLocation = userClass->GetActorLocation();

	Beats->BeatCalculator(DeltaTime, bpm);
	SetBeatValues();

	Music->UpdateTrigger(1);

	Environment->UpdateTrigger(1);

}

void AOrchestrator::SpawnDefaultClasses()
{
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	Master = GetWorld()->SpawnActor<AMaster>(MasterClass[0], SpawnInfo);

	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	Beats = GetWorld()->SpawnActor<ABeats>(BeatsClass[0], SpawnInfo);

	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	Movement = GetWorld()->SpawnActor<AMovement>(MovementClass[0], SpawnInfo);

	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AnimationPlane = GetWorld()->SpawnActor<AAnimationsPlanar>(AnimationsPlanarClass[0], SpawnLoc, SpawnRot, SpawnInfo);

	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	Music = GetWorld()->SpawnActor<AMusic>(MusicClass[0], SpawnInfo);

	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	Environment = GetWorld()->SpawnActor<AEnvironment>(EnvironmentClass[0], SpawnInfo);

	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	Curve = GetWorld()->SpawnActor<ACurves>(CurvesClass[0], SpawnInfo);

	userClass = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

}

void AOrchestrator::SectionProgress()
{
	if (userProgress < ((timeLimit / currentSection) / 4)) {
		currentSection--;
	}
	else if (userProgress > ((timeLimit / currentSection) / 4)) {
		currentSection++;
	}
}

void AOrchestrator::SetBeatValues()
{

	wholeBeat = Beats->GetWholeBeat();
	halfBeat = Beats->GetHalfBeat();
	quarterBeat = Beats->GetQuarterBeat();
	eighthBeat = Beats->GetEighthBeat();

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT(" wholeBeat: %f "), wholeBeat));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT(" halfBeat: %f "), halfBeat));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT(" quarterBeat: %f "), quarterBeat));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT(" eighthBeat: %f "), eighthBeat));

}

void AOrchestrator::AggroUpdate()
{

	masterLocation = Master->GetCurrentLoc();
	userLocation = userClass->GetActorLocation();

}