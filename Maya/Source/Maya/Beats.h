
#pragma once

#include "GameFramework/Actor.h"
#include "Listener.h"
#include "Beats.generated.h"

UCLASS()
class MAYA_API ABeats : public AListener
{
	GENERATED_UCLASS_BODY()
	
public:	

	void UpdateTrigger(int eventIndex) override;

	float elapsedTime;

	void BeatCalculator(float deltaTime, float bpm);
	float GetWholeBeat();
	float GetHalfBeat();
	float GetQuarterBeat();
	float GetEighthBeat();

	TArray<float> currentBeat;
	float wholeBeat;
	float halfBeat;
	float quarterBeat;
	float eighthBeat;

	TArray<float> previousBeat;
	float previousWholeBeat;
	float previousHalfBeat;
	float previousQuarterBeat;
	float previousEighthBeat;

	
	
};
