// Fill out your copyright notice in the Description page of Project Settings.


#include "LampPuzzle.h"
#include "TileActor.h"
#include "LampPuzzleComponent.h"
#include "PuzzleComponent.h"

void ALampPuzzle::Init(ATileActor* Parent)
{
	Super::Init(Parent);

	LampOnMaterial = LampOnMaterials[FMath::RandRange(0, LampOnMaterials.Num() - 1)];

	int32 LampsNumber = Lamps.Num();
	int32 RngLayout = FMath::RandRange(0, StartingLayouts.Num() - 1);
	TArray<bool> Layouts = StartingLayouts[RngLayout].Layout;

	int32 RngRotations = FMath::RandRange(0, 6);
	for (int32 i = 0; i < RngRotations; ++i)
	{
		bool element = Layouts.Pop();
		Layouts.Insert(element, 0);
	}

	for (int32 i = 0; i < LampsNumber; ++i)
	{
		Lamps[i]->Init(this);
		Lamps[i]->Enable(true);
		Lamps[i]->SetIndex(i);

		if (LampsNumber == Layouts.Num())
		{
			Lamps[i]->SetState(Layouts[i]);
			Lamps[i]->SetMaterial(1, (Layouts[i]) ? LampOnMaterial : LampOffMaterial);
		}
		else
		{
			Lamps[i]->SetState(false);
			Lamps[i]->SetMaterial(1, LampOffMaterial);
		}
	}
}

void ALampPuzzle::OnComponentInteracted(UPuzzleComponent* Component)
{
	Super::OnComponentInteracted(Component);

	ULampPuzzleComponent* Lamp = Cast<ULampPuzzleComponent>(Component);
	if (Lamp)
	{
		int32 ToggledIndex = Lamp->Index;
		bool bNewLampState = !Lamp->bLampOnState;
		Lamp->SetState(bNewLampState);

		if (bNewLampState)
		{
			Lamp->SetMaterial(1, LampOnMaterial);
		}
		else
		{
			Lamp->SetMaterial(1, LampOffMaterial);
		}

		// toggle the previous lamp in the array - if the index is < 0 loop it around to Lamps.Num() - 1
		int32 PrevIndex = ToggledIndex - 1;
		int32 NextIndex = ToggledIndex + 1;

		if (PrevIndex < 0)
			PrevIndex = Lamps.Num() - 1;

		if (NextIndex >= Lamps.Num())
			NextIndex = 0;
		// toggle the next lamp in the array - if the index is >= Lamps.Num() loop it to 0
		
		bNewLampState = !Lamps[PrevIndex]->bLampOnState;
		Lamps[PrevIndex]->SetState(bNewLampState);
		Lamps[PrevIndex]->SetMaterial(1, (bNewLampState) ? LampOnMaterial : LampOffMaterial);

		bNewLampState = !Lamps[NextIndex]->bLampOnState;
		Lamps[NextIndex]->SetState(bNewLampState);
		Lamps[NextIndex]->SetMaterial(1, (bNewLampState) ? LampOnMaterial : LampOffMaterial);

		if (!bIsComplete && CheckComplete())
		{
			for (ULampPuzzleComponent* LampComp : Lamps)
			{
				LampComp->Enable(false);
			}

			CompletePuzzle();
		}
	}
}

bool ALampPuzzle::CheckComplete()
{
	for (ULampPuzzleComponent* Lamp : Lamps)
	{
		if (!Lamp->bLampOnState)
			return false;
	}

	return true;
}
