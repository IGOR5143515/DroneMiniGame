// Fill out your copyright notice in the Description page of Project Settings.


#include "DroneMiniGame/Components/HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}

void UHealthComponent::OnTakeAnyDamage(AActor* DamagedActor,
	float Damage, 
	const UDamageType* DamageType, 
	AController* InstigatedBy, 
	AActor* DamageCauser)
{
	MaxHealth = FMath::Clamp(MaxHealth-Damage, 0, 100);

	if (MaxHealth <= 0.0f)
		OnDeath();
}

void UHealthComponent::OnDeath()
{
}

float UHealthComponent::GetPercent()
{
	return MaxHealth/100;
}

