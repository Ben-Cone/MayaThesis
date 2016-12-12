
#include "Maya.h"
#include "Engine.h"
#include "Beats.h"

ABeats::ABeats(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

	beats.Add(wholeBeat);
	beats.Add(halfBeat);
	beats.Add(quarterBeat);
	beats.Add(eighthBeat);

}

void ABeats::BeatCalculator(float deltaTime, float bpm)
{

	elapsedTime += deltaTime;

	beats[0] = (elapsedTime * (bpm / 60)) - FMath::Fmod(elapsedTime * (bpm / 60), 1);
	beats[1] = (elapsedTime * (bpm / 30)) - FMath::Fmod(elapsedTime * (bpm / 30), 1);
	beats[2] = (elapsedTime * (bpm / 15)) - FMath::Fmod(elapsedTime * (bpm / 15), 1);
	beats[3] = (elapsedTime * (bpm / 7.5)) - FMath::Fmod(elapsedTime * (bpm / 7.5), 1);

}

float ABeats::GetWholeBeat()
{
	return beats[0];
}

float ABeats::GetHalfBeat()
{
	return beats[1];
}

float ABeats::GetQuarterBeat()
{
	return beats[2];
}

float ABeats::GetEighthBeat()
{
	return beats[3];
}

void ABeats::UpdateTrigger(int eventIndex)
{

}