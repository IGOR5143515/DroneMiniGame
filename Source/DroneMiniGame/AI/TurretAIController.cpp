// Fill out your copyright notice in the Description page of Project Settings.


#include "DroneMiniGame/AI/TurretAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "DroneMiniGame/Character/DroneCharacter.h"
#include "DroneMiniGame/AI/TurretCharacter.h"
#include "DroneMiniGame/Character/Projectile.h"
ATurretAIController::ATurretAIController()
{

	Perception = CreateDefaultSubobject<UAIPerceptionComponent>("Perception");
    SetPerceptionComponent(*Perception);

}

void ATurretAIController::Shoot()
{

    if (!CurrentTarget || !ProjectileClass || !GetWorld()) return;

    ATurretCharacter* Turret = Cast<ATurretCharacter>(GetPawn());
    if (!Turret)return;
    
    FVector MuzzleLocation = Turret->Mesh3->GetComponentLocation()+ Turret->GetActorForwardVector() * 100.0f;
   
    FVector Direction = (CurrentTarget->GetActorLocation() - MuzzleLocation).GetSafeNormal();
   
    FRotator MuzzleRotation = Direction.Rotation();
   
    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = this;
    SpawnParams.Instigator = GetInstigator();

    
    AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
    if (Projectile)
    {
        Projectile->LaunchProjectile(Direction);
    }
}

void ATurretAIController::Tick(float DeltaTime)
{
    if (CurrentTarget) {
        ATurretCharacter* Turret = Cast<ATurretCharacter>(GetPawn());
        if (!Turret)return;

        FVector MuzzleLocation = Turret->Mesh3->GetComponentLocation() + Turret->GetActorForwardVector() * 100.0f;

        FVector Direction = (CurrentTarget->GetActorLocation() - MuzzleLocation).GetSafeNormal();

        FRotator MuzzleRotation = Direction.Rotation();

        Turret->Mesh3->SetWorldRotation(MuzzleRotation);
    }
}

void ATurretAIController::BeginPlay()
{
	Super::BeginPlay();
    Perception->OnTargetPerceptionUpdated.AddDynamic(this, &ATurretAIController::OnTargetPerception);
	
}

void ATurretAIController::OnTargetPerception(AActor* Actor, FAIStimulus Stimulus)
{
    
    if (!GetWorld())return;

	if (Stimulus.WasSuccessfullySensed()) {
		CurrentTarget = Actor;

        GetWorld()->GetTimerManager().SetTimer(Timer, this, &ATurretAIController::Shoot, 1.0f, true);
	}
    else {
        CurrentTarget = nullptr;
        GetWorld()->GetTimerManager().ClearTimer(Timer);
    }
}


