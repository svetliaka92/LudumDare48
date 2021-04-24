// Copyright Epic Games, Inc. All Rights Reserved.

#include "DeeperAndDeeperGameMode.h"
#include "DeeperAndDeeperHUD.h"
#include "DeeperAndDeeperCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADeeperAndDeeperGameMode::ADeeperAndDeeperGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ADeeperAndDeeperHUD::StaticClass();
}
