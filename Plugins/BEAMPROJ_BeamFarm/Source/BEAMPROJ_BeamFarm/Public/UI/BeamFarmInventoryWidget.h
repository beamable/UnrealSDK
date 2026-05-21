// Copyright Beamable, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Farming/FarmTypes.h"
#include "BeamPlantData.h"
#include "BeamSeedData.h"
#include "BeamFarmInventoryWidget.generated.h"

/**
 * Inventory panel widget for the BeamFarm demo.
 *
 * Displays the player's crops (CROPS tab) and raw materials (MATERIALS tab).
 * Handles item selection, planting selection, and SEND TO LAB routing.
 *
 * Workflow:
 *   - Override OnTabSwitched to swap the visible item grid.
 *   - Override OnItemSelectionChanged to populate the item detail panel.
 *   - Override OnSendToLabRequested to forward the item to UBeamFarmMutationLabWidget.
 *   - Override OnPlantingSelectionRequested to call UBeamFarmSubsystem::SetSelectedCrop.
 *   - Call PopulateInventory() from the Beamable inventory delegate when item counts change.
 */
UCLASS(Abstract, Blueprintable, BlueprintType)
class BEAMPROJ_BEAMFARM_API UBeamFarmInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = "BeamFarm|Inventory")
	EBeamFarmInventoryTab ActiveTab = EBeamFarmInventoryTab::Crops;

	UPROPERTY(BlueprintReadOnly, Category = "BeamFarm|Inventory")
	FBeamPlantData SelectedItem;

	UPROPERTY(BlueprintReadOnly, Category = "BeamFarm|Inventory")
	int32 SelectedItemQuantity = 0;

	UPROPERTY(BlueprintReadOnly, Category = "BeamFarm|Inventory")
	bool bHasSelection = false;

	UPROPERTY(BlueprintReadOnly, Category = "BeamFarm|Inventory")
	FBeamSeedData SelectedSeedItem;

	UPROPERTY(BlueprintReadOnly, Category = "BeamFarm|Inventory")
	int32 SelectedSeedItemQuantity = 0;

	UPROPERTY(BlueprintReadOnly, Category = "BeamFarm|Inventory")
	bool bHasSeedSelection = false;

	// Switch between Crops and Materials tabs.
	UFUNCTION(BlueprintCallable, Category = "BeamFarm|Inventory")
	void SwitchToTab(EBeamFarmInventoryTab Tab);

	// Called from Blueprint item slot widgets when the player taps/clicks a crop item.
	UFUNCTION(BlueprintCallable, Category = "BeamFarm|Inventory")
	void SelectItem(const FBeamPlantData& Item, int32 Quantity);

	// Called from Blueprint item slot widgets when the player taps/clicks a seed item.
	UFUNCTION(BlueprintCallable, Category = "BeamFarm|Inventory")
	void SelectSeedItem(const FBeamSeedData& Item, int32 Quantity);

	// Clears the current selection and hides the detail panel.
	UFUNCTION(BlueprintCallable, Category = "BeamFarm|Inventory")
	void ClearSelection();

	// Triggers SEND TO LAB for the currently selected item.
	// QuantityToSend must be > 0 and <= SelectedItemQuantity.
	UFUNCTION(BlueprintCallable, Category = "BeamFarm|Inventory")
	void RequestSendToLab(int32 QuantityToSend);

	// Triggers planting selection for the currently selected crop.
	// Blueprint should forward this to UBeamFarmSubsystem::SetSelectedCrop.
	UFUNCTION(BlueprintCallable, Category = "BeamFarm|Inventory")
	void RequestSelectForPlanting();

	// Called by Blueprint when Beamable inventory data is available/updated.
	// Push the full item lists here to let the C++ state stay consistent.
	UFUNCTION(BlueprintCallable, Category = "BeamFarm|Inventory")
	void PopulateInventory(const TArray<FBeamPlantData>& CropItems, const TArray<FBeamSeedData>& MaterialItems);

	// Override in Blueprint: rebuild the item grid for the new tab.
	UFUNCTION(BlueprintImplementableEvent, Category = "BeamFarm|Inventory")
	void OnTabSwitched(EBeamFarmInventoryTab NewTab);

	// Override in Blueprint: populate the item detail panel.
	UFUNCTION(BlueprintImplementableEvent, Category = "BeamFarm|Inventory")
	void OnItemSelectionChanged(const FBeamPlantData& Item, int32 Quantity);

	// Override in Blueprint: hide the detail panel and deselect any item slot.
	UFUNCTION(BlueprintImplementableEvent, Category = "BeamFarm|Inventory")
	void OnSelectionCleared();

	// Override in Blueprint: add seed Item to the Mutation Lab queue (call MutationLabWidget->AddToQueue).
	UFUNCTION(BlueprintImplementableEvent, Category = "BeamFarm|Inventory")
	void OnSendToLabRequested(const FBeamSeedData& Item, int32 Quantity);

	// Override in Blueprint: call UBeamFarmSubsystem::SetSelectedCrop and close the inventory panel.
	UFUNCTION(BlueprintImplementableEvent, Category = "BeamFarm|Inventory")
	void OnPlantingSelectionRequested(const FBeamSeedData& Item);

	// Override in Blueprint: populate the seed item detail panel.
	UFUNCTION(BlueprintImplementableEvent, Category = "BeamFarm|Inventory")
	void OnSeedItemSelectionChanged(const FBeamSeedData& Item, int32 Quantity);

	// Override in Blueprint: rebuild item grids with the fresh data.
	UFUNCTION(BlueprintImplementableEvent, Category = "BeamFarm|Inventory")
	void OnInventoryPopulated(const TArray<FBeamPlantData>& CropItems, const TArray<FBeamSeedData>& MaterialItems);

private:
	TArray<FBeamPlantData> CachedCropItems;
	TArray<FBeamSeedData> CachedMaterialItems;
};
