

#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBackend.h"
#include "BeamBackend/ResponseCache/BeamResponseCache.h"
#include "RequestTracker/BeamRequestTracker.h"

#include "BeamableCore/Public/AutoGen/SubSystems/Session/PostHeartbeatRequest.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Session/GetHistoryRequest.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Session/BasicSessionGetStatusRequest.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Session/GetClientHistoryRequest.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Session/PostSessionRequest.h"

#include "BeamSessionApi.generated.h"


/**
 * Subsystem containing request calls for the Session service.
 */
UCLASS(NotBlueprintType)
class BEAMABLECORE_API UBeamSessionApi : public UEngineSubsystem
{
private:
	GENERATED_BODY()
	/** @brief Initializes the auto-increment Id */
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	/** Cleans up the system.  */
	virtual void Deinitialize() override;

	UPROPERTY()
	UBeamBackend* Backend;

	UPROPERTY()
	UBeamRequestTracker* RequestTracker;

	UPROPERTY()
	UBeamResponseCache* ResponseCache;

	

	
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostHeartbeatImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, UPostHeartbeatRequest* RequestData,
	                  const FOnPostHeartbeatSuccess& OnSuccess, const FOnPostHeartbeatError& OnError, const FOnPostHeartbeatComplete& OnComplete, 
					  int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostHeartbeatImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, UPostHeartbeatRequest* RequestData,
	                   const FOnPostHeartbeatFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_GetHistoryImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, UGetHistoryRequest* RequestData,
	                  const FOnGetHistorySuccess& OnSuccess, const FOnGetHistoryError& OnError, const FOnGetHistoryComplete& OnComplete, 
					  int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetHistoryImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, UGetHistoryRequest* RequestData,
	                   const FOnGetHistoryFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_GetStatusImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, UBasicSessionGetStatusRequest* RequestData,
	                  const FOnBasicSessionGetStatusSuccess& OnSuccess, const FOnBasicSessionGetStatusError& OnError, const FOnBasicSessionGetStatusComplete& OnComplete, 
					  int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetStatusImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, UBasicSessionGetStatusRequest* RequestData,
	                   const FOnBasicSessionGetStatusFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_GetClientHistoryImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, UGetClientHistoryRequest* RequestData,
	                  const FOnGetClientHistorySuccess& OnSuccess, const FOnGetClientHistoryError& OnError, const FOnGetClientHistoryComplete& OnComplete, 
					  int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetClientHistoryImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, UGetClientHistoryRequest* RequestData,
	                   const FOnGetClientHistoryFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostSessionImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, UPostSessionRequest* RequestData,
	                  const FOnPostSessionSuccess& OnSuccess, const FOnPostSessionError& OnError, const FOnPostSessionComplete& OnComplete, 
					  int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostSessionImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, UPostSessionRequest* RequestData,
	                   const FOnPostSessionFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;

public:
	
	/** Used by a helper blueprint node so that you can easily chain requests in BP-land. */
	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	static UBeamSessionApi* GetSelf() { return GEngine->GetEngineSubsystem<UBeamSessionApi>(); }

	

	
	/**
	 * @brief Makes an authenticated request to the Post /basic/session/heartbeat endpoint of the Session Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId) and read-only RequestCaches. 
	 */
	void CPP_PostHeartbeat(const FUserSlot& UserSlot, UPostHeartbeatRequest* Request, const FOnPostHeartbeatFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;

		
	/**
	 * @brief Makes an authenticated request to the Get /basic/session/history endpoint of the Session Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId) and read-only RequestCaches. 
	 */
	void CPP_GetHistory(const FUserSlot& UserSlot, UGetHistoryRequest* Request, const FOnGetHistoryFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;

		
	/**
	 * @brief Makes an authenticated request to the Get /basic/session/status endpoint of the Session Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId) and read-only RequestCaches. 
	 */
	void CPP_GetStatus(const FUserSlot& UserSlot, UBasicSessionGetStatusRequest* Request, const FOnBasicSessionGetStatusFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;

		
	/**
	 * @brief Makes an authenticated request to the Get /basic/session/client/history endpoint of the Session Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId) and read-only RequestCaches. 
	 */
	void CPP_GetClientHistory(const FUserSlot& UserSlot, UGetClientHistoryRequest* Request, const FOnGetClientHistoryFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/session/ endpoint of the Session Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId) and read-only RequestCaches. 
	 */
	void CPP_PostSession(const FUserSlot& UserSlot, UPostSessionRequest* Request, const FOnPostSessionFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;


	

	
	/**
	 * @brief Makes an authenticated request to the Post /basic/session/heartbeat endpoint of the Session Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId) and read-only RequestCaches.
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Session|Utils|Make/Break", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="OpHandle,CallingContext",AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void PostHeartbeat(FUserSlot UserSlot, UPostHeartbeatRequest* Request, const FOnPostHeartbeatSuccess& OnSuccess, const FOnPostHeartbeatError& OnError, const FOnPostHeartbeatComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr);

		
	/**
	 * @brief Makes an authenticated request to the Get /basic/session/history endpoint of the Session Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId) and read-only RequestCaches.
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Session|Utils|Make/Break", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="OpHandle,CallingContext",AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void GetHistory(FUserSlot UserSlot, UGetHistoryRequest* Request, const FOnGetHistorySuccess& OnSuccess, const FOnGetHistoryError& OnError, const FOnGetHistoryComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr);

		
	/**
	 * @brief Makes an authenticated request to the Get /basic/session/status endpoint of the Session Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId) and read-only RequestCaches.
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Session|Utils|Make/Break", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="OpHandle,CallingContext",AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void GetStatus(FUserSlot UserSlot, UBasicSessionGetStatusRequest* Request, const FOnBasicSessionGetStatusSuccess& OnSuccess, const FOnBasicSessionGetStatusError& OnError, const FOnBasicSessionGetStatusComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr);

		
	/**
	 * @brief Makes an authenticated request to the Get /basic/session/client/history endpoint of the Session Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId) and read-only RequestCaches.
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Session|Utils|Make/Break", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="OpHandle,CallingContext",AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void GetClientHistory(FUserSlot UserSlot, UGetClientHistoryRequest* Request, const FOnGetClientHistorySuccess& OnSuccess, const FOnGetClientHistoryError& OnError, const FOnGetClientHistoryComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr);

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/session/ endpoint of the Session Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId) and read-only RequestCaches.
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Session|Utils|Make/Break", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="OpHandle,CallingContext",AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void PostSession(FUserSlot UserSlot, UPostSessionRequest* Request, const FOnPostSessionSuccess& OnSuccess, const FOnPostSessionError& OnError, const FOnPostSessionComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr);

};
