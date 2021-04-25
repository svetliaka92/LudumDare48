// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "IInteractable.h"
#include "PuzzleComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEEPERANDDEEPER_API UPuzzleComponent : public UActorComponent, public IIInteractable
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPuzzleComponent();

	virtual void Init(class APuzzle* Puzzle);
	virtual void OnComponentInteracted();
	virtual void Interact();

protected:

	class APuzzle* PuzzleParent;
};
