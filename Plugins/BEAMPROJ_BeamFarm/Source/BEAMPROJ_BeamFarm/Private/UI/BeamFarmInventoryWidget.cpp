// Copyright Beamable, Inc. All Rights Reserved.

#include "UI/BeamFarmInventoryWidget.h"

void UBeamFarmInventoryWidget::SwitchToTab(EBeamFarmInventoryTab Tab)
{
	if (ActiveTab == Tab)
	{
		return;
	}
	ActiveTab = Tab;
	ClearSelection();
	OnTabSwitched(Tab);
}

void UBeamFarmInventoryWidget::SelectItem(const FBeamPlantData& Item, int32 Quantity)
{
	SelectedItem = Item;
	SelectedItemQuantity = Quantity;
	bHasSelection = true;
	OnItemSelectionChanged(Item, Quantity);
}

void UBeamFarmInventoryWidget::SelectSeedItem(const FBeamSeedData& Item, int32 Quantity)
{
	SelectedSeedItem = Item;
	SelectedSeedItemQuantity = Quantity;
	bHasSeedSelection = true;
	OnSeedItemSelectionChanged(Item, Quantity);
}

void UBeamFarmInventoryWidget::ClearSelection()
{
	SelectedItem = FBeamPlantData();
	SelectedItemQuantity = 0;
	bHasSelection = false;
	SelectedSeedItem = FBeamSeedData();
	SelectedSeedItemQuantity = 0;
	bHasSeedSelection = false;
	OnSelectionCleared();
}

void UBeamFarmInventoryWidget::RequestSendToLab(int32 QuantityToSend)
{
	if (!bHasSeedSelection || QuantityToSend <= 0 || QuantityToSend > SelectedSeedItemQuantity)
	{
		return;
	}
	OnSendToLabRequested(SelectedSeedItem, QuantityToSend);
}

void UBeamFarmInventoryWidget::RequestSelectForPlanting()
{
	if (!bHasSeedSelection || SelectedSeedItemQuantity <= 0)
	{
		return;
	}
	OnPlantingSelectionRequested(SelectedSeedItem);
}

void UBeamFarmInventoryWidget::PopulateInventory(const TArray<FBeamPlantData>& CropItems, const TArray<FBeamSeedData>& MaterialItems)
{
	CachedCropItems = CropItems;
	CachedMaterialItems = MaterialItems;
	OnInventoryPopulated(CropItems, MaterialItems);
}
