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
		UCurveFloat* FCurve_001;

	UPROPERTY(EditDefaultsOnly, Category = "Curves")
		UCurveFloat* FCurve_002;

	FOnTimelineFloat InterpFunction{};

	UFUNCTION(BlueprintImplementableEvent, Category = "Curves")
		void TestEvent(float pointOnCurve);

	UFUNCTION(BlueprintImplementableEvent, Category = "Curves")
		float InterpAlong(float speedX, float lengthSeconds, int curveType);
	
	void SetCurveType(int curveType);

	float interpInput;

	float time;

	bool i = true;

	UPROPERTY(EditAnywhere, Category = "Interpolation")
	float timeLength;

	float interpolated;

	float InterpAlongCurve(float lengthSeconds, float timeDelta, int curveType);

	TArray<UCurveFloat*> curveArray;

	int curveIndex;

	// -- Math Functions -- //

	float InverseLerp(float A, float B, float Value);

};
 