// Fill out your copyright notice in the Description page of Project Settings.


#include "PhysicsHandlerWeapon.h"

#include "PhysicsPuzzleGameCharacter.h"
#include "Kismet/GameplayStatics.h"

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

	bPhysicsHandleActive = false;
	
	PlayerCamera = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;

	// Temporary 
	// Attach weapon to character on start
	APhysicsPuzzleGameCharacter* Player = Cast<APhysicsPuzzleGameCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if(Player)
	{
		Player->AttachWeapon(this);
	}
	
}

// Called every frame
void APhysicsHandlerWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APhysicsHandlerWeapon::PickupItem()
{

	bPhysicsHandleActive = !bPhysicsHandleActive;

	if(bPhysicsHandleActive == true)
	{
		FHitResult HitResult;

		FVector StartTrace = PlayerCamera->GetCameraLocation(); 

		FVector ForwardVector = PlayerCamera->GetActorForwardVector();
		FVector EndTrace = ((ForwardVector * PickupDistance) + StartTrace);
		FCollisionQueryParams* TraceParams = new FCollisionQueryParams();

		if(GetWorld()->LineTraceSingleByObjectType(HitResult, StartTrace, EndTrace, ECC_WorldDynamic)) 
		{
			
			DrawDebugLine(GetWorld(), StartTrace, HitResult.Location, FColor::MakeRandomColor(), false, 0.5f);

		}
		
		
	}
	else
	{
		if(PhysicsHandleComponent) // Might have to check is active unsure exactly how works
		{
			PhysicsHandleComponent->ReleaseComponent(); // If PhysicsHandleComponent is active then drop // ToDo: What is PhysicsHandleComponent it looks like its pre much a hand it grabs a component (double check what is needed for grabbing component (ie unity rigidbody).
		}
		
	}
	
}

void APhysicsHandlerWeapon::AttachWeapon(APhysicsPuzzleGameCharacter* TargetCharacter)
{
	if(TargetCharacter)
	{
		// Attach the weapon to the character
		const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
		//AttachToComponent(TargetCharacter->GetRootComponent(), AttachmentRules, FName(TEXT("GripPoint")));
	}
}

