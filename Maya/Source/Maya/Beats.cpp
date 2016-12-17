
#include "Maya.h"
#include "Engine.h"
#include "Beats.h"

ABeats::ABeats(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	previousBeat.Add(previousWholeBeat = 0);
	previousBeat.Add(previousHalfBeat = 0);
	previousBeat.Add(previousQuarterBeat = 0);
	previousBeat.Add(previousEighthBeat = 0);

	currentBeat.Add(wholeBeat = 0);
	currentBeat.Add(halfBeat = 0);
	currentBeat.Add(quarterBeat = 0);
	currentBeat.Add(eighthBeat = 0);
}

void ABeats::BeatCalculator(float deltaTime, float bpm)
{

	elapsedTime += deltaTime;

	currentBeat[0] = (elapsedTime * (bpm / 60)) - FMath::Fmod(elapsedTime * (bpm / 60), 1);
	currentBeat[1] = (elapsedTime * (bpm / 30)) - FMath::Fmod(elapsedTime * (bpm / 30), 1);
	currentBeat[2] = (elapsedTime * (bpm / 15)) - FMath::Fmod(elapsedTime * (bpm / 15), 1);
	currentBeat[3] = (elapsedTime * (bpm / 7.5)) - FMath::Fmod(elapsedTime * (bpm / 7.5), 1);

	// -- iterate through each beat and trigger on beat

	for (int i = 0; i < currentBeat.Num(); i++) {

		if (currentBeat[0] > previousBeat[0]) {

			// -- TRIGGER -- //
			
			previousBeat[0] += 1.f;
		}
	}


	// -- //


	//if (currentBeat[0] > previousBeat[0]) {
	//	beat[0] = 1;
	//	previousBeat[0] += 1.f;
	//}

	//if (currentBeat[1] > previousBeat[1]) {
	//	if (beat[1] == 2.f) {
	//		beat[1] = 0.f;
	//		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT(" 1/2 ")));
	//		// -- TRIGGER -- //
	//	}
	//	else if (currentBeat[1] < 2) {
	//		beat[1] += 1.f;
	//		previousBeat[0] += 1.f;
	//	}

	//}

	//if (currentBeat[2] > previousBeat[2]) {
	//	if (beat[2] == 4.f) {
	//		beat[2] = 0.f;
	//		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT(" 1/4 ")));
	//		// -- TRIGGER -- //
	//	}
	//	else {
	//		beat[2] += 1.f;
	//		previousBeat[0] += 1.f;
	//	}

	//}

	//if (currentBeat[3] > previousBeat[3]) {
	//	if (beat[3] == 8.f) {
	//		beat[3] = 0.f;
	//		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT(" 1/8 ")));
	//		// -- TRIGGER -- //
	//	}
	//	else {
	//		beat[3] += 1.f;
	//		previousBeat[0] += 1.f;
	//	}

	//}
}

float ABeats::GetWholeBeat()
{
	return currentBeat[0];
}

float ABeats::GetHalfBeat()
{
	return currentBeat[1];
}

float ABeats::GetQuarterBeat()
{
	return currentBeat[2];
}

float ABeats::GetEighthBeat()
{
	return currentBeat[3];
}

void ABeats::UpdateTrigger(int eventIndex)
{

}