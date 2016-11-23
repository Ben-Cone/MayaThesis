#include "Maya.h"
#include "Curves.h"


// Sets default values
ACurves::ACurves(const FObjectInitializer& ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UCurveFloat> Curve(TEXT("CurveFloat'/Game/Curves/FCurve_001.FCurve_001'"));
	if (Curve.Object)
	{
		FCurve_001 = Curve.Object;
	}

	Timeline_001 = ObjectInitializer.CreateDefaultSubobject<UTimelineComponent>(this, TEXT("timeline"));

	InterpFunction.BindUFunction(this, FName{ TEXT("TimelineFloatReturn") });


}

// Called when the game starts or when spawned
void ACurves::BeginPlay()
{
	Super::BeginPlay();
	
	Timeline_001->AddInterpFloat(FCurve_001, InterpFunction, FName{ TEXT("InterpFloat") });

}

// Called every frame
void ACurves::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

float ACurves::InterpAlongCurve(float lengthSeconds, float timeDelta)
{

	time += timeDelta;
	interpInput += timeDelta;

	interpolated = this->InterpAlong(interpInput, lengthSeconds);

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("time: %f "), interpolated));

	return interpolated;

}

