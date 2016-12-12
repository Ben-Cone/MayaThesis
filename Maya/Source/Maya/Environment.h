
#pragma once

#include "GameFramework/Actor.h"
#include "Listener.h"
#include "Environment.generated.h"

UCLASS()
class MAYA_API AEnvironment : public AListener
{
	GENERATED_UCLASS_BODY()
	
public:	

	virtual void BeginPlay() override;
	
	virtual void Tick( float DeltaSeconds ) override;

	void UpdateTrigger(int eventIndex) override;
	
};
