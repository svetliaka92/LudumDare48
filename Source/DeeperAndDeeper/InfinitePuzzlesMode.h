// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "InfinitePuzzlesMode.generated.h"

/**
 * 
 */
UCLASS()
class DEEPERANDDEEPER_API AInfinitePuzzlesMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void SpawnTile();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ATileActor> TileClass;

	UPROPERTY(EditAnywhere)
	int32 TilesToSpawn = 3;

private:
	
	FVector NextTileLocation = FVector();
	FRotator NextTileRotation = FRotator();
};
