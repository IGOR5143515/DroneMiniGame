
#include "DroneMiniGame/PickUp/HealthPickUp.h"
#include "DroneMiniGame/Character/DroneCharacter.h"
#include "DroneMiniGame/Components/HealthComponent.h"
void AHealthPickUp::Pickup(AActor* Picker)
{
	ADroneCharacter* Character = Cast<ADroneCharacter>(Picker);
	if (Character) {
		if (Character->HealthComponent->Health == Character->HealthComponent->MaxHealth)return;

		Character->HealthComponent->AddHealth(Heal);
		Destroy();
	}


}
