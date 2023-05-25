// Fill out your copyright notice in the Description page of Project Settings.


#include "PhysicsHandlerWeapon.h"

// Sets default values
APhysicsHandlerWeapon::APhysicsHandlerWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APhysicsHandlerWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APhysicsHandlerWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

