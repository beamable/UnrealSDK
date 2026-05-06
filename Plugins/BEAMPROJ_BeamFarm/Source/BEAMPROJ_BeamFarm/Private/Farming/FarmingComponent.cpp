// Copyright Beamable, Inc. All Rights Reserved.

#include "Farming/FarmingComponent.h"
#include "Subsystems/Content/BeamContentSubsystem.h"
#include "Contents/BeamPlantContent.h"
#include "Contents/BeamPlantRawMaterial.h"
#include "BeamPlantData.h"
#include "Farming/FarmSlotActor.h"
#include "Engine/World.h"

UFarmingComponent::UFarmingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	FarmingState = EFarmingInteractionState::Idle;
}

void UFarmingComponent::SetSelectedCrop(const FBeamPlantData& PlantData)
{
	SelectedCrop = PlantData;
	SetFarmingState(EFarmingInteractionState::Planting);
}

bool UFarmingComponent::SetSelectedCropBySeedId(const FString& SeedItemContentId)
{
	FBeamPlantData Found;
	if (!FindPlantBySeedId(SeedItemContentId, Found))
	{
		return false;
	}
	SetSelectedCrop(Found);
	return true;
}

void UFarmingComponent::ClearSelectedCrop()
{
	SelectedCrop = FBeamPlantData();
	SetFarmingState(EFarmingInteractionState::Idle);
}

bool UFarmingComponent::HasSelectedCrop() const
{
	return !SelectedCrop.SeedItemContentId.IsEmpty();
}

void UFarmingComponent::InteractWithSlot(AFarmSlotActor* Slot)
{
	if (!Slot)
	{
		return;
	}

	if (Slot->SlotState == EFarmSlotState::ReadyToHarvest)
	{
		if (Slot->PlantedCrop.SeedItemContentId.IsEmpty())
		{
			return;
		}

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

TArray<FBeamPlantData> UFarmingComponent::GetAllPlants()
{
	TArray<FBeamPlantData> Result;

	// Get or cache the content subsystem
	if (!ContentSubsystem)
	{
		ContentSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UBeamContentSubsystem>();
		if (!ContentSubsystem)
		{
			UE_LOG(LogTemp, Warning, TEXT("UFarmingComponent::GetAllPlants - Could not get BeamContentSubsystem"));
			return Result;
		}
	}

	// Get all plant content IDs
	TArray<FBeamContentId> PlantIds;
	ContentSubsystem->GetIdsOfContentType(UBeamPlantContent::StaticClass(), PlantIds, true);

	// Convert to plant data
	for (const FBeamContentId& PlantId : PlantIds)
	{
		UBeamPlantContent* PlantContent = nullptr;
		if (ContentSubsystem->TryGetContentOfType<UBeamPlantContent>(PlantId, PlantContent) && PlantContent)
		{
			Result.Add(PlantContent->PlantData);
		}
	}

	// Also get raw material plants
	TArray<FBeamContentId> PlantRawIds;
	ContentSubsystem->GetIdsOfContentType(UBeamPlantRawMaterial::StaticClass(), PlantRawIds, true);

	for (const FBeamContentId& PlantId : PlantRawIds)
	{
		UBeamPlantRawMaterial* PlantContent = nullptr;
		if (ContentSubsystem->TryGetContentOfType<UBeamPlantRawMaterial>(PlantId, PlantContent) && PlantContent)
		{
			Result.Add(PlantContent->PlantData);
		}
	}

	return Result;
}

bool UFarmingComponent::FindPlantBySeedId(const FString& SeedItemContentId, FBeamPlantData& OutPlantData)
{
	// Get or cache the content subsystem
	if (!ContentSubsystem)
	{
		ContentSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UBeamContentSubsystem>();
		if (!ContentSubsystem)
		{
			UE_LOG(LogTemp, Warning, TEXT("UFarmingComponent::FindPlantBySeedId - Could not get BeamContentSubsystem"));
			return false;
		}
	}

	// Get all plant content IDs
	TArray<FBeamContentId> PlantIds;
	ContentSubsystem->GetIdsOfContentType(UBeamPlantContent::StaticClass(), PlantIds, true);
	
	// Get all plant content IDs
	TArray<FBeamContentId> PlantRawIds;
	ContentSubsystem->GetIdsOfContentType(UBeamPlantRawMaterial::StaticClass(), PlantRawIds, true);

	// Search for matching SeedItemContentId in UBeamPlantContent
	for (const FBeamContentId& PlantId : PlantIds)
	{
		UBeamPlantContent* PlantContent = nullptr;
		if (ContentSubsystem->TryGetContentOfType<UBeamPlantContent>(PlantId, PlantContent) && PlantContent)
		{
			if (PlantContent->PlantData.SeedItemContentId == SeedItemContentId)
			{
				OutPlantData = PlantContent->PlantData;
				return true;
			}
		}
	}
	
	// Search for matching SeedItemContentId in UBeamPlantRawMaterial
	for (const FBeamContentId& PlantId : PlantRawIds)
	{
		UBeamPlantRawMaterial* PlantContent = nullptr;
		if (ContentSubsystem->TryGetContentOfType<UBeamPlantRawMaterial>(PlantId, PlantContent) && PlantContent)
		{
			if (PlantContent->PlantData.SeedItemContentId == SeedItemContentId)
			{
				OutPlantData = PlantContent->PlantData;
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
