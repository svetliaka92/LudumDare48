// Fill out your copyright notice in the Description page of Project Settings.


#include "InfinitePuzzlesMode.h"
#include "TileActor.h"

void AInfinitePuzzlesMode::BeginPlay()
{
	Super::BeginPlay();

	for (int32 i = 0; i < TilesToSpawn; ++i)
	{
		SpawnTile();
	}
}

void AInfinitePuzzlesMode::SpawnTile()
{
	UWorld* World = GetWorld();
	if (World == nullptr)
		return;

	if (TileClass != nullptr)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.ObjectFlags = RF_NoFlags;

		ATileActor* Tile = World->SpawnActor<ATileActor>(TileClass, NextTileLocation, NextTileRotation, SpawnInfo);
		if (Tile)
		{
			NextTileLocation = Tile->GetNextTileTransform().GetLocation();
			NextTileRotation = Tile->GetNextTileTransform().GetRotation().Rotator();
			Tile->Init();
		}
	}
}
