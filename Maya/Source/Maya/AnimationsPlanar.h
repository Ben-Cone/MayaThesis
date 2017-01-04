
#pragma once

#include "GameFramework/Actor.h"
#include "Listener.h"
#include "AnimationsPlanar.generated.h"

UCLASS()
class MAYA_API AAnimationsPlanar : public AListener
{
	GENERATED_UCLASS_BODY()
	
public:	

	AAnimationsPlanar();

	virtual void BeginPlay() override;
	
	virtual void Tick( float DeltaSeconds ) override;

	void UpdateTrigger(int eventIndex) override;

	UPROPERTY(EditAnywhere, Category = Spawn)
		USphereComponent* RootNull;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* StaticMesh;

	FVector maskScale;

	UMaterialInstanceDynamic* Dynamic_000;

	void RotateShape(float rotationAngle);


	UPROPERTY(EditAnywhere, Category = "Master Spawn")
		TArray<TSubclassOf<class ACurves> > CurvesClass;
	FActorSpawnParameters SpawnInfo;
	float timeDelta;
	void SpawnDefaultClasses();

	float interpValue;
	float rotation;
	float rotator;
	UPROPERTY(EditDefaultsOnly, Category = "Speed")
		float distanceMultiplier;
	UPROPERTY(EditDefaultsOnly, Category = "Speed")
		float lengthSeconds;

	ACurves* ScaleCurve;
	ACurves* StrokeCurve;
	
	TArray<ACurves*> CurveArray;

	void AnimationPicker(float fSpeed_in, int animType_in, int animCurve_in, float animSpeed_in, float lifetime_in);
	void Update();

	void ScaleSquare(float start, float end, float seconds);
	float squareScale;

	void StrokeSquare(float startWidth, float endWidth, float seconds);
	float strokeScale;

	float fSpeed;
	int animType;
	int animCurve;
	float animSpeed;
	float lifeTime;
	float lifeSpan;
	float decayingRepeater;

	bool updateStroke;
	float strokeStart;
	float strokeEnd;
	float strokeSeconds;
	//
	bool updateScale;
	float scaleStart;
	float scaleEnd;
	float scaleSeconds;

};
