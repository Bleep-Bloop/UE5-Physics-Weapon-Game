// Copyright Epic Games, Inc. All Rights Reserved.

#include "PhysicsPuzzleGameGameMode.h"
#include "PhysicsPuzzleGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

APhysicsPuzzleGameGameMode::APhysicsPuzzleGameGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
