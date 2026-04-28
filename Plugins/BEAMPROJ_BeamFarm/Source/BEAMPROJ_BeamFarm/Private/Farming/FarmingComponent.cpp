// Copyright Beamable, Inc. All Rights Reserved.

#include "Farming/FarmingComponent.h"
#include "Farming/FarmSlotActor.h"
#include "Engine/DataTable.h"

UFarmingComponent::UFarmingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	FarmingState = EFarmingInteractionState::Idle;
}

void UFarmingComponent::SetSelectedCrop(const FFarmCropData& CropData)
{
	SelectedCrop = CropData;
	SetFarmingState(EFarmingInteractionState::Planting);
}

bool UFarmingComponent::SetSelectedCropBySeedId(const FString& SeedItemContentId)
{
	FFarmCropData Found;
	if (!FindCropBySeedId(SeedItemContentId, Found))
	{
		return false;
	}
	SetSelectedCrop(Found);
	return true;
}

void UFarmingComponent::ClearSelectedCrop()
{
	SelectedCrop = FFarmCropData{};
	SetFarmingState(EFarmingInteractionState::Idle);
}

bool UFarmingComponent::HasSelectedCrop() const
{
	return !SelectedCrop.CropId.IsNone();
}

void UFarmingComponent::InteractWithSlot(AFarmSlotActor* Slot)
{
	if (!Slot)
	{
		return;
	}

	if (Slot->SlotState == EFarmSlotState::ReadyToHarvest)
	{
		const FString ItemId = Slot->PlantedCrop.HarvestItemContentId;
		const int32 Yield = Slot->PlantedCrop.HarvestYield;
		Slot->Harvest();
		OnItemsHarvested(Slot, ItemId, Yield);
		return;
	}

	if (Slot->SlotState == EFarmSlotState::Growing)
	{
		return;
	}

	// Empty slot
	if (!HasSelectedCrop())
	{
		OnNoCropSelected();
		return;
	}

	Slot->PlantCrop(SelectedCrop);
	OnSeedConsumed(SelectedCrop.SeedItemContentId, 1);
}

TArray<FFarmCropData> UFarmingComponent::GetAllCrops() const
{
	TArray<FFarmCropData> Result;
	if (!CropDataTable)
	{
		return Result;
	}

	for (const FName& RowName : CropDataTable->GetRowNames())
	{
		if (const FFarmCropData* Row = CropDataTable->FindRow<FFarmCropData>(RowName, TEXT("")))
		{
			Result.Add(*Row);
		}
	}
	return Result;
}

bool UFarmingComponent::FindCropBySeedId(const FString& SeedItemContentId, FFarmCropData& OutCropData) const
{
	if (!CropDataTable)
	{
		return false;
	}

	for (const FName& RowName : CropDataTable->GetRowNames())
	{
		if (const FFarmCropData* Row = CropDataTable->FindRow<FFarmCropData>(RowName, TEXT("")))
		{
			if (Row->SeedItemContentId == SeedItemContentId)
			{
				OutCropData = *Row;
				return true;
			}
		}
	}
	return false;
}

void UFarmingComponent::SetFarmingState(EFarmingInteractionState NewState)
{
	FarmingState = NewState;
	OnFarmingStateChanged(NewState);
}
