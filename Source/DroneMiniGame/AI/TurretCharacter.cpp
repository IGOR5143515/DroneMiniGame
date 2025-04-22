


#include "DroneMiniGame/AI/TurretCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "DroneMiniGame/Components/HealthComponent.h"


ATurretCharacter::ATurretCharacter()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	Mesh1 = CreateDefaultSubobject<UStaticMeshComponent>("Mesh1");
	Mesh1->SetupAttachment(GetRootComponent());


	Mesh2 = CreateDefaultSubobject<UStaticMeshComponent>("Mesh2");
	Mesh2->SetupAttachment(GetRootComponent());


	Mesh3 = CreateDefaultSubobject<UStaticMeshComponent>("Mesh3");
	Mesh3->SetupAttachment(GetRootComponent());

	HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");

}


void ATurretCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATurretCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ATurretCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


