// Fill out your copyright notice in the Description page of Project Settings.


#include "ButtonDoor.h"

// Sets default values
AButtonDoor::AButtonDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DoorStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Door Mesh");
	RootComponent = DoorStaticMesh;
	
}

// Called when the game starts or when spawned
void AButtonDoor::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();
	
}

// Called every frame
void AButtonDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AButtonDoor::OpenDoor()
{
	// Don't have skeletal mesh so just going to move
	DoorStaticMesh->SetRelativeLocation(FVector(0,0,-500));
	bIsOpen = true;
}

void AButtonDoor::CloseDoor()
{
	DoorStaticMesh->SetWorldLocation(StartLocation);	
	bIsOpen = false;
}

