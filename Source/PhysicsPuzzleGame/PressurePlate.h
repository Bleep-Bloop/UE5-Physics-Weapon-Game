// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ButtonDoor.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "PressurePlate.generated.h"

UCLASS()
class PHYSICSPUZZLEGAME_API APressurePlate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APressurePlate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool GetIsPressed() const;

private:

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMeshComponent;
	
	UPROPERTY(EditAnywhere)
	UBoxComponent* ButtonTriggerZone;
	
	UFUNCTION()
	void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);

	UFUNCTION()
	void OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor);

	/**
	 * @brief Mass of the overlapping actor required to trigger the pressure plate.
	 */
	UPROPERTY(EditAnywhere)
	float TriggerMass;

	UPROPERTY(EditAnywhere)
	bool bIsPressed;

	UPROPERTY(EditAnywhere)
	AButtonDoor* LinkedDoor;

	/**
	 * @brief This button will call LinkedDoor's OpenDoor()
	 * @note if false will call LinkedDoor's CloseDoor();
	 */
	UPROPERTY(EditAnywhere)
	bool bIsOpeningDoor;
	
};
