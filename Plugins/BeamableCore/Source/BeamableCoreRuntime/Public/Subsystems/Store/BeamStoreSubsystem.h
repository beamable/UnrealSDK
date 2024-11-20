#pragma once

#include "CoreMinimal.h"
#include "AutoGen/SubSystems/BeamCommerceApi.h"
#include "AutoGen/SubSystems/BeamInventoryApi.h"
#include "Content/BeamContentTypes/BeamListingContent.h"
#include "Content/BeamContentTypes/BeamStoreContent.h"
#include "Runtime/BeamRuntimeSubsystem.h"
#include "BeamStoreSubsystem.generated.h"

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

private:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual TArray<TSubclassOf<UBeamRuntimeSubsystem>> GetDependingOnSubsystems() override;

public:
	virtual void OnBeamableContentReady_Implementation(FBeamOperationHandle& ResultOp) override;

	/**
	 * @brief Performs a purchase operation of a listing content from a specified store content.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Store")
	FBeamOperationHandle PerformPurchaseOperation(FUserSlot UserSlot, FBeamOperationEventHandler OnOperationEvent, FBeamContentId StoreId, FBeamContentId ListingId);

	/**
	 * \copybrief PerformPurchaseOperation
	 */
	FBeamOperationHandle CPP_PerformPurchaseOperation(FUserSlot UserSlot, FBeamOperationEventHandlerCode OnOperationEvent, FBeamContentId StoreId, FBeamContentId ListingId);

	// Helper Functions
	UFUNCTION(BlueprintCallable)
	bool TryGetItemsFromListing(FBeamContentId ListingId, TArray<FBeamOfferObtainItem>& items);
	UFUNCTION(BlueprintCallable)
	bool TryGetCurrenciesFromListing(FBeamContentId ListingId, TArray<FBeamOfferObtainCurrency>& currencies);
	UFUNCTION(BlueprintCallable)
	bool GetFormattedPrice(FBeamContentId ListingId, FString& FormattedPrice);

private:
	void PerformPurchase(FUserSlot UserSlot, FBeamContentId StoreId, FBeamContentId ListingId, FBeamOperationHandle Op = {});	
};
