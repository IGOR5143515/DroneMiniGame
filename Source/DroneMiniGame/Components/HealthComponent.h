
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DRONEMINIGAME_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UHealthComponent();

protected:

	virtual void BeginPlay() override;

public:	

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

	UFUNCTION(BlueprintCallable)
	float GetPercent();
		
};
