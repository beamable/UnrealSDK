// Copyright Beamable, Inc. All Rights Reserved.

#include "Farming/FarmingComponent.h"
#include "Subsystems/Content/BeamContentSubsystem.h"
#include "Contents/BeamPlantContent.h"
#include "Contents/BeamSeedsContent.h"
#include "BeamPlantData.h"
#include "Farming/FarmSlotActor.h"
#include "Engine/World.h"
#include "AutoGen/SubSystems/BeamFarmMs/BeamFarmMsPlantSeedRequest.h"
#include "AutoGen/SubSystems/BeamFarmMs/BeamFarmMsCollectHarvestRequest.h"

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

	if (!BeamFarmMsApi)
	{
		BeamFarmMsApi = GEngine->GetEngineSubsystem<UBeamBeamFarmMsApi>();
	}

	if (Slot->SlotState == EFarmSlotState::ReadyToHarvest)
	{
		if (Slot->PlantedSeed.GrowingSprite.IsNull())
		{
			return;
		}

		// Capture before Harvest() clears the slot state.
		const FString SlotId = Slot->SlotId;
		const FString HarvestItemId = Slot->PlantedSeed.HarvestItemContentId;
		TWeakObjectPtr<AFarmSlotActor> WeakSlot(Slot);

		Slot->Harvest();

		if (BeamFarmMsApi)
		{
			auto* Request = UBeamFarmMsCollectHarvestRequest::Make(SlotId, this, TMap<FString, FString>{});
			FBeamRequestContext RequestContext;
			TWeakObjectPtr<UFarmingComponent> WeakThis(this);

			BeamFarmMsApi->CPP_CollectHarvest(
				FUserSlot{UserSlotName},
				Request,
				FOnBeamFarmMsCollectHarvestFullResponse::CreateLambda(
					[WeakThis, WeakSlot, SlotId, HarvestItemId](FBeamFarmMsCollectHarvestFullResponse Response)
					{
						if (!WeakThis.IsValid()) return;
						if (Response.State == RS_Success && Response.SuccessData && Response.SuccessData->bSuccess)
						{
							WeakThis->OnItemsHarvested(WeakSlot.Get(), Response.SuccessData->HarvestedItemContentId, 1);
						}
						else
						{
							const FString ErrorMsg = (Response.State == RS_Error) ? Response.ErrorData.error : HarvestItemId;
							WeakThis->OnCollectFailed(SlotId, ErrorMsg);
						}
					}),
				RequestContext,
				FBeamOperationHandle(),
				this
			);
		}
		else
		{
			// No API available — fire directly so Blueprint still works without the microservice.
			OnItemsHarvested(WeakSlot.Get(), HarvestItemId, 1);
		}
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

	const FString SeedContentId = SelectedCropContentId;
	const FString SlotId = Slot->SlotId;

	FBeamPlantData HarvestData;
	FindPlantBySeedId(SelectedCrop.HarvestItemContentId, HarvestData);
	Slot->PlantCrop(SelectedCrop, HarvestData);

	if (BeamFarmMsApi)
	{
		auto* Request = UBeamFarmMsPlantSeedRequest::Make(SeedContentId, SlotId, this, TMap<FString, FString>{});
		FBeamRequestContext RequestContext;
		TWeakObjectPtr<UFarmingComponent> WeakThis(this);
		TWeakObjectPtr<AFarmSlotActor> WeakSlot(Slot);

		BeamFarmMsApi->CPP_PlantSeed(
			FUserSlot{UserSlotName},
			Request,
			FOnBeamFarmMsPlantSeedFullResponse::CreateLambda(
				[WeakThis, WeakSlot, SeedContentId, SlotId](FBeamFarmMsPlantSeedFullResponse Response)
				{
					if (!WeakThis.IsValid()) return;
					if (Response.State == RS_Success && Response.SuccessData && Response.SuccessData->bSuccess)
					{
						WeakThis->OnSeedConsumed(SeedContentId, 1);
					}
					else
					{
						if (WeakSlot.IsValid())
						{
							WeakSlot->CancelPlant();
						}
						const FString ErrorMsg = (Response.State == RS_Error) ? Response.ErrorData.error : TEXT("PlantSeed failed");
						WeakThis->OnPlantFailed(SlotId, ErrorMsg);
					}
				}),
			RequestContext,
			FBeamOperationHandle(),
			this
		);
	}
	else
	{
		// No API available — fire directly so Blueprint still works without the microservice.
		OnSeedConsumed(SeedContentId, 1);
	}
}

TArray<FBeamPlantData> UFarmingComponent::GetAllPlants()
{
	TArray<FBeamPlantData> Result;

	if (!ContentSubsystem)
	{
		ContentSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UBeamContentSubsystem>();
		if (!ContentSubsystem)
		{
			UE_LOG(LogTemp, Warning, TEXT("UFarmingComponent::GetAllPlants - Could not get BeamContentSubsystem"));
			return Result;
		}
	}

	TArray<FBeamContentId> PlantIds;
	ContentSubsystem->GetIdsOfContentType(UBeamPlantContent::StaticClass(), PlantIds, true);

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
