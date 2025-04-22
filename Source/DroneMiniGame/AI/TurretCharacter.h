

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TurretCharacter.generated.h"

class UStaticMeshComponent;
class UHealthComponent;

UCLASS()
class DRONEMINIGAME_API ATurretCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	ATurretCharacter();

protected:
	
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:	
	
	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Turret")
	UStaticMeshComponent* Mesh1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Turret")
	UStaticMeshComponent* Mesh2;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Turret")
	UStaticMeshComponent* Mesh3;

	UHealthComponent* HealthComponent;

};
