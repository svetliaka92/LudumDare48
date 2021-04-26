// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"
#include "InGameMenu.generated.h"

/**
 * 
 */
UCLASS()
class DEEPERANDDEEPER_API UInGameMenu : public UMenuWidget
{
	GENERATED_BODY()
	
public:
	virtual bool Initialize() override;

private:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
		class UButton* CancelButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
		class UButton* MainMenuButton;

	UFUNCTION()
		void OnCancelClicked();

	UFUNCTION()
		void OnMainMenuClicked();
};
