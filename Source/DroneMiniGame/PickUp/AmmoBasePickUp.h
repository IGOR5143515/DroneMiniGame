// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DroneMiniGame/PickUp/BasePickUp.h"
#include "AmmoBasePickUp.generated.h"

/**
 * 
 */
UCLASS()
class DRONEMINIGAME_API AAmmoBasePickUp : public ABasePickUp
{
	GENERATED_BODY()
public:
	virtual void Pickup(AActor* Picker)override;

	UPROPERTY(EditDefaultsOnly, Category = "Ammo")
	float TakeAmmo=10.0f;


	
};
