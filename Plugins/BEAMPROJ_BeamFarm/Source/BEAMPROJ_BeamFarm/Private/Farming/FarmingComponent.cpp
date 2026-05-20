// Copyright Beamable, Inc. All Rights Reserved.

#include "Farming/FarmingComponent.h"
#include "Subsystems/Content/BeamContentSubsystem.h"
#include "Contents/BeamPlantContent.h"
#include "Contents/BeamSeedsContent.h"
#include "BeamPlantData.h"
#include "Farming/FarmSlotActor.h"
#include "Engine/World.h"

UFarmingComponent::UFarmingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	FarmingState = EFarmingInteractionState::Idle;
}

void UFarmingComponent::SetSelectedCrop(const FBeamSeedData& SeedData)
{
	SelectedCrop = SeedData;
	// Fallback: derive content ID from the seed data's ContentId field.
	// SetSelectedCropBySeedId overrides this with the authoritative ID from the content system.
	SelectedCropContentId = SeedData.ContentId.ToString();
	SetFarmingState(EFarmingInteractionState::Planting);
}

bool UFarmingComponent::SetSelectedCropBySeedId(const FString& SeedItemContentId)
{
	if (!ContentSubsystem)
	{
		ContentSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UBeamContentSubsystem>();
		if (!ContentSubsystem)
		{
			return false;
		}
	}

	TArray<FBeamContentId> SeedIds;
	ContentSubsystem->GetIdsOfContentType(UBeamSeedsContent::StaticClass(), SeedIds, true);

	for (const FBeamContentId& SeedId : SeedIds)
	{
		if (SeedId.AsString == SeedItemContentId)
		{
			UBeamSeedsContent* SeedContent = nullptr;
			if (ContentSubsystem->TryGetContentOfType<UBeamSeedsContent>(SeedId, SeedContent) && SeedContent)
			{
				SetSelectedCrop(SeedContent->SeedData);
				SelectedCropContentId = SeedId.AsString; // authoritative override
				return true;
			}
		}
	}
	return false;
}

void UFarmingComponent::ClearSelectedCrop()
{
	SelectedCrop = FBeamSeedData();
	SelectedCropContentId = TEXT("");
	SetFarmingState(EFarmingInteractionState::Idle);
}

bool UFarmingComponent::HasSelectedCrop()
{
	return !SelectedCrop.GrowingSprite.IsNull();
}

void UFarmingComponent::InteractWithSlot(AFarmSlotActor* Slot)
{
	if (!Slot)
	{
		return;
	}

	if (Slot->SlotState == EFarmSlotState::ReadyToHarvest)
	{
		if (Slot->PlantedSeed.GrowingSprite.IsNull())
		{
			return;
		}

		// Capture harvest info before Harvest() clears the slot state.
		const FString HarvestItemId = Slot->PlantedSeed.HarvestItemContentId;

		Slot->Harvest();

		// Override in Blueprint: call BeamFarmMsCollectHarvest with Slot->SlotId,
		// then update any local inventory display using CollectResult.harvestedItemContentId.
		OnItemsHarvested(Slot, HarvestItemId, 1);
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

	FBeamPlantData HarvestData;
	FindPlantBySeedId(SelectedCrop.HarvestItemContentId, HarvestData);
	Slot->PlantCrop(SelectedCrop, HarvestData);

	// Override in Blueprint: call BeamFarmMsPlantSeed with:
	//   seedContentId        = SelectedCropContentId
	//   slotId               = Slot->SlotId
	//   harvestItemContentId = SelectedCrop.HarvestItemContentId
	//   growTimeSeconds      = SelectedCrop.GrowTimeSeconds
	OnSeedConsumed(SelectedCropContentId, 1);
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

	return Result;
}

bool UFarmingComponent::FindPlantBySeedId(const FString& plantContentId, FBeamPlantData& OutPlantData)
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

	TArray<FBeamContentId> PlantIds;
	ContentSubsystem->GetIdsOfContentType(UBeamPlantContent::StaticClass(), PlantIds, true);

	for (const FBeamContentId& PlantId : PlantIds)
	{
		UBeamPlantContent* PlantContent = nullptr;
		if (PlantId.AsString == plantContentId)
		{
			if (ContentSubsystem->TryGetContentOfType<UBeamPlantContent>(PlantId, PlantContent) && PlantContent)
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
