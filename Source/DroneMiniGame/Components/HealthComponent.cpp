
#include "DroneMiniGame/Components/HealthComponent.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	if (AActor* Owner = GetOwner())
	{
		Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnTakeAnyDamage);
	}

}

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
	Health = FMath::Clamp(Health-Damage, 0, MaxHealth);

	if (Health <= 0.0f)
		OnDeath();
}

void UHealthComponent::OnDeath()
{
	AActor* Owner = GetOwner();
	Owner->Destroy();
}

void UHealthComponent::AddHealth(float Value)
{
	Health = FMath::Clamp(Health + Value, 0, MaxHealth);
}

float UHealthComponent::GetPercent()
{
	return Health/MaxHealth;
}

