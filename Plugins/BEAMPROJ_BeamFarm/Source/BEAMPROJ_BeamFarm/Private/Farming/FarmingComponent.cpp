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
				return true;
			}
		}
	}
	return false;
}

void UFarmingComponent::ClearSelectedCrop()
{
	SelectedCrop = FBeamSeedData();
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

		// const FString ItemId = Slot->PlantedSeed.HarvestItemContentId;
		// const int32 Yield = 1;
		Slot->Harvest();
		// OnItemsHarvested(Slot, ItemId, Yield);
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
	// OnSeedConsumed(SelectedCrop.ContentId.ToString(), 1);
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
