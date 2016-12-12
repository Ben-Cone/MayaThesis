
#pragma once

#include "GameFramework/Actor.h"
#include "Listener.h"
#include "Music.generated.h"

UCLASS()
class MAYA_API AMusic : public AListener
{
	GENERATED_UCLASS_BODY()
	
public:	

	virtual void BeginPlay() override;
	
	virtual void Tick( float DeltaSeconds ) override;

	void UpdateTrigger(int eventIndex) override;
	
};
