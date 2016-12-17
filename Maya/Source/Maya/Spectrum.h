
#pragma once

#include "GameFramework/Actor.h"
#include "Listener.h"
#include "Spectrum.generated.h"

UCLASS()
class MAYA_API ASpectrum : public AListener
{
	GENERATED_UCLASS_BODY()
	
public:	

	void UpdateTrigger(int eventIndex) override;
	
	int ASpectrum::UserProgress(float pts, float maxPts);

	float points;
	float maxPoints;
	int currentSection;

	void Section0();



};
