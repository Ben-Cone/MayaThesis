
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

	UPROPERTY(EditAnywhere, Category = "Notes")
	USoundCue* cue_1_i;

	UPROPERTY(EditAnywhere, Category = "Notes")
	USoundCue* cue_1_ii;

	UPROPERTY(EditAnywhere, Category = "Notes")
	USoundCue* cue_1_iii;
	
	UPROPERTY(EditAnywhere, Category = "Notes")
	USoundCue* cue_1_iv;

	UPROPERTY(EditAnywhere, Category = "Notes")
	USoundCue* cue_2_i;

	UPROPERTY(EditAnywhere, Category = "Notes")
	USoundCue* cue_2_ii;

	UPROPERTY(EditAnywhere, Category = "Notes")
	USoundCue* cue_2_iii;
	
	UPROPERTY(EditAnywhere, Category = "Notes")
	USoundCue* cue_2_iv;

	UPROPERTY(EditAnywhere, Category = "Notes")
	USoundCue* cue_3_i;

	UPROPERTY(EditAnywhere, Category = "Notes")
	USoundCue* cue_3_ii;

	UPROPERTY(EditAnywhere, Category = "Notes")
	USoundCue* cue_3_iii;
	
	UPROPERTY(EditAnywhere, Category = "Notes")
	USoundCue* cue_3_iv;

	UPROPERTY(EditAnywhere, Category = "Notes")
	USoundCue* cue_4_i;

	UPROPERTY(EditAnywhere, Category = "Notes")
	USoundCue* cue_4_ii;

	UPROPERTY(EditAnywhere, Category = "Notes")
	USoundCue* cue_4_iii;

	UPROPERTY(EditAnywhere, Category = "Notes")
	USoundCue* cue_4_iv;
	
	UAudioComponent* note_1_i;
	UAudioComponent* note_1_ii;
	UAudioComponent* note_1_iii;
	UAudioComponent* note_1_iv;
	
	UAudioComponent* note_2_i;
	UAudioComponent* note_2_ii;
	UAudioComponent* note_2_iii;
	UAudioComponent* note_2_iv;
	
	UAudioComponent* note_3_i;
	UAudioComponent* note_3_ii;
	UAudioComponent* note_3_iii;
	UAudioComponent* note_3_iv;
	
	UAudioComponent* note_4_i;
	UAudioComponent* note_4_ii;
	UAudioComponent* note_4_iii;
	UAudioComponent* note_4_iv;

	TArray<UAudioComponent*> noteArray;


	int delay = 0;

	void InitializeSounds();


};
