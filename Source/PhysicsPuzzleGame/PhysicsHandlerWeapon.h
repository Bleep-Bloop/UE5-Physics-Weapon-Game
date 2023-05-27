// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "PhysicsHandlerWeapon.generated.h"

class APhysicsPuzzleGameCharacter;

UCLASS()
class PHYSICSPUZZLEGAME_API APhysicsHandlerWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APhysicsHandlerWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	
// Components
	UPROPERTY()
	APlayerCameraManager* PlayerCamera;
	
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* StaticMesh;

// Input
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* PickupMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta=(AllowPrivateAccess = "true"))
	class UInputAction* PickupAction;

	UPROPERTY(EditAnywhere)
	float Reach = 100.0f;

	void RaycastTest();

};
