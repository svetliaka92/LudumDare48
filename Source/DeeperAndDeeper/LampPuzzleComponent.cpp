// Fill out your copyright notice in the Description page of Project Settings.


#include "LampPuzzleComponent.h"

void ULampPuzzleComponent::Interact()
{
	Super::Interact();

	if (!bIsEnabled)
		return;

	OnComponentInteracted();
}

void ULampPuzzleComponent::SetIndex(int32 NewIndex)
{
	Index = NewIndex;
}

void ULampPuzzleComponent::SetState(bool bState)
{
	bLampOnState = bState;
}
