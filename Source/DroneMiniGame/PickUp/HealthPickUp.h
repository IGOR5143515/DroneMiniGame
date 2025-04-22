// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DroneMiniGame/PickUp/BasePickUp.h"
#include "HealthPickUp.generated.h"

/**
 * 
 */
UCLASS()
class DRONEMINIGAME_API AHealthPickUp : public ABasePickUp
{
	GENERATED_BODY()
public:

	virtual void Pickup(AActor* Picker)override;
};
