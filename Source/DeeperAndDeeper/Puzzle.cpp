// Fill out your copyright notice in the Description page of Project Settings.


#include "Puzzle.h"
#include "TileActor.h"

// Sets default values
APuzzle::APuzzle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void APuzzle::BeginPlay()
{
	Super::BeginPlay();
	
}

void APuzzle::Init(ATileActor* Parent)
{
	ParentTile = Parent;
}
