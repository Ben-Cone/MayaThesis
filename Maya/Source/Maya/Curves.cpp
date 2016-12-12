#include "Maya.h"
#include "Engine.h"
#include "Curves.h"

ACurves::ACurves(const FObjectInitializer& ObjectInitializer)
{
 	
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UCurveFloat> Curve1(TEXT("CurveFloat'/Game/Unused/Curves/FCurve_001.FCurve_001'"));
	FCurve_001 = Curve1.Object;

	static ConstructorHelpers::FObjectFinder<UCurveFloat> Curve2(TEXT("CurveFloat'/Game/Unused/Curves/FCurve_002.FCurve_002'"));
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

void ACurves::BeginPlay()
{
	Super::BeginPlay();
	
}

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

float ACurves::InverseLerp(float A, float B, float Value)
{
	if (FMath::IsNearlyEqual(A, B))
	{
		if (Value < A)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
	else
	{
		return ((Value - A) / (B - A));
	}
}
