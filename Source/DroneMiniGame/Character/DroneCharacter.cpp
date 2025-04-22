
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
#include "DroneMiniGame/UI/DroneWidget.h"


ADroneCharacter::ADroneCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(GetRootComponent());

	HealthComponent = CreateDefaultSubobject<UHealthComponent>("Healthcomponent");
	
}


void ADroneCharacter::AddAmmo(float Value)
{
	Ammo = FMath::Clamp(Ammo + Value, 0, MaxAmmo);
}

void ADroneCharacter::Shoot()
{
	if (Ammo == 0)return;
	Ammo = FMath::Clamp(Ammo - 1, 0, MaxAmmo);

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

void ADroneCharacter::BeginPlay()
{
	Super::BeginPlay();
	Camera->bUsePawnControlRotation = true;
	
	TeamID = FGenericTeamId(1);

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

	if (WidgetClass) {
		UUserWidget* WidgetInstance = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);
		if (WidgetInstance)
			WidgetInstance->AddToViewport();
	}

}


void ADroneCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}


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

