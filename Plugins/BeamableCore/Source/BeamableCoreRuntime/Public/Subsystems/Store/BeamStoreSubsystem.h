#pragma once

#include "CoreMinimal.h"
#include "AutoGen/SubSystems/BeamCommerceApi.h"
#include "AutoGen/SubSystems/BeamInventoryApi.h"
#include "Content/BeamContentTypes/BeamListingContent.h"
#include "Content/BeamContentTypes/BeamStoreContent.h"
#include "RequestTracker/EventDataTypes/BeamOperationEventData_ContentIds.h"
#include "Runtime/BeamRuntimeSubsystem.h"
#include "BeamStoreSubsystem.generated.h"

UCLASS()
class UBeamStoreView : public UObject
{
	GENERATED_BODY()

	friend class UBeamStoreSubsystem;

	UPROPERTY()
	UBeamStoreSubsystem* Subsystem;

public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FUserSlot OwnerSlot;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UPlayerStoreView* CurrentStoreView;
};

USTRUCT(BlueprintType)
struct FBeamPlayerStoreHandle
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	FUserSlot Slot;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta=(BeamContentTypeFilter="store", BeamContentTypeFilterMode="tree"))
	FBeamContentId StoreId;

	friend bool operator==(const FBeamPlayerStoreHandle& Lhs, const FBeamPlayerStoreHandle& RHS)
	{
		return Lhs.Slot == RHS.Slot && Lhs.StoreId == RHS.StoreId;
	}

	friend bool operator!=(const FBeamPlayerStoreHandle& Lhs, const FBeamPlayerStoreHandle& RHS)
	{
		return !(Lhs == RHS);
	}
};

// Hash function to use FBeamPlayerStoreHandle in TMap
inline uint32 GetTypeHash(const FBeamPlayerStoreHandle& Hash)
{
	return GetTypeHash(Hash.Slot) ^ GetTypeHash(Hash.StoreId);
}

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
	UPROPERTY()
	TMap<FBeamPlayerStoreHandle, UBeamStoreView*> StoreViews = {};

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual TArray<TSubclassOf<UBeamRuntimeSubsystem>> GetDependingOnSubsystems() override;

public:


	// OPERATIONS
	
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
	 * @brief This will refresh the player's view of a configured store.
	 * Call this before displaying the store to ensure you have the correct view of listings for a particular player.
	 * 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Store")
	FBeamOperationHandle RefreshStoresOperation(FUserSlot UserSlot, TArray<FBeamContentId> StoreIds, FBeamOperationEventHandler OnOperationEvent);

	/**
	 * \copybrief RefreshStoresOperation
	 */
	FBeamOperationHandle CPP_RefreshStoresOperation(FUserSlot UserSlot, TArray<FBeamContentId> StoreIds, FBeamOperationEventHandlerCode OnOperationEvent);

	/**
	 * \copybrief RefreshStoresOperation
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Store")
	FBeamOperationHandle RefreshStoreOperation(FUserSlot UserSlot, FBeamContentId StoreId, FBeamOperationEventHandler OnOperationEvent);

	/**
	 * \copybrief RefreshStoresOperation
	 */
	FBeamOperationHandle CPP_RefreshStoreOperation(FUserSlot UserSlot, FBeamContentId StoreId, FBeamOperationEventHandlerCode OnOperationEvent);

	// LOCAL STATE FETCHING
	
	UFUNCTION(BlueprintCallable, meta=(ExpandBoolAsExecs="ReturnValue"))
	bool TryGetStoreView(FUserSlot Slot, FBeamContentId StoreContentId, UBeamStoreView*& Store);

private:

	// OPERATION IMPLEMENTATIONS
	void PerformPurchase(FUserSlot UserSlot, FBeamContentId StoreId, FBeamContentId ListingId, FBeamOperationHandle Op = {});
	void RefreshStoreView(FUserSlot UserSlot, TArray<FBeamContentId> StoreIds, FBeamOperationHandle Op = {});
};
