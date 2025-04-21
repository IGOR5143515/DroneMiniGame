// Fill out your copyright notice in the Description page of Project Settings.


#include "DroneMiniGame/Character/DroneCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DroneMiniGame/Components/HealthComponent.h"
#include "DroneMiniGame/Character/Projectile.h"

// Sets default values
ADroneCharacter::ADroneCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(GetRootComponent());
	

	DroneMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	DroneMesh->SetupAttachment(GetRootComponent());

	HealthComponent = CreateDefaultSubobject<UHealthComponent>("Healthcomponent");

	OnTakeAnyDamage.AddDynamic(HealthComponent, &UHealthComponent::OnTakeAnyDamage);
}


void ADroneCharacter::Shoot()
{
	if (!GetWorld())return;
	FVector Location = GetMesh()->GetSocketLocation("Muzzle") ;
	FRotator Rotation = GetMesh()->GetSocketRotation("Muzzle");

	FVector MuzzleLocation = Location;
	FRotator MuzzleRotation = Rotation;
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = this;
	SpawnParams.Owner = this;
	
	AProjectile* Projectile=GetWorld()->SpawnActor<AProjectile>(ProjectileClass, Location, Rotation, SpawnParams);
	if (Projectile) {
		FVector Direction = Camera->GetComponentRotation().Vector();
		Projectile->LaunchProjectile(Direction);
	}

}

void ADroneCharacter::Move(const FInputActionValue& Value)
{
	FVector2D Input = Value.Get<FVector2D>();
	if (Input != FVector2D::ZeroVector)
	{
		FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
		const FVector Forward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector Right = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(Forward, Input.Y,true);
		AddMovementInput(Right, Input.X,true);
	}
}

void ADroneCharacter::Look(const FInputActionValue& Value)
{
	FVector2D Input = Value.Get<FVector2D>();
	AddControllerYawInput(Input.X);
	AddControllerPitchInput(-Input.Y);
}

void ADroneCharacter::Ascend_Descend(const FInputActionValue& Value)
{
	float VerticalInput = Value.Get<float>();
	AddMovementInput(FVector::UpVector, VerticalInput);
}

// Called when the game starts or when spawned
void ADroneCharacter::BeginPlay()
{
	Super::BeginPlay();
	Camera->bUsePawnControlRotation = true;
	
	UCharacterMovementComponent* Move = Cast<UCharacterMovementComponent>(GetMovementComponent());
	Move->DefaultLandMovementMode = MOVE_Flying;
	Move->MaxFlySpeed = 700;
	Move->BrakingFrictionFactor = 5.0;
	Move->BrakingDecelerationFlying = 100.0f;
	Move->GravityScale=0.0f;
	Move->AirControl = 1.0f;


	if (APlayerController* PC = Cast<APlayerController>(Controller)) {
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer())) {
			Subsystem->AddMappingContext(DroneInputMappingContext, 0);
		}
	}

}

// Called every frame
void ADroneCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADroneCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		EIC->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ADroneCharacter::Move);
		EIC->BindAction(LookAction, ETriggerEvent::Triggered, this, &ADroneCharacter::Look);
		EIC->BindAction(AscendDescend, ETriggerEvent::Triggered, this, &ADroneCharacter::Ascend_Descend);
		EIC->BindAction(ShootAction, ETriggerEvent::Triggered, this, &ADroneCharacter::Shoot);
	}

}

