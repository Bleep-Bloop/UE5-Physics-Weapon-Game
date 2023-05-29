// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ButtonDoor.h"
#include "GameFramework/Actor.h"
#include "ComparativeDoor.generated.h"

// This door is always the opposite of the attached ButtonDoor
UCLASS()
class PHYSICSPUZZLEGAME_API AComparativeDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AComparativeDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

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

	UPROPERTY(EditAnywhere)
	AButtonDoor* OppositeDoor;

};
