// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleComponent.h"
#include "Puzzle.h"

// Sets default values for this component's properties
UPuzzleComponent::UPuzzleComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UPuzzleComponent::Init(class APuzzle* Puzzle)
{
	PuzzleParent = Puzzle;
}

void UPuzzleComponent::OnComponentInteracted()
{
	if (PuzzleParent)
	{
		PuzzleParent->OnComponentInteracted(this);
	}
}

void UPuzzleComponent::Interact()
{
	//..
}
