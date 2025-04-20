// Fill out your copyright notice in the Description page of Project Settings.


#include "DroneMiniGame/Character/Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetupAttachment(GetRootComponent());
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	CollisionComponent = CreateDefaultSubobject<USphereComponent>("CollisionComponent");
	CollisionComponent->InitSphereRadius(10.0f);
	CollisionComponent->SetCollisionProfileName("BlockAll");
	CollisionComponent->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	RootComponent = CollisionComponent;


	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovement->InitialSpeed = 2000.f;
	ProjectileMovement->MaxSpeed = 2000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;

	InitialLifeSpan = 5.0f;


}


// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AProjectile::OnHit(UPrimitiveComponent* HitComp,
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	FVector NormalImpulse, 
	const FHitResult& Hit)
{
}
void AProjectile::LaunchProjectile(FVector& Direction)
{
	ProjectileMovement->Velocity = Direction * ProjectileMovement->InitialSpeed;
}
