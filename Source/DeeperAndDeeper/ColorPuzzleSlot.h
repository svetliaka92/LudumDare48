// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PuzzleComponent.h"
#include "ColorPuzzleSlot.generated.h"

/**
 * 
 */
UCLASS()
class DEEPERANDDEEPER_API UColorPuzzleSlot : public UPuzzleComponent
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	int32 SlotType = -1;

	bool bIsSlotFree = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button")
	class UColorPuzzleButton* ButtonInSlot = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slots")
	TArray<UColorPuzzleSlot*> NeighborSlots;

	void SetSlotType(int32 NewType);
	void UpdateSlot(class UColorPuzzleButton* NewButton);
};
