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
}

void APhysicsHandlerWeapon::RaycastTest()
{
	
}
