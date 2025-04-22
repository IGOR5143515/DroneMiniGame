// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DRONEMINIGAME_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	const float MaxHealth = 100;
	float Health = 100;

	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, 
		float Damage, 
		const UDamageType* DamageType,
		AController* InstigatedBy,
		AActor* DamageCauser);

	void OnDeath();

	void AddHealth(float Value);

	float GetPercent();
		
};
