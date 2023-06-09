// Copyright Epic Games, Inc. All Rights Reserved.

#include "PhysicsPuzzleGameCharacter.h"
#include "PhysicsPuzzleGameProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


//////////////////////////////////////////////////////////////////////////
// APhysicsPuzzleGameCharacter

APhysicsPuzzleGameCharacter::APhysicsPuzzleGameCharacter()
{
	// Character doesnt have a rifle at start
	bHasRifle = false;
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	// Create a static mesh component that will remain empty to attach the weapon too (workaround while no pistol animations)
	EmptyAttachPoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gravity Gun Attach Point"));
	EmptyAttachPoint->SetupAttachment(FirstPersonCameraComponent);
	
	
}

void APhysicsPuzzleGameCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

}

//////////////////////////////////////////////////////////////////////////// Input

void APhysicsPuzzleGameCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APhysicsPuzzleGameCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APhysicsPuzzleGameCharacter::Look);

		//Gravity Gun
		EnhancedInputComponent->BindAction(PickupAction, ETriggerEvent::Started, this, &APhysicsPuzzleGameCharacter::PickupItem);
		EnhancedInputComponent->BindAction(PickupAction, ETriggerEvent::Completed, this, &APhysicsPuzzleGameCharacter::ReleaseItem);
		EnhancedInputComponent->BindAction(ThrowAction, ETriggerEvent::Triggered, this, &APhysicsPuzzleGameCharacter::ThrowItem);
		EnhancedInputComponent->BindAction(FreezeAction, ETriggerEvent::Triggered, this, &APhysicsPuzzleGameCharacter::FreezeItem);
		
	}
}

void APhysicsPuzzleGameCharacter::AttachWeapon(APhysicsHandlerWeapon* Weapon)
{
	
	// Set Weapon
	PhysicsHandlerWeapon = Weapon;

	// Attach Weapon
	const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	//Weapon->AttachToComponent(RootComponent, AttachmentRules, FName(TEXT("GrabPoint")));
	Weapon->AttachToComponent(EmptyAttachPoint, AttachmentRules); 
	
}

void APhysicsPuzzleGameCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void APhysicsPuzzleGameCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}


void APhysicsPuzzleGameCharacter::PickupItem()
{
	if(PhysicsHandlerWeapon)
	{
		PhysicsHandlerWeapon->PickupObject();
	}
}

void APhysicsPuzzleGameCharacter::ReleaseItem()
{
	if(PhysicsHandlerWeapon)
	{
		PhysicsHandlerWeapon->ReleaseObject();
	}
}

void APhysicsPuzzleGameCharacter::ThrowItem()
{
	if(PhysicsHandlerWeapon)
	{
		PhysicsHandlerWeapon->ThrowObject();
	}
}

void APhysicsPuzzleGameCharacter::FreezeItem()
{
	if(PhysicsHandlerWeapon)
	{
		PhysicsHandlerWeapon->FreezeObject();
	}
}

void APhysicsPuzzleGameCharacter::SetHasRifle(bool bNewHasRifle)
{
	bHasRifle = bNewHasRifle;
}

bool APhysicsPuzzleGameCharacter::GetHasRifle()
{
	return bHasRifle;
}