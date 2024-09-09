#pragma once

#include "CoreMinimal.h"
#include "AutoGen/SubSystems/BeamCommerceApi.h"
#include "AutoGen/SubSystems/BeamInventoryApi.h"
#include "Content/BeamContentTypes/BeamListingContent.h"
#include "Content/BeamContentTypes/BeamStoreContent.h"
#include "Runtime/BeamRuntimeSubsystem.h"
#include "BeamStoreSubsystem.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORERUNTIME_API UBeamPurchaseListingOperation : public UObject
{
	GENERATED_BODY()

	UPROPERTY()
	UBeamStoreSubsystem* StoreSubsystem;

public:
	explicit UBeamPurchaseListingOperation() = default;

	void Init(UBeamStoreSubsystem* Subsystem, FUserSlot Slot, FBeamContentId StoreId, FBeamContentId ListingId);

	UPROPERTY(BlueprintReadOnly)
	FUserSlot UserSlot;

	UPROPERTY(BlueprintReadOnly)
	FBeamContentId StoreId;
	
	UPROPERTY(BlueprintReadOnly)
	FBeamContentId ListingId;
};

UCLASS()
class BEAMABLECORERUNTIME_API UBeamStoreSubsystem : public UBeamRuntimeSubsystem
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, meta=(DefaultToSelf="CallingContext"))
	static UBeamStoreSubsystem* GetSelf(const UObject* CallingContext) { return CallingContext->GetWorld()->GetGameInstance()->GetSubsystem<UBeamStoreSubsystem>(); }
	UPROPERTY()
	UBeamUserSlots* UserSlots;
	UPROPERTY()
	UBeamCommerceApi* CommerceApi;
	UPROPERTY()
	UBeamRequestTracker* RequestTracker;
	UPROPERTY()
	UBeamContentSubsystem* ContentSubsystem;
	UPROPERTY()
	TArray<UBeamStoreContent*> StoreContents;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TMap<FUserSlot, UBeamPurchaseListingOperation*> PurchaseCommands;

private:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

public:
	virtual void OnBeamableContentReady_Implementation(FBeamOperationHandle& ResultOp) override;
	
	UFUNCTION(BlueprintCallable, meta=(AutoCreateRefTerm="Store", ExpandBoolAsExecs="ReturnValue"))
	bool TryCreatePurchaseListingOperation(FUserSlot Slot, FBeamContentId StoreId, FBeamContentId ListingId, UBeamPurchaseListingOperation*& Command);
	
	/**
	 * @brief Takes whatever is the current purchase listing command for the given user slot and submits it to the Beamable backend.
	 * Call this only after you've called TryCreatePurchaseListingOperation for this slot.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Store", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle CommitPurchaseListingOperation(FUserSlot UserSlot, FBeamOperationEventHandler OnOperationEvent);
	/**
	 * @copydoc CommitStatsOperation
	 */
	FBeamOperationHandle CPP_CommitPurchaseListingOperation(FUserSlot UserSlot, FBeamOperationEventHandlerCode OnOperationEvent);
	/**
	 * @brief Performs a purchase operation of a listing content from a specified store content.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Store")
	FBeamOperationHandle PerformPurchaseOperation(FUserSlot UserSlot, FBeamOperationEventHandler OnOperationEvent, FBeamContentId StoreId, FBeamContentId ListingId);

	/**
	 * \copybrief PerformPurchaseOperation
	 */
	FBeamOperationHandle CPP_PerformPurchaseOperation(FUserSlot UserSlot, FBeamOperationEventHandlerCode OnOperationEvent, FBeamContentId StoreId, FBeamContentId ListingId);

	/**
	 * @brief Performs a purchase operation of a listing content from a specified store content.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Store")
	FBeamOperationHandle RefreshStoreOperation(FBeamOperationEventHandler ResultOp);
	/**
	 * @copydoc RefreshStoreOperation 
	 */
	FBeamOperationHandle CPP_RefreshStoreOperation(FBeamOperationEventHandlerCode ResultOp);

	// Helper Functions
	UFUNCTION(BlueprintCallable)
	bool TryGetItemsFromListing(FBeamContentId ListingId, TArray<FBeamOfferObtainItem>& items);
	UFUNCTION(BlueprintCallable)
	bool TryGetCurrenciesFromListing(FBeamContentId ListingId, TArray<FBeamOfferObtainCurrency>& currencies);
	UFUNCTION(BlueprintCallable)
	bool GetFormattedPrice(FBeamContentId ListingId, FString& FormattedPrice);
private:
	void PerformPurchase(FUserSlot UserSlot, FBeamContentId StoreId, FBeamContentId ListingId, FBeamOperationHandle Op = {});
	void RefreshStores(FBeamOperationHandle Op = {});
	void CommitPurchaseListings(FUserSlot UserSlot, FBeamOperationHandle Op);

};
