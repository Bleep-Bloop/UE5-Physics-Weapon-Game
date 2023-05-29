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

	UPROPERTY(EditAnywhere)
	float PickupDistance = 100.0f;

	UPROPERTY()
	UPhysicsHandleComponent* PhysicsHandle = nullptr;

	void FindPhysicsHandle();
	
	// Returns player's line trace
	FVector GetPlayersReach() const;    
	FVector GetPlayersWorldPosition() const;

	FHitResult GetFirstPhysicsBodyInReach() const;

	UPROPERTY()
	UPrimitiveComponent* ComponentToGrab;

	UPROPERTY(EditAnywhere)
	float ThrowForce = 150000;

	/**
	 * @brief Sets frozen objects bSimulatePhysics positive
	 * @note Called automatically from FreezeObject() after TimeObjectIsFrozen has elapsed.
	 */
	void UnFreezeObject();

	// Timer used to handle freeze time
	FTimerHandle FrozenTimer;

	/**
	 * @brief Time in seconds a grabbed object will remain frozen in a scene.
	 */
	UPROPERTY(EditAnywhere)
	float TimeObjectIsFrozen;

public:

	// Make friend class
	void PickupObject();

	void ReleaseObject() const;

	void ThrowObject() const;

	/**
	 * @brief Sets grabbed objects bSimulatePhysics negative
	 * @note automatically calls UnFreezeObject after 'TimeObjectIsFrozen' has elapsed
	 */
	void FreezeObject();


	

};
