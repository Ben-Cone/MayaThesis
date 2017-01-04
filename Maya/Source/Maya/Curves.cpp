#include "Maya.h"
#include "Engine.h"
#include "Curves.h"

ACurves::ACurves(const FObjectInitializer& ObjectInitializer)
{
 	
	PrimaryActorTick.bCanEverTick = true;

	Timeline_001 = ObjectInitializer.CreateDefaultSubobject<UTimelineComponent>(this, TEXT("timeline"));

	InterpFunction.BindUFunction(this, FName{ TEXT("TimelineFloatReturn") });

}

void ACurves::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACurves::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("noteProbability_1_i: %f "), noteProbability_1_i));
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("noteProbability_1_ii: %f "), noteProbability_1_ii));
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("noteProbability_1_iii: %f "), noteProbability_1_iii));
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("noteProbability_1_iv: %f "), noteProbability_1_iv));

}

float ACurves::InterpAlongCurve(float lengthSeconds, float timeDelta, int curveType)
{

	time += timeDelta;
	interpInput += timeDelta;

	interpolated = this->InterpAlong(interpInput, lengthSeconds, curveType);

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("time: %f "), interpolated));

	return interpolated;

}

float ACurves::GetInterpInput()
{
	return interpInput;
}

void ACurves::SetCurveStart(float startPoint)
{
	interpInput = startPoint;
}

// -- MATH -- //

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

int ACurves::NoteProbability(int section)
{
	switch (section) {

	case 1:

		noteProbability_1_sum =
			noteProbability_1_i
			+ noteProbability_1_ii
			+ noteProbability_1_iii
			+ noteProbability_1_iv;

		note_1 = FMath::RandRange(0.f, noteProbability_1_sum);

		if (note_1 < noteProbability_1_i) {
			noteToPlay_1 = 0;
		}
		else if (note_1  >= noteProbability_1_i && note_1 < (noteProbability_1_ii + noteProbability_1_i)) {
			noteToPlay_1 = 1;
		}
		else if (note_1 >= (noteProbability_1_ii + noteProbability_1_i) && note_1 < (noteProbability_1_iii + noteProbability_1_ii + noteProbability_1_i)) {
			noteToPlay_1 = 2;
		}
		else if (note_1 >= (noteProbability_1_sum - noteProbability_1_iv)) {
			noteToPlay_1 = 3;
		}

		break;
	}

	return noteToPlay_1;

}

float ACurves::DistanceBetweenFloats(float A, float B)
{
	if (A > B) {
		return (FMath::Abs(A) - FMath::Abs(B));
	}
	else {
		return (FMath::Abs(B) - FMath::Abs(A));
	}

}