
#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TurretAIController.generated.h"

class AProjectile;
class UAIPerceptionComponent;
class UAISenseConfig_Sight;
UCLASS()
class DRONEMINIGAME_API ATurretAIController : public AAIController
{
	GENERATED_BODY()
public:
	ATurretAIController();
	void Shoot();
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay();

	UFUNCTION()
	void OnTargetPerception(AActor* Actor, FAIStimulus Stimulus);

protected:
	AActor* CurrentTarget=nullptr;

	UPROPERTY(EditAnywhere)
	UAIPerceptionComponent* Perception;

	UPROPERTY()
	UAISenseConfig_Sight* SightConfig;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AProjectile>ProjectileClass;

	FTimerHandle Timer;
};
