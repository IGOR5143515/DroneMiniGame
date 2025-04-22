
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "GenericTeamAgentInterface.h"
#include "DroneCharacter.generated.h"

class UInputMappingContext;
class UInputAction;
class UCameraComponent;
class UStaticMeshComponent;
class UFloatingPawnMovement;
class UHealthComponent;
class AProjectile;
class UDroneWidget;

UCLASS()
class DRONEMINIGAME_API ADroneCharacter : public ACharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	
	ADroneCharacter();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputMappingContext* DroneInputMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* LookAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* AscendDescend;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* ShootAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	UHealthComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AProjectile>ProjectileClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = "Ammo")
	float Ammo = 100.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Ammo")
	float MaxAmmo = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UDroneWidget> WidgetClass;

	void AddAmmo(float Value);

	FGenericTeamId TeamID;

	void Shoot();
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Ascend_Descend(const FInputActionValue& Value);

protected:
	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual FGenericTeamId GetGenericTeamId() const override { return TeamID; }
};
