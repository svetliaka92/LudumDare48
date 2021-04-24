// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleComponent.h"
#include "Puzzle.h"

// Sets default values
APuzzleComponent::APuzzleComponent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void APuzzleComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void APuzzleComponent::Init(APuzzle* Puzzle)
{
	ParentPuzzle = Puzzle;
}

void APuzzleComponent::Interact()
{
	if (ParentPuzzle != nullptr)
	{
		ParentPuzzle->OnComponentInteracted(this);
	}
}

void APuzzleComponent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
