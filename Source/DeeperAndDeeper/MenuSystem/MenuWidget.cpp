// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"

void UMenuWidget::SetMenuInterface(IMenuInterface* NewMenuInterface)
{
	MenuInterface = NewMenuInterface;
}

void UMenuWidget::Setup(UMenuWidget* Parent)
{
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr))
		return;

	ParentMenu = Parent;

	this->AddToViewport();
	this->bIsFocusable = true;

	FInputModeUIOnly InputModeData;
	InputModeData.SetWidgetToFocus(this->TakeWidget());
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	PlayerController->SetInputMode(InputModeData);
	PlayerController->bShowMouseCursor = true;
}

void UMenuWidget::Teardown()
{
	this->RemoveFromViewport();

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	UE_LOG(LogTemp, Warning, TEXT("Player is found, enabling game controls..."));
	FInputModeGameOnly InputModeData;
	PlayerController->SetInputMode(InputModeData);
	PlayerController->bShowMouseCursor = false;
}

UMenuWidget* UMenuWidget::GetParentMenu()
{
	return ParentMenu;
}
