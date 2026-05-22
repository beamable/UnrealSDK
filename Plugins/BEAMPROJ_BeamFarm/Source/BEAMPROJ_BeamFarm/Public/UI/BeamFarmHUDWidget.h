// Copyright Beamable, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Farming/FarmTypes.h"
#include "BeamFarmHUDWidget.generated.h"

/**
 * Root HUD widget for the BeamFarm demo.
 *
 * Created and added to viewport by ABeamFarmPlayerController::BeginPlay.
 * Manages which panel is currently open (Farm, Mutation Lab, Inventory, etc.).
 *
 * Workflow:
 *   1. Assign a Blueprint subclass (WBP_BeamFarmHUD) to HUDWidgetClass on the PlayerController.
 *   2. Override OnPanelOpened / OnPanelClosed in that Blueprint to show/hide the relevant UMG panels.
 *   3. Override OnCurrencyUpdated to refresh any always-visible currency text blocks.
 *
 * Call RefreshCurrencyDisplay() from the Beamable inventory delegate in Blueprint whenever
 * currency values change (biomass, crystals, energy).
 */
UCLASS(Abstract, Blueprintable, BlueprintType)
class BEAMPROJ_BEAMFARM_API UBeamFarmHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// Which panel is currently open. None means the HUD is in its idle/gameplay state.
	UPROPERTY(BlueprintReadOnly, Category = "BeamFarm|HUD")
	EBeamFarmBuildingType CurrentPanel = EBeamFarmBuildingType::None;

	UPROPERTY(BlueprintReadOnly, Category = "BeamFarm|HUD")
	bool bIsAnyPanelOpen = false;

	// Opens the panel that corresponds to the given building type.
	// Closes any currently open panel first.
	UFUNCTION(BlueprintCallable, Category = "BeamFarm|HUD")
	void OpenForBuilding(EBeamFarmBuildingType BuildingType);

	// Closes the currently open panel and returns to idle state.
	UFUNCTION(BlueprintCallable, Category = "BeamFarm|HUD")
	void CloseCurrentPanel();

	// Call this whenever Beamable inventory/currency data changes to push updated values.
	UFUNCTION(BlueprintCallable, Category = "BeamFarm|HUD")
	void RefreshCurrencyDisplay(int64 Biomass, int64 Crystals, int64 Energy);

	// Override in Blueprint: show the panel UI for BuildingType (e.g. set widget visibility).
	UFUNCTION(BlueprintImplementableEvent, Category = "BeamFarm|HUD")
	void OnPanelOpened(EBeamFarmBuildingType BuildingType);

	// Override in Blueprint: hide the panel UI for PreviousPanel.
	UFUNCTION(BlueprintImplementableEvent, Category = "BeamFarm|HUD")
	void OnPanelClosed(EBeamFarmBuildingType PreviousPanel);

	// Override in Blueprint: update currency text blocks with the latest values.
	UFUNCTION(BlueprintImplementableEvent, Category = "BeamFarm|HUD")
	void OnCurrencyUpdated(int64 Biomass, int64 Crystals, int64 Energy);
};
