// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TurretCharacter.generated.h"

class UStaticMeshComponent;

UCLASS()
class DRONEMINIGAME_API ATurretCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATurretCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:	
	
	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Turret")
	UStaticMeshComponent* Mesh1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Turret")
	UStaticMeshComponent* Mesh2;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Turret")
	UStaticMeshComponent* Mesh3;

};
