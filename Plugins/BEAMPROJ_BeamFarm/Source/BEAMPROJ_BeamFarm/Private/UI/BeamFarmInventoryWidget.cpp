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

void UBeamFarmInventoryWidget::ClearSelection()
{
	SelectedItem = FBeamPlantData();
	SelectedItemQuantity = 0;
	bHasSelection = false;
	OnSelectionCleared();
}

void UBeamFarmInventoryWidget::RequestSendToLab(int32 QuantityToSend)
{
	if (!bHasSelection || QuantityToSend <= 0 || QuantityToSend > SelectedItemQuantity)
	{
		return;
	}
	OnSendToLabRequested(SelectedItem, QuantityToSend);
}

void UBeamFarmInventoryWidget::RequestSelectForPlanting()
{
	if (!bHasSelection)
	{
		return;
	}
	OnPlantingSelectionRequested(SelectedItem);
}

void UBeamFarmInventoryWidget::PopulateInventory(const TArray<FBeamPlantData>& CropItems, const TArray<FBeamPlantData>& MaterialItems)
{
	CachedCropItems = CropItems;
	CachedMaterialItems = MaterialItems;
	OnInventoryPopulated(CropItems, MaterialItems);
}
