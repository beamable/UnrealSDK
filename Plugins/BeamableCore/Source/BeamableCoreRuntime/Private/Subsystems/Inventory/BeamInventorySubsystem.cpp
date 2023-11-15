// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/Inventory/BeamInventorySubsystem.h"

#include "AutoGen/ItemDeleteRequestBody.h"
#include "AutoGen/ItemUpdateRequestBody.h"
#include "AutoGen/Optionals/OptionalArrayOfItemDeleteRequestBody.h"
#include "AutoGen/Optionals/OptionalArrayOfItemUpdateRequestBody.h"
#include "AutoGen/SubSystems/Inventory/GetInventoryRequest.h"

#include "Content/BeamContentTypes/BeamCurrencyContent.h"
#include "Content/BeamContentTypes/BeamItemContent.h"

#include "AutoGen/SubSystems/BeamInventoryApi.h"
#include "BeamNotifications/SubSystems/BeamInventoryNotifications.h"
#include "Subsystems/Content/BeamContentSubsystem.h"

bool FBeamInventoryState::TryGetPlayerCurrencyProperties(const FBeamContentId& CurrencyId, FBeamPlayerCurrency& Currency)
{
	Currency.OwnerPlayer = OwnerPlayer;
	Currency.ContentId   = CurrencyId;

	TryGetCurrencyProperties(CurrencyId, Currency.Properties);
	return TryGetCurrencyAmount(CurrencyId, Currency.Amount);
}

bool FBeamInventoryState::TryGetCurrencyProperties(const FBeamContentId& CurrencyId, TMap<FString, FString>& Props)
{
	if (CurrencyProperties.Contains(CurrencyId))
	{
		Props = *CurrencyProperties.Find(CurrencyId);
		return true;
	}

	Props = {};
	return false;
}

bool FBeamInventoryState::TryGetCurrencyAmount(const FBeamContentId& CurrencyId, int64& Amount)
{
	if (Currencies.Contains(CurrencyId))
	{
		Amount = *Currencies.Find(CurrencyId);
		return true;
	}

	Amount = 0;
	return false;
}

void FBeamInventoryState::GetAllCurrencies(TArray<FBeamPlayerCurrency>& OutCurrencies)
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

void FBeamInventoryUpdateCommand::AddCurrency(const FBeamContentId& CurrencyId, int64 Amount)
{
	ensureAlwaysMsgf(Amount >= 0, TEXT("Gain must be greater than or equal 0"));
	ModifyCurrency(CurrencyId, Amount);
}

void FBeamInventoryUpdateCommand::RemoveCurrency(const FBeamContentId& CurrencyId, int64 Amount)
{
	ensureAlwaysMsgf(Amount >= 0, TEXT("Gain must be less than or equal 0"));
	ModifyCurrency(CurrencyId, -Amount);
}

void FBeamInventoryUpdateCommand::ModifyCurrency(const FBeamContentId& CurrencyId, int64 Amount)
{
	// No need to add it to the map if you're not gaining anything (can save requests in some cases).
	if (Amount == 0) return;

	if (CurrencyChanges.Contains(CurrencyId))
		CurrencyChanges[CurrencyId] += Amount;
	else
		CurrencyChanges.Add(CurrencyId, Amount);
}

void FBeamInventoryUpdateCommand::GetAllModifiedCurrencies(TArray<FString>& Ids, FOptionalMapOfInt64& Currencies) const
{
	TArray<FBeamContentId> ContentIds;
	TMap<FString, int64>   Amounts;
	CurrencyChanges.GetKeys(ContentIds);

	for (const auto& Id : ContentIds)
	{
		Ids.Add(Id.AsString);
		Amounts.Add(Id.AsString, CurrencyChanges[Id]);
	}
	Currencies.Set(&Amounts);
}

void FBeamInventoryUpdateCommand::CreateItem(FBeamContentId Id, TMap<FString, FString> Properties)
{
	CreatedItems.Add({Id, CreateItemCount++}, Properties);
}

void FBeamInventoryUpdateCommand::RemoveItem(FBeamContentId Id, int64 InstanceId)
{
	RemovedItems.Add({Id, InstanceId});
}

void FBeamInventoryUpdateCommand::UpdateItem(FBeamContentId Id, int64 InstanceId, TMap<FString, FString> Properties)
{
	ChangedItems.Add({Id, InstanceId}, Properties);
}

bool FBeamInventoryUpdateCommand::ApplyToState(FBeamInventoryState& State)
{
	for (const auto& CurrencyChange : CurrencyChanges)
	{
		const auto CurrencyId  = CurrencyChange.Key;
		const auto CurrencyMod = CurrencyChange.Value;

		if (State.Currencies.Contains(CurrencyId))
			State.Currencies[CurrencyId] += CurrencyMod;
		else
			State.Currencies.Add(CurrencyId, CurrencyMod);
	}

	for (const auto CreatedItem : CreatedItems)
	{
		const auto Ids        = CreatedItem.Key;
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
		const auto ContentId  = RemovedItem.Key;
		const auto InstanceId = RemovedItem.Value;

		if (State.Items.Contains(ContentId))
		{
			TArray<FBeamItemState>& Items = State.Items.FindChecked(ContentId);

			Items.RemoveAll([ContentId, InstanceId](const FBeamItemState& ItemState)
			{
				return ItemState.ContentId == ContentId && ItemState.InstanceId == InstanceId;
			});
		}
	}

	for (const auto ChangedItem : ChangedItems)
	{
		const auto Ids        = ChangedItem.Key;
		const auto Properties = ChangedItem.Value;

		const auto ContentId  = Ids.Key;
		const auto InstanceId = Ids.Value;

		if (State.Items.Contains(Ids.Key))
		{
			TArray<FBeamItemState> Items = State.Items[ContentId];
			if (FBeamItemState* ItemState = Items.FindByPredicate([ContentId, InstanceId](FBeamItemState s)
			{
				return s.ContentId == ContentId && s.InstanceId == InstanceId;
			}))
			{
				ItemState->Properties = Properties;
			}
		}
		else
		{
			State.Items.Add(Ids.Key, {
				                FBeamItemState{
					                ContentId, InstanceId, {},
					                Properties, {}, {}
				                }
			                });
		}
	}

	return true;
}

void FBeamInventoryUpdateCommand::GetAllDeletedItems(FOptionalArrayOfItemDeleteRequestBody& DeletedItems, UObject* Owner) const
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
		Deletion->ContentId              = RemovedItem.Key.AsString;
		Deletion->Id                     = RemovedItem.Value;
		DeleteRequests.Add(Deletion);
	}

	DeletedItems = FOptionalArrayOfItemDeleteRequestBody(DeleteRequests);
}

void FBeamInventoryUpdateCommand::GetAllUpdatedItems(FOptionalArrayOfItemUpdateRequestBody& UpdatedItems, UObject* Owner) const
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
		Update->ContentId              = ChangedItem.Key.Key.AsString;
		Update->Id                     = ChangedItem.Key.Value;

		TArray<UItemProperty*> Properties;
		for (const auto& Prop : ChangedItem.Value)
		{
			UItemProperty* ItemProp = NewObject<UItemProperty>(Owner);
			ItemProp->Name          = Prop.Key;
			ItemProp->Value         = Prop.Value;
			Properties.Add(ItemProp);
		}
		Update->Properties = Properties;
		UpdateRequests.Add(Update);
	}

	UpdatedItems = FOptionalArrayOfItemUpdateRequestBody(UpdateRequests);
}

void FBeamInventoryUpdateCommand::GetAllCreatedItems(FOptionalArrayOfItemCreateRequestBody& NewItems, UObject* Owner) const
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
		Create->ContentId              = CreatedItem.Key.Key.AsString;

		TArray<UItemProperty*> Properties;
		for (const auto& Prop : CreatedItem.Value)
		{
			UItemProperty* ItemProp = NewObject<UItemProperty>(Owner);
			ItemProp->Name          = Prop.Key;
			ItemProp->Value         = Prop.Value;
			Properties.Add(ItemProp);
		}
		Create->Properties = Properties;
		CreateRequests.Add(Create);
	}

	NewItems = FOptionalArrayOfItemCreateRequestBody(CreateRequests);
}

void UBeamInventorySubsystem::InitializeWhenUnrealReady_Implementation(FBeamOperationHandle& ResultOp)
{
	InventoryApi           = GEngine->GetEngineSubsystem<UBeamInventoryApi>();
	InventoryNotifications = GEngine->GetEngineSubsystem<UBeamInventoryNotifications>();

	ContentSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UBeamContentSubsystem>();

	for (const auto RuntimeUserSlot : GetDefault<UBeamCoreSettings>()->RuntimeUserSlots)
	{
		const auto UserSlot = FUserSlot{RuntimeUserSlot};
		Inventories.Add(UserSlot, FBeamInventoryState{UserSlot, {}, {}, {}, {}});
	}

	Super::InitializeWhenUnrealReady_Implementation(ResultOp);
}

void UBeamInventorySubsystem::OnPostUserSignedOut_Implementation(const FUserSlot& UserSlot, const EUserSlotClearedReason Reason, const FBeamRealmUser& BeamRealmUser, FBeamOperationHandle& ResultOp)
{
	if (Inventories.Contains(UserSlot))
	{
		FBeamInventoryState&  Inventory     = *Inventories.Find(UserSlot);
		Inventory.Currencies.Reset();
		Inventory.Items.Reset();
		Inventory.CachedScopes.Reset();
		Inventory.CurrencyProperties.Reset();		
	}

	Super::OnPostUserSignedOut_Implementation(UserSlot, Reason, BeamRealmUser, ResultOp);
}

void UBeamInventorySubsystem::OnUserSignedIn_Implementation(const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser, const bool bIsFirstAuth, FBeamOperationHandle& ResultOp)
{
	// Fetch the inventory
	FBeamOperationHandle Op = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetName(), {});
	FetchAllInventory(UserSlot, Op, this);

	// We also set up the inventory refresh notification here.
	const FOnInventoryRefreshNotificationCode NotificationHandler = FOnInventoryRefreshNotificationCode::CreateLambda([this, UserSlot, BeamRealmUser](const FInventoryRefreshNotificationMessage& InventoryRefreshNotificationMessage)
	{
		UPostInventoryRequest* Req = UPostInventoryRequest::Make(BeamRealmUser.GamerTag, FOptionalArrayOfString{InventoryRefreshNotificationMessage.Scopes}, GetTransientPackage(), {});

		const FOnPostInventoryFullResponse PostInventoryHandler = FOnPostInventoryFullResponse::CreateLambda([this](const FBeamFullResponse<UPostInventoryRequest*, UInventoryView*>& Resp)
		{
			FBeamInventoryState&  Inventory     = *Inventories.Find(Resp.Context.UserSlot);
			const UInventoryView* InventoryView = Resp.SuccessData;
			MergeInventoryViewIntoState(InventoryView, Inventory);
		});
		FBeamRequestContext Ctx;
		InventoryApi->CPP_PostInventory(UserSlot, Req, PostInventoryHandler, Ctx, {}, this);
	});

	GEngine->GetEngineSubsystem<UBeamInventoryNotifications>()->CPP_SubscribeToInventoryRefresh(UserSlot, Runtime->DefaultNotificationChannel, NotificationHandler);
	ResultOp = Op;
}

FBeamOperationHandle UBeamInventorySubsystem::FetchAllInventoryOperation(FUserSlot UserSlot, FBeamOperationEventHandler OnOperationEvent, UObject* CallingContext)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	FetchAllInventory(UserSlot, Handle, CallingContext);
	return Handle;
}

FBeamOperationHandle UBeamInventorySubsystem::CPP_FetchAllInventoryOperation(FUserSlot Player, FBeamOperationEventHandlerCode OnOperationEvent, UObject* CallingContext)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({Player}, GetClass()->GetFName().ToString(), OnOperationEvent);
	FetchAllInventory(Player, Handle, CallingContext);
	return Handle;
}

FBeamOperationHandle UBeamInventorySubsystem::CommitInventoryUpdateOperation(FUserSlot UserSlot, FBeamOperationEventHandler OnOperationEvent, UObject* CallingContext)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	CommitInventoryUpdate(UserSlot, Handle, CallingContext);
	return Handle;
}

FBeamOperationHandle UBeamInventorySubsystem::CPP_CommitInventoryUpdateOperation(FUserSlot Player, FBeamOperationEventHandlerCode OnOperationEvent, UObject* CallingContext)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({Player}, GetClass()->GetFName().ToString(), OnOperationEvent);
	CommitInventoryUpdate(Player, Handle, CallingContext);
	return Handle;
}

FBeamOperationHandle UBeamInventorySubsystem::ModifyCurrenciesOperation(FUserSlot Player, TMap<FBeamContentId, int64> CurrencyChanges, FBeamOperationEventHandler OnOperationEvent, UObject* CallingContext)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({Player}, GetClass()->GetFName().ToString(), OnOperationEvent);

	FBeamInventoryUpdateCommand Cmd;
	BeginInventoryUpdate(Player, Cmd, true);
	for (const auto& CurrencyChange : CurrencyChanges)
		PrepareModifyCurrency(Player, CurrencyChange.Key, CurrencyChange.Value);

	CommitInventoryUpdate(Player, Handle, CallingContext);

	return Handle;
}

FBeamOperationHandle UBeamInventorySubsystem::CPP_ModifyCurrenciesOperation(FUserSlot Player, TMap<FBeamContentId, int64> CurrencyChanges, FBeamOperationEventHandlerCode OnOperationEvent, UObject* CallingContext)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({Player}, GetClass()->GetFName().ToString(), OnOperationEvent);

	FBeamInventoryUpdateCommand Cmd;
	BeginInventoryUpdate(Player, Cmd, true);
	for (const auto& CurrencyChange : CurrencyChanges)
		PrepareModifyCurrency(Player, CurrencyChange.Key, CurrencyChange.Value);

	CommitInventoryUpdate(Player, Handle, CallingContext);
	return Handle;
}

bool UBeamInventorySubsystem::TryGetCurrencyAmount(FUserSlot Player, const FBeamContentId& CurrencyId, int64& Amount)
{
	Amount = 0;
	if (!Inventories.Contains(Player))
		return false;

	return Inventories.Find(Player)->TryGetCurrencyAmount(CurrencyId, Amount);
}

bool UBeamInventorySubsystem::TryGetAllCurrencies(FUserSlot Player, TArray<FBeamPlayerCurrency>& Currencies)
{
	Currencies = {};
	if (!Inventories.Contains(Player))
		return false;

	Inventories.Find(Player)->GetAllCurrencies(Currencies);
	return true;
}

bool UBeamInventorySubsystem::TryGetAllItems(FUserSlot Player, TArray<FBeamItemState>& ItemStates)
{
	ItemStates = {};
	if (!Inventories.Contains(Player))
		return false;

	const auto inventory = Inventories.FindRef(Player);
	for (const auto Item : inventory.Items)
		ItemStates.Append(Item.Value);

	return true;
}

bool UBeamInventorySubsystem::BeginInventoryUpdate(FUserSlot Player, FBeamInventoryUpdateCommand& Commands, bool ResetIfExists)
{
	if (UpdateCommands.Contains(Player))
	{
		if (ResetIfExists)
			UpdateCommands.Remove(Player);
		else
			return false;
	}

	Commands           = FBeamInventoryUpdateCommand();
	Commands.OwnerSlot = Player;
	UpdateCommands.Add(Player, Commands);
	return true;
}

void UBeamInventorySubsystem::PrepareAddCurrency(FUserSlot Player, FBeamContentId CurrencyId, int64 Gain)
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

void UBeamInventorySubsystem::PrepareRemoveCurrency(FUserSlot Player, FBeamContentId CurrencyId, int64 Loss)
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

void UBeamInventorySubsystem::PrepareModifyCurrency(FUserSlot Player, FBeamContentId CurrencyId, int64 Amount)
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

void UBeamInventorySubsystem::PrepareCreateItem(FUserSlot Player, FBeamContentId ItemId, TMap<FString, FString> Properties)
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

void UBeamInventorySubsystem::PrepareRemoveItem(FUserSlot Player, const FBeamItemState& State)
{
	FBeamContentId ContentId  = State.ContentId;
	int64          InstanceId = State.InstanceId;
	PrepareRemoveItemWithId(Player, ContentId, InstanceId);
}

void UBeamInventorySubsystem::PrepareRemoveItemWithId(FUserSlot Player, FBeamContentId ContentId, int64 InstanceId)
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

void UBeamInventorySubsystem::PrepareModifyItem(FUserSlot Player, const FBeamItemState& State)
{
	PrepareModifyItemById(Player, State.ContentId, State.InstanceId, State.Properties);
}

void UBeamInventorySubsystem::PrepareModifyItemById(FUserSlot Player, FBeamContentId ContentId, int64 InstanceId, TMap<FString, FString> Properties)
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

bool UBeamInventorySubsystem::FetchAllInventory(FUserSlot Player, FBeamOperationHandle Op, UObject* CallingContext)
{
	FBeamRealmUser UserData;
	Runtime->UserSlotSystem->GetUserDataAtSlot(Player, UserData, this);

	FOnGetInventoryFullResponse GetInventoryHandler = FOnGetInventoryFullResponse::CreateLambda([this, Op](FBeamFullResponse<UGetInventoryRequest*, UInventoryView*> Response)
	{
		if (Response.State == RS_Success)
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
					State.ContentId   = ItemContentId;
					State.InstanceId  = Item->Id;
					State.CreatedAt   = Item->CreatedAt.IsSet ? FDateTime::FromUnixTimestamp(Item->CreatedAt.Val) : FDateTime::UtcNow();
					State.UpdatedAt   = Item->UpdatedAt.IsSet ? FDateTime::FromUnixTimestamp(Item->UpdatedAt.Val) : FDateTime::UtcNow();
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
	FBeamRequestContext         Ctx;
	UGetInventoryRequest* const GetInventoryReq = UGetInventoryRequest::Make(UserData.GamerTag, {}, GetTransientPackage(), {});
	InventoryApi->CPP_GetInventory(Player, GetInventoryReq, GetInventoryHandler, Ctx, Op, CallingContext);
	return true;
}


bool UBeamInventorySubsystem::CommitInventoryUpdate(FUserSlot Player, FBeamOperationHandle Op, UObject* CallingContext)
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

	const auto          GamerTag = UserData.GamerTag;
	TArray<FString>     CurrencyIds;
	FOptionalMapOfInt64 CurrencyChanges;
	Commands.GetAllModifiedCurrencies(CurrencyIds, CurrencyChanges);

	FOptionalArrayOfItemCreateRequestBody CreatedItems{};
	FOptionalArrayOfItemDeleteRequestBody DeletedItems{};
	FOptionalArrayOfItemUpdateRequestBody UpdatedItems{};
	Commands.GetAllCreatedItems(CreatedItems);
	Commands.GetAllDeletedItems(DeletedItems);
	Commands.GetAllUpdatedItems(UpdatedItems);

	FOnPutInventoryFullResponse Handler = FOnPutInventoryFullResponse::CreateLambda([this, Op, Player](const FBeamFullResponse<UPutInventoryRequest*, UCommonResponse*>& Resp)
	{
		// Clear the command buffer regardless off result
		FBeamInventoryUpdateCommand Cmd;
		UpdateCommands.RemoveAndCopyValue(Player, Cmd);

		// Handle success/error/cancellation
		if (Resp.State == RS_Success)
		{
			FBeamInventoryState& State = *Inventories.Find(Player);
			ensureAlwaysMsgf(Cmd.ApplyToState(State), TEXT("Should never see this. If you do see it, file a bug report."));
			Runtime->RequestTrackerSystem->TriggerOperationSuccess(Op, TEXT(""));
			return;
		}

		if (Resp.State == RS_Error)
		{
			Runtime->RequestTrackerSystem->TriggerOperationError(Op, Resp.ErrorData.message);
			return;
		}

		if (Resp.State == RS_Cancelled)
		{
			Runtime->RequestTrackerSystem->TriggerOperationCancelled(Op, Resp.ErrorData.message);
			return;
		}
	});

	UPutInventoryRequest* const Request = UPutInventoryRequest::Make(GamerTag, false, CurrencyIds, {},
	                                                                 {}, {},
	                                                                 UpdatedItems, CreatedItems, DeletedItems,
	                                                                 CurrencyChanges, {},
	                                                                 GetTransientPackage(), {});

	FBeamRequestContext Ctx;
	InventoryApi->CPP_PutInventory(Player, Request, Handler, Ctx, Op, CallingContext);
	return true;
}

void UBeamInventorySubsystem::MergeInventoryViewIntoState(const UInventoryView* InventoryView, FBeamInventoryState& Inventory)
{
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
			State.ContentId   = ItemContentId;
			State.InstanceId  = Item->Id;
			State.CreatedAt   = Item->CreatedAt.IsSet ? FDateTime::FromUnixTimestamp(Item->CreatedAt.Val) : FDateTime::UtcNow();
			State.UpdatedAt   = Item->UpdatedAt.IsSet ? FDateTime::FromUnixTimestamp(Item->UpdatedAt.Val) : FDateTime::UtcNow();
			State.FederatedId = Item->ProxyId.IsSet ? Item->ProxyId.Val : TEXT("");
			for (const auto Property : Item->Properties) State.Properties.Add(Property->Name, Property->Value);

			ItemsState.Add(State);
		}
	}
}
