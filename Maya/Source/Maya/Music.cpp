
#include "Maya.h"
#include "Engine.h"
#include "Music.h"


AMusic::AMusic(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

	PrimaryActorTick.bCanEverTick = true;

	// -- Section 1

	note_1_i = CreateDefaultSubobject<UAudioComponent>(TEXT("note_1_i"));
	note_1_i->bAutoActivate = false;
	note_1_ii = CreateDefaultSubobject<UAudioComponent>(TEXT("note_1_ii"));
	note_1_ii->bAutoActivate = false;
	note_1_iii = CreateDefaultSubobject<UAudioComponent>(TEXT("note_1_iii"));
	note_1_iii->bAutoActivate = false;
	note_1_iv = CreateDefaultSubobject<UAudioComponent>(TEXT("note_1_iv"));
	note_1_iv->bAutoActivate = false;

	// -- Section 2

	note_2_i = CreateDefaultSubobject<UAudioComponent>(TEXT("note_2_i"));
	note_2_i->bAutoActivate = false;
	note_2_ii = CreateDefaultSubobject<UAudioComponent>(TEXT("note_2_ii"));
	note_2_ii->bAutoActivate = false;
	note_2_iii = CreateDefaultSubobject<UAudioComponent>(TEXT("note_2_iii"));
	note_2_iii->bAutoActivate = false;
	note_2_iv = CreateDefaultSubobject<UAudioComponent>(TEXT("note_2_iv"));
	note_2_iv->bAutoActivate = false;

	// -- Section 3

	note_3_i = CreateDefaultSubobject<UAudioComponent>(TEXT("note_3_i"));
	note_3_i->bAutoActivate = false;
	note_3_ii = CreateDefaultSubobject<UAudioComponent>(TEXT("note_3_ii"));
	note_3_ii->bAutoActivate = false;
	note_3_iii = CreateDefaultSubobject<UAudioComponent>(TEXT("note_3_iii"));
	note_3_iii->bAutoActivate = false;
	note_3_iv = CreateDefaultSubobject<UAudioComponent>(TEXT("note_3_iv"));
	note_3_iv->bAutoActivate = false;

	// -- Section 4

	note_4_i = CreateDefaultSubobject<UAudioComponent>(TEXT("note_4_i"));
	note_4_i->bAutoActivate = false;
	note_4_ii = CreateDefaultSubobject<UAudioComponent>(TEXT("note_4_ii"));
	note_4_ii->bAutoActivate = false;
	note_4_iii = CreateDefaultSubobject<UAudioComponent>(TEXT("note_4_iii"));
	note_4_iii->bAutoActivate = false;
	note_4_iv = CreateDefaultSubobject<UAudioComponent>(TEXT("note_4_iv"));
	note_4_iv->bAutoActivate = false;

}

void AMusic::BeginPlay()
{
	Super::BeginPlay();
	InitializeSounds();

}

void AMusic::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("array length: %d"), noteArray.Num()));

}

void AMusic::UpdateTrigger(int eventIndex)
{
	noteArray[eventIndex]->Play();
}

void AMusic::InitializeSounds()
{

	// -- Section 1

	note_1_i->SetSound(cue_1_i);
	noteArray.Add(note_1_i);
	note_1_ii->SetSound(cue_1_ii);
	noteArray.Add(note_1_ii);
	note_1_iii->SetSound(cue_1_ii);
	noteArray.Add(note_1_iii);
	note_1_iv->SetSound(cue_1_iv);
	noteArray.Add(note_1_iv);

	// -- Section 2

	note_2_i->SetSound(cue_2_i);
	noteArray.Add(note_2_i);
	note_2_ii->SetSound(cue_2_ii);
	noteArray.Add(note_2_ii);
	note_2_iii->SetSound(cue_2_iii);
	noteArray.Add(note_2_iii);
	note_2_iv->SetSound(cue_2_iv);
	noteArray.Add(note_2_iv);

	// -- Section 3

	note_3_i->SetSound(cue_3_i);
	noteArray.Add(note_3_i);
	note_3_ii->SetSound(cue_3_ii);
	noteArray.Add(note_3_ii);
	note_3_iii->SetSound(cue_3_iii);
	noteArray.Add(note_3_iii);
	note_3_iv->SetSound(cue_3_iv);
	noteArray.Add(note_3_iv);

	// -- Section 4

	note_4_i->SetSound(cue_4_i);
	noteArray.Add(note_4_i);
	note_4_ii->SetSound(cue_4_ii);
	noteArray.Add(note_4_ii);
	note_4_iii->SetSound(cue_4_iii);
	noteArray.Add(note_4_iii);
	note_4_iv->SetSound(cue_4_iv);
	noteArray.Add(note_4_iv);




}

