

#pragma once

#include "CoreMinimal.h"
#include "BeamBackend.h"

#include "Commerce/GetSkusRequest.h"
#include "Commerce/GetCouponsCountRequest.h"
#include "Commerce/PostCatalogLegacyRequest.h"
#include "Commerce/GetCatalogRequest.h"
#include "Commerce/PostSkusRequest.h"
#include "Commerce/GetCommerceRequest.h"
#include "Commerce/PutListingsCooldownRequest.h"
#include "Commerce/GetOffersAdminRequest.h"
#include "Commerce/PostPurchaseRequest.h"
#include "Commerce/PutPurchaseRequest.h"
#include "Commerce/GetListingsRequest.h"
#include "Commerce/DeleteStatusRequest.h"
#include "Commerce/PostCouponsRequest.h"
#include "Commerce/PostStatsUpdateRequest.h"
#include "Commerce/GetOffersRequest.h"

#include "BeamCommerceApi.generated.h"


/**
 * Subsystem containing request calls for the Commerce service.
 */
UCLASS(BlueprintType)
class BEAMABLECORE_API UBeamCommerceApi : public UEngineSubsystem
{
private:
	GENERATED_BODY()
	/** @brief Initializes the auto-increment Id and binds the ExecuteRequestDelegate to DefaultExecuteRequestImpl  */
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	/** Cleans up the system.  */
	virtual void Deinitialize() override;

	UPROPERTY()
	UBeamBackend* Backend;

	
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_GetSkusImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetSkusRequest* RequestData,
	                                const FOnGetSkusSuccess& OnSuccess, const FOnGetSkusError& OnError, const FOnGetSkusComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetSkusImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetSkusRequest* RequestData,
	                                 const FOnGetSkusFullResponse& Handler) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_GetCouponsCountImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetCouponsCountRequest* RequestData,
	                                const FOnGetCouponsCountSuccess& OnSuccess, const FOnGetCouponsCountError& OnError, const FOnGetCouponsCountComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetCouponsCountImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetCouponsCountRequest* RequestData,
	                                 const FOnGetCouponsCountFullResponse& Handler) const;


	
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostCatalogLegacyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostCatalogLegacyRequest* RequestData,
	                  const FOnPostCatalogLegacySuccess& OnSuccess, const FOnPostCatalogLegacyError& OnError, const FOnPostCatalogLegacyComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostCatalogLegacyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostCatalogLegacyRequest* RequestData,
	                   const FOnPostCatalogLegacyFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_GetCatalogImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetCatalogRequest* RequestData,
	                  const FOnGetCatalogSuccess& OnSuccess, const FOnGetCatalogError& OnError, const FOnGetCatalogComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetCatalogImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetCatalogRequest* RequestData,
	                   const FOnGetCatalogFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostSkusImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostSkusRequest* RequestData,
	                  const FOnPostSkusSuccess& OnSuccess, const FOnPostSkusError& OnError, const FOnPostSkusComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostSkusImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostSkusRequest* RequestData,
	                   const FOnPostSkusFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_GetCommerceImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetCommerceRequest* RequestData,
	                  const FOnGetCommerceSuccess& OnSuccess, const FOnGetCommerceError& OnError, const FOnGetCommerceComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetCommerceImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetCommerceRequest* RequestData,
	                   const FOnGetCommerceFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PutListingsCooldownImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPutListingsCooldownRequest* RequestData,
	                  const FOnPutListingsCooldownSuccess& OnSuccess, const FOnPutListingsCooldownError& OnError, const FOnPutListingsCooldownComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PutListingsCooldownImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPutListingsCooldownRequest* RequestData,
	                   const FOnPutListingsCooldownFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_GetOffersAdminImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetOffersAdminRequest* RequestData,
	                  const FOnGetOffersAdminSuccess& OnSuccess, const FOnGetOffersAdminError& OnError, const FOnGetOffersAdminComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetOffersAdminImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetOffersAdminRequest* RequestData,
	                   const FOnGetOffersAdminFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostPurchaseImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostPurchaseRequest* RequestData,
	                  const FOnPostPurchaseSuccess& OnSuccess, const FOnPostPurchaseError& OnError, const FOnPostPurchaseComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostPurchaseImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostPurchaseRequest* RequestData,
	                   const FOnPostPurchaseFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PutPurchaseImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPutPurchaseRequest* RequestData,
	                  const FOnPutPurchaseSuccess& OnSuccess, const FOnPutPurchaseError& OnError, const FOnPutPurchaseComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PutPurchaseImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPutPurchaseRequest* RequestData,
	                   const FOnPutPurchaseFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_GetListingsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetListingsRequest* RequestData,
	                  const FOnGetListingsSuccess& OnSuccess, const FOnGetListingsError& OnError, const FOnGetListingsComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetListingsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetListingsRequest* RequestData,
	                   const FOnGetListingsFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_DeleteStatusImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UDeleteStatusRequest* RequestData,
	                  const FOnDeleteStatusSuccess& OnSuccess, const FOnDeleteStatusError& OnError, const FOnDeleteStatusComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_DeleteStatusImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UDeleteStatusRequest* RequestData,
	                   const FOnDeleteStatusFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostCouponsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostCouponsRequest* RequestData,
	                  const FOnPostCouponsSuccess& OnSuccess, const FOnPostCouponsError& OnError, const FOnPostCouponsComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostCouponsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostCouponsRequest* RequestData,
	                   const FOnPostCouponsFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostStatsUpdateImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostStatsUpdateRequest* RequestData,
	                  const FOnPostStatsUpdateSuccess& OnSuccess, const FOnPostStatsUpdateError& OnError, const FOnPostStatsUpdateComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostStatsUpdateImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostStatsUpdateRequest* RequestData,
	                   const FOnPostStatsUpdateFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_GetOffersImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetOffersRequest* RequestData,
	                  const FOnGetOffersSuccess& OnSuccess, const FOnGetOffersError& OnError, const FOnGetOffersComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetOffersImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetOffersRequest* RequestData,
	                   const FOnGetOffersFullResponse& Handler) const;

public:
	
	/** Used by a helper blueprint node so that you can easily chain requests in BP-land. */
	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	static UBeamCommerceApi* GetSelf() { return GEngine->GetEngineSubsystem<UBeamCommerceApi>(); }

	
	/**
	 * @brief Makes a request to the Get /basic/commerce/skus endpoint of the Commerce Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetSkus(UGetSkusRequest* Request, const FOnGetSkusFullResponse& Handler) const;

		
	/**
	 * @brief Makes a request to the Get /object/commerce/{objectId}/coupons/count endpoint of the Commerce Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetCouponsCount(UGetCouponsCountRequest* Request, const FOnGetCouponsCountFullResponse& Handler) const;


	
	/**
	 * @brief Makes an authenticated request to the Post /basic/commerce/catalog/legacy endpoint of the Commerce Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostCatalogLegacy(const FUserSlot& UserSlot, UPostCatalogLegacyRequest* Request, const FOnPostCatalogLegacyFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Get /basic/commerce/catalog endpoint of the Commerce Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetCatalog(const FUserSlot& UserSlot, UGetCatalogRequest* Request, const FOnGetCatalogFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/commerce/skus endpoint of the Commerce Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostSkus(const FUserSlot& UserSlot, UPostSkusRequest* Request, const FOnPostSkusFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Get /object/commerce/{objectId}/ endpoint of the Commerce Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetCommerce(const FUserSlot& UserSlot, UGetCommerceRequest* Request, const FOnGetCommerceFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Put /object/commerce/{objectId}/listings/cooldown endpoint of the Commerce Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PutListingsCooldown(const FUserSlot& UserSlot, UPutListingsCooldownRequest* Request, const FOnPutListingsCooldownFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Get /object/commerce/{objectId}/offersAdmin endpoint of the Commerce Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetOffersAdmin(const FUserSlot& UserSlot, UGetOffersAdminRequest* Request, const FOnGetOffersAdminFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /object/commerce/{objectId}/purchase endpoint of the Commerce Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostPurchase(const FUserSlot& UserSlot, UPostPurchaseRequest* Request, const FOnPostPurchaseFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Put /object/commerce/{objectId}/purchase endpoint of the Commerce Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PutPurchase(const FUserSlot& UserSlot, UPutPurchaseRequest* Request, const FOnPutPurchaseFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Get /object/commerce/{objectId}/listings endpoint of the Commerce Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetListings(const FUserSlot& UserSlot, UGetListingsRequest* Request, const FOnGetListingsFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Delete /object/commerce/{objectId}/status endpoint of the Commerce Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_DeleteStatus(const FUserSlot& UserSlot, UDeleteStatusRequest* Request, const FOnDeleteStatusFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /object/commerce/{objectId}/coupons endpoint of the Commerce Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostCoupons(const FUserSlot& UserSlot, UPostCouponsRequest* Request, const FOnPostCouponsFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /object/commerce/{objectId}/stats/update endpoint of the Commerce Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostStatsUpdate(const FUserSlot& UserSlot, UPostStatsUpdateRequest* Request, const FOnPostStatsUpdateFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Get /object/commerce/{objectId}/offers endpoint of the Commerce Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetOffers(const FUserSlot& UserSlot, UGetOffersRequest* Request, const FOnGetOffersFullResponse& Handler) const;


	
	/**
	 * @brief Makes a request to the Get /basic/commerce/skus endpoint of the Commerce Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Commerce", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void GetSkus(UGetSkusRequest* Request, const FOnGetSkusSuccess& OnSuccess, const FOnGetSkusError& OnError, const FOnGetSkusComplete& OnComplete,
								 int64& OutRequestId);

		
	/**
	 * @brief Makes a request to the Get /object/commerce/{objectId}/coupons/count endpoint of the Commerce Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Commerce", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void GetCouponsCount(UGetCouponsCountRequest* Request, const FOnGetCouponsCountSuccess& OnSuccess, const FOnGetCouponsCountError& OnError, const FOnGetCouponsCountComplete& OnComplete,
								 int64& OutRequestId);


	
	/**
	 * @brief Makes an authenticated request to the Post /basic/commerce/catalog/legacy endpoint of the Commerce Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Commerce", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void PostCatalogLegacy(const FUserSlot& UserSlot, UPostCatalogLegacyRequest* Request, const FOnPostCatalogLegacySuccess& OnSuccess, const FOnPostCatalogLegacyError& OnError, const FOnPostCatalogLegacyComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Get /basic/commerce/catalog endpoint of the Commerce Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Commerce", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void GetCatalog(const FUserSlot& UserSlot, UGetCatalogRequest* Request, const FOnGetCatalogSuccess& OnSuccess, const FOnGetCatalogError& OnError, const FOnGetCatalogComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/commerce/skus endpoint of the Commerce Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Commerce", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void PostSkus(const FUserSlot& UserSlot, UPostSkusRequest* Request, const FOnPostSkusSuccess& OnSuccess, const FOnPostSkusError& OnError, const FOnPostSkusComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Get /object/commerce/{objectId}/ endpoint of the Commerce Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Commerce", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void GetCommerce(const FUserSlot& UserSlot, UGetCommerceRequest* Request, const FOnGetCommerceSuccess& OnSuccess, const FOnGetCommerceError& OnError, const FOnGetCommerceComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Put /object/commerce/{objectId}/listings/cooldown endpoint of the Commerce Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Commerce", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void PutListingsCooldown(const FUserSlot& UserSlot, UPutListingsCooldownRequest* Request, const FOnPutListingsCooldownSuccess& OnSuccess, const FOnPutListingsCooldownError& OnError, const FOnPutListingsCooldownComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Get /object/commerce/{objectId}/offersAdmin endpoint of the Commerce Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Commerce", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void GetOffersAdmin(const FUserSlot& UserSlot, UGetOffersAdminRequest* Request, const FOnGetOffersAdminSuccess& OnSuccess, const FOnGetOffersAdminError& OnError, const FOnGetOffersAdminComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Post /object/commerce/{objectId}/purchase endpoint of the Commerce Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Commerce", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void PostPurchase(const FUserSlot& UserSlot, UPostPurchaseRequest* Request, const FOnPostPurchaseSuccess& OnSuccess, const FOnPostPurchaseError& OnError, const FOnPostPurchaseComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Put /object/commerce/{objectId}/purchase endpoint of the Commerce Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Commerce", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void PutPurchase(const FUserSlot& UserSlot, UPutPurchaseRequest* Request, const FOnPutPurchaseSuccess& OnSuccess, const FOnPutPurchaseError& OnError, const FOnPutPurchaseComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Get /object/commerce/{objectId}/listings endpoint of the Commerce Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Commerce", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void GetListings(const FUserSlot& UserSlot, UGetListingsRequest* Request, const FOnGetListingsSuccess& OnSuccess, const FOnGetListingsError& OnError, const FOnGetListingsComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Delete /object/commerce/{objectId}/status endpoint of the Commerce Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Commerce", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void DeleteStatus(const FUserSlot& UserSlot, UDeleteStatusRequest* Request, const FOnDeleteStatusSuccess& OnSuccess, const FOnDeleteStatusError& OnError, const FOnDeleteStatusComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Post /object/commerce/{objectId}/coupons endpoint of the Commerce Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Commerce", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void PostCoupons(const FUserSlot& UserSlot, UPostCouponsRequest* Request, const FOnPostCouponsSuccess& OnSuccess, const FOnPostCouponsError& OnError, const FOnPostCouponsComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Post /object/commerce/{objectId}/stats/update endpoint of the Commerce Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Commerce", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void PostStatsUpdate(const FUserSlot& UserSlot, UPostStatsUpdateRequest* Request, const FOnPostStatsUpdateSuccess& OnSuccess, const FOnPostStatsUpdateError& OnError, const FOnPostStatsUpdateComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Get /object/commerce/{objectId}/offers endpoint of the Commerce Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Commerce", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void GetOffers(const FUserSlot& UserSlot, UGetOffersRequest* Request, const FOnGetOffersSuccess& OnSuccess, const FOnGetOffersError& OnError, const FOnGetOffersComplete& OnComplete, int64& OutRequestId);
	
};