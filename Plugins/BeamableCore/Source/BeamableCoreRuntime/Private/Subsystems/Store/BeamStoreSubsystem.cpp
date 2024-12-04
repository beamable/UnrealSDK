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

TArray<TSubclassOf<UBeamRuntimeSubsystem>> UBeamStoreSubsystem::GetDependingOnSubsystems()
{
	auto DependentSystems = Super::GetDependingOnSubsystems();
	DependentSystems.Add(UBeamInventorySubsystem::StaticClass());
	return DependentSystems;
}

FBeamOperationHandle UBeamStoreSubsystem::PerformPurchaseOperation(FUserSlot UserSlot, FBeamOperationEventHandler OnOperationEvent, FBeamContentId StoreId, FBeamContentId ListingId)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	PerformPurchase(UserSlot, StoreId, ListingId, Handle);
	return Handle;
}

FBeamOperationHandle UBeamStoreSubsystem::CPP_PerformPurchaseOperation(FUserSlot UserSlot, FBeamOperationEventHandlerCode OnOperationEvent, FBeamContentId StoreId, FBeamContentId ListingId)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	PerformPurchase(UserSlot, StoreId, ListingId, Handle);
	return Handle;
}

FBeamOperationHandle UBeamStoreSubsystem::RefreshStoresOperation(FUserSlot UserSlot, TArray<FBeamContentId> StoreIds, FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	RefreshStoreView(UserSlot, StoreIds, Handle);
	return Handle;
}

FBeamOperationHandle UBeamStoreSubsystem::CPP_RefreshStoresOperation(FUserSlot UserSlot, TArray<FBeamContentId> StoreIds, FBeamOperationEventHandlerCode OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	RefreshStoreView(UserSlot, StoreIds, Handle);
	return Handle;
}

FBeamOperationHandle UBeamStoreSubsystem::RefreshStoreOperation(FUserSlot UserSlot, FBeamContentId StoreId, FBeamOperationEventHandler OnOperationEvent)
{
	return RefreshStoresOperation(UserSlot, {StoreId}, OnOperationEvent);
}

FBeamOperationHandle UBeamStoreSubsystem::CPP_RefreshStoreOperation(FUserSlot UserSlot, FBeamContentId StoreId, FBeamOperationEventHandlerCode OnOperationEvent)
{
	return CPP_RefreshStoresOperation(UserSlot, {StoreId}, OnOperationEvent);
}

bool UBeamStoreSubsystem::TryGetStoreView(FUserSlot Slot, FBeamContentId StoreContentId, UBeamStoreView*& Store)
{
	FBeamPlayerStoreHandle Handle{Slot, StoreContentId};
	if (const auto Ptr = StoreViews.Find(Handle))
	{
		Store = *Ptr;
		return true;
	}

	return false;		
}


void UBeamStoreSubsystem::PerformPurchase(FUserSlot UserSlot, FBeamContentId StoreId, FBeamContentId ListingId, FBeamOperationHandle Op)
{
	FBeamRealmUser RealmUser;
	if (!UserSlots->GetUserDataAtSlot(UserSlot, RealmUser, this))
	{
		RequestTracker->TriggerOperationError(Op, TEXT("NO_AUTHENTICATED_USER_AT_SLOT"));
		return;
	}

	if (!StoreId.GetTypeId().StartsWith(FString("stores")))
	{
		RequestTracker->TriggerOperationError(Op, TEXT("INVALID_STORE_CONTENT_ID"));
		return;
	}

	if (!ListingId.GetTypeId().StartsWith(FString("listings")))
	{
		RequestTracker->TriggerOperationError(Op, TEXT("INVALID_LISTING_CONTENT_ID"));
		return;
	}

	FString PurchaseRequestName = ListingId.AsString;
	PurchaseRequestName.AppendChar(':');
	PurchaseRequestName.Append(StoreId.AsString);

	const auto Request = UPostPurchaseRequest::Make(RealmUser.GamerTag.AsLong, PurchaseRequestName, this, {});
	const auto Handler = FOnPostPurchaseFullResponse::CreateLambda([this, Op, UserSlot, &RealmUser](const FPostPurchaseFullResponse& Resp)
	{
		if (Resp.State == RS_Retrying)
			return;

		if (Resp.State != RS_Success)
		{
			UE_LOG(LogBeamStore, Verbose, TEXT("[BeamStore] Request failed: %s"), *Resp.ErrorData.error);
			RequestTracker->TriggerOperationError(Op, Resp.ErrorData.error);
			return;
		}

		UE_LOG(LogBeamStore, Verbose, TEXT("[BeamStore] Request succesfull: %s"), *Resp.SuccessData->Result);
		const auto InventoryHandler = FBeamOperationEventHandlerCode::CreateLambda([this, Op, UserSlot](FBeamOperationEvent Evt)
		{
			if (Evt.EventType == OET_SUCCESS)
				UE_LOG(LogBeamStore, Verbose, TEXT("[BeamStore] Inventory updated"));

			if (Evt.EventType == OET_ERROR)
				UE_LOG(LogBeamStore, Error, TEXT("[BeamStore] Purchase successful,but failed to update local inventory data"));

			// Whether we successfully fetched the inventory or not, we should trigger the purchase operation as a success.
			// TODO: Ideally, we should be updating the local inventory state manually here instead of making a request to fetch it since we have all the info to apply locally. 
			RequestTracker->TriggerOperationSuccess(Op, {});
		});

		const auto Inventory = UBeamInventorySubsystem::GetSelf(this);
		Inventory->CPP_FetchAllInventoryOperation(UserSlot, InventoryHandler);
	});
	FBeamRequestContext Ctx;
	CommerceApi->CPP_PostPurchase(UserSlot, Request, Handler, Ctx, Op, this);
}


void UBeamStoreSubsystem::RefreshStoreView(FUserSlot UserSlot, TArray<FBeamContentId> StoreIds, FBeamOperationHandle Op)
{
	FBeamRealmUser RealmUser;
	if (!UserSlots->GetUserDataAtSlot(UserSlot, RealmUser, this))
	{
		RequestTracker->TriggerOperationError(Op, TEXT("NO_AUTHENTICATED_USER_AT_SLOT"));
		return;
	}

	TArray<FBeamContentId> InvalidIds = {};
	if (!ContentSubsystem->ValidateContentsTypeHierarchy({UBeamStoreContent::StaticClass()}, StoreIds, InvalidIds))
	{
		auto Data = NewObject<UBeamOperationEventData_ContentIds>();
		Data->Ids = InvalidIds;
		RequestTracker->TriggerOperationErrorWithData(Op, TEXT("INVALID_STORE_CONTENT_IDS"), Data);
		return;
	}

	TArray<FString> Scopes = {};
	for (const auto& StoreId : StoreIds) Scopes.Add(StoreId.AsString);

	const auto Scope = FOptionalString{Scopes.Num() > 1 ? FString::Join(Scopes, TEXT(",")) : Scopes[0]};
	const auto Request = UGetCommerceRequest::Make(RealmUser.GamerTag.AsLong, Scope, GetTransientPackage(), {});
	const auto Handler = FOnGetCommerceFullResponse::CreateLambda([this, Op, Scope, UserSlot](const FGetCommerceFullResponse& Resp)
	{
		if (Resp.State == RS_Retrying)
			return;

		if (Resp.State != RS_Success)
		{
			UE_LOG(LogBeamStore, Verbose, TEXT("[BeamStore] Request failed: %s"), *Resp.ErrorData.error);
			RequestTracker->TriggerOperationError(Op, Resp.ErrorData.error);
			return;
		}

		UE_LOG(LogBeamStore, Verbose, TEXT("[BeamStore] Successfully refreshed stores: %s"), *Scope.Val);

		for (UPlayerStoreView* Store : Resp.SuccessData->Stores)
		{
			FBeamPlayerStoreHandle Handle{UserSlot, Store->Symbol};
			auto StoreView = NewObject<UBeamStoreView>();
			StoreView->OwnerSlot = UserSlot;
			StoreView->CurrentStoreView = DuplicateObject<UPlayerStoreView>(Resp.SuccessData->Stores.Last(), GetTransientPackage());

			if (StoreViews.Contains(Handle)) StoreViews[Handle] = StoreView;
			else StoreViews.Add(Handle, StoreView);
		}

		RequestTracker->TriggerOperationSuccess(Op, TEXT("STORES_REFRESHED"));
	});
	FBeamRequestContext Ctx;
	CommerceApi->CPP_GetCommerce(UserSlot, Request, Handler, Ctx, Op, this);
}
