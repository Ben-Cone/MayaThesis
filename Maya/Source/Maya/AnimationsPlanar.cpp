// Fill out your copyright notice in the Description page of Project Settings.

#include "Maya.h"
#include "Curves.h"
#include "Engine.h"
#include "Kismet/KismetMathLibrary.h"
#include "AnimationsPlanar.h"


// Sets default values
AAnimationsPlanar::AAnimationsPlanar()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = RootNull;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMesh"));
	static ConstructorHelpers::FObjectFinder<UMaterial> MatFinder(TEXT("Material'/Game/Cube/AP_Circles.AP_Circles'"));

}

// Called when the game starts or when spawned
void AAnimationsPlanar::BeginPlay()
{
	Super::BeginPlay();
	SpawnDefaultClasses();

}

// Called every frame
void AAnimationsPlanar::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	timeDelta = DeltaTime;

	interpValue = Curve->InterpAlongCurve(lengthSeconds, timeDelta, 0);
	
	maskScale.X = interpValue * 2;
	maskScale.Y = interpValue * 2;

	Dynamic_Circle->SetVectorParameterValue(FName("CircleMaskScale"), maskScale);

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT(" current location : %f"), interpValue));

	rotator += .001;

	RotateShape(rotator);

}

void AAnimationsPlanar::SpawnDefaultClasses()
{
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	Curve = GetWorld()->SpawnActor<ACurves>(CurvesClass[0], SpawnInfo);

	Curve->SetCurveType(0);

	Dynamic_Circle = StaticMesh->CreateAndSetMaterialInstanceDynamic(0);
	Dynamic_001 = StaticMesh->CreateAndSetMaterialInstanceDynamic(1);
	Dynamic_002 = StaticMesh->CreateAndSetMaterialInstanceDynamic(2);
	Dynamic_003 = StaticMesh->CreateAndSetMaterialInstanceDynamic(3);
	Dynamic_004 = StaticMesh->CreateAndSetMaterialInstanceDynamic(4);
	Dynamic_005 = StaticMesh->CreateAndSetMaterialInstanceDynamic(5);
	Dynamic_006 = StaticMesh->CreateAndSetMaterialInstanceDynamic(6);
	Dynamic_007 = StaticMesh->CreateAndSetMaterialInstanceDynamic(7);
	Dynamic_008 = StaticMesh->CreateAndSetMaterialInstanceDynamic(8);
	Dynamic_009 = StaticMesh->CreateAndSetMaterialInstanceDynamic(9);

}

void AAnimationsPlanar::RotateShape(float rotationAngle)
{
	Dynamic_001->SetScalarParameterValue(FName("RotationAngle"), rotationAngle);
}