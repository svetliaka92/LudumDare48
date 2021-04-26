// Fill out your copyright notice in the Description page of Project Settings.


#include "DeeperGameInstance.h"
#include "UObject/ConstructorHelpers.h"
#include "MenuSystem/MenuWidget.h"
#include "MenuSystem/MainMenu.h"
#include "MenuSystem/InGameMenu.h"
#include "MenuSystem/InstructionsMenu.h"

UDeeperGameInstance::UDeeperGameInstance(const FObjectInitializer& ObjectInitializer)
{
	//ConstructorHelpers::FClassFinder<UMainMenu> MenuBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));
	if (MenuBPClass != nullptr)
	{
		MenuClass = CreateWidget(GetWorld(), MenuBPClass);
	}

	//ConstructorHelpers::FClassFinder<UInGameMenu> InGameMenuBPClass(TEXT("/Game/MenuSystem/WBP_PauseMenu"));
	if (InGameMenuBPClass != nullptr)
	{
		InGameMenuClass = CreateWidget(GetWorld(), InGameMenuBPClass);
	}

	if (InstructionsBPClass != nullptr)
	{
		InstructionsMenuClass = CreateWidget(GetWorld(), InstructionsBPClass);
	}
}

void UDeeperGameInstance::Init()
{
	Super::Init();
}

void UDeeperGameInstance::LoadMenu()
{
	if (!ensure(MenuBPClass != nullptr)) return;

	UMenuWidget* NewMenu = CreateWidget<UMainMenu>(this, MenuBPClass);
	if (!ensure(NewMenu != nullptr)) return;

	NewMenu->Setup(Menu);
	NewMenu->SetMenuInterface(this);

	Menu = NewMenu;
}

void UDeeperGameInstance::LoadInGameMenu()
{
	if (!ensure(InGameMenuBPClass != nullptr)) return;

	UMenuWidget* NewMenu = CreateWidget<UInGameMenu>(this, InGameMenuBPClass);
	if (!ensure(NewMenu != nullptr)) return;

	NewMenu->Setup(Menu);
	NewMenu->SetMenuInterface(this);

	Menu = NewMenu;
}

void UDeeperGameInstance::LoadInstructionsMenu()
{
	UE_LOG(LogTemp, Warning, TEXT("Loading instructions..."));

	if (!ensure(InstructionsBPClass != nullptr)) return;

	UMenuWidget* NewMenu = CreateWidget<UInstructionsMenu>(this, InstructionsBPClass);
	if (!ensure(NewMenu != nullptr)) return;

	NewMenu->Setup(Menu);
	NewMenu->SetMenuInterface(this);

	Menu = NewMenu;
}

void UDeeperGameInstance::Play()
{
	if (Menu != nullptr)
	{
		Menu->Teardown();
	}

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (PlayerController == nullptr)
		return;

	PlayerController->ClientTravel("/Game/Dynamic/Levels/PuzzleLevel", ETravelType::TRAVEL_Absolute);
}

void UDeeperGameInstance::LoadMainMenu()
{
	if (Menu != nullptr)
	{
		Menu->Teardown();
	}

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (PlayerController == nullptr)
		return;

	PlayerController->ClientTravel("/Game/Dynamic/Levels/MainMenu", ETravelType::TRAVEL_Absolute);
}

void UDeeperGameInstance::QuitGame()
{
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (PlayerController == nullptr)
		return;

	PlayerController->ConsoleCommand("Quit");
}
