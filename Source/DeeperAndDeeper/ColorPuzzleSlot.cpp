// Fill out your copyright notice in the Description page of Project Settings.


#include "ColorPuzzleSlot.h"
#include "ColorPuzzleButton.h"

void UColorPuzzleSlot::SetSlotType(int32 NewType)
{
	SlotType = NewType;
}

void UColorPuzzleSlot::UpdateSlot(class UColorPuzzleButton* NewButton)
{
	ButtonInSlot = NewButton;
	bIsSlotFree = ButtonInSlot == nullptr;
}
