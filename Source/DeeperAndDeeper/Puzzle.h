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

	void Init(class ATileActor* Parent);
	virtual void OnComponentInteracted(class APuzzleComponent* Component);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	class ATileActor* ParentTile;
	TArray<class APuzzleComponent*> Components;
};
