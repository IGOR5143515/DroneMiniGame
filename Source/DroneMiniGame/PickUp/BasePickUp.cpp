
#include "DroneMiniGame/PickUp/BasePickUp.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "DroneMiniGame/Character/DroneCharacter.h"


ABasePickUp::ABasePickUp()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetupAttachment(RootComponent);
	StaticMesh->SetCollisionProfileName("BlockAll");

	CollisionSphere = CreateDefaultSubobject<USphereComponent>("CollisionSphere");
	CollisionSphere->InitSphereRadius(50.f);
	CollisionSphere->SetupAttachment(RootComponent);
	CollisionSphere->SetCollisionProfileName("OverlapAllDynamic");
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ABasePickUp::OnOverlapBegin);
	
}


void ABasePickUp::BeginPlay()
{
	Super::BeginPlay();
	
}


void ABasePickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasePickUp::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor&&OtherActor->IsA<ADroneCharacter>()) {
		Pickup(OtherActor);
	}
}

void ABasePickUp::Pickup(AActor* Picker)
{
}

