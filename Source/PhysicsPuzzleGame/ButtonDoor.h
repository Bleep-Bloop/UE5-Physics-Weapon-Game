// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ButtonDoor.generated.h"

UCLASS()
class PHYSICSPUZZLEGAME_API AButtonDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AButtonDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FVector WorldLocation;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* DoorStaticMesh;
	
	UPROPERTY(EditAnywhere)
	bool bIsOpen;

	void OpenDoor();

	void CloseDoor();

	FVector StartLocation;
	
};
