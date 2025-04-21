// Fill out your copyright notice in the Description page of Project Settings.


#include "DroneMiniGame/AI/TurretAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "DroneMiniGame/Character/DroneCharacter.h"
#include "DroneMiniGame/AI/TurretCharacter.h"
#include "DroneMiniGame/Character/Projectile.h"
ATurretAIController::ATurretAIController()
{

	Perception = CreateDefaultSubobject<UAIPerceptionComponent>("Perception");



}

void ATurretAIController::Shoot()
{
    if (!CurrentTarget || !ProjectileClass || !GetWorld()) return;

    ATurretCharacter* Turret = Cast<ATurretCharacter>(GetPawn());
    if (!Turret)return;
    // Точка, откуда стреляет турель
    FVector MuzzleLocation = Turret->GetActorLocation() + Turret->GetActorForwardVector() * 100.0f;

    // Вектор до цели
    FVector Direction = (CurrentTarget->GetActorLocation() - MuzzleLocation).GetSafeNormal();

    // Ротация в сторону цели
    FRotator MuzzleRotation = Direction.Rotation();

    // Параметры спавна
    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = this;
    SpawnParams.Instigator = GetInstigator();

    // Спавн
    AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
    if (Projectile)
    {
        Projectile->LaunchProjectile(Direction); // передаём направление
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
	if (Stimulus.WasSuccessfullySensed() && Actor->IsA<ADroneCharacter>()) {
		CurrentTarget = Actor;
        
	}
	else
		CurrentTarget = nullptr;
}


