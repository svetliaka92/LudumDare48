// Fill out your copyright notice in the Description page of Project Settings.


#include "ColorPuzzle.h"
#include "TileActor.h"
#include "PuzzleComponent.h"
#include "ColorPuzzleSlot.h"
#include "ColorPuzzleButton.h"
#include "Components/StaticMeshComponent.h"

AColorPuzzle::AColorPuzzle()
{
	PuzzleFrame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Frame"));
	RootComponent = PuzzleFrame;
}

void AColorPuzzle::Init(ATileActor* Parent)
{
	Super::Init(Parent);

	ResetSlotIndexes();

	for (UColorPuzzleButton* Button : Buttons)
	{
		Button->Init(this);
		Button->Enable(true);
		Button->Slot->UpdateSlot(Button);
	}

	// loop through all buttons and slots
	// if slot or button type < 0 - give them default material
	// else give them colored material according to their type

	int32 SlotsNum = Slots.Num();
	TArray<int32> TypeIndexes;
	for (int32 i = 1; i < SlotsNum; ++i)
	{
		bool Unique = true;
		int32 RngNum = 0;
		do
		{
			Unique = true;
			RngNum = GetRandomIndex();
			for (int32 i1 = 1; i1 < i; ++i1)
			{
				if (SlotIndexes[i1] == RngNum)
				{
					Unique = false;
					break;
				}
			}
		} while (!Unique);
		SlotIndexes[i] = RngNum;
		Slots[i]->SetSlotType(SlotIndexes[i]);
		PuzzleFrame->SetMaterial(i, Materials[SlotIndexes[i]]);
		TypeIndexes.Push(SlotIndexes[i]);
	}

	// shuffle the type indexes array, and then assign the values to the buttons
	for (int32 i = 0; i < 10; ++i)
	{
		for (int32 j = 0; j < TypeIndexes.Num(); ++j)
		{
			int32 rngIndex = FMath::RandRange(0, TypeIndexes.Num() - 1);
			int32 temp = TypeIndexes[j];
			TypeIndexes[j] = TypeIndexes[rngIndex];
			TypeIndexes[rngIndex] = temp;
		}
	}

	int32 ButtonsNum = Buttons.Num();
	for (int32 i = 0; i < ButtonsNum; ++i)
	{
		int32 Index = TypeIndexes.Pop();
		Buttons[i]->SetButtonType(Index);
		Buttons[i]->SetMaterial(1, Materials[Index]);
	}
}

void AColorPuzzle::ResetSlotIndexes()
{
	for (int32 i = 0; i < MAX_MATERIALS; ++i)
	{
		SlotIndexes[i] = -1;
	}
}

int32 AColorPuzzle::GetRandomIndex()
{
	return FMath::RandRange(0, MAX_MATERIALS - 1);
}

void AColorPuzzle::OnComponentInteracted(UPuzzleComponent* Component)
{
	Super::OnComponentInteracted(Component);

	if (bIsBusy)
		return;

	// cast the component to color button
	// get the button slot
	// check if any of the neighbors of the slot are empty
	// if there is an empty slot - move button to it
		// on button move - free current slot, and set the button in the new slot

	UColorPuzzleButton* Button = Cast<UColorPuzzleButton>(Component);
	if (Button != nullptr)
	{
		UColorPuzzleSlot* Slot = FindFreeSlot(Button);
		if (Slot != nullptr)
		{
			//UE_LOG(LogTemp, Warning, TEXT("Button slot: %s"), *Slot->GetName());
			bIsBusy = true;

			// TODO - animate movement
			FVector NewButtonLocation = Slot->GetComponentTransform().GetLocation();
			Button->SetWorldLocation(NewButtonLocation + ButtonOffset);
			Button->Slot->UpdateSlot(nullptr);
			Slot->UpdateSlot(Button);
			Button->UpdateSlot(Slot);

			// check for puzzle complete
			if (!bIsComplete && CheckPuzzleComplete())
				CompletePuzzle();

			bIsBusy = false;
		}
	}
}

UColorPuzzleSlot* AColorPuzzle::FindFreeSlot(UColorPuzzleButton* Button)
{
	//UE_LOG(LogTemp, Warning, TEXT("Button slot neighbors count: %i"), Button->Slot->NeighborSlots.Num());
	for (UColorPuzzleSlot* Slot : Button->Slot->NeighborSlots)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Slot: %s, free state: %d"), *Slot->GetName(),Slot->bIsSlotFree);
		if (Slot->bIsSlotFree)
			return Slot;
	}

	return nullptr;
}

bool AColorPuzzle::CheckPuzzleComplete()
{
	for (UColorPuzzleSlot* Slot : Slots)
	{
		if (Slot->SlotType < 0)
			continue;

		if (Slot->ButtonInSlot == nullptr)
			return false;

		if (Slot->SlotType != Slot->ButtonInSlot->ButtonType)
			return false;
	}

	return true;
}
