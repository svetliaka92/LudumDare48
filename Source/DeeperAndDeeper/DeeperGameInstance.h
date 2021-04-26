// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuSystem/MenuInterface.h"
#include "DeeperGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class DEEPERANDDEEPER_API UDeeperGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()
	
public:
	UDeeperGameInstance(const FObjectInitializer& ObjectInitializer);

	virtual void Init() override;

	UFUNCTION(BlueprintCallable, Category = "Menu")
		void LoadMenu();

	UFUNCTION(BlueprintCallable, Category = "Menu")
		void LoadInGameMenu();

	UFUNCTION(BlueprintCallable, Category = "Menu")
		void LoadInstructionsMenu();

	UFUNCTION(Exec)
		virtual void Play() override;

	UFUNCTION(Exec)
		virtual void LoadMainMenu() override;

	UFUNCTION(Exec)
		virtual void QuitGame() override;

private:
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UUserWidget> MenuBPClass;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UUserWidget> InGameMenuBPClass;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UUserWidget> InstructionsBPClass;

	UPROPERTY()
		class UUserWidget* MenuClass;
	UPROPERTY()
		class UUserWidget* InGameMenuClass;
	UPROPERTY()
		class UUserWidget* InstructionsMenuClass;

	class UMenuWidget* Menu;
};
