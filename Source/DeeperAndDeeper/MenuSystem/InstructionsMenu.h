// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"
#include "InstructionsMenu.generated.h"

/**
 * 
 */
UCLASS()
class DEEPERANDDEEPER_API UInstructionsMenu : public UMenuWidget
{
	GENERATED_BODY()
	
public:
	virtual bool Initialize() override;

private:

	// buttons and functions here
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
		class UWidgetSwitcher* InstructionsSwitcher;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
		class UButton* Next1Button;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
		class UButton* Back2Button;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
		class UButton* Next2Button;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
		class UButton* Back3Button;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
		class UButton* CloseButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
		class UWidget* InstructionsPage1;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
		class UWidget* InstructionsPage2;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget, AllowPrivateAccess = true))
		class UWidget* InstructionsPage3;

private:

	UFUNCTION()
		void OnNext1Clicked();

	UFUNCTION()
		void OnBack2Clicked();

	UFUNCTION()
		void OnNext2Clicked();

	UFUNCTION()
		void OnBack3Clicked();

	UFUNCTION()
		void OnCloseClicked();
};
