﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/InventoryView.h"
#include "Runtime/BeamRuntimeSubsystem.h"
#include "Subsystems/Content/BeamContentSubsystem.h"
#include "BeamInventorySubsystem.generated.h"

struct FOptionalMapOfInt64;
struct FOptionalArrayOfItemUpdateRequestBody;
struct FOptionalArrayOfItemDeleteRequestBody;
class UBeamInventoryApi;
class UBeamInventoryNotifications;

USTRUCT(BlueprintType)
struct FBeamPlayerCurrency
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly,Category="Beam")
	FUserSlot OwnerPlayer;

	UPROPERTY(BlueprintReadOnly,Category="Beam")
	FBeamContentId ContentId;

	UPROPERTY(BlueprintReadWrite, Category="Beam")
	int64 Amount = 0;

	UPROPERTY(BlueprintReadWrite, Category="Beam")
	TMap<FString, FString> Properties;
};

USTRUCT(BlueprintType)
struct FBeamItemState
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Beam")
	FBeamContentId ContentId;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Beam")
	int64 InstanceId = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Beam")
	FString FederatedId;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Beam")
	TMap<FString, FString> Properties;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Beam")
	FDateTime CreatedAt;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Beam")
	FDateTime UpdatedAt;

	friend bool operator==(const FBeamItemState& Lhs, const FBeamItemState& RHS)
	{
		return Lhs.InstanceId == RHS.InstanceId;
	}

	friend bool operator!=(const FBeamItemState& Lhs, const FBeamItemState& RHS)
	{
		return !(Lhs == RHS);
	}
};


USTRUCT(BlueprintType)
struct FBeamInventoryState
{
	GENERATED_BODY()

	FBeamGamerTag OwnerPlayerGamerTag;
	FUserSlot OwnerPlayer;


	TMap<FBeamContentId, int64> Currencies;
	TMap<FBeamContentId, TMap<FString, FString>> CurrencyProperties;

	TMap<FBeamContentId, TArray<FBeamItemState>> Items;

	TArray<FString> CachedScopes;

	bool TryGetPlayerCurrencyProperties(const FBeamContentId& CurrencyId, FBeamPlayerCurrency& Currency);

	bool TryGetCurrencyProperties(const FBeamContentId& CurrencyId, TMap<FString, FString>& Props);

	bool TryGetCurrencyAmount(const FBeamContentId& CurrencyId, int64& Amount);

	void GetAllCurrencies(TArray<FBeamPlayerCurrency>& OutCurrencies);
};

USTRUCT(BlueprintType)
struct FBeamInventoryUpdateCommand
{
	GENERATED_BODY()

	UPROPERTY()
	TMap<FBeamContentId, int64> CurrencyChanges;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Beam")
	FUserSlot OwnerSlot;

	int64 CreateItemCount;

	TMap<TTuple<FBeamContentId, int64>, TMap<FString, FString>> CreatedItems;
	TArray<TTuple<FBeamContentId, int64>> RemovedItems;
	TMap<TTuple<FBeamContentId, int64>, TMap<FString, FString>> ChangedItems;


	/**
	 * Adds the given 'amount' to the passed in currency.  
	 */
	void AddCurrency(const FBeamContentId& CurrencyId, int64 Amount);

	/**
	 * Removes 'amount' of the passed in currency. Amount is a positive number.
	 * @param Amount Positive number representing the amount to remove.
	 */
	void RemoveCurrency(const FBeamContentId& CurrencyId, int64 Amount);

	/**
	 * Modifies the currency by the given amount ('amount' sign matters). 
	 */
	void ModifyCurrency(const FBeamContentId& CurrencyId, int64 Amount);

	void GetAllModifiedCurrencies(TArray<FString>& Ids, FOptionalMapOfInt64& Currencies) const;


	void CreateItem(FBeamContentId Id, TMap<FString, FString> Properties);

	void RemoveItem(FBeamContentId Id, int64 InstanceId);

	void UpdateItem(FBeamContentId Id, int64 InstanceId, TMap<FString, FString> Properties);

	bool ApplyToState(FBeamInventoryState& State);

	void GetAllDeletedItems(FOptionalArrayOfItemDeleteRequestBody& DeletedItems, UObject* Owner = GetTransientPackage()) const;

	void GetAllUpdatedItems(FOptionalArrayOfItemUpdateRequestBody& UpdatedItems, UObject* Owner = GetTransientPackage()) const;

	void GetAllCreatedItems(FOptionalArrayOfItemCreateRequestBody& NewItems, UObject* Owner = GetTransientPackage()) const;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInventoryRefreshed, FBeamGamerTag, GamerTag, FUserSlot, UserSlot);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnInventoryRefreshedCode, FBeamGamerTag, FUserSlot);

/**
 * 
 */
UCLASS(BlueprintType)
class BEAMABLECORERUNTIME_API UBeamInventorySubsystem : public UBeamRuntimeSubsystem
{
	GENERATED_BODY()

	TMap<FBeamGamerTag, FBeamInventoryState> Inventories;

	TMap<FUserSlot, FBeamInventoryUpdateCommand> UpdateCommands;

	UPROPERTY()
	UBeamInventoryApi* InventoryApi;

	UPROPERTY()
	UBeamInventoryNotifications* InventoryNotifications;

	UPROPERTY()
	UBeamContentSubsystem* ContentSubsystem;


	virtual void InitializeWhenUnrealReady_Implementation(FBeamOperationHandle& ResultOp) override;

	virtual void OnUserSignedIn_Implementation(const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser, const bool bIsFirstAuth, FBeamOperationHandle& ResultOp) override;

	virtual void OnPostUserSignedOut_Implementation(const FUserSlot& UserSlot, const EUserSlotClearedReason Reason, const FBeamRealmUser& BeamRealmUser, FBeamOperationHandle& ResultOp) override;

public:
	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, meta=(DefaultToSelf="CallingContext"))
	static UBeamInventorySubsystem* GetSelf(const UObject* CallingContext) { return CallingContext->GetWorld()->GetGameInstance()->GetSubsystem<UBeamInventorySubsystem>(); }

	/**
	 * This gets called in three cases:
	 *  - Whenever a FetchAllInventoryOperation for a given UserSlot is about to be completed.
	 *  - Whenever a FetchPlayerInventoryOperation for a given GamerTag is about to be completed.
	 *  - After we have updated the local inventory in response to receiving a remote notification that the inventory needed refreshing.
	 *
	 *  This is NOT called as part of any write-based operations of this subsystem.
	 */
	UPROPERTY(BlueprintAssignable)
	FOnInventoryRefreshed OnInventoryRefreshed;

	/**
	 * @copybrief OnInventoryRefreshed
	 */
	FOnInventoryRefreshedCode OnInventoryRefreshedCode;
	
	/**
	 * @brief Gets the list of all inventory items and currencies from the backend and updates the local inventory state.  
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Inventory", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle FetchAllInventoryOperation(FUserSlot UserSlot, FBeamOperationEventHandler OnOperationEvent);

	/**
	 * @copydoc FetchAllInventoryOperation 
	 */
	FBeamOperationHandle CPP_FetchAllInventoryOperation(FUserSlot Player, FBeamOperationEventHandlerCode OnOperationEvent);

	/**
	 * @brief Gets the list of all inventory items and currencies from the backend and updates the local inventory state for the given GamerTag.  
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Inventory", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle FetchPlayerInventoryOperation(FUserSlot UserSlot, FBeamGamerTag GamerTag, FBeamOperationEventHandler OnOperationEvent);
	
	/**
	 * @copydoc FetchPlayerInventoryOperation 
	 */
	FBeamOperationHandle CPP_FetchPlayerInventoryOperation(FUserSlot Player, FBeamGamerTag GamerTag, FBeamOperationEventHandlerCode OnOperationEvent);

	/**
	 * @brief Commits the prepared FBeamInventoryUpdateCommand for the requesting player (see BeginInventoryUpdate and Prepare_____ functions).  
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Inventory", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle CommitInventoryUpdateOperation(FUserSlot UserSlot, FBeamOperationEventHandler OnOperationEvent);

	/**
	 * @copydoc CommitInventoryUpdateOperation 
	 */
	FBeamOperationHandle CPP_CommitInventoryUpdateOperation(FUserSlot Player, FBeamOperationEventHandlerCode OnOperationEvent);

	/**
	 * @brief Takes a map of currency (and their deltas), prepare the FBeamInventoryUpdate and then Commits the update operation.
	 * Its a shorthand for BeginInventoryUpdate => PrepareModifyCurrency (N times) => CommitInventoryUpdateOperation.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Inventory", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle ModifyCurrenciesOperation(FUserSlot Player, TMap<FBeamContentId, int64> CurrencyChanges, FBeamOperationEventHandler OnOperationEvent);

	/**
	 * @copydoc ModifyCurrenciesOperation 
	 */
	FBeamOperationHandle CPP_ModifyCurrenciesOperation(FUserSlot Player, TMap<FBeamContentId, int64> CurrencyChanges, FBeamOperationEventHandlerCode OnOperationEvent);


	/**
	 * @brief Given a currency FBeamContentId, gets the amount the player has. Returns false if no player is signed into th given slot.
	 */
	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"),Category="Beam")
	bool TryGetCurrencyAmount(FUserSlot Player, const FBeamContentId& CurrencyId, int64& Amount);

	/**
	 * @brief Gets the list of all currencies the given player has. Returns false if no player is signed into th given slot.
	 */
	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"),Category="Beam")
	bool TryGetAllCurrencies(FUserSlot Player, TArray<FBeamPlayerCurrency>& Currencies);

	/**
	 * @brief Gets all items for the given player. 
	 */
	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue", AutoCreateRefTerm="ItemStates"), Category="Beam")
	bool TryGetAllItems(FUserSlot Player, TArray<FBeamItemState>& ItemStates);

	/**
	 * @brief Given a currency FBeamContentId, gets the amount the player has. Returns false if no player is signed into th given slot.
	 */
	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"),Category="Beam")
	bool TryGetCurrencyAmountByGamerTag(const FBeamGamerTag& GamerTag, const FBeamContentId& CurrencyId, int64& Amount);

	/**
	 * @brief Gets the list of all currencies the given player has. Returns false if no player is signed into th given slot.
	 */
	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"),Category="Beam")
	bool TryGetAllCurrenciesByGamerTag(const FBeamGamerTag& GamerTag, TArray<FBeamPlayerCurrency>& Currencies);

	/**
	 * @brief Gets all items for the given player. 
	 */
	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue", AutoCreateRefTerm="ItemStates"), Category="Beam")
	bool TryGetAllItemsByGamerTag(const FBeamGamerTag& GamerTag, TArray<FBeamItemState>& ItemStates);
	
	/**
	 * @brief Begins constructing an FBeamInventoryUpdateCommand for a particular player. Can force reset any update already in construction for the given player. 
	 */
	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"),Category="Beam")
	bool BeginInventoryUpdate(FUserSlot Player, FBeamInventoryUpdateCommand& Commands, bool ResetIfExists = false);

	/**
	 * @brief Adds an "Add Currency" change to the FBeamInventoryUpdateCommand of the given player. Must be called between BeginInventoryUpdate and CommitInventoryUpdate.
	 * Gain is a positive number here (how much you want to add?).
	 */
	UFUNCTION(BlueprintCallable, Category="Beam")
	void PrepareAddCurrency(FUserSlot Player, FBeamContentId CurrencyId, int64 Gain);

	/**
	 * @brief Adds an "Remove Currency" change to the FBeamInventoryUpdateCommand of the given player. Must be called between BeginInventoryUpdate and CommitInventoryUpdate.
	 * Loss is a positive number here (how much you want to remove?).
	 */
	UFUNCTION(BlueprintCallable, Category="Beam")
	void PrepareRemoveCurrency(FUserSlot Player, FBeamContentId CurrencyId, int64 Loss);

	/**
	 * @brief Adds an "Modify Currency" change to the FBeamInventoryUpdateCommand of the given player. Must be called between BeginInventoryUpdate and CommitInventoryUpdate.
	 * Amount is a positive OR negative number here (what's the delta you want to apply?).
	 */
	UFUNCTION(BlueprintCallable, Category="Beam")
	void PrepareModifyCurrency(FUserSlot Player, FBeamContentId CurrencyId, int64 Amount);

	/**
	 * @brief Adds an "Create Item" change to the FBeamInventoryUpdateCommand of the given player. Must be called between BeginInventoryUpdate and CommitInventoryUpdate.	 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam")
	void PrepareCreateItem(FUserSlot Player, FBeamContentId ItemId, TMap<FString, FString> Properties);


	/**
	 * @brief Adds an "Remove Item" change to the FBeamInventoryUpdateCommand of the given player. Must be called between BeginInventoryUpdate and CommitInventoryUpdate.	 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam")
	void PrepareRemoveItem(FUserSlot Player, const FBeamItemState& State);

	/**
	 * @brief Adds an "Remove Item" change to the FBeamInventoryUpdateCommand of the given player. Must be called between BeginInventoryUpdate and CommitInventoryUpdate.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam")
	void PrepareRemoveItemWithId(FUserSlot Player, FBeamContentId ContentId, int64 InstanceId);

	/**
	 * @brief Adds an "Modify Item" change to the FBeamInventoryUpdateCommand of the given player. Must be called between BeginInventoryUpdate and CommitInventoryUpdate.
	 * Will pass along the properties in the given FBeamItemState to update that item's state.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam")
	void PrepareModifyItem(FUserSlot Player, const FBeamItemState& State);

	/**
	 * @brief Adds an "Modify Item" change to the FBeamInventoryUpdateCommand of the given player. Must be called between BeginInventoryUpdate and CommitInventoryUpdate.	 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam")
	void PrepareModifyItemById(FUserSlot Player, FBeamContentId ContentId, int64 InstanceId, TMap<FString, FString> Properties);

private:
	UFUNCTION()
	bool FetchInventoryForSlot(FUserSlot Player, FBeamOperationHandle Op);

	UFUNCTION()
	bool FetchInventoryForPlayer(FUserSlot RequestingSlot, FBeamGamerTag GamerTag, FBeamOperationHandle Op);

	UFUNCTION()
	bool CommitInventoryUpdate(FUserSlot Player, FBeamOperationHandle Op);	

	UFUNCTION()
	void MergeInventoryViewIntoState(const UInventoryView* InventoryView, FBeamInventoryState& Inventory);
	
	UFUNCTION()
	void InvokeOnInventoryRefreshed(const FBeamGamerTag& GamerTag, const FUserSlot OwnerPlayer);
};
