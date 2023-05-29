// Fill out your copyright notice in the Description page of Project Settings.


#include "PhysicsHandlerWeapon.h"

#include "PhysicsPuzzleGameCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
APhysicsHandlerWeapon::APhysicsHandlerWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Weapon Static Mesh");
	if(StaticMesh)
		RootComponent = StaticMesh;
	
}

// Called when the game starts or when spawned
void APhysicsHandlerWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	FindPhysicsHandle();
	
	PlayerCamera = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
	
	// Temporary 
	// Attach weapon to character on start
	APhysicsPuzzleGameCharacter* Player = Cast<APhysicsPuzzleGameCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if(Player)
	{
		Player->AttachWeapon(this);
		Player->SetHasRifle(true);
	}
	
}

// Called every frame
void APhysicsHandlerWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PhysicsHandle->GrabbedComponent)
	{
		// Move the object that we are currently holding
		PhysicsHandle->SetTargetLocation(GetPlayersReach());
		
	}
}


void APhysicsHandlerWeapon::PickupObject()
{
	const FHitResult HitResult = GetFirstPhysicsBodyInReach();
	ComponentToGrab = HitResult.GetComponent();
	AActor* ActorHit = HitResult.GetActor();    
	if (ActorHit)
	{
		if (!PhysicsHandle) {return;}
		{
			PhysicsHandle->GrabComponentAtLocationWithRotation
			(
				ComponentToGrab,
				NAME_None,
				ComponentToGrab->GetComponentLocation(),
				ComponentToGrab->GetComponentRotation()
			);

		}
	}
}

void APhysicsHandlerWeapon::ReleaseObject() const
{
	PhysicsHandle->ReleaseComponent();
}

void APhysicsHandlerWeapon::ThrowObject() const
{

	if(ComponentToGrab)
	{
		FVector ThrowVector = PlayerCamera->GetActorForwardVector() * ThrowForce;
		PhysicsHandle->ReleaseComponent();
		ComponentToGrab->AddImpulse(ThrowVector, NAME_None, false);
	}
}

void APhysicsHandlerWeapon::FindPhysicsHandle()
{
	PhysicsHandle = FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("No Physics Handle Found!"))
	}
}

FVector APhysicsHandlerWeapon::GetPlayersReach() const
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint
	(
		PlayerViewPointLocation,
		PlayerViewPointRotation
	);    return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * PickupDistance;
}

FVector APhysicsHandlerWeapon::GetPlayersWorldPosition() const
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint
	(
		PlayerViewPointLocation,
		PlayerViewPointRotation
	);
	return PlayerViewPointLocation;
}

FHitResult APhysicsHandlerWeapon::GetFirstPhysicsBodyInReach() const
{
	FHitResult Hit;    
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType
	(
		Hit,
		GetPlayersWorldPosition(),
		GetPlayersReach(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);

	return Hit;
}
