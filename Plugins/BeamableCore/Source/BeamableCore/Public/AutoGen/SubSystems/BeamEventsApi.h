

#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBackend.h"

#include "Events/GetRunningRequest.h"
#include "Events/BasicEventsGetContentRequest.h"
#include "Events/GetCalendarRequest.h"
#include "Events/PostApplyContentRequest.h"
#include "Events/PutEndPhaseRequest.h"
#include "Events/GetEventsRequest.h"
#include "Events/GetPingRequest.h"
#include "Events/PutContentRequest.h"
#include "Events/DeleteContentRequest.h"
#include "Events/PutRefreshRequest.h"

#include "BeamEventsApi.generated.h"


/**
 * Subsystem containing request calls for the Events service.
 */
UCLASS(BlueprintType)
class BEAMABLECORE_API UBeamEventsApi : public UEngineSubsystem
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
	void BP_GetRunningImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetRunningRequest* RequestData,
	                                const FOnGetRunningSuccess& OnSuccess, const FOnGetRunningError& OnError, const FOnGetRunningComplete& OnComplete,
	                                int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetRunningImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetRunningRequest* RequestData,
	                                 const FOnGetRunningFullResponse& Handler) const;


	
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_GetContentImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UBasicEventsGetContentRequest* RequestData,
	                  const FOnBasicEventsGetContentSuccess& OnSuccess, const FOnBasicEventsGetContentError& OnError, const FOnBasicEventsGetContentComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetContentImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UBasicEventsGetContentRequest* RequestData,
	                   const FOnBasicEventsGetContentFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_GetCalendarImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetCalendarRequest* RequestData,
	                  const FOnGetCalendarSuccess& OnSuccess, const FOnGetCalendarError& OnError, const FOnGetCalendarComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetCalendarImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetCalendarRequest* RequestData,
	                   const FOnGetCalendarFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PostApplyContentImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostApplyContentRequest* RequestData,
	                  const FOnPostApplyContentSuccess& OnSuccess, const FOnPostApplyContentError& OnError, const FOnPostApplyContentComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PostApplyContentImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPostApplyContentRequest* RequestData,
	                   const FOnPostApplyContentFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PutEndPhaseImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPutEndPhaseRequest* RequestData,
	                  const FOnPutEndPhaseSuccess& OnSuccess, const FOnPutEndPhaseError& OnError, const FOnPutEndPhaseComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PutEndPhaseImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPutEndPhaseRequest* RequestData,
	                   const FOnPutEndPhaseFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_GetEventsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetEventsRequest* RequestData,
	                  const FOnGetEventsSuccess& OnSuccess, const FOnGetEventsError& OnError, const FOnGetEventsComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetEventsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetEventsRequest* RequestData,
	                   const FOnGetEventsFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_GetPingImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetPingRequest* RequestData,
	                  const FOnGetPingSuccess& OnSuccess, const FOnGetPingError& OnError, const FOnGetPingComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_GetPingImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UGetPingRequest* RequestData,
	                   const FOnGetPingFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PutContentImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPutContentRequest* RequestData,
	                  const FOnPutContentSuccess& OnSuccess, const FOnPutContentError& OnError, const FOnPutContentComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PutContentImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPutContentRequest* RequestData,
	                   const FOnPutContentFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_DeleteContentImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UDeleteContentRequest* RequestData,
	                  const FOnDeleteContentSuccess& OnSuccess, const FOnDeleteContentError& OnError, const FOnDeleteContentComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_DeleteContentImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UDeleteContentRequest* RequestData,
	                   const FOnDeleteContentFullResponse& Handler) const;
		
	/**
	 * @brief Private implementation for requests that require authentication that all overloaded BP UFunctions call.	  
	 */
	void BP_PutRefreshImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPutRefreshRequest* RequestData,
	                  const FOnPutRefreshSuccess& OnSuccess, const FOnPutRefreshError& OnError, const FOnPutRefreshComplete& OnComplete, int64& OutRequestId) const;
	/**
	 * @brief Overload version for binding lambdas when in C++ land. Prefer the BP version whenever possible, this is here mostly for quick experimentation purposes.	 
	 */
	void CPP_PutRefreshImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus, UPutRefreshRequest* RequestData,
	                   const FOnPutRefreshFullResponse& Handler) const;

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
	 */
	void CPP_GetRunning(UGetRunningRequest* Request, const FOnGetRunningFullResponse& Handler) const;


	
	/**
	 * @brief Makes an authenticated request to the Get /basic/events/content endpoint of the Events Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetContent(const FUserSlot& UserSlot, UBasicEventsGetContentRequest* Request, const FOnBasicEventsGetContentFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Get /basic/events/calendar endpoint of the Events Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetCalendar(const FUserSlot& UserSlot, UGetCalendarRequest* Request, const FOnGetCalendarFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/events/applyContent endpoint of the Events Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PostApplyContent(const FUserSlot& UserSlot, UPostApplyContentRequest* Request, const FOnPostApplyContentFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Put /object/events/{objectId}/endPhase endpoint of the Events Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PutEndPhase(const FUserSlot& UserSlot, UPutEndPhaseRequest* Request, const FOnPutEndPhaseFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Get /object/events/{objectId}/ endpoint of the Events Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetEvents(const FUserSlot& UserSlot, UGetEventsRequest* Request, const FOnGetEventsFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Get /object/events/{objectId}/ping endpoint of the Events Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_GetPing(const FUserSlot& UserSlot, UGetPingRequest* Request, const FOnGetPingFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Put /object/events/{objectId}/content endpoint of the Events Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PutContent(const FUserSlot& UserSlot, UPutContentRequest* Request, const FOnPutContentFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Delete /object/events/{objectId}/content endpoint of the Events Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_DeleteContent(const FUserSlot& UserSlot, UDeleteContentRequest* Request, const FOnDeleteContentFullResponse& Handler) const;

		
	/**
	 * @brief Makes an authenticated request to the Put /object/events/{objectId}/refresh endpoint of the Events Service.
	 *
	 * PREFER THE UFUNCTION OVERLOAD AS OPPOSED TO THIS. THIS MAINLY EXISTS TO ALLOW LAMBDA BINDING THE HANDLER.
	 * (Dynamic delegates do not allow for that so... we autogen this one to make experimenting in CPP a bit faster).
	 * 
	 * @param UserSlot The Authenticated User Slot that is making this request.
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param Handler A callback that defines how to handle success, error and completion. 
	 */
	void CPP_PutRefresh(const FUserSlot& UserSlot, UPutRefreshRequest* Request, const FOnPutRefreshFullResponse& Handler) const;


	
	/**
	 * @brief Makes a request to the Get /basic/events/running endpoint of the Events Service.
	 *
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Events", meta=(AutoCreateRefTerm="OnSuccess,OnError,OnComplete"))
	void GetRunning(UGetRunningRequest* Request, const FOnGetRunningSuccess& OnSuccess, const FOnGetRunningError& OnError, const FOnGetRunningComplete& OnComplete,
								 int64& OutRequestId);


	
	/**
	 * @brief Makes an authenticated request to the Get /basic/events/content endpoint of the Events Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Events", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void GetContent(const FUserSlot& UserSlot, UBasicEventsGetContentRequest* Request, const FOnBasicEventsGetContentSuccess& OnSuccess, const FOnBasicEventsGetContentError& OnError, const FOnBasicEventsGetContentComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Get /basic/events/calendar endpoint of the Events Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Events", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void GetCalendar(const FUserSlot& UserSlot, UGetCalendarRequest* Request, const FOnGetCalendarSuccess& OnSuccess, const FOnGetCalendarError& OnError, const FOnGetCalendarComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Post /basic/events/applyContent endpoint of the Events Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Events", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void PostApplyContent(const FUserSlot& UserSlot, UPostApplyContentRequest* Request, const FOnPostApplyContentSuccess& OnSuccess, const FOnPostApplyContentError& OnError, const FOnPostApplyContentComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Put /object/events/{objectId}/endPhase endpoint of the Events Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Events", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void PutEndPhase(const FUserSlot& UserSlot, UPutEndPhaseRequest* Request, const FOnPutEndPhaseSuccess& OnSuccess, const FOnPutEndPhaseError& OnError, const FOnPutEndPhaseComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Get /object/events/{objectId}/ endpoint of the Events Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Events", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void GetEvents(const FUserSlot& UserSlot, UGetEventsRequest* Request, const FOnGetEventsSuccess& OnSuccess, const FOnGetEventsError& OnError, const FOnGetEventsComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Get /object/events/{objectId}/ping endpoint of the Events Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Events", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void GetPing(const FUserSlot& UserSlot, UGetPingRequest* Request, const FOnGetPingSuccess& OnSuccess, const FOnGetPingError& OnError, const FOnGetPingComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Put /object/events/{objectId}/content endpoint of the Events Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Events", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void PutContent(const FUserSlot& UserSlot, UPutContentRequest* Request, const FOnPutContentSuccess& OnSuccess, const FOnPutContentError& OnError, const FOnPutContentComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Delete /object/events/{objectId}/content endpoint of the Events Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Events", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void DeleteContent(const FUserSlot& UserSlot, UDeleteContentRequest* Request, const FOnDeleteContentSuccess& OnSuccess, const FOnDeleteContentError& OnError, const FOnDeleteContentComplete& OnComplete, int64& OutRequestId);

		
	/**
	 * @brief Makes an authenticated request to the Put /object/events/{objectId}/refresh endpoint of the Events Service.
	 *
	 * @param UserSlot The authenticated UserSlot with the user making the request. 
	 * @param Request The Request UObject. All (de)serialized data the request data creates is tied to the lifecycle of this object.
	 * @param OnSuccess What to do if the requests receives a successful response.
	 * @param OnError What to do if the request receives an error response.
	 * @param OnComplete What to after either OnSuccess or OnError have finished executing.
	 * @param OutRequestId The Request Id -- used to query information about the request or to cancel it while it's in flight. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|APIs|Events", meta=(AutoCreateRefTerm="UserSlot,OnSuccess,OnError,OnComplete"))
	void PutRefresh(const FUserSlot& UserSlot, UPutRefreshRequest* Request, const FOnPutRefreshSuccess& OnSuccess, const FOnPutRefreshError& OnError, const FOnPutRefreshComplete& OnComplete, int64& OutRequestId);
	
};
