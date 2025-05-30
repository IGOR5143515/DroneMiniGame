

#include "DroneMiniGame/AI/TurretAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "DroneMiniGame/Character/DroneCharacter.h"
#include "DroneMiniGame/AI/TurretCharacter.h"
#include "DroneMiniGame/Character/Projectile.h"
#include "Perception/AISenseConfig_Sight.h"

ATurretAIController::ATurretAIController()
{

	Perception = CreateDefaultSubobject<UAIPerceptionComponent>("Perception");
    SetPerceptionComponent(*Perception);
    SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));

    SightConfig->SightRadius = 1500.0f;
    SightConfig->LoseSightRadius = 1600.0f;
    SightConfig->PeripheralVisionAngleDegrees = 180.0f;
    SightConfig->SetMaxAge(0.5f);

    SightConfig->DetectionByAffiliation.bDetectEnemies = true;
    SightConfig->DetectionByAffiliation.bDetectNeutrals = false;
    SightConfig->DetectionByAffiliation.bDetectFriendlies = false;

    PerceptionComponent->ConfigureSense(*SightConfig);
}

void ATurretAIController::Shoot()
{

    if (!CurrentTarget || !ProjectileClass || !GetWorld()) return;

    ATurretCharacter* Turret = Cast<ATurretCharacter>(GetPawn());
    if (!Turret)return;
    
    FVector MuzzleLocation = Turret->Mesh3->GetComponentLocation()+ Turret->Mesh3->GetForwardVector() * 100.0f;
   
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
    if (!Perception) return;
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


