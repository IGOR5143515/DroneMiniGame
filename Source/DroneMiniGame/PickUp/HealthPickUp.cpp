// Fill out your copyright notice in the Description page of Project Settings.


#include "DroneMiniGame/PickUp/HealthPickUp.h"
#include "DroneMiniGame/Character/DroneCharacter.h"
#include "DroneMiniGame/Components/HealthComponent.h"
void AHealthPickUp::Pickup(AActor* Picker)
{
	ADroneCharacter* Character = Cast<ADroneCharacter>(Picker);
	if (Character) {
		Character->HealthComponent->AddHealth(Heal);
	}


}
