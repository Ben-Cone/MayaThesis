
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
	static ConstructorHelpers::FObjectFinder<UMaterial> MatFinder(TEXT("Material'/Game/Unused/Cube/M_AnimPlane.M_AnimPlane'"));

}

void AAnimationsPlanar::BeginPlay()
{
	Super::BeginPlay();
	SpawnDefaultClasses();

}

void AAnimationsPlanar::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	timeDelta = DeltaTime;
	Update();

}

void AAnimationsPlanar::UpdateTrigger(int eventIndex)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("test")));
}

void AAnimationsPlanar::SpawnDefaultClasses()
{
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	ScaleCurve = GetWorld()->SpawnActor<ACurves>(CurvesClass[0], SpawnInfo);

	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	StrokeCurve = GetWorld()->SpawnActor<ACurves>(CurvesClass[0], SpawnInfo);

	Dynamic_000 = StaticMesh->CreateAndSetMaterialInstanceDynamic(0);

}

void AAnimationsPlanar::RotateShape(float rotationAngle)
{
	Dynamic_000->SetScalarParameterValue(FName("RotationAngle"), rotationAngle);
}

void AAnimationsPlanar::AnimationPicker(float fSpeed_in, int animType_in, int animCurve_in, float animSpeed_in, float lifeTime_in)
{
	fSpeed = fSpeed_in;
	animType = animType_in;
	animCurve = animCurve_in;
	animSpeed = animSpeed_in;
	lifeTime = lifeTime_in;
}

void AAnimationsPlanar::Update()
{
	lifeSpan += timeDelta;

	if (lifeSpan > lifeTime) {
		Destroy();
	}

	if (updateScale == true) {
		ScaleSquare(scaleStart, scaleEnd, scaleSeconds);
	}
	
	if (updateStroke == true) {
		StrokeSquare(strokeStart, strokeEnd, strokeSeconds);
	}

}

void AAnimationsPlanar::ScaleSquare(float start, float end, float seconds)
{
	scaleStart = start;
	scaleEnd = end;
	scaleSeconds = seconds;

	squareScale = FMath::Lerp(start, end, ScaleCurve->InterpAlongCurve(seconds, timeDelta, 0));

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("squareScale : %f"), squareScale));

	Dynamic_000->SetScalarParameterValue(FName("Rect_Scale_X"), squareScale);
	Dynamic_000->SetScalarParameterValue(FName("Rect_Scale_Y"), squareScale);

	updateScale = true;
}

void AAnimationsPlanar::StrokeSquare(float startWidth, float endWidth, float seconds)
{
	strokeStart = startWidth;
	strokeEnd = endWidth;
	strokeSeconds = seconds;

	strokeScale = FMath::Lerp(startWidth, endWidth, StrokeCurve->InterpAlongCurve(seconds, timeDelta, 0));

	Dynamic_000->SetScalarParameterValue(FName("Rect_Stroke"), strokeScale);

	updateStroke = true;
}
