// Fill out your copyright notice in the Description page of Project Settings.


#include "Puzzle.h"
#include "TileActor.h"

// Sets default values
APuzzle::APuzzle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void APuzzle::Init(ATileActor* Parent)
{
	ParentTile = Parent;
}

void APuzzle::OnComponentInteracted(class UPuzzleComponent* Component)
{

}

void APuzzle::CompletePuzzle()
{
	bIsComplete = true;

	if (ParentTile != nullptr)
		ParentTile->OnPuzzleComplete();
}
