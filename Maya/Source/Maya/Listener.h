// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Listener.generated.h"

UCLASS(Abstract, Blueprintable)
class AListener : public AActor
{
	GENERATED_UCLASS_BODY()

public:
	virtual void UpdateTrigger(int eventIndex);

};
