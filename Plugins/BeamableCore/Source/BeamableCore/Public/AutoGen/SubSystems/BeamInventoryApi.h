

#pragma once

#include "CoreMinimal.h"
#include "BeamBackend.h"

#include "Inventory/GetItemsRequest.h"
#include "Inventory/GetCurrencyRequest.h"
#include "Inventory/PutPreviewRequest.h"
#include "Inventory/GetMultipliersRequest.h"
#include "Inventory/GetInventoryRequest.h"
#include "Inventory/PostInventoryRequest.h"
#include "Inventory/PutInventoryRequest.h"
#include "Inventory/DeleteTransactionRequest.h"
#include "Inventory/PutTransferRequest.h"

#include "BeamInventoryApi.generated.h"


/**
 * Subsystem containing request calls for the Inventory service.
 */
UCLASS(BlueprintType)
class BEAMABLECORE_API UBeamInventoryApi : public UEngineSubsystem
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
	void BP_GetItemsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetItemsRequest* RequestData,
	                                const FOnGetItemsSuccess& OnSuccess, const FOnGetItemsError& OnError, const FOnGetItemsComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetItemsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetItemsRequest* RequestData,
	                                 const FOnGetItemsFullResponse& Handler) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_GetCurrencyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetCurrencyRequest* RequestData,
	                                const FOnGetCurrencySuccess& OnSuccess, const FOnGetCurrencyError& OnError, const FOnGetCurrencyComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetCurrencyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetCurrencyRequest* RequestData,
	                                 const FOnGetCurrencyFullResponse& Handler) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_PutPreviewImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPutPreviewRequest* RequestData,
	                                const FOnPutPreviewSuccess& OnSuccess, const FOnPutPreviewError& OnError, const FOnPutPreviewComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PutPreviewImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPutPreviewRequest* RequestData,
	                                 const FOnPutPreviewFullResponse& Handler) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_GetMultipliersImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetMultipliersRequest* RequestData,
	                                const FOnGetMultipliersSuccess& OnSuccess, const FOnGetMultipliersError& OnError, const FOnGetMultipliersComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetMultipliersImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetMultipliersRequest* RequestData,
	                                 const FOnGetMultipliersFullResponse& Handler) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_GetInventoryImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetInventoryRequest* RequestData,
	                                const FOnGetInventorySuccess& OnSuccess, const FOnGetInventoryError& OnError, const FOnGetInventoryComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetInventoryImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetInventoryRequest* RequestData,
	                                 const FOnGetInventoryFullResponse& Handler) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_PostInventoryImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostInventoryRequest* RequestData,
	                                const FOnPostInventorySuccess& OnSuccess, const FOnPostInventoryError& OnError, const FOnPostInventoryComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostInventoryImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostInventoryRequest* RequestData,
	                                 const FOnPostInventoryFullResponse& Handler) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_PutInventoryImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPutInventoryRequest* RequestData,
	                                const FOnPutInventorySuccess& OnSuccess, const FOnPutInventoryError& OnError, const FOnPutInventoryComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PutInventoryImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPutInventoryRequest* RequestData,
	                                 const FOnPutInventoryFullResponse& Handler) const;


	
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_DeleteTransactionImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UDeleteTransactionRequest* RequestData,
	                  const FOnDeleteTransactionSuccess& OnSuccess, const FOnDeleteTransactionError& OnError, const FOnDeleteTransactionComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_DeleteTransactionImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UDeleteTransactionRequest* RequestData,
	                   const FOnDeleteTransactionFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PutTransferImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPutTransferRequest* RequestData,
	                  const FOnPutTransferSuccess& OnSuccess, const FOnPutTransferError& OnError, const FOnPutTransferComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PutTransferImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPutTransferRequest* RequestData,
	                   const FOnPutTransferFullResponse& Handler) const;

public:
	
	/** Used by a helper blueprint node so that you can easily chain requests in BP-land. */
	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	static UBeamInventoryApi* GetSelf() { return GEngine->GetEngineSubsystem<UBeamInventoryApi>(); }

	
	/**
	 * @brief Makes a request to the Get /basic/inventory/items endpoint of the Inventory Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetItems(UGetItemsRequest* Request, const FOnGetItemsFullResponse& Handler) const;

		
	/**
	 * @brief Makes a request to the Get /basic/inventory/currency endpoint of the Inventory Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetCurrency(UGetCurrencyRequest* Request, const FOnGetCurrencyFullResponse& Handler) const;

		
	/**
	 * @brief Makes a request to the Put /object/inventory/{objectId}/preview endpoint of the Inventory Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PutPreview(UPutPreviewRequest* Request, const FOnPutPreviewFullResponse& Handler) const;

		
	/**
	 * @brief Makes a request to the Get /object/inventory/{objectId}/multipliers endpoint of the Inventory Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetMultipliers(UGetMultipliersRequest* Request, const FOnGetMultipliersFullResponse& Handler) const;

		
	/**
	 * @brief Makes a request to the Get /object/inventory/{objectId}/ endpoint of the Inventory Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetInventory(UGetInventoryRequest* Request, const FOnGetInventoryFullResponse& Handler) const;

		
	/**
	 * @brief Makes a request to the Post /object/inventory/{objectId}/ endpoint of the Inventory Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostInventory(UPostInventoryRequest* Request, const FOnPostInventoryFullResponse& Handler) const;

		
	/**
	 * @brief Makes a request to the Put /object/inventory/{objectId}/ endpoint of the Inventory Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PutInventory(UPutInventoryRequest* Request, const FOnPutInventoryFullResponse& Handler) const;


	
	/**
	 * @brief Makes an authenticated request to the Delete /object/inventory/{objectId}/transaction endpoint of the Inventory Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_DeleteTransaction(const FUserSlot& UserSlot, UDeleteTransactionRequest* Request, const FOnDeleteTransactionFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Put /object/inventory/{objectId}/transfer endpoint of the Inventory Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PutTransfer(const FUserSlot& UserSlot, UPutTransferRequest* Request, const FOnPutTransferFullResponse& Handler) const;


	
	/**
	 * @brief Makes a request to the Get /basic/inventory/items endpoint of the Inventory Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Inventory", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void GetItems(UGetItemsRequest* Request, const FOnGetItemsSuccess& OnSuccess, const FOnGetItemsError& OnError, const FOnGetItemsComplete& OnComplete,
								 int64& OutRequestId);

		
	/**
	 * @brief Makes a request to the Get /basic/inventory/currency endpoint of the Inventory Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Inventory", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void GetCurrency(UGetCurrencyRequest* Request, const FOnGetCurrencySuccess& OnSuccess, const FOnGetCurrencyError& OnError, const FOnGetCurrencyComplete& OnComplete,
								 int64& OutRequestId);

		
	/**
	 * @brief Makes a request to the Put /object/inventory/{objectId}/preview endpoint of the Inventory Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Inventory", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void PutPreview(UPutPreviewRequest* Request, const FOnPutPreviewSuccess& OnSuccess, const FOnPutPreviewError& OnError, const FOnPutPreviewComplete& OnComplete,
								 int64& OutRequestId);

		
	/**
	 * @brief Makes a request to the Get /object/inventory/{objectId}/multipliers endpoint of the Inventory Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Inventory", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void GetMultipliers(UGetMultipliersRequest* Request, const FOnGetMultipliersSuccess& OnSuccess, const FOnGetMultipliersError& OnError, const FOnGetMultipliersComplete& OnComplete,
								 int64& OutRequestId);

		
	/**
	 * @brief Makes a request to the Get /object/inventory/{objectId}/ endpoint of the Inventory Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Inventory", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void GetInventory(UGetInventoryRequest* Request, const FOnGetInventorySuccess& OnSuccess, const FOnGetInventoryError& OnError, const FOnGetInventoryComplete& OnComplete,
								 int64& OutRequestId);

		
	/**
	 * @brief Makes a request to the Post /object/inventory/{objectId}/ endpoint of the Inventory Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Inventory", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void PostInventory(UPostInventoryRequest* Request, const FOnPostInventorySuccess& OnSuccess, const FOnPostInventoryError& OnError, const FOnPostInventoryComplete& OnComplete,
								 int64& OutRequestId);

		
	/**
	 * @brief Makes a request to the Put /object/inventory/{objectId}/ endpoint of the Inventory Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Inventory", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void PutInventory(UPutInventoryRequest* Request, const FOnPutInventorySuccess& OnSuccess, const FOnPutInventoryError& OnError, const FOnPutInventoryComplete& OnComplete,
								 int64& OutRequestId);


	
	/**
	 * @brief Makes an authenticated request to the Delete /object/inventory/{objectId}/transaction endpoint of the Inventory Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Inventory", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void DeleteTransaction(const FUserSlot& UserSlot, UDeleteTransactionRequest* Request, const FOnDeleteTransactionSuccess& OnSuccess, const FOnDeleteTransactionError& OnError, const FOnDeleteTransactionComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Put /object/inventory/{objectId}/transfer endpoint of the Inventory Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Inventory", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void PutTransfer(const FUserSlot& UserSlot, UPutTransferRequest* Request, const FOnPutTransferSuccess& OnSuccess, const FOnPutTransferError& OnError, const FOnPutTransferComplete& OnComplete, int64& OutRequestId);
	
};
