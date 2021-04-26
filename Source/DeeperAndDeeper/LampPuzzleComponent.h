// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PuzzleComponent.h"
#include "LampPuzzleComponent.generated.h"

/**
 * 
 */
UCLASS()
class DEEPERANDDEEPER_API ULampPuzzleComponent : public UPuzzleComponent
{
	GENERATED_BODY()
	
public:

	bool bLampOnState = false;
	int32 Index = -1;

	void SetIndex(int32 NewIndex);
	void SetState(bool bState);

	virtual void Interact() override;
};
