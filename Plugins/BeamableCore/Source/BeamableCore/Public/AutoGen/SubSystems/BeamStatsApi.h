

#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBackend.h"

#include "Stats/GetClientBatchRequest.h"
#include "Stats/PostClientStringlistRequest.h"
#include "Stats/GetClientRequest.h"
#include "Stats/PostClientRequest.h"
#include "Stats/PutSubscribeRequest.h"
#include "Stats/PostBatchRequest.h"
#include "Stats/BasicStatsPostSearchRequest.h"
#include "Stats/PostSearchExtendedRequest.h"
#include "Stats/GetStatsRequest.h"
#include "Stats/PostStatsRequest.h"
#include "Stats/DeleteStatsRequest.h"

#include "BeamStatsApi.generated.h"


/**
 * Subsystem containing request calls for the Stats service.
 */
UCLASS(NotBlueprintType)
class BEAMABLECORE_API UBeamStatsApi : public UEngineSubsystem
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
	void BP_GetClientBatchImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetClientBatchRequest* RequestData,
	                                const FOnGetClientBatchSuccess& OnSuccess, const FOnGetClientBatchError& OnError, const FOnGetClientBatchComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetClientBatchImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetClientBatchRequest* RequestData,
	                                 const FOnGetClientBatchFullResponse& Handler) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_PostClientStringlistImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostClientStringlistRequest* RequestData,
	                                const FOnPostClientStringlistSuccess& OnSuccess, const FOnPostClientStringlistError& OnError, const FOnPostClientStringlistComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostClientStringlistImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostClientStringlistRequest* RequestData,
	                                 const FOnPostClientStringlistFullResponse& Handler) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_GetClientImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetClientRequest* RequestData,
	                                const FOnGetClientSuccess& OnSuccess, const FOnGetClientError& OnError, const FOnGetClientComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetClientImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetClientRequest* RequestData,
	                                 const FOnGetClientFullResponse& Handler) const;

		
	/**
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_PostClientImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostClientRequest* RequestData,
	                                const FOnPostClientSuccess& OnSuccess, const FOnPostClientError& OnError, const FOnPostClientComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostClientImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostClientRequest* RequestData,
	                                 const FOnPostClientFullResponse& Handler) const;


	
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PutSubscribeImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPutSubscribeRequest* RequestData,
	                  const FOnPutSubscribeSuccess& OnSuccess, const FOnPutSubscribeError& OnError, const FOnPutSubscribeComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PutSubscribeImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPutSubscribeRequest* RequestData,
	                   const FOnPutSubscribeFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostBatchImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostBatchRequest* RequestData,
	                  const FOnPostBatchSuccess& OnSuccess, const FOnPostBatchError& OnError, const FOnPostBatchComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostBatchImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostBatchRequest* RequestData,
	                   const FOnPostBatchFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostSearchImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UBasicStatsPostSearchRequest* RequestData,
	                  const FOnBasicStatsPostSearchSuccess& OnSuccess, const FOnBasicStatsPostSearchError& OnError, const FOnBasicStatsPostSearchComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostSearchImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UBasicStatsPostSearchRequest* RequestData,
	                   const FOnBasicStatsPostSearchFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostSearchExtendedImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostSearchExtendedRequest* RequestData,
	                  const FOnPostSearchExtendedSuccess& OnSuccess, const FOnPostSearchExtendedError& OnError, const FOnPostSearchExtendedComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostSearchExtendedImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostSearchExtendedRequest* RequestData,
	                   const FOnPostSearchExtendedFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_GetStatsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetStatsRequest* RequestData,
	                  const FOnGetStatsSuccess& OnSuccess, const FOnGetStatsError& OnError, const FOnGetStatsComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetStatsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetStatsRequest* RequestData,
	                   const FOnGetStatsFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostStatsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostStatsRequest* RequestData,
	                  const FOnPostStatsSuccess& OnSuccess, const FOnPostStatsError& OnError, const FOnPostStatsComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostStatsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostStatsRequest* RequestData,
	                   const FOnPostStatsFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_DeleteStatsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UDeleteStatsRequest* RequestData,
	                  const FOnDeleteStatsSuccess& OnSuccess, const FOnDeleteStatsError& OnError, const FOnDeleteStatsComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_DeleteStatsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UDeleteStatsRequest* RequestData,
	                   const FOnDeleteStatsFullResponse& Handler) const;

public:
	
	/** Used by a helper blueprint node so that you can easily chain requests in BP-land. */
	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	static UBeamStatsApi* GetSelf() { return GEngine->GetEngineSubsystem<UBeamStatsApi>(); }

	
	/**
	 * @brief Makes a request to the Get /basic/stats/client/batch endpoint of the Stats Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetClientBatch(UGetClientBatchRequest* Request, const FOnGetClientBatchFullResponse& Handler) const;

		
	/**
	 * @brief Makes a request to the Post /object/stats/{objectId}/client/stringlist endpoint of the Stats Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostClientStringlist(UPostClientStringlistRequest* Request, const FOnPostClientStringlistFullResponse& Handler) const;

		
	/**
	 * @brief Makes a request to the Get /object/stats/{objectId}/client endpoint of the Stats Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetClient(UGetClientRequest* Request, const FOnGetClientFullResponse& Handler) const;

		
	/**
	 * @brief Makes a request to the Post /object/stats/{objectId}/client endpoint of the Stats Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostClient(UPostClientRequest* Request, const FOnPostClientFullResponse& Handler) const;


	
	/**
	 * @brief Makes an authenticated request to the Put /basic/stats/subscribe endpoint of the Stats Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PutSubscribe(const FUserSlot& UserSlot, UPutSubscribeRequest* Request, const FOnPutSubscribeFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/stats/batch endpoint of the Stats Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostBatch(const FUserSlot& UserSlot, UPostBatchRequest* Request, const FOnPostBatchFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/stats/search endpoint of the Stats Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostSearch(const FUserSlot& UserSlot, UBasicStatsPostSearchRequest* Request, const FOnBasicStatsPostSearchFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/stats/search/extended endpoint of the Stats Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostSearchExtended(const FUserSlot& UserSlot, UPostSearchExtendedRequest* Request, const FOnPostSearchExtendedFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Get /object/stats/{objectId}/ endpoint of the Stats Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetStats(const FUserSlot& UserSlot, UGetStatsRequest* Request, const FOnGetStatsFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /object/stats/{objectId}/ endpoint of the Stats Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostStats(const FUserSlot& UserSlot, UPostStatsRequest* Request, const FOnPostStatsFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Delete /object/stats/{objectId}/ endpoint of the Stats Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_DeleteStats(const FUserSlot& UserSlot, UDeleteStatsRequest* Request, const FOnDeleteStatsFullResponse& Handler) const;


	
	/**
	 * @brief Makes a request to the Get /basic/stats/client/batch endpoint of the Stats Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Stats", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete", BeamFlowStart))
	void GetClientBatch(UGetClientBatchRequest* Request, const FOnGetClientBatchSuccess& OnSuccess, const FOnGetClientBatchError& OnError, const FOnGetClientBatchComplete& OnComplete, FBeamRequestContext& OutRequestContext);

		
	/**
	 * @brief Makes a request to the Post /object/stats/{objectId}/client/stringlist endpoint of the Stats Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Stats", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete", BeamFlowStart))
	void PostClientStringlist(UPostClientStringlistRequest* Request, const FOnPostClientStringlistSuccess& OnSuccess, const FOnPostClientStringlistError& OnError, const FOnPostClientStringlistComplete& OnComplete, FBeamRequestContext& OutRequestContext);

		
	/**
	 * @brief Makes a request to the Get /object/stats/{objectId}/client endpoint of the Stats Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Stats", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete", BeamFlowStart))
	void GetClient(UGetClientRequest* Request, const FOnGetClientSuccess& OnSuccess, const FOnGetClientError& OnError, const FOnGetClientComplete& OnComplete, FBeamRequestContext& OutRequestContext);

		
	/**
	 * @brief Makes a request to the Post /object/stats/{objectId}/client endpoint of the Stats Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Stats", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete", BeamFlowStart))
	void PostClient(UPostClientRequest* Request, const FOnPostClientSuccess& OnSuccess, const FOnPostClientError& OnError, const FOnPostClientComplete& OnComplete, FBeamRequestContext& OutRequestContext);


	
	/**
	 * @brief Makes an authenticated request to the Put /basic/stats/subscribe endpoint of the Stats Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Stats", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowStart))
	void PutSubscribe(FUserSlot UserSlot, UPutSubscribeRequest* Request, const FOnPutSubscribeSuccess& OnSuccess, const FOnPutSubscribeError& OnError, const FOnPutSubscribeComplete& OnComplete, FBeamRequestContext& OutRequestContext);

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/stats/batch endpoint of the Stats Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Stats", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowStart))
	void PostBatch(FUserSlot UserSlot, UPostBatchRequest* Request, const FOnPostBatchSuccess& OnSuccess, const FOnPostBatchError& OnError, const FOnPostBatchComplete& OnComplete, FBeamRequestContext& OutRequestContext);

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/stats/search endpoint of the Stats Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Stats", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowStart))
	void PostSearch(FUserSlot UserSlot, UBasicStatsPostSearchRequest* Request, const FOnBasicStatsPostSearchSuccess& OnSuccess, const FOnBasicStatsPostSearchError& OnError, const FOnBasicStatsPostSearchComplete& OnComplete, FBeamRequestContext& OutRequestContext);

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/stats/search/extended endpoint of the Stats Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Stats", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowStart))
	void PostSearchExtended(FUserSlot UserSlot, UPostSearchExtendedRequest* Request, const FOnPostSearchExtendedSuccess& OnSuccess, const FOnPostSearchExtendedError& OnError, const FOnPostSearchExtendedComplete& OnComplete, FBeamRequestContext& OutRequestContext);

		
	/**
	 * @brief Makes an authenticated request to the Get /object/stats/{objectId}/ endpoint of the Stats Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Stats", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowStart))
	void GetStats(FUserSlot UserSlot, UGetStatsRequest* Request, const FOnGetStatsSuccess& OnSuccess, const FOnGetStatsError& OnError, const FOnGetStatsComplete& OnComplete, FBeamRequestContext& OutRequestContext);

		
	/**
	 * @brief Makes an authenticated request to the Post /object/stats/{objectId}/ endpoint of the Stats Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Stats", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowStart))
	void PostStats(FUserSlot UserSlot, UPostStatsRequest* Request, const FOnPostStatsSuccess& OnSuccess, const FOnPostStatsError& OnError, const FOnPostStatsComplete& OnComplete, FBeamRequestContext& OutRequestContext);

		
	/**
	 * @brief Makes an authenticated request to the Delete /object/stats/{objectId}/ endpoint of the Stats Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Stats", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowStart))
	void DeleteStats(FUserSlot UserSlot, UDeleteStatsRequest* Request, const FOnDeleteStatsSuccess& OnSuccess, const FOnDeleteStatsError& OnError, const FOnDeleteStatsComplete& OnComplete, FBeamRequestContext& OutRequestContext);
	

	
	/**
	 * @brief Makes a request to the Get /basic/stats/client/batch endpoint of the Stats Service.
	 *	 
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Stats", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete", BeamFlowStart))
	void GetClientBatchWithRetry(const FBeamRetryConfig& RetryConfig, UGetClientBatchRequest* Request, const FOnGetClientBatchSuccess& OnSuccess, const FOnGetClientBatchError& OnError, const FOnGetClientBatchComplete& OnComplete, FBeamRequestContext& OutRequestContext);
		
	/**
	 * @brief Makes a request to the Post /object/stats/{objectId}/client/stringlist endpoint of the Stats Service.
	 *	 
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Stats", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete", BeamFlowStart))
	void PostClientStringlistWithRetry(const FBeamRetryConfig& RetryConfig, UPostClientStringlistRequest* Request, const FOnPostClientStringlistSuccess& OnSuccess, const FOnPostClientStringlistError& OnError, const FOnPostClientStringlistComplete& OnComplete, FBeamRequestContext& OutRequestContext);
		
	/**
	 * @brief Makes a request to the Get /object/stats/{objectId}/client endpoint of the Stats Service.
	 *	 
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Stats", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete", BeamFlowStart))
	void GetClientWithRetry(const FBeamRetryConfig& RetryConfig, UGetClientRequest* Request, const FOnGetClientSuccess& OnSuccess, const FOnGetClientError& OnError, const FOnGetClientComplete& OnComplete, FBeamRequestContext& OutRequestContext);
		
	/**
	 * @brief Makes a request to the Post /object/stats/{objectId}/client endpoint of the Stats Service.
	 *	 
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Stats", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete", BeamFlowStart))
	void PostClientWithRetry(const FBeamRetryConfig& RetryConfig, UPostClientRequest* Request, const FOnPostClientSuccess& OnSuccess, const FOnPostClientError& OnError, const FOnPostClientComplete& OnComplete, FBeamRequestContext& OutRequestContext);

	
	/**
	 * @brief Makes an authenticated request to the Put /basic/stats/subscribe endpoint of the Stats Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request.
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Stats", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowStart))
	void PutSubscribeWithRetry(FUserSlot UserSlot, const FBeamRetryConfig& RetryConfig, UPutSubscribeRequest* Request, const FOnPutSubscribeSuccess& OnSuccess, const FOnPutSubscribeError& OnError, const FOnPutSubscribeComplete& OnComplete, FBeamRequestContext& OutRequestContext);
		
	/**
	 * @brief Makes an authenticated request to the Post /basic/stats/batch endpoint of the Stats Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request.
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Stats", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowStart))
	void PostBatchWithRetry(FUserSlot UserSlot, const FBeamRetryConfig& RetryConfig, UPostBatchRequest* Request, const FOnPostBatchSuccess& OnSuccess, const FOnPostBatchError& OnError, const FOnPostBatchComplete& OnComplete, FBeamRequestContext& OutRequestContext);
		
	/**
	 * @brief Makes an authenticated request to the Post /basic/stats/search endpoint of the Stats Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request.
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Stats", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowStart))
	void PostSearchWithRetry(FUserSlot UserSlot, const FBeamRetryConfig& RetryConfig, UBasicStatsPostSearchRequest* Request, const FOnBasicStatsPostSearchSuccess& OnSuccess, const FOnBasicStatsPostSearchError& OnError, const FOnBasicStatsPostSearchComplete& OnComplete, FBeamRequestContext& OutRequestContext);
		
	/**
	 * @brief Makes an authenticated request to the Post /basic/stats/search/extended endpoint of the Stats Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request.
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Stats", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowStart))
	void PostSearchExtendedWithRetry(FUserSlot UserSlot, const FBeamRetryConfig& RetryConfig, UPostSearchExtendedRequest* Request, const FOnPostSearchExtendedSuccess& OnSuccess, const FOnPostSearchExtendedError& OnError, const FOnPostSearchExtendedComplete& OnComplete, FBeamRequestContext& OutRequestContext);
		
	/**
	 * @brief Makes an authenticated request to the Get /object/stats/{objectId}/ endpoint of the Stats Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request.
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Stats", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowStart))
	void GetStatsWithRetry(FUserSlot UserSlot, const FBeamRetryConfig& RetryConfig, UGetStatsRequest* Request, const FOnGetStatsSuccess& OnSuccess, const FOnGetStatsError& OnError, const FOnGetStatsComplete& OnComplete, FBeamRequestContext& OutRequestContext);
		
	/**
	 * @brief Makes an authenticated request to the Post /object/stats/{objectId}/ endpoint of the Stats Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request.
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Stats", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowStart))
	void PostStatsWithRetry(FUserSlot UserSlot, const FBeamRetryConfig& RetryConfig, UPostStatsRequest* Request, const FOnPostStatsSuccess& OnSuccess, const FOnPostStatsError& OnError, const FOnPostStatsComplete& OnComplete, FBeamRequestContext& OutRequestContext);
		
	/**
	 * @brief Makes an authenticated request to the Delete /object/stats/{objectId}/ endpoint of the Stats Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request.
	 * @param RetryConfig The retry config for this specific request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Backend|Stats", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete", BeamFlowStart))
	void DeleteStatsWithRetry(FUserSlot UserSlot, const FBeamRetryConfig& RetryConfig, UDeleteStatsRequest* Request, const FOnDeleteStatsSuccess& OnSuccess, const FOnDeleteStatsError& OnError, const FOnDeleteStatsComplete& OnComplete, FBeamRequestContext& OutRequestContext);
};
