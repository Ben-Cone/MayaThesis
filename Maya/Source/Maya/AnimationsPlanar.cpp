
#include "Maya.h"
#include "Curves.h"
#include "Engine.h"
#include "Kismet/KismetMathLibrary.h"
#include "AnimationsPlanar.h"

AAnimationsPlanar::AAnimationsPlanar(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = RootNull;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMesh"));
	static ConstructorHelpers::FObjectFinder<UMaterial> MatFinder(TEXT("Material'/Game/Unused/Cube/AP_Circles.AP_Circles'"));

}

void AAnimationsPlanar::BeginPlay()
{
	Super::BeginPlay();
	SpawnDefaultClasses();

	//Dynamic_001->SetScalarParameterValue(FName("OnOff"), 1.f);
	//Dynamic_000->SetScalarParameterValue(FName("OnOff"), 1.f);
	//Dynamic_000->SetScalarParameterValue(FName("circleLineWeight"), 1.f);
}

void AAnimationsPlanar::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	timeDelta = DeltaTime;

	//interpValue = Curve->InterpAlongCurve(lengthSeconds, timeDelta, 0);
	//
	//maskScale.X = interpValue * 2;
	//maskScale.Y = interpValue * 2;

	//Dynamic_000->SetVectorParameterValue(FName("CircleMaskScale"), FLinearColor(maskScale.X, maskScale.Y, 0.f, 0.f));

	//rotator += .001;

	//RotateShape(rotator);

}

void AAnimationsPlanar::UpdateTrigger(int eventIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("test")));
}

void AAnimationsPlanar::SpawnDefaultClasses()
{
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	Curve = GetWorld()->SpawnActor<ACurves>(CurvesClass[0], SpawnInfo);

	Curve->SetCurveType(0);

	Dynamic_000 = StaticMesh->CreateAndSetMaterialInstanceDynamic(0);
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

void AAnimationsPlanar::AnimationPicker(int animIndex)
{
	switch (animIndex)

		case 0: 
			Dynamic_001->SetScalarParameterValue(FName("OnOff"), 1);
}
