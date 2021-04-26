// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Puzzle.generated.h"

UCLASS()
class DEEPERANDDEEPER_API APuzzle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APuzzle();

	virtual void Init(class ATileActor* Parent);
	virtual void OnComponentInteracted(class UPuzzleComponent* Component);

protected:

	class ATileActor* ParentTile;
	bool bIsComplete = false;

	virtual void CompletePuzzle();
};
