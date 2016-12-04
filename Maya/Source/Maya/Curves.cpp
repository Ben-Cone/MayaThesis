#include "Maya.h"
#include "Engine.h"
#include "Curves.h"


// Sets default values
ACurves::ACurves(const FObjectInitializer& ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UCurveFloat> Curve1(TEXT("CurveFloat'/Game/Curves/FCurve_001.FCurve_001'"));
	FCurve_001 = Curve1.Object;

	static ConstructorHelpers::FObjectFinder<UCurveFloat> Curve2(TEXT("CurveFloat'/Game/Curves/FCurve_002.FCurve_002'"));
	FCurve_002 = Curve2.Object;


	curveArray.Add(FCurve_001);
	curveArray.Add(FCurve_002);

	curveIndex = curveArray.Num();

	Timeline_001 = ObjectInitializer.CreateDefaultSubobject<UTimelineComponent>(this, TEXT("timeline"));

	InterpFunction.BindUFunction(this, FName{ TEXT("TimelineFloatReturn") });

}

void ACurves::SetCurveType(int curveType)
{
	Timeline_001->AddInterpFloat(curveArray[curveType], InterpFunction, FName{ TEXT("InterpFloat") });
}
// Called when the game starts or when spawned
void ACurves::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACurves::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

float ACurves::InterpAlongCurve(float lengthSeconds, float timeDelta, int curveType)
{

	time += timeDelta;
	interpInput += timeDelta;

	interpolated = this->InterpAlong(interpInput, lengthSeconds, curveType);

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("time: %f "), interpolated));

	return interpolated;

}



