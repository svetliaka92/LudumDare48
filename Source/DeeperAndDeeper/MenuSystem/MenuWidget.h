#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"
#include "MenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class DEEPERANDDEEPER_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	void SetMenuInterface(IMenuInterface* NewMenuInterface);
	void Setup(UMenuWidget* Parent = nullptr);
	void Teardown();

	UMenuWidget* GetParentMenu();

protected:

	IMenuInterface* MenuInterface;
	UMenuWidget* ParentMenu;
};
