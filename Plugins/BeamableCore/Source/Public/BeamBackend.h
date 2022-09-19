// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BeamCoreTypes.h"
#include "BeamEnvironment.h"
#include "BeamUserSlots.h"
#include "HttpManager.h"

#include "BeamBackend.generated.h"


// Forward declaration of the Automated Testing class so we can make it a friend and make it easier to test internal state.
class FBeamBackendSpec;


/**
 * 
 */
UCLASS()
class BEAMABLECORE_API UBeamBackend : public UEngineSubsystem
{
	GENERATED_BODY()

	// Makes the Automated Testing class a friend so we can write tests more easily.
	friend FBeamBackendSpec;

private:
	/**
	 * @brief  Just an Auto-Increment ID of each running request.
	 */
	long volatile* InFlightRequestId;

	/**
	 * @brief Delegate handle to the tick function of the UBeamBackend sub-system.
	 */
	FTSTicker::FDelegateHandle TickDelegateHandle;

	/**
	 * @brief Queue of failed requests that we must retry.
	 */
	TQueue<FRequestToRetry> EnqueuedRetries;


	template <class TRequestData>
	static void StaticCheckForRequestType();

	template <class TResponseData>
	static void StaticCheckForResponseType();

	bool TickRetryQueue(float DeltaTime);

public:
	const static FString ACCEPT_HEADER;

	/**
	 * @brief Since it only actually makes sense to retry errors in some cases, we keep a list of the error codes that we do try again. 
	 */
	const static TArray<int> RETRY_ALLOWED_ERRORS;

	/**
	 * @brief Pointer to the UBeamEnvironment Engine Subsystem. Gathers which platform we are running as well as the Beamable SDK version.
	 */
	UPROPERTY()
	UBeamEnvironment* BeamEnvironment;

	/**
	 * @brief Pointer to the UBeamUserSlot Engine Subsystem.
	 * We use this to fetch valid authenticated user data for the user making the request. 
	 */
	UPROPERTY()
	UBeamUserSlots* BeamUserSlots;

	/** @brief Initializes the auto-increment Id and binds the ExecuteRequestDelegate to DefaultExecuteRequestImpl  */
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	/** Cleans up the system.  */
	virtual void Deinitialize() override;

	/*
	  _____                            _         __  _____                                      
	 |  __ \                          | |       / / |  __ \                                     
	 | |__) |___  __ _ _   _  ___  ___| |_     / /  | |__) |___  ___ _ __   ___  _ __  ___  ___ 
	 |  _  // _ \/ _` | | | |/ _ \/ __| __|   / /   |  _  // _ \/ __| '_ \ / _ \| '_ \/ __|/ _ \
	 | | \ \  __/ (_| | |_| |  __/\__ \ |_   / /    | | \ \  __/\__ \ |_) | (_) | | | \__ \  __/
	 |_|  \_\___|\__, |\__,_|\___||___/\__| /_/     |_|  \_\___||___/ .__/ \___/|_| |_|___/\___|
					| |                                             | |                         
					|_|                                             |_|                         	                                                                               
	*/

	/**
	* @brief A RealmHandle struct defining the CustomerID and RealmID that the request is targeting.
	* Can be overriden at the request level and is only used for unauthenticated request.
	* Authenticated Requests are expected to pass in the correct RealmHandle for which the Token was generated.
	*
	* To see how to send authenticated requests by hand, take a look at the BeamUserSlot SubSystem as well as any
	* authenticated request from the AutoGen API. 
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBeamRealmHandle UnauthenticatedRequestsTargetRealm;

	/**
	* @brief The current state of internet connection as detected by Beamable. This is updated automatically on every non-timeout request.
	*/
	UPROPERTY(BlueprintReadOnly)
	FBeamConnectivity CurrentConnectivityStatus;

	/**
	 * @brief A delegate wrapper so we can easily replace the code that sends the request by assertions over the request data. 
	 */
	FBeamMakeRequestDelegate ExecuteRequestDelegate;

	/**
	 * @brief When set to true, the Global Request Error Handlers will run IN ADDITION to the one provided at the callsite. 
	 */
	UPROPERTY(BlueprintReadOnly)
	bool AlwaysRunGlobalHandlers;

	/**
	 * @brief When set to true, we will log all success responses regardless of whether or not you passed in a handler. 
	 */
	UPROPERTY(BlueprintReadOnly)
	bool AlwaysLogSuccessResponses;

	/**
	 * @brief When set to true, we will log all error responses regardless of whether or not you passed in a handler. 
	 */
	UPROPERTY(BlueprintReadOnly)
	bool AlwaysLogErrorResponses;

	/**
	 * @brief When set to true, we will log all completed requests. 
	 */
	UPROPERTY(BlueprintReadOnly)
	bool AlwaysLogCompleteResponses;

	/**
	 * @brief A global request handler delegate that'll be called 
	 */
	UPROPERTY(BlueprintAssignable)
	FGlobalRequestErrorHandler GlobalRequestErrorHandler;

	/**
	 * \copydoc GlobalRequestErrorHandler	
	 * @brief Another global request handler --- this one can be used to bind lambdas from code.	 
	 */
	FGlobalRequestErrorCodeHandler GlobalRequestErrorCodeHandler;

	/**
	 * @brief Tracking of all requests generated by the CreateUnrealRequest and went through the pipeline of PrepareBeamableRequest methods.
	 */
	TMap<FBeamRequestId, TUnrealRequestPtr> InFlightRequests;

	/**
	 * @brief Tracking of overriden retry configurations per-request. If a Request Id does not exist here, fall back to the DefaultRetryConfig.
	 */
	TMap<FBeamRequestId, FBeamRetryConfig> InFlightRetryConfigs;

	/**
	 * @brief Tracking of all requests that failed and have started processing.
	 * Processing is just waiting for the correct amount of time, before actually trying again.
	 */
	TMap<FBeamRequestId, FProcessingRequestRetry> InFlightProcessingRequests;

	/**
	 * @brief Map of @see {FBeamRequestId} to the number of times a request with that id failed. Used to do exponential back-off.
	 */
	TMap<FBeamRequestId, int> InFlightFailureCount;

	/**
	 * @brief Tracking of all request ids that were cancelled by the user.
	 * In BP-land, a cancelled request will simply discard it's response and call OnComplete.
	 * You can use IsRequestCancelled(RequestId) during the callback to handle cancelled requests.
	 *
	 * In Code, a cancelled request will also discard it's response, but the callback will be the same. The FullResponse has a
	 * property you can read that determines whether the request was cancelled or not.
	 */
	TArray<FBeamRequestId> InFlightRequestsCancelled;

	/**
	 *  @brief Used only as delegate set in ExecuteRequestDelegate.
	 *  When testing, this is [optionally] swapped out so we can assert the state of the TUnrealRequest instance that would be sent out.
	 *  
	 */
	UFUNCTION()
	void DefaultExecuteRequestImpl(const FBeamRequestContext& RequestContext, FBeamConnectivity& Connectivity, int64 ActiveRequestId);

	/**
	 * @brief Creates a request and prepares it to be sent out. This does not bind the lambda --- see any auto-generated API to understand how to manually make
	 * a beamable request.
	 * 
	 * @tparam TRequestData A type that implements the FBeamBaseRequest struct.
	 * @param OutRequestId  The RequestId assigned to the returned TUnrealRequest.
	 * @param TargetRealm The Realm with which we are communicating with.
	 * @param RetryConfig The Retry Configuration for this request. 
	 * @param RequestData An instance of the request type.
	 * 
	 * @return A TUnrealRequest object that will be tracked by UBeamBackend.
	 */
	template <typename TRequestData>
	TUnrealRequestPtr CreateRequest(int64& OutRequestId, const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const TRequestData& RequestData);

	/**
	 * @brief Creates an authenticated request and prepares it to be sent out.
	 * This does not bind the lambda --- see any auto-generated API to understand how to manually make a beamable request.
	 * 
	 * @tparam TRequestData A type that implements the FBeamBaseRequest struct.
	 * @param OutRequestId  The RequestId assigned to the returned TUnrealRequest.
	 * @param TargetRealm The Realm with which we are communicating with.
	 * @param RetryConfig The Retry Configuration for this request.
	 * @param AuthToken An AuthenticationToken to be used to make the request.
	 * @param RequestData An instance of the request type.
	 * 
	 * @return A TUnrealRequest object that will be tracked by UBeamBackend.
	 */
	template <typename TRequestData>
	TUnrealRequestPtr CreateAuthenticatedRequest(int64& OutRequestId, const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
	                                             const TRequestData& RequestData);

	/**
	 * @brief Creates a TUnrealRequest that is tied to a specific InFlightRequestId.
	 * You need to manually call the PrepareBeamableRequestXXX functions and then attach a function generated from one of the MakeXXXRequestProcessor
	 * for this to work properly.
	 *
	 * Better to call the CreateRequest and CreateAuthenticatedRequestFunctions and then attaching the appropriate MakeXXXRequestProcessor manually.
	 * You can look at any of the auto-generated APIs to see what this looks like.
	 * 
	 * @param OutRequestId  The RequestId assigned to the returned TUnrealRequest.
	 * @param RetryConfig The Retry Configuration for this request.
	 * 
	 * @return A TUnrealRequest object that will be tracked by UBeamBackend.
	 */
	TUnrealRequestPtr CreateUnpreparedRequest(int64& OutRequestId, const FBeamRetryConfig& RetryConfig);

	/**
	 * @brief This is mainly used in Unit tests where we want to build the request and not send it.
	 * However, if a request is ever created manually by a user and never sent, they need to call this otherwise
	 * they'll "leak" some memory (the data associated with the request here will never be cleared).
	 * 
	 * @param RequestId The RequestId of the request you wish to discard.
	 */
	UFUNCTION(BlueprintCallable)
	void DiscardUnsentRequest(const int64& RequestId);

	/**
	 * @brief This will tell the BeamBackend to ignore the result of this request if it was sent but has not returned yet.
	 * If the request was not sent, it'll simply discard the unsent request instead.
	 * 
	 * @param RequestId The RequestId of the request you wish to cancel.
	 */
	UFUNCTION(BlueprintCallable)
	void CancelRequest(int64 RequestId);

	/**
	 * @brief This will check and see if the request was cancelled and is awaiting cancellation.
	 * This does not track inactive request ids (that have been discard and/or completed). This is only valid while a
	 * request is in-fact in flight and during it's callback executions.
	 */
	UFUNCTION(BlueprintCallable)
	bool IsRequestCancelled(int64 RequestId) const;

	/**
	 * @brief Gets the number of times this request failed.
	 * Can be used to change UI in order to allow users to cancel out of a popup after a certain amount of retries, for example.
	 * 
	 * @param RequestId The RequestId of the request.
	 * @return The number of times this request has failed.
	 */
	UFUNCTION(BlueprintCallable)
	int GetRequestFailureCount(int64 RequestId) const;

	/**
	 * @brief Prepares an TUnrealRequest using data from a FBeamRealmHandle and an FBeamAuthToken by setting up Beamable's custom request headers.
	 * @param RealmHandle A RealmHandle describing which realm this request is talking too.
	 * @param UnrealRequest The actual HttpRequest we are configuring to send out through the Unreal Http Module.
	 */
	static void PrepareBeamableRequestToRealm(const TUnrealRequestPtr& UnrealRequest, const FBeamRealmHandle& RealmHandle);

	/**
	 * @brief Prepares an TUnrealRequest using data from a FBeamRealmHandle and an FBeamAuthToken by setting up a JWT Authentication header.
	 * @param RealmHandle A RealmHandle describing which realm this request is talking too.
	 * @param AuthToken An AuthToken to configure the authentication data required for the request.
	 * @param UnrealRequest The actual HttpRequest we are configuring to send out through the Unreal Http Module. 
	 */
	static void PrepareBeamableRequestToRealmWithAuthToken(const TUnrealRequestPtr& UnrealRequest, const FBeamRealmHandle& RealmHandle, const FBeamAuthToken& AuthToken);

	/**
	 * @brief Prepares an TUnrealRequest using any UStruct containing the data (route and body params) we need to make the request.
	 * @tparam TRequestData A type that implements the FBeamBaseRequest struct.
	 * @param RequestData An instance of the request type.
	 * @param Request The actual HttpRequest we are configuring to send out through the Unreal Http Module.
	 * @param TargetBeamableUrl The target beamable URL --- typically from the current UBeamEnvironment.
	 */
	template <typename TRequestData>
	void PrepareBeamableRequestVerbRouteBody(const TUnrealRequestPtr& Request, const TRequestData& RequestData, const FString& TargetBeamableUrl);

	/**
	 * @brief The blueprint-only version of the Beamable Request Processor implementation. This generates a function to be used as the lambda for the HttpRequest completion.
	 * 
	 * @tparam TRequestData A type that implements the FBeamBaseRequest struct.
	 * @tparam TResponseData A type that implements the FBeamBaseResponse struct.
	 * @tparam TSuccessCallback A Dynamic Delegate with two params (DECLARE_DYNAMIC_DELEGATE_TwoParams) that blueprints can define to handle the successful request.
	 * @tparam TErrorCallback A Dynamic Delegate with two params (DECLARE_DYNAMIC_DELEGATE_TwoParams) that blueprints can define to handle a irrecoverable error in the request.
	 * @tparam TCompleteCallback A Dynamic Delegate with one params (DECLARE_DYNAMIC_DELEGATE_OneParam) that blueprints can define to run after the request completes, be it an error or success.
	 * @param RequestId The Request Id generated by the UBeamBackend::CreateRequest function.
	 * @param RequestData An instance of the request type.
	 * @param OnSuccess The callback to handle success.
	 * @param OnError The callback to handle irrecoverable errors.
	 * @param OnComplete The callback to run after success/errors have been handled.
	 * 
	 * @return The request processor function, with correctly captured variables and properly set up to handle errors, retry and other utilities.
	 */
	template <typename TRequestData, typename TResponseData, typename TSuccessCallback, typename TErrorCallback, typename TCompleteCallback>
	FBeamRequestProcessor MakeBlueprintRequestProcessor(const int64& RequestId, const TRequestData& RequestData, TSuccessCallback OnSuccess, TErrorCallback OnError,
	                                                    TCompleteCallback OnComplete);

	/**
	 * @brief Callback that MakeBlueprintRequestProcessor uses to handle un-authenticated requests.	  
	 */
	template <typename TRequestData, typename TResponseData, typename TSuccessCallback, typename TErrorCallback, typename TCompleteCallback>
	void ProcessBlueprintRequest(const int32& ResponseCode, const FString& ContentAsString, const bool bWasSent,
	                             const int64& RequestId, const TRequestData& RequestData,
	                             TSuccessCallback OnSuccess, TErrorCallback OnError, TCompleteCallback OnComplete);

	/**
	 * @brief The blueprint-only version of the Beamable Request Processor implementation for authenticated requests.	 * 
	 * 
	 * @tparam TRequestData A type that implements the FBeamBaseRequest struct.
	 * @tparam TResponseData A type that implements the FBeamBaseResponse struct.
	 * @tparam TSuccessCallback A Dynamic Delegate with two params (DECLARE_DYNAMIC_DELEGATE_TwoParams) that blueprints can define to handle the successful request.
	 * @tparam TErrorCallback A Dynamic Delegate with two params (DECLARE_DYNAMIC_DELEGATE_TwoParams) that blueprints can define to handle a irrecoverable error in the request.
	 * @tparam TCompleteCallback A Dynamic Delegate with one params (DECLARE_DYNAMIC_DELEGATE_OneParam) that blueprints can define to run after the request completes, be it an error or success.
	 * @param RequestId The Request Id generated by the UBeamBackend::CreateRequest function.
	 * @param RealmHandle The Realm (CID+PID) we are making the request to.
	 * @param AuthToken The AuthenticationToken we should be using to make the request.
	 * @param RequestData An instance of the request type.
	 * @param OnSuccess The callback to handle success.
	 * @param OnError The callback to handle irrecoverable errors.
	 * @param OnComplete The callback to run after success/errors have been handled. 
	 * @return A function to be used as the lambda for the HttpRequest completion callback.
	 */
	template <typename TRequestData, typename TResponseData, typename TSuccessCallback, typename TErrorCallback, typename TCompleteCallback>
	FBeamRequestProcessor MakeAuthenticatedBlueprintRequestProcessor(const int64& RequestId, const FBeamRealmHandle& RealmHandle, const FBeamAuthToken& AuthToken,
	                                                                 const TRequestData& RequestData, TSuccessCallback OnSuccess, TErrorCallback OnError, TCompleteCallback OnComplete);

	/**
	 * @brief Callback that MakeAuthenticatedBlueprintRequestProcessor uses to handle authenticated requests. 
	 */
	template <typename TRequestData, typename TResponseData, typename TSuccessCallback, typename TErrorCallback, typename TCompleteCallback>
	void ProcessAuthenticatedBlueprintRequest(const int32& ResponseCode, const FString& ContentAsString, const bool bWasSent,
	                                          const int64& RequestId, const FBeamRealmHandle& RealmHandle, const FBeamAuthToken& AuthToken,
	                                          const TRequestData& RequestData, TSuccessCallback OnSuccess, TErrorCallback OnError, TCompleteCallback OnComplete);

	/**
	 * @brief The code-only version of the Beamable Request Processor implementation. This generates 2 things:
	 * a function to be used as the lambda for the HttpRequest completion and a set of Future objects user-code can attach to.
	 * 
	 * @tparam TRequestData A type that implements the FBeamBaseRequest struct.
	 * @tparam TResponseData A type that implements the FBeamBaseResponse struct.
	 * @param RequestId The Request Id generated by the UBeamBackend::CreateRequest function.
	 * @param RequestData An instance of the request type.
	 * @param ResponseHandler A callback to handle the full response of this request. To handle success/error/retry, read from the TBeamFullResponse data.  	 
	 * 
	 * @return The request processor function, with correctly captured variables and properly set up to handle errors, retry and other utilities.
	 */
	template <typename TRequestData, typename TResponseData>
	FBeamRequestProcessor MakeCodeRequestProcessor(const int64& RequestId, const TRequestData& RequestData, TBeamFullResponseHandler<TRequestData, TResponseData> ResponseHandler);

	/**
	 * @brief Callback that MakeCodeRequestProcessor uses to handle requests that don't require authentication.	  
	 */
	template <typename TRequestData, typename TResponseData>
	void ProcessCodeRequest(const int32& ResponseCode, const FString& ContentAsString, const bool bWasSent,
	                        const int64& RequestId, const TRequestData& RequestData, TBeamFullResponseHandler<TRequestData, TResponseData> ResponseHandler);

	/**
	 * @brief The code-only version of the Beamable Request Processor implementation. This generates 2 things:
	 * a function to be used as the lambda for the HttpRequest completion and a set of Future objects user-code can attach to.
	 * 
	 * @tparam TRequestData A type that implements the FBeamBaseRequest struct.
	 * @tparam TResponseData A type that implements the FBeamBaseResponse struct.
	 * @param RequestId The Request Id generated by the UBeamBackend::CreateRequest function.
	 * @param RealmHandle The Realm (CID+PID) we are making the request to.
	 * @param AuthToken The AuthenticationToken we should be using to make the request.
	 * @param RequestData An instance of the request type.
	 * @param ResponseHandler A callback to handle the full response of this request. To handle success/error/retry, read from the TBeamFullResponse data.  	 
	 * 
	 * @return The request processor function, with correctly captured variables and properly set up to handle errors, retry and other utilities.
	 */
	template <typename TRequestData, typename TResponseData>
	FBeamRequestProcessor MakeAuthenticatedCodeRequestProcessor(const int64& RequestId, const FBeamRealmHandle& RealmHandle, const FBeamAuthToken& AuthToken,
	                                                            const TRequestData& RequestData, TBeamFullResponseHandler<TRequestData, TResponseData> ResponseHandler);

	/**
	 * @brief Callback that MakeAuthenticatedCodeRequestProcessor uses to handle authenticated request's responses.
	 */
	template <typename TRequestData, typename TResponseData>
	void ProcessAuthenticatedCodeRequest(const int32& ResponseCode, const FString& ContentAsString, const bool bWasSent, const int64& RequestId,
	                                     const FBeamRealmHandle& RealmHandle, const FBeamAuthToken& AuthToken, const TRequestData& RequestData,
	                                     const TBeamFullResponseHandler<TRequestData, TResponseData>& ResponseHandler);

	/*
	 
  _____      _                 _____             __ _       
 |  __ \    | |               / ____|           / _(_)      
 | |__) |___| |_ _ __ _   _  | |     ___  _ __ | |_ _  __ _ 
 |  _  // _ \ __| '__| | | | | |    / _ \| '_ \|  _| |/ _` |
 | | \ \  __/ |_| |  | |_| | | |___| (_) | | | | | | | (_| |
 |_|  \_\___|\__|_|   \__, |  \_____\___/|_| |_|_| |_|\__, |
					   __/ |                           __/ |
					  |___/                           |___/ 

	 */

	/**
	* @brief Retry configuration data. Can be overriden at the request level. 
	*/
	UPROPERTY(BlueprintReadWrite)
	FBeamRetryConfig DefaultRetryConfig;

	/**
	 * @brief Key is the request struct type's GetName() call. Value can be set by users. 
	 */
	UPROPERTY(BlueprintReadOnly)
	TMap<FRequestType, FBeamRetryConfig> PerTypeRetryConfigs;

	/**
	 * @brief Key is the request struct type's GetName() call and the UserSlotId for which this configuration is set separated by '₢'.
	 * Value can be set by users.
	 */
	UPROPERTY(BlueprintReadOnly)
	TMap<FString, FBeamRetryConfig> PerUserPerTypeRetryConfig;

	/**
	 * @brief Key is the UserSlotId for which this configuration is set. Value can be set by users.
	 */
	UPROPERTY(BlueprintReadOnly)
	TMap<FUserSlot, FBeamRetryConfig> PerUserRetryConfig;

	/**
	 * @brief Modifies a request context to use the correct fallback retry configuration.  Called for authenticated requests.
	 * @tparam TRequestData A type that implements the FBeamBaseRequest struct.
	 * @param UserSlotId The UserSlotId that is making the request.
	 * @param Config The request context we are modifying.
	 */
	template <typename TRequestData>
	void GetRetryConfig(const FUserSlot& UserSlotId, FBeamRetryConfig& Config);

	/**
	 * @brief Modifies a request context to use the correct fallback retry configuration. Called for non-authenticated requests.
	 * @tparam TRequestData A type that implements the FBeamBaseRequest struct.	 
	 * @param Config The request context we are modifying. 
	 */
	template <typename TRequestData>
	void GetRetryConfig(FBeamRetryConfig& Config);

	/**
	 * @brief Sets the retry configuration for a given request type's requests.
	 * @param RequestType The Request type whose retry configuration you wish to reset.
	 * @param RetryConfig The retry config you wish that request type to use.
	 */
	UFUNCTION(BlueprintCallable)
	void SetRetryConfigForRequestType(const FRequestType& RequestType, const FBeamRetryConfig& RetryConfig);

	/**
	 * @brief Sets the retry configuration for a given user's requests. 
	 * @param UserSlot The user slot whose retry configuration you wish to set.
	 * @param RetryConfig The retry config you wish that user to use.
	 */
	UFUNCTION(BlueprintCallable)
	void SetRetryConfigForUser(const FUserSlot UserSlot, const FBeamRetryConfig& RetryConfig);

	/**
	 * @brief Sets the retry configuration for a given user + request type combination's requests.
	 * @param UserSlot The user slot whose retry configuration you wish to set.
	 * @param RequestType The Request type whose retry configuration you wish to reset. 
	 * @param RetryConfig The retry config you wish that user + request type combination to use.
	 */
	UFUNCTION(BlueprintCallable)
	void SetRetryConfigForUserAndRequestType(const FUserSlot& UserSlot, const FRequestType& RequestType, const FBeamRetryConfig& RetryConfig);

	/**
	 * @brief Resets the Retry Configuration for the given request type  back to the default retry configuration.
	 * @param RequestType The Request type whose retry configuration you wish to reset.
	 */
	UFUNCTION(BlueprintCallable)
	void ResetRetryConfigForRequestType(const FRequestType& RequestType);

	/**
	 * @brief Resets the Retry Configuration for the given user back to the default retry configuration.
	 * @param UserSlot The user slot whose retry configuration you wish to reset.
	 */
	UFUNCTION(BlueprintCallable)
	void ResetRetryConfigForUser(const FUserSlot& UserSlot);

	/**
	 * @brief Resets the Retry Configuration for the given user and request type combination back to the default retry configuration.	 
	 * @param UserSlot The user slot whose retry configuration you wish to reset.
	 * @param RequestType The Request type whose retry configuration you wish to reset.
	 */
	UFUNCTION(BlueprintCallable)
	void ResetRetryConfigForUserAndRequestType(const FUserSlot& UserSlot, const FRequestType& RequestType);
};
