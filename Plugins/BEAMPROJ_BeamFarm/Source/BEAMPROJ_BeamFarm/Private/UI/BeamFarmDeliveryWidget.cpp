// Copyright Beamable, Inc. All Rights Reserved.

#include "UI/BeamFarmDeliveryWidget.h"
#include "Subsystem/BeamFarmSubsystem.h"

void UBeamFarmDeliveryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UBeamFarmSubsystem* Sub = GetGameInstance()->GetSubsystem<UBeamFarmSubsystem>();
	if (Sub)
	{
		Sub->OnDeliveryOrdersReceived.AddDynamic(this, &UBeamFarmDeliveryWidget::HandleDeliveryOrdersReceived);
		Sub->OnDeliveryCompleted.AddDynamic(this, &UBeamFarmDeliveryWidget::HandleDeliveryCompleted);
		Sub->OnDeliveryFailed.AddDynamic(this, &UBeamFarmDeliveryWidget::HandleDeliveryFailed);
	}
}

void UBeamFarmDeliveryWidget::NativeDestruct()
{
	UBeamFarmSubsystem* Sub = GetGameInstance()->GetSubsystem<UBeamFarmSubsystem>();
	if (Sub)
	{
		Sub->OnDeliveryOrdersReceived.RemoveDynamic(this, &UBeamFarmDeliveryWidget::HandleDeliveryOrdersReceived);
		Sub->OnDeliveryCompleted.RemoveDynamic(this, &UBeamFarmDeliveryWidget::HandleDeliveryCompleted);
		Sub->OnDeliveryFailed.RemoveDynamic(this, &UBeamFarmDeliveryWidget::HandleDeliveryFailed);
	}

	Super::NativeDestruct();
}

void UBeamFarmDeliveryWidget::RefreshOrders()
{
	UBeamFarmSubsystem* Sub = GetGameInstance()->GetSubsystem<UBeamFarmSubsystem>();
	if (Sub)
	{
		Sub->GetDeliveryOrders();
	}
}

void UBeamFarmDeliveryWidget::SelectOrder(const FBeamDeliveryOrderInfo& Order)
{
	SelectedOrder = Order;
	bHasSelectedOrder = true;
	OnOrderSelected(Order);
}

void UBeamFarmDeliveryWidget::ClearSelectedOrder()
{
	SelectedOrder = FBeamDeliveryOrderInfo{};
	bHasSelectedOrder = false;
	OnOrderSelectionCleared();
}

void UBeamFarmDeliveryWidget::SelectItemForDelivery(int64 ItemInstanceId, const FString& ItemContentId)
{
	SelectedItemInstanceId = ItemInstanceId;
	SelectedItemContentId = ItemContentId;
	bHasSelectedItem = true;
	OnItemSelectedForDelivery(ItemInstanceId, ItemContentId);
}

void UBeamFarmDeliveryWidget::ClearSelectedItem()
{
	SelectedItemInstanceId = 0;
	SelectedItemContentId = TEXT("");
	bHasSelectedItem = false;
}

void UBeamFarmDeliveryWidget::ConfirmDelivery()
{
	if (!bHasSelectedOrder || !bHasSelectedItem || bIsDelivering)
	{
		return;
	}

	UBeamFarmSubsystem* Sub = GetGameInstance()->GetSubsystem<UBeamFarmSubsystem>();
	if (!Sub)
	{
		return;
	}

	bIsDelivering = true;
	Sub->DeliverOrder(SelectedOrder.OrderId, SelectedItemInstanceId);
}

void UBeamFarmDeliveryWidget::HandleDeliveryOrdersReceived(const TArray<FBeamDeliveryOrderInfo>& Orders)
{
	ActiveOrders = Orders;
	OnOrdersRefreshed(Orders);
}

void UBeamFarmDeliveryWidget::HandleDeliveryCompleted(const FString& OrderId, const FString& RewardCurrencyId, int32 RewardAmount)
{
	bIsDelivering = false;
	ClearSelectedOrder();
	ClearSelectedItem();
	OnDeliveryCompleted(OrderId, RewardCurrencyId, RewardAmount);
}

void UBeamFarmDeliveryWidget::HandleDeliveryFailed(const FString& OrderId, const FString& ErrorMessage)
{
	bIsDelivering = false;
	OnDeliveryFailed(OrderId, ErrorMessage);
}
