// Fill out your copyright notice in the Description page of Project Settings.


#include "DroneMiniGame/PickUp/BasePickUp.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ABasePickUp::ABasePickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetupAttachment(RootComponent);

	CollisionSphere = CreateDefaultSubobject<USphereComponent>("CollisionSphere");
	CollisionSphere->InitSphereRadius(50.f);
	CollisionSphere->SetupAttachment(RootComponent);
	CollisionSphere->SetCollisionProfileName("OverlapAllDynamic");
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ABasePickUp::OnOverlapBegin);

}

// Called when the game starts or when spawned
void ABasePickUp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasePickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasePickUp::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor&&OtherActor!=this) {
		Pickup(OtherActor);
		Destroy();
	}
}

void ABasePickUp::Pickup(AActor* Picker)
{
}

