// Copyright Beamable, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Farming/FarmTypes.h"
#include "FarmingComponent.generated.h"

class AFarmSlotActor;

/**
 * Attach to your Character/Pawn to handle all farming interactions.
 *
 * Workflow:
 *   1. Player opens inventory and selects a seed item.
 *   2. Inventory widget calls SetSelectedCrop(CropData) — enters Planting state.
 *   3. Player clicks any empty slot → slot is planted, OnSeedConsumed fires (deduct from inventory here).
 *   4. Player clicks any ReadyToHarvest slot → harvested, OnItemsHarvested fires (add to inventory here).
 *   5. Player deselects seed in inventory (or calls ClearSelectedCrop) → returns to Idle.
 *
 * Use CropDataTable to look up FFarmCropData by SeedItemContentId when the inventory
 * widget only knows the Beamable item content ID.
 *
 * Requires bEnableClickEvents = true and bEnableTouchEvents = true on the PlayerController.
 */
UCLASS(ClassGroup = (BeamFarm), meta = (BlueprintSpawnableComponent))
class BEAMPROJ_BEAMFARM_API UFarmingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFarmingComponent();

	// DataTable with rows of type FFarmCropData. Used by FindCropBySeedId and GetAllCrops.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Farming")
	TObjectPtr<UDataTable> CropDataTable;

	UPROPERTY(BlueprintReadOnly, Category = "BeamFarm|Farming")
	EFarmingInteractionState FarmingState;

	// The crop currently selected from inventory. Valid only during Planting state.
	UPROPERTY(BlueprintReadOnly, Category = "BeamFarm|Farming")
	FFarmCropData SelectedCrop;

	// Call this from your inventory widget when the player selects a seed item.
	UFUNCTION(BlueprintCallable, Category = "BeamFarm|Farming")
	void SetSelectedCrop(const FFarmCropData& CropData);

	// Convenience: look up a crop in CropDataTable by its SeedItemContentId, then select it.
	// Returns false if no matching row is found.
	UFUNCTION(BlueprintCallable, Category = "BeamFarm|Farming")
	bool SetSelectedCropBySeedId(const FString& SeedItemContentId);

	// Deselects the current crop and returns to Idle. Call when the player closes the inventory
	// or explicitly removes the seed selection.
	UFUNCTION(BlueprintCallable, Category = "BeamFarm|Farming")
	void ClearSelectedCrop();

	UFUNCTION(BlueprintPure, Category = "BeamFarm|Farming")
	bool HasSelectedCrop() const;

	// Main entry point from slot click. Dispatches based on slot and farming state.
	UFUNCTION(BlueprintCallable, Category = "BeamFarm|Farming")
	void InteractWithSlot(AFarmSlotActor* Slot);

	// Returns all rows from CropDataTable — useful for populating inventory UIs.
	UFUNCTION(BlueprintPure, Category = "BeamFarm|Farming")
	TArray<FFarmCropData> GetAllCrops() const;

	// Looks up a single crop row by SeedItemContentId. Returns false if not found.
	UFUNCTION(BlueprintPure, Category = "BeamFarm|Farming")
	bool FindCropBySeedId(const FString& SeedItemContentId, FFarmCropData& OutCropData) const;

	// Implement in Blueprint: remove one seed (SeedItemContentId) from Beamable inventory.
	UFUNCTION(BlueprintImplementableEvent, Category = "BeamFarm|Farming")
	void OnSeedConsumed(const FString& SeedItemContentId, int32 Quantity);

	// Implement in Blueprint: add harvested items (HarvestItemContentId) to Beamable inventory.
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
};
