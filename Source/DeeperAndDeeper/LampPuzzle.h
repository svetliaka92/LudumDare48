// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Puzzle.h"
#include "LampPuzzle.generated.h"

class ULampPuzzleComponent;
USTRUCT()
struct FStartingLayouts
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TArray<bool> Layout;
};

UCLASS()
class DEEPERANDDEEPER_API ALampPuzzle : public APuzzle
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LampPuzzle")
	TArray<ULampPuzzleComponent*> Lamps;

	UPROPERTY(EditAnywhere)
	class UMaterialInstance* LampOffMaterial;

	UPROPERTY(EditAnywhere)
	TArray<class UMaterialInstance*> LampOnMaterials;

	UPROPERTY(EditAnywhere)
	class UMaterialInstance* LampOnMaterial;

	UPROPERTY(EditAnywhere)
	TArray<FStartingLayouts> StartingLayouts;

	virtual void Init(class ATileActor* Parent) override;
	virtual void OnComponentInteracted(class UPuzzleComponent* Component) override;

protected:
	bool CheckComplete();
};
