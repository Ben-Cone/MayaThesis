#pragma once

#include "GameFramework/Actor.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Curves.generated.h"

UCLASS()
class MAYA_API ACurves : public AActor
{
	GENERATED_BODY()
	
public:	

	ACurves(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;
	
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditDefaultsOnly, Category = "Curves")
		UTimelineComponent* Timeline_001;

	UPROPERTY(EditDefaultsOnly, Category = "Curves")
		UTimelineComponent* Timeline_Points;

	FOnTimelineFloat InterpFunction{};

	UFUNCTION(BlueprintImplementableEvent, Category = "Curves")
		void TestEvent(float pointOnCurve);

	UFUNCTION(BlueprintImplementableEvent, Category = "Curves")
		float InterpAlong(float speedX, float lengthSeconds, int curveType);

	UFUNCTION(BlueprintImplementableEvent, Category = "Curves")
		float InterpNotes(float points);

	// -- Note Probability -- //

	int NoteProbability(int noteType);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Notes)
		float noteProbability_1_i;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Notes)
		float noteProbability_1_ii;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Notes)
		float noteProbability_1_iii;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Notes)
		float noteProbability_1_iv;

	float noteProbability_1_sum;
	float note_1;
	int noteToPlay_1;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Notes)
		float noteProbability_2_i;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Notes)
		float noteProbability_2_ii;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Notes)
		float noteProbability_2_iii;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Notes)
		float noteProbability_2_iv;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Notes)
		float noteProbability_3_i;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Notes)
		float noteProbability_3_ii;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Notes)
		float noteProbability_3_iii;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Notes)
		float noteProbability_3_iv;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Notes)
		float noteProbability_4_i;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Notes)
		float noteProbability_4_ii;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Notes)
		float noteProbability_4_iii;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Notes)
		float noteProbability_4_iv;

	float interpInput;

	float time;

	bool i = true;

	UPROPERTY(EditAnywhere, Category = "Interpolation")
	float timeLength;

	float interpolated;

	float InterpAlongCurve(float lengthSeconds, float timeDelta, int curveType);

	void SetCurveStart(float startPoint);

	float GetInterpInput();

	// -- Math Functions -- //

	float InverseLerp(float A, float B, float Value);

	float DistanceBetweenFloats(float A, float B);

};
 