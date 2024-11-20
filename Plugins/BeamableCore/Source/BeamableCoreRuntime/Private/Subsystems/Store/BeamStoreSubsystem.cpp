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

void UBeamStoreSubsystem::OnBeamableContentReady_Implementation(FBeamOperationHandle& ResultOp)
{
	ResultOp = Runtime->RequestTrackerSystem->CPP_BeginSuccessfulOperation({}, GetName(), {}, {});
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
		const auto InventoryHandler = FBeamOperationEventHandlerCode::CreateLambda([this, Op, UserSlot](FBeamOperationEvent)
		{
			UE_LOG(LogBeamStore, Verbose, TEXT("[BeamStore] Inventory updated"));
			RequestTracker->TriggerOperationSuccess(Op, {});
		});

		const auto Inventory = UBeamInventorySubsystem::GetSelf(this);
		Inventory->CPP_FetchPlayerInventoryOperation(UserSlot, RealmUser.GamerTag, InventoryHandler);
	});
	FBeamRequestContext Ctx;
	CommerceApi->CPP_PostPurchase(UserSlot, Request, Handler, Ctx, Op, this);
}

bool UBeamStoreSubsystem::TryGetItemsFromListing(FBeamContentId ListingId, TArray<FBeamOfferObtainItem>& items)
{
	if (UBeamListingContent* content; ContentSubsystem->TryGetContentOfType(ListingId, content))
	{
		items = content->offer.ObtainItems;
	}
	return false;
}

bool UBeamStoreSubsystem::TryGetCurrenciesFromListing(FBeamContentId ListingId, TArray<FBeamOfferObtainCurrency>& currencies)
{
	if (UBeamListingContent* content; ContentSubsystem->TryGetContentOfType(
		ListingId, content))
	{
		currencies = content->offer.ObtainCurrency;
	}
	return false;
}

bool UBeamStoreSubsystem::GetFormattedPrice(FBeamContentId ListingId, FString& FormattedPrice)
{
	if (UBeamListingContent* content; ContentSubsystem->TryGetContentOfType(
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
