// Fill out your copyright notice in the Description page of Project Settings.


#include "PressurePlate.h"

// Sets default values
APressurePlate::APressurePlate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh Component");
	RootComponent = StaticMeshComponent;

	ButtonTriggerZone = CreateDefaultSubobject<UBoxComponent>("Box Trigger Zone");
	ButtonTriggerZone->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	
	OnActorBeginOverlap.AddDynamic(this, &APressurePlate::OnOverlapBegin);
	
}

// Called when the game starts or when spawned
void APressurePlate::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APressurePlate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APressurePlate::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	if(OtherActor->GetComponentByClass<UStaticMeshComponent>()->GetMass() > TriggerMass)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "Button Down");
	}
}

