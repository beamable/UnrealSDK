

#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBackend.h"
#include "BeamBackend/ResponseCache/BeamResponseCache.h"
#include "RequestTracker/BeamRequestTracker.h"

#include "BeamableCore/Public/AutoGen/SubSystems/Events/GetRunningRequest.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Events/BasicEventsGetContentRequest.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Events/GetCalendarRequest.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Events/PostApplyContentRequest.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Events/PutEndPhaseRequest.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Events/GetEventsRequest.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Events/GetPingRequest.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Events/PutContentRequest.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Events/DeleteContentRequest.h"
#include "BeamableCore/Public/AutoGen/SubSystems/Events/PutRefreshRequest.h"

#include "BeamEventsApi.generated.h"


/**
 * Subsystem containing request calls for the Events service.
 */
UCLASS(NotBlueprintType)
class BEAMABLECORE_API UBeamEventsApi : public UEngineSubsystem
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
	 * @brief Private implementation that all overloaded BP UFunctions call.	  
	 */
	void BP_GetRunningImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, UGetRunningRequest* RequestData,
	                                const FOnGetRunningSuccess& OnSuccess, const FOnGetRunningError& OnError, const FOnGetRunningComplete& OnComplete,
	                                int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetRunningImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, UGetRunningRequest* RequestData,
	                                 const FOnGetRunningFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;


	
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_GetContentImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, UBasicEventsGetContentRequest* RequestData,
	                  const FOnBasicEventsGetContentSuccess& OnSuccess, const FOnBasicEventsGetContentError& OnError, const FOnBasicEventsGetContentComplete& OnComplete, 
					  int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetContentImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, UBasicEventsGetContentRequest* RequestData,
	                   const FOnBasicEventsGetContentFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_GetCalendarImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, UGetCalendarRequest* RequestData,
	                  const FOnGetCalendarSuccess& OnSuccess, const FOnGetCalendarError& OnError, const FOnGetCalendarComplete& OnComplete, 
					  int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetCalendarImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, UGetCalendarRequest* RequestData,
	                   const FOnGetCalendarFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostApplyContentImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, UPostApplyContentRequest* RequestData,
	                  const FOnPostApplyContentSuccess& OnSuccess, const FOnPostApplyContentError& OnError, const FOnPostApplyContentComplete& OnComplete, 
					  int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostApplyContentImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, UPostApplyContentRequest* RequestData,
	                   const FOnPostApplyContentFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PutEndPhaseImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, UPutEndPhaseRequest* RequestData,
	                  const FOnPutEndPhaseSuccess& OnSuccess, const FOnPutEndPhaseError& OnError, const FOnPutEndPhaseComplete& OnComplete, 
					  int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PutEndPhaseImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, UPutEndPhaseRequest* RequestData,
	                   const FOnPutEndPhaseFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_GetEventsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, UGetEventsRequest* RequestData,
	                  const FOnGetEventsSuccess& OnSuccess, const FOnGetEventsError& OnError, const FOnGetEventsComplete& OnComplete, 
					  int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetEventsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, UGetEventsRequest* RequestData,
	                   const FOnGetEventsFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_GetPingImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, UGetPingRequest* RequestData,
	                  const FOnGetPingSuccess& OnSuccess, const FOnGetPingError& OnError, const FOnGetPingComplete& OnComplete, 
					  int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetPingImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, UGetPingRequest* RequestData,
	                   const FOnGetPingFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PutContentImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, UPutContentRequest* RequestData,
	                  const FOnPutContentSuccess& OnSuccess, const FOnPutContentError& OnError, const FOnPutContentComplete& OnComplete, 
					  int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PutContentImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, UPutContentRequest* RequestData,
	                   const FOnPutContentFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_DeleteContentImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, UDeleteContentRequest* RequestData,
	                  const FOnDeleteContentSuccess& OnSuccess, const FOnDeleteContentError& OnError, const FOnDeleteContentComplete& OnComplete, 
					  int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_DeleteContentImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, UDeleteContentRequest* RequestData,
	                   const FOnDeleteContentFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PutRefreshImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, UPutRefreshRequest* RequestData,
	                  const FOnPutRefreshSuccess& OnSuccess, const FOnPutRefreshError& OnError, const FOnPutRefreshComplete& OnComplete, 
					  int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PutRefreshImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, UPutRefreshRequest* RequestData,
	                   const FOnPutRefreshFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;

public:
	
	/** Used by a helper blueprint node so that you can easily chain requests in BP-land. */
	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	static UBeamEventsApi* GetSelf() { return GEngine->GetEngineSubsystem<UBeamEventsApi>(); }

	
	/**
	 * @brief Makes a request to the Get /basic/events/running endpoint of the Events Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster and for whenever you need to capture variables).
	 * 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion.
     * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param OpHandle When made as part of an Operation, you can pass this in and it'll register the request with the operation automatically.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId) and read-only RequestCaches. 
	 */
	void CPP_GetRunning(UGetRunningRequest* Request, const FOnGetRunningFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;


	
	/**
	 * @brief Makes an authenticated request to the Get /basic/events/content endpoint of the Events Service.
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
	void CPP_GetContent(const FUserSlot& UserSlot, UBasicEventsGetContentRequest* Request, const FOnBasicEventsGetContentFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;

		
	/**
	 * @brief Makes an authenticated request to the Get /basic/events/calendar endpoint of the Events Service.
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
	void CPP_GetCalendar(const FUserSlot& UserSlot, UGetCalendarRequest* Request, const FOnGetCalendarFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/events/applyContent endpoint of the Events Service.
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
	void CPP_PostApplyContent(const FUserSlot& UserSlot, UPostApplyContentRequest* Request, const FOnPostApplyContentFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;

		
	/**
	 * @brief Makes an authenticated request to the Put /object/events/{objectId}/endPhase endpoint of the Events Service.
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
	void CPP_PutEndPhase(const FUserSlot& UserSlot, UPutEndPhaseRequest* Request, const FOnPutEndPhaseFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;

		
	/**
	 * @brief Makes an authenticated request to the Get /object/events/{objectId}/ endpoint of the Events Service.
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
	void CPP_GetEvents(const FUserSlot& UserSlot, UGetEventsRequest* Request, const FOnGetEventsFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;

		
	/**
	 * @brief Makes an authenticated request to the Get /object/events/{objectId}/ping endpoint of the Events Service.
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
	void CPP_GetPing(const FUserSlot& UserSlot, UGetPingRequest* Request, const FOnGetPingFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;

		
	/**
	 * @brief Makes an authenticated request to the Put /object/events/{objectId}/content endpoint of the Events Service.
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
	void CPP_PutContent(const FUserSlot& UserSlot, UPutContentRequest* Request, const FOnPutContentFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;

		
	/**
	 * @brief Makes an authenticated request to the Delete /object/events/{objectId}/content endpoint of the Events Service.
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
	void CPP_DeleteContent(const FUserSlot& UserSlot, UDeleteContentRequest* Request, const FOnDeleteContentFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;

		
	/**
	 * @brief Makes an authenticated request to the Put /object/events/{objectId}/refresh endpoint of the Events Service.
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
	void CPP_PutRefresh(const FUserSlot& UserSlot, UPutRefreshRequest* Request, const FOnPutRefreshFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr) const;


	
	/**
	 * @brief Makes a request to the Get /basic/events/running endpoint of the Events Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId) and read-only RequestCaches. 
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Events|Utils|Make/Break", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="OpHandle,CallingContext", AutoCreateRefTerm="OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void GetRunning(UGetRunningRequest* Request, const FOnGetRunningSuccess& OnSuccess, const FOnGetRunningError& OnError, const FOnGetRunningComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr);


	
	/**
	 * @brief Makes an authenticated request to the Get /basic/events/content endpoint of the Events Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId) and read-only RequestCaches.
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Events|Utils|Make/Break", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="OpHandle,CallingContext",AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void GetContent(FUserSlot UserSlot, UBasicEventsGetContentRequest* Request, const FOnBasicEventsGetContentSuccess& OnSuccess, const FOnBasicEventsGetContentError& OnError, const FOnBasicEventsGetContentComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr);

		
	/**
	 * @brief Makes an authenticated request to the Get /basic/events/calendar endpoint of the Events Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId) and read-only RequestCaches.
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Events|Utils|Make/Break", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="OpHandle,CallingContext",AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void GetCalendar(FUserSlot UserSlot, UGetCalendarRequest* Request, const FOnGetCalendarSuccess& OnSuccess, const FOnGetCalendarError& OnError, const FOnGetCalendarComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr);

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/events/applyContent endpoint of the Events Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId) and read-only RequestCaches.
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Events|Utils|Make/Break", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="OpHandle,CallingContext",AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void PostApplyContent(FUserSlot UserSlot, UPostApplyContentRequest* Request, const FOnPostApplyContentSuccess& OnSuccess, const FOnPostApplyContentError& OnError, const FOnPostApplyContentComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr);

		
	/**
	 * @brief Makes an authenticated request to the Put /object/events/{objectId}/endPhase endpoint of the Events Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId) and read-only RequestCaches.
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Events|Utils|Make/Break", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="OpHandle,CallingContext",AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void PutEndPhase(FUserSlot UserSlot, UPutEndPhaseRequest* Request, const FOnPutEndPhaseSuccess& OnSuccess, const FOnPutEndPhaseError& OnError, const FOnPutEndPhaseComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr);

		
	/**
	 * @brief Makes an authenticated request to the Get /object/events/{objectId}/ endpoint of the Events Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId) and read-only RequestCaches.
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Events|Utils|Make/Break", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="OpHandle,CallingContext",AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void GetEvents(FUserSlot UserSlot, UGetEventsRequest* Request, const FOnGetEventsSuccess& OnSuccess, const FOnGetEventsError& OnError, const FOnGetEventsComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr);

		
	/**
	 * @brief Makes an authenticated request to the Get /object/events/{objectId}/ping endpoint of the Events Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId) and read-only RequestCaches.
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Events|Utils|Make/Break", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="OpHandle,CallingContext",AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void GetPing(FUserSlot UserSlot, UGetPingRequest* Request, const FOnGetPingSuccess& OnSuccess, const FOnGetPingError& OnError, const FOnGetPingComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr);

		
	/**
	 * @brief Makes an authenticated request to the Put /object/events/{objectId}/content endpoint of the Events Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId) and read-only RequestCaches.
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Events|Utils|Make/Break", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="OpHandle,CallingContext",AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void PutContent(FUserSlot UserSlot, UPutContentRequest* Request, const FOnPutContentSuccess& OnSuccess, const FOnPutContentError& OnError, const FOnPutContentComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr);

		
	/**
	 * @brief Makes an authenticated request to the Delete /object/events/{objectId}/content endpoint of the Events Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId) and read-only RequestCaches.
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Events|Utils|Make/Break", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="OpHandle,CallingContext",AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void DeleteContent(FUserSlot UserSlot, UDeleteContentRequest* Request, const FOnDeleteContentSuccess& OnSuccess, const FOnDeleteContentError& OnError, const FOnDeleteContentComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr);

		
	/**
	 * @brief Makes an authenticated request to the Put /object/events/{objectId}/refresh endpoint of the Events Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestContext The Request Context associated with this request -- used to query information about the request or to cancel it while it's in flight.
	 * @param CallingContext A UObject managed by the UWorld that's making the request. Used to support multiple PIEs (see UBeamUserSlot::GetNamespacedSlotId) and read-only RequestCaches.
	 */
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category="Beam|Events|Utils|Make/Break", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="OpHandle,CallingContext",AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete,OpHandle", BeamFlowFunction))
	void PutRefresh(FUserSlot UserSlot, UPutRefreshRequest* Request, const FOnPutRefreshSuccess& OnSuccess, const FOnPutRefreshError& OnError, const FOnPutRefreshComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle = FBeamOperationHandle(), const UObject* CallingContext = nullptr);

};
