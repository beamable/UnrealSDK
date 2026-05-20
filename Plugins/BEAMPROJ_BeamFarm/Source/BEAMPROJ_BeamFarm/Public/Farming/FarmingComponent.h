// Copyright Beamable, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Farming/FarmTypes.h"
#include "BeamPlantData.h"
#include "BeamSeedData.h"
#include "FarmingComponent.generated.h"

class AFarmSlotActor;
class UBeamPlantContent;
class UBeamContentSubsystem;

/**
 * Attach to your Character/Pawn to handle all farming interactions.
 *
 * Workflow:
 *   1. Player opens inventory and selects a seed item.
 *   2. Inventory widget calls SetSelectedCrop(PlantContent) — enters Planting state.
 *   3. Player clicks any empty slot → slot is planted, OnSeedConsumed fires (deduct from inventory here).
 *   4. Player clicks any ReadyToHarvest slot → harvested, OnItemsHarvested fires (add to inventory here).
 *   5. Player deselects seed in inventory (or calls ClearSelectedCrop) → returns to Idle.
 *
 * Uses UBeamContentSubsystem to look up UBeamPlantContent by SeedItemContentId.
 *
 * Requires bEnableClickEvents = true and bEnableTouchEvents = true on the PlayerController.
 */
UCLASS(ClassGroup = (BeamFarm), meta = (BlueprintSpawnableComponent))
class BEAMPROJ_BEAMFARM_API UFarmingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFarmingComponent();

	UPROPERTY(BlueprintReadOnly, Category = "BeamFarm|Farming")
	EFarmingInteractionState FarmingState;

	// The seed currently selected from inventory. Valid only during Planting state.
	UPROPERTY(BlueprintReadOnly, Category = "BeamFarm|Farming")
	FBeamSeedData SelectedCrop;

	// Authoritative Beamable content ID string for the selected seed.
	// Set by SetSelectedCropBySeedId (from content system) or falls back to SelectedCrop.ContentId.ToString().
	// Use this as PlantRequest.seedContentId in the BeamFarmMsPlantSeed microservice call.
	UPROPERTY(BlueprintReadOnly, Category = "BeamFarm|Farming")
	FString SelectedCropContentId;

	// Call this from your inventory widget when the player selects a seed item.
	UFUNCTION(BlueprintCallable, Category = "BeamFarm|Farming")
	void SetSelectedCrop(const FBeamSeedData& SeedData);

	// Convenience: look up a plant in the content system by its SeedItemContentId, then select it.
	// Returns false if no matching plant content is found.
	UFUNCTION(BlueprintCallable, Category = "BeamFarm|Farming")
	bool SetSelectedCropBySeedId(const FString& SeedItemContentId);

	// Deselects the current crop and returns to Idle. Call when the player closes the inventory
	// or explicitly removes the seed selection.
	UFUNCTION(BlueprintCallable, Category = "BeamFarm|Farming")
	void ClearSelectedCrop();

	UFUNCTION(BlueprintPure, Category = "BeamFarm|Farming")
	bool HasSelectedCrop();

	// Main entry point from slot click. Dispatches based on slot and farming state.
	UFUNCTION(BlueprintCallable, Category = "BeamFarm|Farming")
	void InteractWithSlot(AFarmSlotActor* Slot);

	// Returns all plant data from content objects loaded in the content system.
	UFUNCTION(BlueprintCallable, Category = "BeamFarm|Farming")
	TArray<FBeamPlantData> GetAllPlants();

	// Looks up a single plant by SeedItemContentId. Returns false if not found.
	UFUNCTION(BlueprintCallable, Category = "BeamFarm|Farming")
	bool FindPlantBySeedId(const FString& plantContentId, FBeamPlantData& OutPlantData);

	// Fired after a seed is consumed from the slot. Override in Blueprint to:
	//   1. Call the auto-generated BeamFarmMsPlantSeed node with:
	//        seedContentId        = SeedItemContentId  (== SelectedCropContentId)
	//        slotId               = the slot actor's SlotId property
	//        harvestItemContentId = SelectedCrop.HarvestItemContentId
	//        growTimeSeconds      = SelectedCrop.GrowTimeSeconds
	//   2. Optionally deduct the seed from any local UI inventory cache.
	// The Slot actor reference is not passed here because it was already planted by the time
	// this fires — use the slot's SlotId from your Blueprint context instead.
	UFUNCTION(BlueprintImplementableEvent, Category = "BeamFarm|Farming")
	void OnSeedConsumed(const FString& SeedItemContentId, int32 Quantity);

	// Fired after the slot is reset following a harvest. Override in Blueprint to:
	//   1. Call the auto-generated BeamFarmMsCollectHarvest node with:
	//        slotId = Slot->SlotId
	//   2. On success, use CollectResult.harvestedItemContentId to update any local UI.
	//      (Beamable SDK also pushes an inventory-changed event automatically.)
	UFUNCTION(BlueprintImplementableEvent, Category = "BeamFarm|Farming")
	void OnItemsHarvested(AFarmSlotActor* Slot, const FString& ItemContentId, int32 Quantity);

	// Implement in Blueprint to react to state transitions (e.g. show/hide planting cursor).
	UFUNCTION(BlueprintImplementableEvent, Category = "BeamFarm|Farming")
	void OnFarmingStateChanged(EFarmingInteractionState NewState);

	// Implement in Blueprint to show feedback when the player clicks an empty slot with no crop selected.
	UFUNCTION(BlueprintImplementableEvent, Category = "BeamFarm|Farming")
	void OnNoCropSelected();

private:
	void SetFarmingState(EFarmingInteractionState NewState);

	// Cached reference to the content subsystem
	UPROPERTY()
	TObjectPtr<UBeamContentSubsystem> ContentSubsystem;
};
