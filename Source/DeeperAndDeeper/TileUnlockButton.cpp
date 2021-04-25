// Fill out your copyright notice in the Description page of Project Settings.


#include "TileUnlockButton.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "TileActor.h"

ATileUnlockButton::ATileUnlockButton()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	ButtonStand = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Stand"));
	ButtonStand->SetupAttachment(RootComponent);

	Button = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button"));
	Button->SetupAttachment(RootComponent);
}

void ATileUnlockButton::Init(class ATileActor* Parent)
{
	ParentTile = Parent;
}

void ATileUnlockButton::SetButtonEnableState(bool bState)
{
	bEnableState = bState;
	if (bEnableState)
	{
		Button->SetMaterial(0, ButtonOnMaterial);
	}
	else
	{
		Button->SetMaterial(0, ButtonOffMaterial);
	}
}

void ATileUnlockButton::Interact()
{
	if (bEnableState && !bIsBusy)
	{
		bIsBusy = true;

		AnimateButton();
	}
}

void ATileUnlockButton::AnimateButton()
{
	// do animation
	OnAnimateButtonComplete();
}

void ATileUnlockButton::OnAnimateButtonComplete()
{
	if (ParentTile)
		ParentTile->OnUnlockButtonPressed();
}
