// Fill out your copyright notice in the Description page of Project Settings.


#include "DroneMiniGame/AI/TurretCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "DroneMiniGame/Components/HealthComponent.h"

// Sets default values
ATurretCharacter::ATurretCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh1 = CreateDefaultSubobject<UStaticMeshComponent>("Mesh1");
	Mesh1->SetupAttachment(GetRootComponent());


	Mesh2 = CreateDefaultSubobject<UStaticMeshComponent>("Mesh2");
	Mesh2->SetupAttachment(GetRootComponent());


	Mesh3 = CreateDefaultSubobject<UStaticMeshComponent>("Mesh3");
	Mesh3->SetupAttachment(GetRootComponent());

	HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");

}

// Called when the game starts or when spawned
void ATurretCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATurretCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATurretCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


