// Fill out your copyright notice in the Description page of Project Settings.


#include "ColorPuzzleButton.h"
#include "Puzzle.h"

void UColorPuzzleButton::Interact()
{
	Super::Interact();

	if (!bIsEnabled)
		return;

	OnComponentInteracted();
}

void UColorPuzzleButton::UpdateSlot(class UColorPuzzleSlot* NewSlot)
{
	Slot = NewSlot;
}

void UColorPuzzleButton::SetButtonType(int32 NewType)
{
	ButtonType = NewType;
}
