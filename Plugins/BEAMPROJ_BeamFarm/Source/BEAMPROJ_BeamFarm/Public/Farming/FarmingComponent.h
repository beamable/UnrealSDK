// Copyright Beamable, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Farming/FarmTypes.h"
#include "BeamPlantData.h"
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

	// The crop currently selected from inventory. Valid only during Planting state.
	UPROPERTY(BlueprintReadOnly, Category = "BeamFarm|Farming")
	FBeamPlantData SelectedCrop;

	// Call this from your inventory widget when the player selects a seed item.
	UFUNCTION(BlueprintCallable, Category = "BeamFarm|Farming")
	void SetSelectedCrop(const FBeamPlantData& PlantContent);

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

	// Cached reference to the content subsystem
	UPROPERTY()
	TObjectPtr<UBeamContentSubsystem> ContentSubsystem;
};
