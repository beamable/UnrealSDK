// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalArrayOfInt32.h"
#include "AutoGen/Optionals/OptionalArrayOfInt64.h"
#include "AutoGen/SubSystems/BeamInventoryApi.h"
#include "BeamBackend/ReplacementTypes/BeamFederation.h"
#include "Content/BeamContentTypes/BeamCurrencyContent.h"
#include "Content/BeamContentTypes/BeamItemContent.h"
#include "Runtime/BeamRuntimeSubsystem.h"
#include "Subsystems/Content/BeamContentSubsystem.h"
#include "BeamInventorySubsystem.generated.h"

USTRUCT(BlueprintType)
struct FBeamPlayerCurrency
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FUserSlot OwnerPlayer;

	UPROPERTY(BlueprintReadOnly)
	FBeamContentId ContentId;

	UPROPERTY(BlueprintReadWrite)
	int64 Amount = 0;

	UPROPERTY(BlueprintReadWrite)
	TMap<FString, FString> Properties;
};

USTRUCT(BlueprintType)
struct FBeamItemState
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FBeamContentId ContentId;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int64 InstanceId = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString FederatedId;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<FString, FString> Properties;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FDateTime CreatedAt;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FDateTime UpdatedAt;
};


USTRUCT(BlueprintType)
struct FBeamInventoryState
{
	GENERATED_BODY()

	FUserSlot OwnerPlayer;


	TMap<FBeamContentId, int64> Currencies;
	TMap<FBeamContentId, TMap<FString, FString>> CurrencyProperties;

	TMap<FBeamContentId, TArray<FBeamItemState>> Items;

	TArray<FString> CachedScopes;

	bool TryGetPlayerCurrencyProperties(const FBeamContentId& CurrencyId, FBeamPlayerCurrency& Currency)
	{
		Currency.OwnerPlayer = OwnerPlayer;
		Currency.ContentId = CurrencyId;

		TryGetCurrencyProperties(CurrencyId, Currency.Properties);
		return TryGetCurrencyAmount(CurrencyId, Currency.Amount);
	}

	bool TryGetCurrencyProperties(const FBeamContentId& CurrencyId, TMap<FString, FString>& Props)
	{
		if (CurrencyProperties.Contains(CurrencyId))
		{
			Props = *CurrencyProperties.Find(CurrencyId);
			return true;
		}

		Props = {};
		return false;
	}

	bool TryGetCurrencyAmount(const FBeamContentId& CurrencyId, int64& Amount)
	{
		if (Currencies.Contains(CurrencyId))
		{
			Amount = *Currencies.Find(CurrencyId);
			return true;
		}

		Amount = 0;
		return false;
	}

	void GetAllCurrencies(TArray<FBeamPlayerCurrency>& OutCurrencies)
	{
		for (const auto Currency : Currencies)
		{
			TMap<FString, FString> Properties = {};
			if (CurrencyProperties.Contains(Currency.Key))
			{
				Properties = CurrencyProperties[Currency.Key];
			}

			OutCurrencies.Add(FBeamPlayerCurrency{
				OwnerPlayer,
				Currency.Key,
				Currency.Value,
				Properties
			});
		}
	}
};

USTRUCT(BlueprintType)
struct FBeamInventoryUpdateCommand
{
	GENERATED_BODY()

	UPROPERTY()
	TMap<FBeamContentId, int64> CurrencyChanges;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FUserSlot OwnerSlot;

	int64 CreateItemCount;

	TMap<TTuple<FBeamContentId, int64>, TMap<FString, FString>> CreatedItems;
	TArray<TTuple<FBeamContentId, int64>> RemovedItems;
	TMap<TTuple<FBeamContentId, int64>, TMap<FString, FString>> ChangedItems;


	/**
	 * Adds the given 'amount' to the passed in currency.  
	 */
	void AddCurrency(const FBeamContentId& CurrencyId, int64 Amount)
	{
		ensureAlwaysMsgf(Amount >= 0, TEXT("Gain must be greater than or equal 0"));
		ModifyCurrency(CurrencyId, Amount);
	}

	/**
	 * Removes 'amount' of the passed in currency. Amount is a positive number.
	 * @param Amount Positive number representing the amount to remove.
	 */
	void RemoveCurrency(const FBeamContentId& CurrencyId, int64 Amount)
	{
		ensureAlwaysMsgf(Amount >= 0, TEXT("Gain must be less than or equal 0"));
		ModifyCurrency(CurrencyId, -Amount);
	}

	/**
	 * Modifies the currency by the given amount ('amount' sign matters). 
	 */
	void ModifyCurrency(const FBeamContentId& CurrencyId, int64 Amount)
	{
		// No need to add it to the map if you're not gaining anything (can save requests in some cases).
		if (Amount == 0) return;

		if (CurrencyChanges.Contains(CurrencyId))
			CurrencyChanges[CurrencyId] += Amount;
		else
			CurrencyChanges.Add(CurrencyId, Amount);
	}

	void GetAllModifiedCurrencies(TArray<FString>& Ids, FOptionalMapOfInt64& Currencies) const
	{
		TArray<FBeamContentId> ContentIds;
		TMap<FString, int64> Amounts;
		CurrencyChanges.GetKeys(ContentIds);

		for (const auto& Id : ContentIds)
		{
			Ids.Add(Id.AsString);
			Amounts.Add(Id.AsString, CurrencyChanges[Id]);
		}
		Currencies.Set(&Amounts);
	}


	void CreateItem(FBeamContentId Id, TMap<FString, FString> Properties)
	{
		CreatedItems.Add({Id, CreateItemCount++}, Properties);
	}

	void RemoveItem(FBeamContentId Id, int64 InstanceId)
	{
		RemovedItems.Add({Id, InstanceId});
	}

	void UpdateItem(FBeamContentId Id, int64 InstanceId, TMap<FString, FString> Properties)
	{
		ChangedItems.Add({Id, InstanceId}, Properties);
	}

	bool ApplyToState(FBeamInventoryState& State)
	{
		for (const auto& CurrencyChange : CurrencyChanges)
		{
			const auto CurrencyId = CurrencyChange.Key;
			const auto CurrencyMod = CurrencyChange.Value;

			if (State.Currencies.Contains(CurrencyId))
				State.Currencies[CurrencyId] += CurrencyMod;
			else
				State.Currencies.Add(CurrencyId, CurrencyMod);
		}

		for (const auto CreatedItem : CreatedItems)
		{
			const auto Ids = CreatedItem.Key;
			const auto Properties = CreatedItem.Value;

			if (State.Items.Contains(Ids.Key))
			{
				auto Items = State.Items[Ids.Key];
				Items.Add(FBeamItemState{
					Ids.Key,
					Ids.Value,
					{},
					Properties,
					{},
					{}
				});
			}
			else
			{
				State.Items.Add(Ids.Key, {
					                FBeamItemState{
						                Ids.Key,
						                Ids.Value,
						                {},
						                Properties,
						                {},
						                {}
					                }
				                });
			}
		}

		for (const auto RemovedItem : RemovedItems)
		{
			const auto ContentId = RemovedItem.Key;
			const auto InstanceId = RemovedItem.Value;

			if (State.Items.Contains(ContentId))
			{
				auto Items = State.Items[ContentId];
				Items.RemoveAll([ContentId, InstanceId](FBeamItemState s)
				{
					return s.ContentId == ContentId && s.InstanceId == InstanceId;
				});
			}
		}

		for (const auto ChangedItem : ChangedItems)
		{
			const auto Ids = ChangedItem.Key;
			const auto Properties = ChangedItem.Value;

			const auto ContentId = Ids.Key;
			const auto InstanceId = Ids.Value;

			if (State.Items.Contains(Ids.Key))
			{
				auto Items = State.Items[ContentId];
				auto ItemState = Items.FindByPredicate([ContentId, InstanceId](FBeamItemState s)
				{
					return s.ContentId == ContentId && s.InstanceId == InstanceId;
				});
				if (ItemState)
					ItemState->Properties = Properties;
			}
			else
			{
				State.Items.Add(Ids.Key, {
					                FBeamItemState{
						                ContentId,
						                InstanceId,
						                {},
						                Properties,
						                {},
						                {}
					                }
				                });
			}
		}

		return true;
	}

	void GetAllDeletedItems(FOptionalArrayOfItemDeleteRequestBody& DeletedItems, UObject* Owner = GetTransientPackage()) const
	{
		// We don't set it if we have no items to remove
		if (RemovedItems.Num() == 0)
		{
			DeletedItems = {};
			return;
		}

		TArray<UItemDeleteRequestBody*> DeleteRequests;
		for (const auto RemovedItem : RemovedItems)
		{
			UItemDeleteRequestBody* Deletion = NewObject<UItemDeleteRequestBody>(Owner);
			Deletion->ContentId = RemovedItem.Key.AsString;
			Deletion->Id = RemovedItem.Value;
			DeleteRequests.Add(Deletion);
		}

		DeletedItems = FOptionalArrayOfItemDeleteRequestBody(DeleteRequests);
	}

	void GetAllUpdatedItems(FOptionalArrayOfItemUpdateRequestBody& UpdatedItems, UObject* Owner = GetTransientPackage()) const
	{
		// We don't set it if we have no items to remove
		if (ChangedItems.Num() == 0)
		{
			UpdatedItems = {};
			return;
		}

		TArray<UItemUpdateRequestBody*> UpdateRequests;
		for (const auto ChangedItem : ChangedItems)
		{
			UItemUpdateRequestBody* Update = NewObject<UItemUpdateRequestBody>(Owner);
			Update->ContentId = ChangedItem.Key.Key.AsString;
			Update->Id = ChangedItem.Key.Value;

			TArray<UItemProperty*> Properties;
			for (const auto& Prop : ChangedItem.Value)
			{
				UItemProperty* ItemProp = NewObject<UItemProperty>(Owner);
				ItemProp->Name = Prop.Key;
				ItemProp->Value = Prop.Value;
				Properties.Add(ItemProp);
			}
			Update->Properties = Properties;
			UpdateRequests.Add(Update);
		}

		UpdatedItems = FOptionalArrayOfItemUpdateRequestBody(UpdateRequests);
	}

	void GetAllCreatedItems(FOptionalArrayOfItemCreateRequestBody& NewItems, UObject* Owner = GetTransientPackage()) const
	{
		// We don't set it if we have no items to remove
		if (CreatedItems.Num() == 0)
		{
			NewItems = {};
			return;
		}

		TArray<UItemCreateRequestBody*> CreateRequests;
		for (const auto CreatedItem : CreatedItems)
		{
			UItemCreateRequestBody* Create = NewObject<UItemCreateRequestBody>(Owner);
			Create->ContentId = CreatedItem.Key.Key.AsString;

			TArray<UItemProperty*> Properties;
			for (const auto& Prop : CreatedItem.Value)
			{
				UItemProperty* ItemProp = NewObject<UItemProperty>(Owner);
				ItemProp->Name = Prop.Key;
				ItemProp->Value = Prop.Value;
				Properties.Add(ItemProp);
			}
			Create->Properties = Properties;
			CreateRequests.Add(Create);
		}

		NewItems = FOptionalArrayOfItemCreateRequestBody(CreateRequests);
	}
};


/**
 * 
 */
UCLASS(BlueprintType)
class BEAMABLECORERUNTIME_API UBeamInventorySubsystem : public UBeamRuntimeSubsystem
{
	GENERATED_BODY()

	TMap<FUserSlot, FBeamInventoryState> Inventories;

	TMap<FUserSlot, FBeamInventoryUpdateCommand> UpdateCommands;

	UPROPERTY()
	UBeamInventoryApi* InventoryApi;

	UPROPERTY()
	UBeamContentSubsystem* ContentSubsystem;

	virtual FBeamOperationHandle InitializeWhenUnrealReady() override
	{
		InventoryApi = GEngine->GetEngineSubsystem<UBeamInventoryApi>();
		ContentSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UBeamContentSubsystem>();

		for (const auto RuntimeUserSlot : GetDefault<UBeamCoreSettings>()->RuntimeUserSlots)
		{
			const auto UserSlot = FUserSlot{RuntimeUserSlot};
			Inventories.Add(UserSlot, FBeamInventoryState{UserSlot, {}, {}, {}, {}});
		}

		return Super::InitializeWhenUnrealReady();
	}

	virtual void OnPostUserSignedOut_Implementation(const FUserSlot& UserSlot, const EUserSlotClearedReason Reason, const FBeamRealmUser& BeamRealmUser) override
	{
		if (Inventories.Contains(UserSlot))
			Inventories.Remove(UserSlot);
	}

	virtual FBeamOperationHandle OnUserSignedIn(const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser, const bool bIsFirstAuth) override
	{
		FBeamOperationHandle Op = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetName(), {});
		FetchAllInventory(UserSlot, Op, this);
		return Op;
	}

public:
	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, meta=(DefaultToSelf="CallingContext"))
	static UBeamInventorySubsystem* GetSelf(const UObject* CallingContext) { return CallingContext->GetWorld()->GetGameInstance()->GetSubsystem<UBeamInventorySubsystem>(); }


	/**
	 * @brief Gets the list of all inventory items and currencies from the backend and updates the local inventory state.  
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Inventory", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle FetchAllInventoryOperation(FUserSlot UserSlot, FBeamOperationEventHandler OnOperationEvent, UObject* CallingContext)
	{
		const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
		FetchAllInventory(UserSlot, Handle, CallingContext);
		return Handle;
	}

	/**
	 * @copydoc FetchAllInventoryOperation 
	 */
	FBeamOperationHandle CPP_FetchAllInventoryOperation(FUserSlot Player, FBeamOperationEventHandlerCode OnOperationEvent, UObject* CallingContext)
	{
		const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({Player}, GetClass()->GetFName().ToString(), OnOperationEvent);
		FetchAllInventory(Player, Handle, CallingContext);
		return Handle;
	}

	/**
	 * @brief Commits the prepared FBeamInventoryUpdateCommand for the requesting player (see BeginInventoryUpdate and Prepare_____ functions).  
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Inventory", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle CommitInventoryUpdateOperation(FUserSlot UserSlot, FBeamOperationEventHandler OnOperationEvent, UObject* CallingContext)
	{
		const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
		CommitInventoryUpdate(UserSlot, Handle, CallingContext);
		return Handle;
	}

	/**
	 * @copydoc CommitInventoryUpdateOperation 
	 */
	FBeamOperationHandle CPP_CommitInventoryUpdateOperation(FUserSlot Player, FBeamOperationEventHandlerCode OnOperationEvent, UObject* CallingContext)
	{
		const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({Player}, GetClass()->GetFName().ToString(), OnOperationEvent);
		CommitInventoryUpdate(Player, Handle, CallingContext);
		return Handle;
	}

	/**
	 * @brief Takes a map of currency (and their deltas), prepare the FBeamInventoryUpdate and then Commits the update operation.
	 * Its a shorthand for BeginInventoryUpdate => PrepareModifyCurrency (N times) => CommitInventoryUpdateOperation.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Inventory", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle ModifyCurrenciesOperation(FUserSlot Player, TMap<FBeamContentId, int64> CurrencyChanges, FBeamOperationEventHandler OnOperationEvent, UObject* CallingContext)
	{
		const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({Player}, GetClass()->GetFName().ToString(), OnOperationEvent);

		FBeamInventoryUpdateCommand Cmd;
		BeginInventoryUpdate(Player, Cmd, true);
		for (const auto& CurrencyChange : CurrencyChanges)
			PrepareModifyCurrency(Player, CurrencyChange.Key, CurrencyChange.Value);

		CommitInventoryUpdate(Player, Handle, CallingContext);

		return Handle;
	}

	/**
	 * @copydoc ModifyCurrenciesOperation 
	 */
	FBeamOperationHandle CPP_ModifyCurrenciesOperation(FUserSlot Player, TMap<FBeamContentId, int64> CurrencyChanges, FBeamOperationEventHandlerCode OnOperationEvent, UObject* CallingContext)
	{
		const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({Player}, GetClass()->GetFName().ToString(), OnOperationEvent);

		FBeamInventoryUpdateCommand Cmd;
		BeginInventoryUpdate(Player, Cmd, true);
		for (const auto& CurrencyChange : CurrencyChanges)
			PrepareModifyCurrency(Player, CurrencyChange.Key, CurrencyChange.Value);

		CommitInventoryUpdate(Player, Handle, CallingContext);
		return Handle;
	}


	/**
	 * @brief Given a currency FBeamContentId, gets the amount the player has. Returns false if no player is signed into th given slot.
	 */
	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	bool TryGetCurrencyAmount(FUserSlot Player, const FBeamContentId& CurrencyId, int64& Amount)
	{
		Amount = 0;
		if (!Inventories.Contains(Player))
			return false;

		return Inventories.Find(Player)->TryGetCurrencyAmount(CurrencyId, Amount);
	}

	/**
	 * @brief Gets the list of all currencies the given player has. Returns false if no player is signed into th given slot.
	 */
	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	bool TryGetAllCurrencies(FUserSlot Player, TArray<FBeamPlayerCurrency>& Currencies)
	{
		Currencies = {};
		if (!Inventories.Contains(Player))
			return false;

		Inventories.Find(Player)->GetAllCurrencies(Currencies);
		return true;
	}

	/**
	 * @brief Gets all items for the given player. 
	 */
	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	bool TryGetAllItems(FUserSlot Player, TArray<FBeamItemState>& ItemStates)
	{
		ItemStates = {};
		if (!Inventories.Contains(Player))
			return false;

		const auto inventory = Inventories.FindRef(Player);
		for (const auto Item : inventory.Items)
			ItemStates.Append(Item.Value);

		return true;
	}

	/**
	 * @brief Begins constructing an FBeamInventoryUpdateCommand for a particular player. Can force reset any update already in construction for the given player. 
	 */
	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	bool BeginInventoryUpdate(FUserSlot Player, FBeamInventoryUpdateCommand& Commands, bool ResetIfExists = false)
	{
		if (UpdateCommands.Contains(Player))
		{
			if (ResetIfExists)
				UpdateCommands.Remove(Player);
			else
				return false;
		}

		Commands = FBeamInventoryUpdateCommand();
		Commands.OwnerSlot = Player;
		UpdateCommands.Add(Player, Commands);
		return true;
	}

	/**
	 * @brief Adds an "Add Currency" change to the FBeamInventoryUpdateCommand of the given player. Must be called between BeginInventoryUpdate and CommitInventoryUpdate.
	 * Gain is a positive number here (how much you want to add?).
	 */
	UFUNCTION(BlueprintCallable)
	void PrepareAddCurrency(FUserSlot Player, FBeamContentId CurrencyId, int64 Gain)
	{
		UBeamCurrencyContent* CurrencyContent;
		ensureAlwaysMsgf(ContentSubsystem->TryGetContentOfType(CurrencyId, CurrencyContent), TEXT("Given currency could not be found. CURRENCY_ID=%s"), *CurrencyId.AsString);
		auto Command = UpdateCommands.Find(Player);
		ensureAlwaysMsgf(Command, TEXT("BeginInventoryUpdate has not been called for the given player slot. SLOT_ID=%s"), *Player.Name);
		if (Command)
		{
			Command->AddCurrency(CurrencyId, Gain);
		}
	}

	/**
	 * @brief Adds an "Remove Currency" change to the FBeamInventoryUpdateCommand of the given player. Must be called between BeginInventoryUpdate and CommitInventoryUpdate.
	 * Loss is a positive number here (how much you want to remove?).
	 */
	UFUNCTION(BlueprintCallable)
	void PrepareRemoveCurrency(FUserSlot Player, FBeamContentId CurrencyId, int64 Loss)
	{
		UBeamCurrencyContent* CurrencyContent;
		ensureAlwaysMsgf(ContentSubsystem->TryGetContentOfType(CurrencyId, CurrencyContent), TEXT("Given currency could not be found. CURRENCY_ID=%s"), *CurrencyId.AsString);
		auto Command = UpdateCommands.Find(Player);
		ensureAlwaysMsgf(Command, TEXT("BeginInventoryUpdate has not been called for the given player slot. SLOT_ID=%s"), *Player.Name);
		if (Command)
		{
			Command->RemoveCurrency(CurrencyId, Loss);
		}
	}

	/**
	 * @brief Adds an "Modify Currency" change to the FBeamInventoryUpdateCommand of the given player. Must be called between BeginInventoryUpdate and CommitInventoryUpdate.
	 * Amount is a positive OR negative number here (what's the delta you want to apply?).
	 */
	UFUNCTION(BlueprintCallable)
	void PrepareModifyCurrency(FUserSlot Player, FBeamContentId CurrencyId, int64 Amount)
	{
		UBeamCurrencyContent* CurrencyContent;
		ensureAlwaysMsgf(ContentSubsystem->TryGetContentOfType(CurrencyId, CurrencyContent), TEXT("Given currency could not be found. CURRENCY_ID=%s"), *CurrencyId.AsString);
		auto Command = UpdateCommands.Find(Player);
		ensureAlwaysMsgf(Command, TEXT("BeginInventoryUpdate has not been called for the given player slot. SLOT_ID=%s"), *Player.Name);
		if (Command)
		{
			Command->ModifyCurrency(CurrencyId, Amount);
		}
	}

	/**
	 * @brief Adds an "Create Item" change to the FBeamInventoryUpdateCommand of the given player. Must be called between BeginInventoryUpdate and CommitInventoryUpdate.	 
	 */
	UFUNCTION(BlueprintCallable)
	void PrepareCreateItem(FUserSlot Player, FBeamContentId ItemId, TMap<FString, FString> Properties)
	{
		UBeamItemContent* ItemContent;
		ensureAlwaysMsgf(ContentSubsystem->TryGetContentOfType(ItemId, ItemContent), TEXT("Given item could not be found or is of the wrong type. ITEM_ID=%s"), *ItemId.AsString);
		auto Command = UpdateCommands.Find(Player);
		ensureAlwaysMsgf(Command, TEXT("BeginInventoryUpdate has not been called for the given player slot. SLOT_ID=%s"), *Player.Name);
		if (Command)
		{
			Command->CreateItem(ItemId, Properties);
		}
	}


	/**
	 * @brief Adds an "Remove Item" change to the FBeamInventoryUpdateCommand of the given player. Must be called between BeginInventoryUpdate and CommitInventoryUpdate.	 
	 */
	UFUNCTION(BlueprintCallable)
	void PrepareRemoveItem(FUserSlot Player, const FBeamItemState& State)
	{
		FBeamContentId ContentId = State.ContentId;
		int64 InstanceId = State.InstanceId;
		PrepareRemoveItemWithId(Player, ContentId, InstanceId);
	}

	/**
	 * @brief Adds an "Remove Item" change to the FBeamInventoryUpdateCommand of the given player. Must be called between BeginInventoryUpdate and CommitInventoryUpdate.
	 */
	UFUNCTION(BlueprintCallable)
	void PrepareRemoveItemWithId(FUserSlot Player, FBeamContentId ContentId, int64 InstanceId)
	{
		UBeamItemContent* ItemContent;
		ensureAlwaysMsgf(ContentSubsystem->TryGetContentOfType(ContentId, ItemContent), TEXT("Given item could not be found. ITEM_ID=%s"), *ContentId.AsString);
		auto Command = UpdateCommands.Find(Player);
		ensureAlwaysMsgf(Command, TEXT("BeginInventoryUpdate has not been called for the given player slot. SLOT_ID=%s"), *Player.Name);
		if (Command)
		{
			Command->RemoveItem(ContentId, InstanceId);
		}
	}

	/**
	 * @brief Adds an "Modify Item" change to the FBeamInventoryUpdateCommand of the given player. Must be called between BeginInventoryUpdate and CommitInventoryUpdate.
	 * Will pass along the properties in the given FBeamItemState to update that item's state.
	 */
	UFUNCTION(BlueprintCallable)
	void PrepareModifyItem(FUserSlot Player, const FBeamItemState& State)
	{
		PrepareModifyItemById(Player, State.ContentId, State.InstanceId, State.Properties);
	}

	/**
	 * @brief Adds an "Modify Item" change to the FBeamInventoryUpdateCommand of the given player. Must be called between BeginInventoryUpdate and CommitInventoryUpdate.	 
	 */
	UFUNCTION(BlueprintCallable)
	void PrepareModifyItemById(FUserSlot Player, FBeamContentId ContentId, int64 InstanceId, TMap<FString, FString> Properties)
	{
		UBeamItemContent* ItemContent;
		ensureAlwaysMsgf(ContentSubsystem->TryGetContentOfType(ContentId, ItemContent), TEXT("Given item could not be found. ITEM_ID=%s"), *ContentId.AsString);
		auto Command = UpdateCommands.Find(Player);
		ensureAlwaysMsgf(Command, TEXT("BeginInventoryUpdate has not been called for the given player slot. SLOT_ID=%s"), *Player.Name);
		if (Command)
		{
			Command->UpdateItem(ContentId, InstanceId, Properties);
		}
	}

private:
	UFUNCTION()
	bool FetchAllInventory(FUserSlot Player, FBeamOperationHandle Op, UObject* CallingContext)
	{
		FBeamRealmUser UserData;
		Runtime->UserSlotSystem->GetUserDataAtSlot(Player, UserData, this);

		const auto GetInventoryReq = UGetInventoryRequest::Make(UserData.GamerTag, {}, GetTransientPackage());
		FOnGetInventoryFullResponse Handler{};
		Handler.BindLambda([this, Op](FBeamFullResponse<UGetInventoryRequest*, UInventoryView*> Response)
		{
			if (Response.State == Success)
			{
				FBeamInventoryState& Inventory = *Inventories.Find(Response.Context.UserSlot);

				const auto InventoryView = Response.SuccessData;
				for (const auto Currency : InventoryView->Currencies)
				{
					const auto CurrencyContentId = FBeamContentId{Currency->Id};
					if (Inventory.Currencies.Contains(CurrencyContentId))
					{
						Inventory.Currencies[CurrencyContentId] = Currency->Amount;
					}
					else
					{
						Inventory.Currencies.Add(CurrencyContentId, Currency->Amount);
					}
				}

				for (const auto PerItemIdGroup : InventoryView->Items)
				{
					const auto ItemContentId = FBeamContentId{PerItemIdGroup->Id};

					if (!Inventory.Items.Contains(ItemContentId))
						Inventory.Items.Add(ItemContentId, {});

					auto& ItemsState = *Inventory.Items.Find(ItemContentId);
					for (UItem* Item : PerItemIdGroup->Items)
					{
						FBeamItemState State;
						State.ContentId = ItemContentId;
						State.InstanceId = Item->Id;
						State.CreatedAt = Item->CreatedAt.IsSet ? FDateTime::FromUnixTimestamp(Item->CreatedAt.Val) : FDateTime::UtcNow();
						State.UpdatedAt = Item->UpdatedAt.IsSet ? FDateTime::FromUnixTimestamp(Item->UpdatedAt.Val) : FDateTime::UtcNow();
						State.FederatedId = Item->ProxyId.IsSet ? Item->ProxyId.Val : TEXT("");
						for (const auto Property : Item->Properties) State.Properties.Add(Property->Name, Property->Value);

						ItemsState.Add(State);
					}
				}

				Runtime->RequestTrackerSystem->TriggerOperationSuccess(Op, TEXT(""));
				return;
			}
			Runtime->RequestTrackerSystem->TriggerOperationError(Op, TEXT(""));
		});

		// Make the request
		FBeamRequestContext Ctx;
		InventoryApi->CPP_GetInventory(Player, GetInventoryReq, Handler, Ctx, Op, CallingContext);
		return true;
	}

	UFUNCTION()
	bool CommitInventoryUpdate(FUserSlot Player, FBeamOperationHandle Op, UObject* CallingContext)
	{
		const auto InventoryUpdateCmdPtr = UpdateCommands.Find(Player);
		if (!InventoryUpdateCmdPtr)
		{
			Runtime->RequestTrackerSystem->TriggerOperationError(Op, TEXT("Did not call BeginInventoryUpdate for this player."));
			return false;
		}

		const auto& Commands = *InventoryUpdateCmdPtr;

		FBeamRealmUser UserData;
		Runtime->UserSlotSystem->GetUserDataAtSlot(Commands.OwnerSlot, UserData, CallingContext);

		const auto GamerTag = UserData.GamerTag;
		TArray<FString> CurrencyIds;
		FOptionalMapOfInt64 CurrencyChanges;
		Commands.GetAllModifiedCurrencies(CurrencyIds, CurrencyChanges);

		FOptionalArrayOfItemCreateRequestBody CreatedItems{};
		FOptionalArrayOfItemDeleteRequestBody DeletedItems{};
		FOptionalArrayOfItemUpdateRequestBody UpdatedItems{};
		Commands.GetAllCreatedItems(CreatedItems);
		Commands.GetAllDeletedItems(DeletedItems);
		Commands.GetAllUpdatedItems(UpdatedItems);

		const auto Request = UPutInventoryRequest::Make(GamerTag, false, CurrencyIds, {},
		                                                {}, {},
		                                                UpdatedItems, CreatedItems, DeletedItems,
		                                                CurrencyChanges, {},
		                                                GetTransientPackage());

		FOnPutInventoryFullResponse Handler;
		Handler.BindLambda([this, Op, Player](const FBeamFullResponse<UPutInventoryRequest*, UCommonResponse*>& Resp)
		{
			// Clear the command buffer regardless off result
			FBeamInventoryUpdateCommand Cmd;
			UpdateCommands.RemoveAndCopyValue(Player, Cmd);

			// Handle success/error/cancellation
			if (Resp.State == Success)
			{
				FBeamInventoryState& State = *Inventories.Find(Player);
				ensureAlwaysMsgf(Cmd.ApplyToState(State), TEXT("Should never see this. If you do see it, file a bug report."));
				Runtime->RequestTrackerSystem->TriggerOperationSuccess(Op, TEXT(""));
				return;
			}

			if (Resp.State == Error)
			{
				Runtime->RequestTrackerSystem->TriggerOperationError(Op, Resp.ErrorData.message);
				return;
			}

			if (Resp.State == Cancelled)
			{
				Runtime->RequestTrackerSystem->TriggerOperationCancelled(Op, Resp.ErrorData.message);
				return;
			}
		});

		FBeamRequestContext Ctx;
		InventoryApi->CPP_PutInventory(Player, Request, Handler, Ctx, Op, CallingContext);
		return true;
	}
};
