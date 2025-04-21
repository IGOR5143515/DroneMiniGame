// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TurretAIController.generated.h"

class AProjectile;
class UAIPerceptionComponent;
UCLASS()
class DRONEMINIGAME_API ATurretAIController : public AAIController
{
	GENERATED_BODY()
public:
	ATurretAIController();
	void Shoot();
	
	virtual void BeginPlay();

	UFUNCTION()
	void OnTargetPerception(AActor* Actor, FAIStimulus Stimulus);

protected:
	AActor* CurrentTarget=nullptr;

	UPROPERTY(EditAnywhere)
	UAIPerceptionComponent* Perception;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AProjectile>ProjectileClass;


};
