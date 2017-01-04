
#include "Maya.h"
#include "Engine.h"
#include "Spectrum.h"

ASpectrum::ASpectrum(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void ASpectrum::UpdateTrigger(int eventIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT(" test ")));
}

int ASpectrum::UserProgress(float pts, float maxPts)
{

	points = pts;
	maxPoints = maxPts;

	if (points == 0) {
		currentSection = 0;
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT(" 0 ")));
	}
	else if (points > 0 && points < (maxPoints / 4)) {
		currentSection = 1;
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT(" 1 ")));
	}
	else if (points >= (maxPoints / 4) && points < (maxPoints / 4) * 2) {
		currentSection = 2;
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT(" 2 ")));
	}
	else if (points >= (maxPoints / 4) * 2 && points < (maxPoints / 4) * 3) {
		currentSection = 3;
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT(" 3 ")));
	}
	else if (points >= (maxPoints / 4) * 3 && points < maxPoints) {
		currentSection = 4;
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT(" 4 ")));
	}
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT(" current section	: %d "), currentSection));
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT(" points: %f "), points));

	return currentSection;


}

void ASpectrum::Section0()
{

}