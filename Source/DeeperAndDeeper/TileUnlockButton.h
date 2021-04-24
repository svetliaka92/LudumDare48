// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IInteractable.h"
#include "TileUnlockButton.generated.h"

UCLASS()
class DEEPERANDDEEPER_API ATileUnlockButton : public AActor, public IIInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATileUnlockButton();

	UPROPERTY(EditDefaultsOnly)
	class USceneComponent* Root;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* ButtonStand;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* Button;

	UPROPERTY(EditAnywhere, Category = "Tile")
	class UMaterialInstance* ButtonOnMaterial;

	UPROPERTY(EditAnywhere, Category = "Tile")
	class UMaterialInstance* ButtonOffMaterial;

	void Init(class ATileActor* Parent);
	void SetButtonEnableState(bool bState);
	virtual void Interact() override;

protected:
	void AnimateButton();
	void OnAnimateButtonComplete();

	class ATileActor* ParentTile;
	bool bEnableState = false;
	bool bIsBusy = false;
};
