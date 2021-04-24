// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IInteractable.h"
#include "PuzzleComponent.generated.h"

UCLASS()
class DEEPERANDDEEPER_API APuzzleComponent : public AActor, public IIInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APuzzleComponent();

	virtual void Interact() override;
	virtual void Init(class APuzzle* Puzzle);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	class APuzzle* ParentPuzzle;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
