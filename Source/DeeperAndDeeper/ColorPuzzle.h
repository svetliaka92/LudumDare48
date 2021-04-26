// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Puzzle.h"
#include "ColorPuzzle.generated.h"

class UColorPuzzleSlot;
class UColorPuzzleButton;

UCLASS()
class DEEPERANDDEEPER_API AColorPuzzle : public APuzzle
{
	GENERATED_BODY()
	
public:
	AColorPuzzle();

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* PuzzleFrame;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	TArray<UColorPuzzleSlot*> Slots;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	TArray<UColorPuzzleButton*> Buttons;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	FVector ButtonOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	TArray<class UMaterialInstance*> Materials;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	class UMaterialInstance* DefaultMaterial;

	virtual void Init(class ATileActor* Parent) override;
	virtual void OnComponentInteracted(UPuzzleComponent* Component) override;

protected:

	bool bIsBusy = false;

	UColorPuzzleSlot* FindFreeSlot(UColorPuzzleButton* Button);

	bool CheckPuzzleComplete();

	const int32 MAX_MATERIALS = 16;
	int32 SlotIndexes[16];
	

	void ResetSlotIndexes();
	void ResetButtonIndexes();
	int32 GetRandomIndex();
};
