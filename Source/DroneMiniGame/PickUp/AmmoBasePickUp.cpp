// Fill out your copyright notice in the Description page of Project Settings.


#include "DroneMiniGame/PickUp/AmmoBasePickUp.h"
#include "DroneMiniGame/Character/DroneCharacter.h"

void AAmmoBasePickUp::Pickup(AActor* Picker)
{

	ADroneCharacter* Character = Cast<ADroneCharacter>(Picker);
	if (Character) {
		if (Character->Ammo== 100)return;
		Character->AddAmmo(TakeAmmo);
		Destroy();
	}
}
