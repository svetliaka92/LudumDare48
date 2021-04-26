// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "Components/Button.h"

bool UMainMenu::Initialize()
{
	bool result = Super::Initialize();
	if (!result)
		return false;

	// todo setup
	if (!ensure(PlayButton != nullptr)) return false;
	PlayButton->OnClicked.AddDynamic(this, &UMainMenu::OnPlayClicked);

	if (!ensure(QuitGameButton != nullptr)) return false;
	QuitGameButton->OnClicked.AddDynamic(this, &UMainMenu::OnQuitClicked);

	return true;
}

void UMainMenu::OnPlayClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("PlayButton Clicked"));
	if (MenuInterface != nullptr)
	{
		MenuInterface->Play();
	}
}

void UMainMenu::OnQuitClicked()
{
	if (MenuInterface != nullptr)
	{
		MenuInterface->QuitGame();
	}
}
