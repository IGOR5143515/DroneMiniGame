
#pragma once

#include "CoreMinimal.h"
#include "DroneMiniGame/PickUp/BasePickUp.h"
#include "HealthPickUp.generated.h"

UCLASS()
class DRONEMINIGAME_API AHealthPickUp : public ABasePickUp
{
	GENERATED_BODY()
public:

	virtual void Pickup(AActor* Picker)override;

	UPROPERTY(EditDefaultsOnly)
	float Heal = 10;
};
