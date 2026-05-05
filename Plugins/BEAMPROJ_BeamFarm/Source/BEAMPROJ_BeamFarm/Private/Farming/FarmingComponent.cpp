// Copyright Beamable, Inc. All Rights Reserved.

#include "Farming/FarmingComponent.h"
#include "Subsystems/Content/BeamContentSubsystem.h"
#include "Contents/BeamPlantContent.h"
#include "Contents/BeamPlantRawMaterial.h"
#include "Farming/FarmSlotActor.h"
#include "Engine/World.h"

UFarmingComponent::UFarmingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	FarmingState = EFarmingInteractionState::Idle;
}

void UFarmingComponent::SetSelectedCrop(UBeamPlantContent* PlantContent)
{
	SelectedCrop = PlantContent;
	SetFarmingState(EFarmingInteractionState::Planting);
}

bool UFarmingComponent::SetSelectedCropBySeedId(const FString& SeedItemContentId)
{
	UBeamPlantContent* Found = nullptr;
	if (!FindPlantBySeedId(SeedItemContentId, Found))
	{
		return false;
	}
	SetSelectedCrop(Found);
	return true;
}

void UFarmingComponent::ClearSelectedCrop()
{
	SelectedCrop = nullptr;
	SetFarmingState(EFarmingInteractionState::Idle);
}

bool UFarmingComponent::HasSelectedCrop() const
{
	return SelectedCrop != nullptr;
}

void UFarmingComponent::InteractWithSlot(AFarmSlotActor* Slot)
{
	if (!Slot)
	{
		return;
	}

	if (Slot->SlotState == EFarmSlotState::ReadyToHarvest)
	{
		if (!Slot->PlantedCrop)
		{
			return;
		}

		const FString ItemId = Slot->PlantedCrop->HarvestItemContentId;
		const int32 Yield = Slot->PlantedCrop->HarvestYield;
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
	OnSeedConsumed(SelectedCrop->SeedItemContentId, 1);
}

TArray<UBeamPlantContent*> UFarmingComponent::GetAllPlants()
{
	TArray<UBeamPlantContent*> Result;

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

	// Convert to plant content objects
	for (const FBeamContentId& PlantId : PlantIds)
	{
		UBeamPlantContent* PlantContent = nullptr;
		if (ContentSubsystem->TryGetContentOfType<UBeamPlantContent>(PlantId, PlantContent) && PlantContent)
		{
			Result.Add(PlantContent);
		}
	}

	return Result;
}

bool UFarmingComponent::FindPlantBySeedId(const FString& SeedItemContentId, UBeamPlantContent*& OutPlantContent)
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

	// Search for matching SeedItemContentId
	for (const FBeamContentId& PlantId : PlantIds)
	{
		UBeamPlantContent* PlantContent = nullptr;
		if (ContentSubsystem->TryGetContentOfType<UBeamPlantContent>(PlantId, PlantContent) && PlantContent)
		{
			if (PlantContent->SeedItemContentId == SeedItemContentId)
			{
				OutPlantContent = PlantContent;
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
