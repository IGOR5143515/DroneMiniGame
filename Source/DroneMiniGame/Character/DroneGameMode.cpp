// Fill out your copyright notice in the Description page of Project Settings.


#include "DroneMiniGame/Character/DroneGameMode.h"
#include "DroneMiniGame/Character/DroneCharacter.h"


ADroneGameMode::ADroneGameMode()
{

	DefaultPawnClass = ADroneCharacter::StaticClass();
}
	
