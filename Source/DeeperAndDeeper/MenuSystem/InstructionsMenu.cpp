// Fill out your copyright notice in the Description page of Project Settings.


#include "InstructionsMenu.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"

bool UInstructionsMenu::Initialize()
{
	bool result = Super::Initialize();
	if (!result)
		return false;

	// next 1, next 2, and close instructions buttons
	if (!ensure(Next1Button != nullptr)) return false;
	Next1Button->OnClicked.AddDynamic(this, &UInstructionsMenu::OnNext1Clicked);

	if (!ensure(Back2Button != nullptr)) return false;
	Back2Button->OnClicked.AddDynamic(this, &UInstructionsMenu::OnBack2Clicked);

	if (!ensure(Next2Button != nullptr)) return false;
	Next2Button->OnClicked.AddDynamic(this, &UInstructionsMenu::OnNext2Clicked);

	if (!ensure(Back3Button != nullptr)) return false;
	Back3Button->OnClicked.AddDynamic(this, &UInstructionsMenu::OnBack3Clicked);

	if (!ensure(CloseButton != nullptr)) return false;
	CloseButton->OnClicked.AddDynamic(this, &UInstructionsMenu::OnCloseClicked);

	return true;
}

void UInstructionsMenu::OnNext1Clicked()
{
	// open page 2
	if (!ensure(InstructionsSwitcher != nullptr)) return;

	if (!ensure(InstructionsPage2 != nullptr)) return;

	InstructionsSwitcher->SetActiveWidget(InstructionsPage2);
}

void UInstructionsMenu::OnBack2Clicked()
{
	// go back to page 1
	if (!ensure(InstructionsSwitcher != nullptr)) return;

	if (!ensure(InstructionsPage1 != nullptr)) return;

	InstructionsSwitcher->SetActiveWidget(InstructionsPage1);
}

void UInstructionsMenu::OnNext2Clicked()
{
	// go to page 3
	if (!ensure(InstructionsSwitcher != nullptr)) return;

	if (!ensure(InstructionsPage3 != nullptr)) return;

	InstructionsSwitcher->SetActiveWidget(InstructionsPage3);
}

void UInstructionsMenu::OnBack3Clicked()
{
	// go back to page 2
	if (!ensure(InstructionsSwitcher != nullptr)) return;

	if (!ensure(InstructionsPage2 != nullptr)) return;

	InstructionsSwitcher->SetActiveWidget(InstructionsPage2);
}

void UInstructionsMenu::OnCloseClicked()
{
	// close menu
	Teardown();
}
