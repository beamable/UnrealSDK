// Copyright Beamable, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Farming/FarmTypes.h"
#include "BeamFarmDeliveryWidget.generated.h"

class UBeamFarmSubsystem;

/**
 * Delivery panel widget for the BeamFarm demo.
 *
 * Displays the player's active delivery orders (populated via UBeamFarmSubsystem::GetDeliveryOrders).
 * The player selects an order and then picks a matching item from their inventory to deliver.
 * On ConfirmDelivery() the subsystem calls DeliverOrder on the microservice, which validates
 * the item's property requirements server-side, removes the item, and grants the reward currency.
 *
 * Workflow:
 *   1. Override OnOrdersRefreshed to render the order list (one slot per FBeamDeliveryOrderInfo).
 *   2. Call SelectOrder() when the player taps an order slot.
 *   3. Override OnOrderSelected to highlight the slot and show required item/properties.
 *   4. Call SelectItemForDelivery() from the inventory item slot widget, passing the item's
 *      Beamable instance ID (int64) and content ID.
 *   5. Call ConfirmDelivery() when the player presses the deliver button.
 *   6. Override OnDeliveryCompleted / OnDeliveryFailed for outcome feedback.
 *
 * Call RefreshOrders() on NativeConstruct (or when the panel becomes visible) to populate
 * the initial order list.
 */
UCLASS(Abstract, Blueprintable, BlueprintType)
class BEAMPROJ_BEAMFARM_API UBeamFarmDeliveryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// Current active delivery orders for this player.
	UPROPERTY(BlueprintReadOnly, Category = "BeamFarm|Delivery")
	TArray<FBeamDeliveryOrderInfo> ActiveOrders;

	// Order the player has chosen to fulfil.
	UPROPERTY(BlueprintReadOnly, Category = "BeamFarm|Delivery")
	FBeamDeliveryOrderInfo SelectedOrder;

	UPROPERTY(BlueprintReadOnly, Category = "BeamFarm|Delivery")
	bool bHasSelectedOrder = false;

	// Item instance the player has picked from their inventory to deliver.
	// This is the Beamable item instance ID (int64).
	UPROPERTY(BlueprintReadOnly, Category = "BeamFarm|Delivery")
	int64 SelectedItemInstanceId = 0;

	// Content ID of the selected item (e.g. "itemplant.green_spore").
	UPROPERTY(BlueprintReadOnly, Category = "BeamFarm|Delivery")
	FString SelectedItemContentId;

	UPROPERTY(BlueprintReadOnly, Category = "BeamFarm|Delivery")
	bool bHasSelectedItem = false;

	// True while a DeliverOrder call is in-flight.
	UPROPERTY(BlueprintReadOnly, Category = "BeamFarm|Delivery")
	bool bIsDelivering = false;

	// ─── Actions ───────────────────────────────────────────────────────────

	// Asks the subsystem for the latest active orders (auto-fills to MaxActiveOrders).
	// Results arrive via OnOrdersRefreshed.
	UFUNCTION(BlueprintCallable, Category = "BeamFarm|Delivery")
	void RefreshOrders();

	// Marks the given order as the one to fulfil.
	UFUNCTION(BlueprintCallable, Category = "BeamFarm|Delivery")
	void SelectOrder(const FBeamDeliveryOrderInfo& Order);

	// Clears the selected order.
	UFUNCTION(BlueprintCallable, Category = "BeamFarm|Delivery")
	void ClearSelectedOrder();

	// Records which inventory item the player wants to deliver.
	// Call from the inventory item slot widget, passing the Beamable instance ID
	// (exposed as int64 on the item entry in the Beamable inventory response).
	UFUNCTION(BlueprintCallable, Category = "BeamFarm|Delivery")
	void SelectItemForDelivery(int64 ItemInstanceId, const FString& ItemContentId);

	// Clears the selected item.
	UFUNCTION(BlueprintCallable, Category = "BeamFarm|Delivery")
	void ClearSelectedItem();

	// Submits the delivery: requires bHasSelectedOrder && bHasSelectedItem && !bIsDelivering.
	// Calls UBeamFarmSubsystem::DeliverOrder; outcome arrives via OnDeliveryCompleted /
	// OnDeliveryFailed.
	UFUNCTION(BlueprintCallable, Category = "BeamFarm|Delivery")
	void ConfirmDelivery();

	// ─── Blueprint implementable events ────────────────────────────────────

	// Override in Blueprint: rebuild the order list with the received orders.
	UFUNCTION(BlueprintImplementableEvent, Category = "BeamFarm|Delivery")
	void OnOrdersRefreshed(const TArray<FBeamDeliveryOrderInfo>& Orders);

	// Override in Blueprint: highlight the chosen order slot and show its requirements.
	UFUNCTION(BlueprintImplementableEvent, Category = "BeamFarm|Delivery")
	void OnOrderSelected(const FBeamDeliveryOrderInfo& Order);

	// Override in Blueprint: deselect the highlighted order slot.
	UFUNCTION(BlueprintImplementableEvent, Category = "BeamFarm|Delivery")
	void OnOrderSelectionCleared();

	// Override in Blueprint: show a preview of the item the player intends to deliver.
	UFUNCTION(BlueprintImplementableEvent, Category = "BeamFarm|Delivery")
	void OnItemSelectedForDelivery(int64 ItemInstanceId, const FString& ItemContentId);

	// Override in Blueprint: show success feedback and refresh inventory / order list.
	// RewardAmount units of RewardCurrencyId have been added to the player's account.
	UFUNCTION(BlueprintImplementableEvent, Category = "BeamFarm|Delivery")
	void OnDeliveryCompleted(const FString& OrderId, const FString& RewardCurrencyId, int32 RewardAmount);

	// Override in Blueprint: show error feedback (ErrorMessage explains the failure).
	UFUNCTION(BlueprintImplementableEvent, Category = "BeamFarm|Delivery")
	void OnDeliveryFailed(const FString& OrderId, const FString& ErrorMessage);

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

private:
	UFUNCTION()
	void HandleDeliveryOrdersReceived(const TArray<FBeamDeliveryOrderInfo>& Orders);

	UFUNCTION()
	void HandleDeliveryCompleted(const FString& OrderId, const FString& RewardCurrencyId, int32 RewardAmount);

	UFUNCTION()
	void HandleDeliveryFailed(const FString& OrderId, const FString& ErrorMessage);
};
