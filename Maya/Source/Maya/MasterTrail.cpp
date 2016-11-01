
#include "Maya.h"
#include "MasterTrail.h"


// Sets default values
AMasterTrail::AMasterTrail()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = RootNull;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMesh"));
	static ConstructorHelpers::FObjectFinder<UMaterial> MatFinder(TEXT("Material'/Game/Base_Trail.Base_Trail'"));

}

// Called when the game starts or when spawned
void AMasterTrail::BeginPlay()
{
	Super::BeginPlay();

	Death = FMath::FRandRange(.5f, 2.1f);

	GlitchReset = FMath::RandRange(3, 20);

	TimeAdjust = 0;

	ColorOverLife();
}

// Called every frame
void AMasterTrail::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	LifeTime += DeltaTime;

	if (LifeTime > Death)
	{
		Destroy();
	}

	if (TimeAdjust < 10) {
		TimeAdjust++;
	}
	else if (TimeAdjust == 10) {
		ColorOverLife();
		TimeAdjust = 0;
	}
}

void AMasterTrail::ColorOverLife()
{
	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, FString::Printf(TEXT("%f"), RandomPanValue.Y));


	if (GlitchCurrent < GlitchReset) {
		GlitchCurrent++;
	}
	else if (GlitchCurrent == GlitchReset) {
		GlitchReset = FMath::RandRange(20, 600);

		RandomPanValue = FVector(0.f, FMath::RandRange(0.f, 1.f), 0.f);

		GlitchCurrent = 0;
	}


	UMaterialInstanceDynamic* DynamicMatInstance = StaticMesh->CreateAndSetMaterialInstanceDynamic(0);

	if (LifeTime > Death - (Death / 4))
	{
		TextureSwitch_03 = 1;
		OutColor = FVector(0.f, .75f, .94f);
		DynamicMatInstance->SetScalarParameterValue(FName("TextureSwitch_03"), TextureSwitch_03);
	}
	else if (LifeTime > Death / 2)
	{
		TextureSwitch_02 = 1;
		OutColor = FVector(.59f, .045f, .84f);
		DynamicMatInstance->SetScalarParameterValue(FName("TextureSwitch_02"), TextureSwitch_02);
	}
	else if (LifeTime > Death / 6)
	{
		TextureSwitch_01 = 1;
		OutColor = FVector(.84f * 5, .38f, .64f);
		DynamicMatInstance->SetScalarParameterValue(FName("TextureSwitch_01"), TextureSwitch_01);
	}
	else
	{
		OutColor = FVector(2.8f, 2.8f, 2.8f);
	}

	DynamicMatInstance->SetVectorParameterValue(FName("ColorOverLife"), OutColor);
	DynamicMatInstance->SetVectorParameterValue(FName("GlitchPanner"), RandomPanValue);

}