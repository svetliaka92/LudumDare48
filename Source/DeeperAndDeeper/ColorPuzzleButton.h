// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PuzzleComponent.h"
#include "ColorPuzzleButton.generated.h"

/**
 * 
 */
UCLASS()
class DEEPERANDDEEPER_API UColorPuzzleButton : public UPuzzleComponent
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = "Button")
	int32 ButtonType = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button")
	class UColorPuzzleSlot* Slot;

	virtual void Interact() override;
	void UpdateSlot(class UColorPuzzleSlot* NewSlot);
	void SetButtonType(int32 NewType);
};
