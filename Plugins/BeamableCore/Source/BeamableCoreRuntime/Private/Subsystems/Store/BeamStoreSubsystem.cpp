#include "Subsystems/Store/BeamStoreSubsystem.h"

#include "AutoGen/SubSystems/Stats/PostClientRequest.h"
#include "Content/BeamContentTypes/BeamStoreContent.h"
#include "Subsystems/Inventory/BeamInventorySubsystem.h"

void UBeamStoreSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	ContentSubsystem = Collection.InitializeDependency<UBeamContentSubsystem>();

	UserSlots = Runtime->UserSlotSystem;
	RequestTracker = Runtime->RequestTrackerSystem;
	CommerceApi = GEngine->GetEngineSubsystem<UBeamCommerceApi>();
}

void UBeamStoreSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UBeamStoreSubsystem::OnBeamableContentReady_Implementation(FBeamOperationHandle& ResultOp)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({}, GetName(), {});
	RefreshStores(Handle);
	ResultOp = Handle;
}

bool UBeamStoreSubsystem::TryCreatePurchaseListingOperation(FUserSlot Slot, FBeamContentId StoreId,
                                                            FBeamContentId ListingId,
                                                            UBeamPurchaseListingOperation*& Command)
{
	// Ensure we have a user at the given slot.
	FBeamRealmUser RealmUser;
	if (!UserSlots->GetUserDataAtSlot(Slot, RealmUser, this))
	{
		Command = nullptr;
		return false;
	}

	// If we already have
	if (PurchaseCommands.Contains(Slot))
	{
		UE_LOG(LogBeamStats, Warning, TEXT("Trying to start a new update command while one is building."))
		Command = nullptr;
		return false;
	}


	// Create a new update command buffer from it.
	Command = NewObject<UBeamPurchaseListingOperation>(GetTransientPackage());
	Command->Init(this, Slot, StoreId, ListingId);

	PurchaseCommands.Add(Slot, Command);
	return true;
}

FBeamOperationHandle UBeamStoreSubsystem::CommitPurchaseListingOperation(FUserSlot UserSlot,
                                                                         FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(),
	                                                                  OnOperationEvent);
	CommitPurchaseListings(UserSlot, Handle);
	return Handle;
}

FBeamOperationHandle UBeamStoreSubsystem::CPP_CommitPurchaseListingOperation(FUserSlot UserSlot,
                                                                             FBeamOperationEventHandlerCode
                                                                             OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation(
		{UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	CommitPurchaseListings(UserSlot, Handle);
	return Handle;
}

FBeamOperationHandle UBeamStoreSubsystem::PerformPurchaseOperation(FUserSlot UserSlot,
                                                                   FBeamOperationEventHandler OnOperationEvent,
                                                                   FBeamContentId StoreId, FBeamContentId ListingId)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(),
	                                                                  OnOperationEvent);
	PerformPurchase(UserSlot, StoreId, ListingId, Handle);
	return Handle;
}

FBeamOperationHandle UBeamStoreSubsystem::CPP_PerformPurchaseOperation(FUserSlot UserSlot,
                                                                       FBeamOperationEventHandlerCode OnOperationEvent,
                                                                       FBeamContentId StoreId, FBeamContentId ListingId)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation(
		{UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	PerformPurchase(UserSlot, StoreId, ListingId, Handle);
	return Handle;
}

FBeamOperationHandle UBeamStoreSubsystem::RefreshStoreOperation(FBeamOperationEventHandler ResultOp)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation(
		{}, GetClass()->GetFName().ToString(), ResultOp);
	RefreshStores(Handle);
	return Handle;
}


FBeamOperationHandle UBeamStoreSubsystem::CPP_RefreshStoreOperation(FBeamOperationEventHandlerCode ResultOp)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation(
		{}, GetClass()->GetFName().ToString(), ResultOp);
	RefreshStores(Handle);
	return Handle;
}

void UBeamStoreSubsystem::PerformPurchase(FUserSlot UserSlot, FBeamContentId StoreId, FBeamContentId ListingId,
                                          FBeamOperationHandle Op)
{
	FBeamRealmUser RealmUser;
	checkf(UserSlots->GetUserDataAtSlot(UserSlot, RealmUser, this),
	       TEXT("You must only call this function with an authenticated UserSlot"));
	checkf(StoreId.GetTypeId().Equals(FString("stores")), TEXT("StoreId item must be stores type"));
	checkf(ListingId.GetTypeId().Equals(FString("listings")), TEXT("StoreId item must be stores type"));
	FString purchaseRequestName = ListingId.AsString;
	purchaseRequestName.AppendChar(':');
	purchaseRequestName.Append(StoreId.AsString);

	const auto request = UPostPurchaseRequest::Make(RealmUser.GamerTag.AsLong, purchaseRequestName, this, {});

	const auto handler = FOnPostPurchaseFullResponse::CreateLambda(
		[this, Op, UserSlot, &RealmUser](const FPostPurchaseFullResponse& Resp)
		{
			if (Resp.State == RS_Retrying)
			{
				return;
			}

			if (Resp.State != RS_Success)
			{
				UE_LOG(LogTemp, Verbose, TEXT("[BeamStore] Request failed: %s"), *Resp.ErrorData.error);
				RequestTracker->TriggerOperationError(Op, Resp.ErrorData.error);
				return;
			}
			UE_LOG(LogTemp, Verbose, TEXT("[BeamStore] Request succesfull: %s"), *Resp.SuccessData->Result);
			const auto handler = FBeamOperationEventHandlerCode::CreateLambda(
				[this, Op, UserSlot](FBeamOperationEvent Evt)
				{
					UE_LOG(LogTemp, Verbose,
					       TEXT("[BeamStore] Inventory updated"));
					RequestTracker->TriggerOperationSuccess(Op, {});
				});
			auto Inventory = UBeamInventorySubsystem::GetSelf(this);
			Inventory->CPP_FetchPlayerInventoryOperation(UserSlot, RealmUser.GamerTag, handler);
		});
	FBeamRequestContext Ctx;
	CommerceApi->CPP_PostPurchase(UserSlot, request, handler, Ctx, Op, this);
}

void UBeamStoreSubsystem::RefreshStores(FBeamOperationHandle Op)
{
	const auto DefaultStores = GetDefault<UBeamRuntimeSettings>()->StoreContentToDownload;
	const auto ContentHandle = FBeamOperationEventHandlerCode::CreateLambda(
		[this, Op, DefaultStores](const FBeamOperationEvent& Resp)
		{
			this->StoreContents.Reset();
			const auto getAllStores = DefaultStores.IsEmpty();
			TArray<FBeamContentId> ContentIds;
			const auto contentAmount = ContentSubsystem->GetIdsOfContentType(
				UBeamStoreContent::StaticClass(), ContentIds);
			for (int i = 0; i < contentAmount; i++)
			{
				const auto id = ContentIds[i];
				if (getAllStores || DefaultStores.Contains(id))
				{
					UBeamStoreContent* store;
					if (ContentSubsystem->TryGetContentOfType(id, store))
					{
						this->StoreContents.Add(store);
					}
				}
			}
			RequestTracker->TriggerOperationSuccess(Op, {});
		});

	if (DefaultStores.IsEmpty())
	{
		ContentSubsystem->
			CPP_FetchContentManifestOperation(FBeamContentManifestId(TEXT("global")), true, ContentHandle);
	}
	else
	{
		ContentSubsystem->CPP_FetchIndividualContentBatchOperation(FBeamContentManifestId(TEXT("global")),
		                                                           DefaultStores, ContentHandle);
	}
}

void UBeamStoreSubsystem::CommitPurchaseListings(FUserSlot UserSlot, FBeamOperationHandle Op)
{
	// Ensure we have a user at the given slot.
	FBeamRealmUser RealmUser;
	if (!UserSlots->GetUserDataAtSlot(UserSlot, RealmUser, this))
	{
		RequestTracker->TriggerOperationError(Op, TEXT("NO_AUTHENTICATED_USER_AT_SLOT"));
		return;
	}

	// Get the command buffer that is being build.
	const UBeamPurchaseListingOperation* CommandBuffer = PurchaseCommands.FindChecked(UserSlot);
	PerformPurchase(UserSlot, CommandBuffer->StoreId, CommandBuffer->ListingId, Op);
	PurchaseCommands.Remove(UserSlot);
}

bool UBeamStoreSubsystem::TryGetItemsFromListing(FBeamContentId ListingId, TArray<FBeamOfferObtainItem>& items)
{
	if(UBeamListingContent* content; ContentSubsystem->TryGetContentOfType(
		ListingId, content))
	{
		items = content->offer.ObtainItems;
	}
	return false;
}

bool UBeamStoreSubsystem::TryGetCurrenciesFromListing(FBeamContentId ListingId, TArray<FBeamOfferObtainCurrency>& currencies)
{
	if(UBeamListingContent* content; ContentSubsystem->TryGetContentOfType(
		ListingId, content))
	{
		currencies = content->offer.ObtainCurrency;
	}
	return false;
}

bool UBeamStoreSubsystem::GetFormattedPrice(FBeamContentId ListingId, FString& FormattedPrice)
{
	if(UBeamListingContent* content; ContentSubsystem->TryGetContentOfType(
		ListingId, content))
	{
		FormattedPrice = TEXT("");
		FormattedPrice.AppendInt(content->price.Amount);
		FormattedPrice.Append(TEXT(" "));
		FormattedPrice.Append(content->price.Symbol.AsString);
		return true;
	}
	return false;
}


void UBeamPurchaseListingOperation::Init(UBeamStoreSubsystem* Subsystem, FUserSlot Slot, FBeamContentId StoreIdContent,
                                         FBeamContentId ListingIdContent)
{
	this->StoreSubsystem = Subsystem;
	this->UserSlot = Slot;
	this->ListingId = ListingIdContent;
	this->StoreId = StoreIdContent;
}
