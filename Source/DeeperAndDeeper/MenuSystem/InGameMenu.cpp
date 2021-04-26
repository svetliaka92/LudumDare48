// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameMenu.h"
#include "Components/Button.h"

bool UInGameMenu::Initialize()
{
	bool result = Super::Initialize();
	if (!result)
		return false;

	if (!ensure(CancelButton != nullptr)) return false;
	CancelButton->OnClicked.AddDynamic(this, &UInGameMenu::OnCancelClicked);

	if (!ensure(MainMenuButton != nullptr)) return false;
	MainMenuButton->OnClicked.AddDynamic(this, &UInGameMenu::OnMainMenuClicked);

	return true;
}

void UInGameMenu::OnCancelClicked()
{
	Teardown();
}

void UInGameMenu::OnMainMenuClicked()
{
	if (MenuInterface != nullptr)
	{
		Teardown();
		MenuInterface->LoadMainMenu();
	}
}
