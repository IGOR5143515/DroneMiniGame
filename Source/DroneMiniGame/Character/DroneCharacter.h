// Fill out your copyright notice in the Description page of Project Settings.

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
	// Sets default values for this character's properties
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
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual FGenericTeamId GetGenericTeamId() const override { return TeamID; }
};
