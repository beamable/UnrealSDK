// Copyright Beamable, Inc. All Rights Reserved.

#include "UI/BeamFarmHUDWidget.h"

void UBeamFarmHUDWidget::OpenForBuilding(EBeamFarmBuildingType BuildingType)
{
	if (bIsAnyPanelOpen)
	{
		const EBeamFarmBuildingType Previous = CurrentPanel;
		bIsAnyPanelOpen = false;
		CurrentPanel = EBeamFarmBuildingType::None;
		OnPanelClosed(Previous);

		// If the player clicked the same building again, just close.
		if (Previous == BuildingType)
		{
			return;
		}
	}

	CurrentPanel = BuildingType;
	bIsAnyPanelOpen = true;
	OnPanelOpened(BuildingType);
}

void UBeamFarmHUDWidget::CloseCurrentPanel()
{
	if (!bIsAnyPanelOpen)
	{
		return;
	}

	const EBeamFarmBuildingType Previous = CurrentPanel;
	CurrentPanel = EBeamFarmBuildingType::None;
	bIsAnyPanelOpen = false;
	OnPanelClosed(Previous);
}

void UBeamFarmHUDWidget::RefreshCurrencyDisplay(int64 Biomass, int64 Crystals, int64 Energy)
{
	OnCurrencyUpdated(Biomass, Crystals, Energy);
}
