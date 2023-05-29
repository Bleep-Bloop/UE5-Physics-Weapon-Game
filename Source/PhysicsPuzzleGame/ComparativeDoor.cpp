// Fill out your copyright notice in the Description page of Project Settings.


#include "ComparativeDoor.h"

// Sets default values
AComparativeDoor::AComparativeDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DoorStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Door Mesh");
	RootComponent = DoorStaticMesh;

}

// Called when the game starts or when spawned
void AComparativeDoor::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();
	
}

// Called every frame
void AComparativeDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(OppositeDoor)
	{
		if(OppositeDoor->bIsOpen)
		{
			CloseDoor();
		}
		else
		{
			OpenDoor();
		}
	}

}

void AComparativeDoor::OpenDoor()
{
	// Don't have skeletal mesh so just going to move
	DoorStaticMesh->SetRelativeLocation(FVector(0,0,-500));
	bIsOpen = true;
}

void AComparativeDoor::CloseDoor()
{
	DoorStaticMesh->SetWorldLocation(StartLocation);	
	bIsOpen = false;
}

