// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BeamBaseResponseBodyInterface.h"
#include "HttpManager.h"


#include "BeamEnvironment.h"
#include "BeamLogging.h"
#include "BeamableOSS.h"

#include "BeamBackend/RequestType.h"
#include "BeamBackend/BeamFullResponse.h"
#include "Interfaces/IHttpResponse.h"

#include "UserSlots/BeamUserSlots.h"

#include "BeamBackend.generated.h"


class IBeamBaseRequestInterface;

/**
 * @brief Shorter name for Unreal's HttpRequest struct.
 */
typedef TSharedRef<IHttpRequest, ESPMode::ThreadSafe> TUnrealRequest;

/**
 * @brief Shorter name for the pointer to Unreal's HttpRequest struct.
 */
typedef TSharedPtr<IHttpRequest, ESPMode::ThreadSafe> TUnrealRequestPtr;

/**
 * @brief Shorter name for unreal's request status.
 */
typedef EHttpRequestStatus::Type TUnrealRequestStatus;

/**
 * @brief Semantic separation for the Functor declaration representing a Beamable Request Processor.
 * Exist to make explicit any assumptions we make about passing parameters to the request processing callback.
 */
typedef TFunction<void (FHttpRequestPtr request, FHttpResponsePtr response, bool success)> FBeamRequestProcessor;

/**
 * @brief Handle to an Enqueued Request that needs to be retried.
 */
struct FRequestToRetry
{
	/**
	 * @brief The unique request id.
	 */
	FBeamRequestId RequestId = 0;

	/**
	 * @brief Whether or not the request was made with a blueprint compatible handler. 
	 */
	int32 IsBlueprintCompatible;

	/**
	 * @brief The HTTP status code.
	 */
	int32 ResponseCode;

	/**
	 * @brief The realm the request was targeted to.
	 */
	FBeamRealmHandle RealmHandle;

	/**
	 * @brief The authentication token used in the request, if any.
	 */
	FBeamAuthToken AuthToken;

	/**
	 * @brief A custom error code independent of the HTTP status code.
	 */
	FString ErrorCode;

	friend bool operator==(const FRequestToRetry& Lhs, const FRequestToRetry& RHS)
	{
		return Lhs.RequestId == RHS.RequestId
			&& Lhs.IsBlueprintCompatible == RHS.IsBlueprintCompatible
			&& Lhs.ResponseCode == RHS.ResponseCode
			&& Lhs.RealmHandle == RHS.RealmHandle
			&& Lhs.AuthToken == RHS.AuthToken;
	}

	friend bool operator!=(const FRequestToRetry& Lhs, const FRequestToRetry& RHS)
	{
		return !(Lhs == RHS);
	}
};

/**
 * @brief Data needed to decided when enough time has passed that we should retry again.
 */
struct FProcessingRequestRetry
{
	/**
	 * @brief The handle defining which request we are processing.
	 */
	FRequestToRetry RequestToRetry;

	/**
	 * @brief How long (in seconds) should we wait before trying the request again.
	 */
	float TimeToWait;

	/**
	 * @brief How long (in seconds) have we waited for this retry.
	 */
	float AccumulatedTime;
};


DECLARE_DELEGATE_TwoParams(FBeamMakeRequestDelegate, int64 /*ActiveRequestId*/, const UObject* /* CallingContext */);

DECLARE_DELEGATE_TwoParams(FGlobalRequestErrorCodeHandler, const FBeamRequestContext&, const FBeamErrorResponse&);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGlobalRequestErrorHandler, const FBeamRequestContext&, RequestContext,
                                             const FBeamErrorResponse&, Error);

DECLARE_MULTICAST_DELEGATE_ThreeParams(FGlobalConnectivityChangedCodeHandler, const FBeamRequestContext&,
                                       const FRequestType&, const bool);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FGlobalConnectivityChangedHandler, const FBeamRequestContext&,
                                               RequestContext, const FRequestType&, FailedRequestType, const bool,
                                               bConnected);

/**
* @brief Subsystems that associate data with in-flight requests and require guarantees that those request objects stay alive need to tell the backend subsystem which
* requests are still in use by them to guarantee the requests/response data associated with the request won't be cleaned up.
*/
DECLARE_DYNAMIC_DELEGATE_OneParam(FTickOnBackendCleanUp, TArray<int64>&, OutUsingRequestIds);

/**
* @brief Subsystems that associate data with in-flight requests and require and want to react to the fact that a request was completed can register themselves here.
*/
DECLARE_DYNAMIC_DELEGATE_OneParam(FTickOnRequestIdCompleted, int64, CompletedRequestId);


DECLARE_STATS_GROUP(TEXT("BeamBackend"), STATGROUP_BeamBackend, STATCAT_Backend)

DECLARE_DWORD_ACCUMULATOR_STAT(TEXT("RequestsStarted"), STATID_RequestStarted, STATGROUP_BeamBackend)
DECLARE_DWORD_ACCUMULATOR_STAT(TEXT("RequestsSucceeded"), STATID_RequestSucceeded, STATGROUP_BeamBackend)
DECLARE_DWORD_ACCUMULATOR_STAT(TEXT("RequestsFailed"), STATID_RequestFailed, STATGROUP_BeamBackend)
DECLARE_DWORD_ACCUMULATOR_STAT(TEXT("RequestsCancelled"), STATID_RequestCancelled, STATGROUP_BeamBackend)

/**
 * 
 */
UCLASS(NotBlueprintable)
class BEAMABLECORE_API UBeamBackend : public UEngineSubsystem
{
	GENERATED_BODY()

	// Forward declaration of the Automated Testing class so we can make it a friend and make it easier to test internal state.
	// Also, mock request types declared for Automated Testing purposes.
	friend class FBeamBackendSpec;
	friend class UBeamRequestTracker;
	friend class FBeamRequestTrackerSpec;
	friend class UBeamResponseCache;

private:
	/**
	 * @brief  Just an Auto-Increment ID of each running request.
	 */
	std::atomic<long> InFlightRequestId;

	/**
	 * @brief Delegate handle to the tick function of the UBeamBackend sub-system used to update and handle retry requests.
	 */
	FTSTicker::FDelegateHandle RetryQueueTickHandle;

	/**
	 * @brief Queue of failed requests that we must retry.
	 */
	TQueue<FRequestToRetry> EnqueuedRetries;

	/**
	 * @brief Delegates that other subsystems register to tell UBeamBackend of RequestIds that they are using.
	 * This is called to give subsystems an opportunity to clean up their internal state that relates to Requests.
	 * The subsystems should fill out the given array with any RequestIds that they are still using and don't want to be cleaned up. 
	 */
	TArray<FTickOnBackendCleanUp> TickOnBackendCleanUpDelegates;

	/**
	 * @brief Delegates that other subsystems register to react whenever a request is completed.
	 * The guarantees here is that OnComplete will have run in all cases for all types of request.
	 */
	TArray<FTickOnRequestIdCompleted> TickOnRequestIdCompletedDelegates;


	template <class TRequestData>
	static void StaticCheckForRequestType()
	{
		static_assert(TIsDerivedFrom<TRequestData, IBeamBaseRequestInterface>::Value, "TRequestData must be a IBeamBaseRequestInterface type.");
		static_assert(TIsDerivedFrom<TRequestData, UObject>::Value, "TRequestData must be a UObject type.");
	}

	template <class TResponseData>
	static void StaticCheckForResponseType()
	{
		static_assert(TIsDerivedFrom<TResponseData, IBeamBaseResponseBodyInterface>::Value, "TResponseData must be a IBeamBaseResponseBodyInterface type.");
		static_assert(TIsDerivedFrom<TResponseData, UObject>::Value, "TResponseData must be a UObject type.");
	}

	void TryTriggerRequestCompleteDelegates(const int64& RequestId);

	bool TickRetryQueue(float DeltaTime);

	bool CleanUpRequestData();

	/**
	 * @brief Tracks whether we are in PIE mode.
	 */
	bool bIsInPIE;

public:
	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	static UBeamBackend* GetSelf() { return GEngine->GetEngineSubsystem<UBeamBackend>(); }

	static const FString HEADER_CONTENT_TYPE;
	static const FString HEADER_ACCEPT;
	static const FString HEADER_VALUE_ACCEPT_CONTENT_TYPE;
	static const FString HEADER_AUTHORIZATION;
	static const FString HEADER_REQUEST_SCOPE;
	static const FString HEADER_VALUE_AUTHORIZATION;
	static const FString HEADER_CLIENT_ID;
	static const FString HEADER_PROJECT_ID;
	static const FString HEADER_ROUTING_KEY_MAP;
	static const FString HEADER_GAMERTAG;
	static const FString HEADER_SIGNATURE;
	static const FString HEADER_TIMEOUT;
	

	static const FString HEADER_BEAMABLE_VERSION;
	static const FString HEADER_UNREAL_VERSION;
	static const FString HEADER_ENGINE_TYPE;
	static const FString HEADER_APPLICATION_VERSION;

	/**
	 * @brief List of error codes that mean we should re-auth and automatically make the request again.
	 */
	const static TArray<FString> AUTH_ERROR_CODE_RETRY_ALLOWED;


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


	/** @brief Initializes the subsystem.  */
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	/** Cleans up the system.  */
	virtual void Deinitialize() override;

	/** Checks if at least one PIE world exists.  */
	void UpdatePieState();

	/** Returns true only when at least one PIE world exists.  */
	bool IsInPIE() const;

	/** Returns the current project build version from the ini file.  */
	FString GetProjectAppVersion() const;

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
	 * @brief Function called by the auto-generated API to send over a request. 
	 */
	void SendPreparedRequest(int64 ActiveRequest, const UObject* CallingContext) const { ExecuteRequestDelegate.ExecuteIfBound(ActiveRequest, CallingContext); }

	/**
	 * @brief A delegate wrapper so we can easily replace the code that sends the request by assertions over the request data. 
	 */
	FBeamMakeRequestDelegate ExecuteRequestDelegate;

	/**
	 * @brief When set to true, the Global Request Error Handlers will run IN ADDITION to the one provided at the callsite. 
	 */
	UPROPERTY(BlueprintReadOnly, Category="Beam|Config")
	bool AlwaysRunGlobalHandlers;

	/**
	 * @brief When set to true, we will log all success responses regardless of whether you passed in a handler. 
	 */
	UPROPERTY(BlueprintReadOnly, Category="Beam|Config")
	bool AlwaysLogSuccessResponses;

	/**
	 * @brief When set to true, we will log all error responses regardless of whether you passed in a handler. 
	 */
	UPROPERTY(BlueprintReadOnly, Category="Beam|Config")
	bool AlwaysLogErrorResponses;

	/**
	 * @brief When set to true, we will log all completed requests. 
	 */
	UPROPERTY(BlueprintReadOnly, Category="Beam|Config")
	bool AlwaysLogCompleteResponses;

	/**
	 * @brief A global request handler delegate that'll be called 
	 */
	UPROPERTY(BlueprintAssignable, Category="Beam|Config")
	FGlobalRequestErrorHandler GlobalRequestErrorHandler;

	/**
	 * \copydoc GlobalRequestErrorHandler	
	 * @brief Another global request handler --- this one can be used to bind lambdas from code. Use the other handler if you can.	 
	 */
	FGlobalRequestErrorCodeHandler GlobalRequestErrorCodeHandler;

	/**
	 * @brief Tracking of all requests generated by CreateUnrealRequest as well as non-beamable we make that we wish to track and cancel in case we leave PIE.
	 * This is used to solve a use-after-free problem that is caused by having requests with process delegates that depend on PIE-instanced objects return after PIE is stopped.
	 *
	 * While running in PIE, we hook into "On PIE Stopped" and cancel all these requests so their process  
	 */
	TArray<TUnrealRequestPtr> InFlightPIERequests;


	/**
	 * @brief Tracking of all requests generated by the CreateUnrealRequest and went through the pipeline of PrepareBeamableRequest methods.
	 */
	TMap<FBeamRequestId, TUnrealRequestPtr> InFlightRequests;

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
	 * @brief Tracking of all request contexts used to send out Beamable requests. 
	 */
	TMap<FBeamRequestId, FBeamRequestContext> InFlightRequestContexts;

	/**
	 * @brief When we create a new request, authenticated or otherwise, we store it's RequestData object here.
	 * When it and WaitHandles that depend on it are completed, we remove it from here.
	 */
	UPROPERTY(BlueprintReadOnly, Category="Beam")
	TMap<FBeamRequestContext, TScriptInterface<IBeamBaseRequestInterface>> InFlightRequestData;
	/**
	 * @brief When we create a new request, authenticated or otherwise, we store it's deserialized response object here.
	 * When it and WaitHandles that depend on it are completed, we remove it from here.	 
	 */
	UPROPERTY(BlueprintReadOnly, Category="Beam")
	TMap<FBeamRequestContext, TScriptInterface<IBeamBaseResponseBodyInterface>> InFlightResponseBodyData;

	/**
	 * @brief When we create a new request, authenticated or otherwise, we store it's deserialized error object here.
	 * When it and WaitHandles that depend on it are completed, we remove it from here.	 
	 */
	UPROPERTY(BlueprintReadOnly, Category="Beam")
	TMap<FBeamRequestContext, FBeamErrorResponse> InFlightResponseErrorData;

	/**
	 * @brief Map of @see {FBeamRequestId} to the number of times a request with that id failed. Used to do exponential back-off.
	 */
	TMap<FBeamRequestId, int> InFlightFailureCount;

	/**
	 * @brief Tracking of all requests that failed and have started processing.
	 * Processing is just waiting for the correct amount of time, before actually trying again.
	 */
	TMap<FBeamRequestId, FProcessingRequestRetry> InFlightProcessingRequests;


	/**
	 * @brief This is the current routing keys set for each individual user requests.
	 * These maps tell the Beamable backend how to forward requests to specific microservice instances (both for direct client->microservice requests AND for in-band federation requests).
	 * They are included into the headers of every authenticated and non-authenticated request.
	 * Non-authenticated requests use whatever is defined for the Player0.
	 *
	 * This is what enables the Beamable backend to route requests made from your client only to any specific microservice instance-set running in the realm.
	 */
	TMap<FUserSlot, FString> CurrentRoutingKeyMaps;

	/**
	 *  @brief Used only as delegate set in ExecuteRequestDelegate.
	 *  When testing, this is [optionally] swapped out so we can assert the state of the TUnrealRequest instance that would be sent out.
	 *  
	 */
	UFUNCTION()
	void DefaultExecuteRequestImpl(int64 ActiveRequestId, const UObject* CallingContext);

	/**
	 * Takes in a fully formed URL from a TUnrealRequest (ie: https://dev.api.beamable.com/object/stats/game.public.player.1595037680985091/) and generates the correct form of it for the signature.
	 */
	void ExtractUrlForSignature(const FString& FullUrl, FString& Url);

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
	template <class TRequestData>
	TUnrealRequestPtr CreateRequest(int64& OutRequestId, const FBeamRealmHandle& TargetRealm,
	                                const FBeamRetryConfig& RetryConfig, const TRequestData* RequestData)
	{
		StaticCheckForRequestType<TRequestData>();
		UE_LOG(LogBeamBackend, Verbose, TEXT("Request Preparation - Preparing Request of Type: REQUEST_TYPE=%s"), *RequestData->GetRequestType().Name);

		// Ensures we get a valid Next Id even if requests get made from multiple threads.
		int64 ReqId;
		auto Req = CreateUnpreparedRequest(ReqId, RetryConfig);
		PrepareBeamableRequestToRealm(Req, TargetRealm);
		PrepareBeamableRequestVerbRouteBody<TRequestData>(Req, RequestData, BeamEnvironment->GetAPIUrl());
		PrepareBeamableRequestToRealmWithRoutingKey(Req, GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot());


		const auto RequestContext = FBeamRequestContext{ReqId, RetryConfig, TargetRealm, -1, FUserSlot(""), AS_None};

		// Keep track of this request and it's data. 
		InFlightRequestContexts.Add(ReqId, RequestContext);
		InFlightRequestData.Add(RequestContext, TScriptInterface<IBeamBaseRequestInterface>(const_cast<TRequestData*>(RequestData)));

		// Store make sure we have a slot waiting for the response/error value to be added
		InFlightResponseBodyData.Add(RequestContext, nullptr);
		InFlightResponseErrorData.Add(RequestContext, FBeamErrorResponse{});


		INC_DWORD_STAT(STATID_RequestStarted)
		OutRequestId = ReqId;
		return Req;
	}

	/**
	 * @brief Creates a Microservice Request and prepares it to be sent out.
	 * This does not bind the lambda --- see any auto-generated API to understand how to manually make a beamable request.
	 * 
	 * @tparam TRequestData A type that implements the FBeamBaseRequest struct.
	 * @param OutRequestId  The RequestId assigned to the returned TUnrealRequest.
	 * @param TargetRealm The Realm with which we are communicating with.
	 * @param RetryConfig The Retry Configuration for this request. 
	 * @param RequestData An instance of the request type.
	 * @param Prefix The Prefix for the Microservice that'll handle this request.
	 * 
	 * @return A TUnrealRequest object that will be tracked by UBeamBackend.
	 */
	template <class TRequestData>
	TUnrealRequestPtr CreateMicroserviceRequest(int64& OutRequestId, const FBeamRealmHandle& TargetRealm,
	                                            const FBeamRetryConfig& RetryConfig, const TRequestData* RequestData, const FString& Prefix)
	{
		StaticCheckForRequestType<TRequestData>();
		UE_LOG(LogBeamBackend, Verbose, TEXT("Request Preparation - Preparing Request of Type: REQUEST_TYPE=%s"), *RequestData->GetRequestType().Name);

		// Ensures we get a valid Next Id even if requests get made from multiple threads.
		int64 ReqId;
		auto Req = CreateUnpreparedRequest(ReqId, RetryConfig);
		PrepareBeamableRequestToRealm(Req, TargetRealm);
		PrepareBeamableRequestVerbRouteBody<TRequestData>(Req, RequestData, BeamEnvironment->GetAPIUrl(), TargetRealm, Prefix);
		PrepareBeamableRequestToRealmWithRoutingKey(Req, GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot());

		const auto RequestContext = FBeamRequestContext{ReqId, RetryConfig, TargetRealm, -1, FUserSlot(""), AS_None};

		// Keep track of this request and it's data. 
		InFlightRequestContexts.Add(ReqId, RequestContext);
		InFlightRequestData.Add(RequestContext,
		                        TScriptInterface<IBeamBaseRequestInterface>(const_cast<TRequestData*>(RequestData)));

		// Store make sure we have a slot waiting for the response/error value to be added
		InFlightResponseBodyData.Add(RequestContext, nullptr);
		InFlightResponseErrorData.Add(RequestContext, FBeamErrorResponse{});

		INC_DWORD_STAT(STATID_RequestStarted)
		OutRequestId = ReqId;
		return Req;
	}

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
	TUnrealRequestPtr CreateAuthenticatedRequest(int64& OutRequestId, const FBeamRealmHandle& TargetRealm,
	                                             const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
	                                             const TRequestData* RequestData)
	{
		StaticCheckForRequestType<TRequestData>();
		UE_LOG(LogBeamBackend, Verbose, TEXT("Request Preparation - Preparing Request of Type: REQUEST_TYPE=%s"), *RequestData->GetRequestType().Name);

		// Get information about the user making the request
		FUserSlot OutUserSlot;
		FBeamRealmUser OutUserData;
		FString NamespacedSlotId;
		BeamUserSlots->GetUserDataWithRefreshTokenAndPid(AuthToken.RefreshToken, TargetRealm.Pid, OutUserData, OutUserSlot, NamespacedSlotId);

		// Ensures we get a valid Next Id even if requests get made from multiple threads.
		int64 ReqId;
		auto ApiUrl = BeamEnvironment->GetAPIUrl();
		auto Req = CreateUnpreparedRequest(ReqId, RetryConfig);
		PrepareBeamableRequestToRealmWithAuthToken(Req, TargetRealm, AuthToken);
		PrepareBeamableRequestVerbRouteBody<TRequestData>(Req, RequestData, ApiUrl);
		PrepareBeamableRequestToRealmWithRoutingKey(Req, OutUserSlot);

		// Add to the InFlight request list
		const auto RequestContext = FBeamRequestContext{ReqId, RetryConfig, TargetRealm, -1, OutUserSlot, AS_None};

		// Keep track of this request and it's data. 
		InFlightRequestContexts.Add(ReqId, RequestContext);
		InFlightRequestData.Add(RequestContext, TScriptInterface<IBeamBaseRequestInterface>(const_cast<TRequestData*>(RequestData)));

		// Store make sure we have a slot waiting for the response/error value to be added
		InFlightResponseBodyData.Add(RequestContext, nullptr);
		InFlightResponseErrorData.Add(RequestContext, FBeamErrorResponse{});

		OutRequestId = ReqId;
		return Req;
	}


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
	 * @param Prefix The Prefix for the Microservice that'll handle this request.
	 * 
	 * @return A TUnrealRequest object that will be tracked by UBeamBackend.
	 */
	template <typename TRequestData>
	TUnrealRequestPtr CreateMicroserviceAuthenticatedRequest(int64& OutRequestId, const FBeamRealmHandle& TargetRealm,
	                                                         const FBeamRetryConfig& RetryConfig,
	                                                         const FBeamAuthToken& AuthToken,
	                                                         const TRequestData* RequestData,
	                                                         const FString& Prefix)
	{
		StaticCheckForRequestType<TRequestData>();
		UE_LOG(LogBeamBackend, Verbose, TEXT("Request Preparation - Preparing Request of Type: REQUEST_TYPE=%s"), *RequestData->GetRequestType().Name);

		// Get some data about the user making the request
		FUserSlot OutUserSlot;
		FBeamRealmUser OutUserData;
		FString NamespacedSlotId;
		BeamUserSlots->GetUserDataWithRefreshTokenAndPid(AuthToken.RefreshToken, TargetRealm.Pid, OutUserData, OutUserSlot, NamespacedSlotId);

		// Ensures we get a valid Next Id even if requests get made from multiple threads.
		int64 ReqId;
		auto Req = CreateUnpreparedRequest(ReqId, RetryConfig);
		PrepareBeamableRequestToRealmWithAuthToken(Req, TargetRealm, AuthToken);
		PrepareBeamableRequestVerbRouteBody<TRequestData>(Req, RequestData, BeamEnvironment->GetAPIUrl(), TargetRealm, Prefix);
		PrepareBeamableRequestToRealmWithRoutingKey(Req, OutUserSlot);

		// Add to the InFlight request list
		const auto RequestContext = FBeamRequestContext{ReqId, RetryConfig, TargetRealm, -1, OutUserSlot, AS_None};

		// Keep track of this request and it's data. 
		InFlightRequestContexts.Add(ReqId, RequestContext);
		InFlightRequestData.Add(RequestContext,
		                        TScriptInterface<IBeamBaseRequestInterface>(const_cast<TRequestData*>(RequestData)));

		// Store make sure we have a slot waiting for the response/error value to be added
		InFlightResponseBodyData.Add(RequestContext, nullptr);
		InFlightResponseErrorData.Add(RequestContext, FBeamErrorResponse{});

		OutRequestId = ReqId;
		return Req;
	}

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
	 * However, if a request is ever created manually by a user (not via one of our API Subsystems) and never sent, they need to call this otherwise
	 * they'll "leak" some memory (the data associated with the request here will never be cleared).
	 * 
	 * @param RequestId The RequestId of the request you wish to discard.
	 */
	UFUNCTION()
	void DiscardUnsentRequest(const int64& RequestId);

	/**
	 * @brief This will tell the BeamBackend to ignore the result of this request if it was sent but has not returned yet.
	 * If the request was not sent, it'll simply discard the unsent request instead.
	 * 
	 * @param RequestId The RequestId of the request you wish to cancel.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam")
	void CancelRequest(int64 RequestId);

	/**
	 * @brief This will check and see if the request was cancelled and is awaiting cancellation.
	 * This does not track inactive request ids (that have been discard and/or completed). This is only valid while a
	 * request is in-fact in flight and during it's callback executions.
	 */
	UFUNCTION(BlueprintGetter, Category="Beam")
	bool IsRequestCancelled(int64 RequestId) const;

	/**
	 * @brief Gets the number of times this request failed.
	 * Can be used to change UI in order to allow users to cancel out of a popup after a certain amount of retries, for example.
	 * 
	 * @param RequestId The RequestId of the request.
	 * @return The number of times this request has failed.
	 */
	UFUNCTION(BlueprintGetter, Category="Beam")
	int GetRequestFailureCount(int64 RequestId) const;

	/**
	 * @brief Prepares an TUnrealRequest using data from a FBeamRealmHandle and an FBeamAuthToken by setting up Beamable's custom request headers.
	 * @param RealmHandle A RealmHandle describing which realm this request is talking too.
	 * @param UnrealRequest The actual HttpRequest we are configuring to send out through the Unreal Http Module.
	 */
	void PrepareBeamableRequestToRealm(const TUnrealRequestPtr& UnrealRequest,
	                                   const FBeamRealmHandle& RealmHandle);

	/**
	 * @brief Prepares an TUnrealRequest using data from a FBeamRealmHandle and an FBeamAuthToken by setting up a JWT Authentication header.
	 * @param RealmHandle A RealmHandle describing which realm this request is talking too.
	 * @param AuthToken An AuthToken to configure the authentication data required for the request.
	 * @param UnrealRequest The actual HttpRequest we are configuring to send out through the Unreal Http Module. 
	 */
	void PrepareBeamableRequestToRealmWithAuthToken(const TUnrealRequestPtr& UnrealRequest,
	                                                const FBeamRealmHandle& RealmHandle,
	                                                const FBeamAuthToken& AuthToken);

	/**
	 * Prepares a TUnrealRequest using the data in the CurrentRoutingKeyMaps.
	 * @param Request The request to prepare.
	 * @param Slot The user-slot making the request, if any. Only relevant for authenticated requests; non-authenticated and dedicated server requests use the data set for the UBeamCoreSettings::GetOwnerPlayerSlot().
	 */
	void PrepareBeamableRequestToRealmWithRoutingKey(const TUnrealRequestPtr& Request, FUserSlot Slot);

	/**
	 * @brief Prepares an TUnrealRequest using any UStruct containing the data (route and body params) we need to make the request.
	 * @tparam TRequestData A type that implements the FBeamBaseRequest struct.
	 * @param RequestData An instance of the request type.
	 * @param Request The actual HttpRequest we are configuring to send out through the Unreal Http Module.
	 * @param TargetBeamableUrl The target beamable URL --- typically from the current UBeamEnvironment.
	 */
	template <typename TRequestData>
	void PrepareBeamableRequestVerbRouteBody(const TUnrealRequestPtr& Request, const TRequestData* RequestData,
	                                         const FString& TargetBeamableUrl)
	{
		StaticCheckForRequestType<TRequestData>();

		// Build Route --- this is determined by the environment we are in plus some other stuff
		// Build verb --- this is solely determined by the type of request we are making.
		// Build body from the request object			
		FString Route = TargetBeamableUrl, Verb = TEXT(""), Body = TEXT("");
		RequestData->BuildRoute(Route);
		RequestData->BuildVerb(Verb);
		RequestData->BuildBody(Body);

		// Set the Verb/Route/Body...
		Request->SetURL(Route);
		Request->SetVerb(Verb);
		Request->SetContentAsString(Body);

		UE_LOG(LogBeamBackend, Verbose, TEXT("Request Preparation - Verb, Route and Body: VERB=%s ROUTE=%s, BODY=%s"),
		       *Verb, *Route, *Body);

		// Add any custom headers
		for (const auto CustomHeader : RequestData->CustomHeaders)
		{
			const auto Header = CustomHeader.Key;
			const auto Value = CustomHeader.Value;
			Request->SetHeader(Header, Value);
			UE_LOG(LogBeamBackend, Verbose, TEXT("Request Preparation - Custom Header: HEADER=%s VALUE=%s"),
			       *Header, *Value);
		}
	}


	/**
	 * @brief Prepares an TUnrealRequest using any UStruct containing the data (route and body params) we need to make the request to a Microservice.
	 * @tparam TRequestData A type that implements the FBeamBaseRequest struct.
	 * @param RequestData An instance of the request type.
	 * @param Request The actual HttpRequest we are configuring to send out through the Unreal Http Module.
	 * @param TargetBeamableUrl The target beamable URL --- typically from the current UBeamEnvironment.
	 * @param RealmHandle The realm handle that we are talking to. 
	 * @param Prefix The Prefix for the Microservice that we should talk to.
	 */
	template <typename TRequestData>
	void PrepareBeamableRequestVerbRouteBody(const TUnrealRequestPtr& Request,
	                                         const TRequestData* RequestData,
	                                         const FString& TargetBeamableUrl,
	                                         const FBeamRealmHandle& RealmHandle,
	                                         const FString& Prefix)
	{
		StaticCheckForRequestType<TRequestData>();
		FString Route = TEXT(""), Verb = TEXT(""), Body = TEXT("");

		// Build Route --- Microservice requests return a string in the following format: 'micro_{servicename}/{endpoint}'
		if (!IsRunningDedicatedServer())
		{
			RequestData->BuildRoute(Route);
			Route = TargetBeamableUrl + FString::Format(TEXT("/basic/{0}.{1}.{2}{3}"), {RealmHandle.Cid.AsString, RealmHandle.Pid.AsString, Prefix, Route});
		}
		// For dedicated servers, we always use the TargetRealm
		else
		{
			const auto DedicatedServerRealm = GetDefault<UBeamCoreSettings>()->TargetRealm;
			RequestData->BuildRoute(Route);
			Route = TargetBeamableUrl + FString::Format(TEXT("/basic/{0}.{1}.{2}{3}"), {DedicatedServerRealm.Cid.AsString, DedicatedServerRealm.Pid.AsString, Prefix, Route});
		}

		// Build verb --- this is always POST in the case of a Microservice
		RequestData->BuildVerb(Verb);

		// Build body from the request object			
		RequestData->BuildBody(Body);

		// Set the Verb/Route/Body...
		Request->SetURL(Route);
		Request->SetVerb(Verb);
		Request->SetContentAsString(Body);

		UE_LOG(LogBeamBackend, Verbose, TEXT("Request Preparation - Verb, Route and Body: VERB=%s ROUTE=%s, BODY=%s"),
		       *Verb, *Route, *Body);

		// Add any custom headers
		for (const auto CustomHeader : RequestData->CustomHeaders)
		{
			const auto Header = CustomHeader.Key;
			const auto Value = CustomHeader.Value;
			Request->SetHeader(Header, Value);
			UE_LOG(LogBeamBackend, Verbose, TEXT("Request Preparation - Custom Header: HEADER=%s VALUE=%s"),
			       *Header, *Value);
		}
	}


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
	 * @param CallingContext A UObject that defines a context for the caller. Used to support multiple PIE sessions and read-only request cache.
	 * 
	 * @return The request processor function, with correctly captured variables and properly set up to handle errors, retry and other utilities.
	 */
	template <typename TRequestData, typename TResponseData, typename TSuccessCallback, typename TErrorCallback,
	          typename TCompleteCallback>
	FBeamRequestProcessor MakeBlueprintRequestProcessor(const int64& RequestId, TRequestData* RequestData,
	                                                    TSuccessCallback OnSuccess, TErrorCallback OnError,
	                                                    TCompleteCallback OnComplete,
	                                                    const UObject* CallingContext = nullptr)
	{
		StaticCheckForRequestType<TRequestData>();
		StaticCheckForResponseType<TResponseData>();

		UE_LOG(LogBeamBackend, Verbose,
		       TEXT("Request Preparation - Processor Preparation: Making Blueprint Un-authenticated Request Processor"));

		FBeamRequestProcessor BoundResponseHandler(
			// Capture, by-value, the Backend system, request id for this request and request data --- these are plain structs with no allocations.
			[this, RequestId, RequestData, OnSuccess, OnError, OnComplete, CallingContext]

			// This just passes the captured data along to the Process function (we do this so we can unit test the process function in isolation).
		(const FHttpRequestPtr Request, const FHttpResponsePtr Response, const bool bWasCompleted)
			{
#if WITH_EDITOR
				if (HandlePIESessionRequestGuard(Request, RequestId))
					return;
#endif

				const auto RequestType = RequestData->GetRequestType();

				EHttpRequestStatus::Type RequestStatus;
				int32 ResponseCode;
				FString ContentAsString;
				if (!ExtractDataFromResponse(Request, Response, bWasCompleted, RequestStatus, ResponseCode, ContentAsString))
				{
					UE_LOG(LogBeamBackend, Error, TEXT("Beamable Request Failed Parsing Response | REQUEST_ID=%lld, REQUEST_TYPE=%s"), RequestId, *RequestType.Name);
					return;
				}
				UE_LOG(LogBeamBackend, Verbose, TEXT("Beamable Request Parsed Response | REQUEST_ID=%lld, REQUEST_TYPE=%s"), RequestId, *RequestType.Name);

				// If it was a success, we try to cache the response.
				if (IsSuccessfulResponse(ResponseCode))
					UpdateResponseCache(RequestType, CallingContext, Request, ContentAsString);


				RunBlueprintRequestProcessor<TRequestData, TResponseData, TSuccessCallback, TErrorCallback,
				                             TCompleteCallback>
					(ResponseCode, ContentAsString, RequestStatus, RequestId, RequestData, OnSuccess, OnError, OnComplete);
			});

		// We return the build processor function so the API request function can bind it to UnrealHttpRequest's response handler delegate.
		return BoundResponseHandler;
	}

	/**
	* @brief Runs the blueprint-only version of the Beamable Request Processor implementation for un-authenticated requests.
	 * @tparam TRequestData A type that implements the FBeamBaseRequest struct.
	 * @tparam TResponseData A type that implements the FBeamBaseResponse struct.
	 * @tparam TSuccessCallback A Dynamic Delegate with two params (DECLARE_DYNAMIC_DELEGATE_TwoParams) that blueprints can define to handle the successful request.
	 * @tparam TErrorCallback A Dynamic Delegate with two params (DECLARE_DYNAMIC_DELEGATE_TwoParams) that blueprints can define to handle a irrecoverable error in the request.
	 * @tparam TCompleteCallback A Dynamic Delegate with one params (DECLARE_DYNAMIC_DELEGATE_OneParam) that blueprints can define to run after the request completes, be it an error or success.
	 * @param ResponseCode The result code you're running with. Typically, 200.
	 * @param ContentAsString The serialized response you received. 
	 * @param RequestStatus The status for the request. Typically, success.
	 * @param RequestId The Request Id generated by the UBeamBackend::CreateRequest function.	 
	 * @param RequestData An instance of the request type.
	 * @param OnSuccess The callback to handle success.
	 * @param OnError The callback to handle irrecoverable errors.
	 * @param OnComplete The callback to run after success/errors have been handled.	 
	 */
	template <class TRequestData, class TResponseData, class TSuccessCallback, class TErrorCallback, class
	          TCompleteCallback>
	void RunBlueprintRequestProcessor(const int32& ResponseCode, const FString& ContentAsString,
	                                  TUnrealRequestStatus RequestStatus, const int64& RequestId,
	                                  TRequestData* RequestData,
	                                  TSuccessCallback OnSuccess, TErrorCallback OnError, TCompleteCallback OnComplete)
	{
		ProcessBlueprintRequest<TRequestData, TResponseData, TSuccessCallback, TErrorCallback, TCompleteCallback>
			(ResponseCode, ContentAsString, RequestStatus, RequestId, RequestData, OnSuccess, OnError, OnComplete);

		// Run any registered callback for handling Request completion.
		TryTriggerRequestCompleteDelegates(RequestId);
	}

	/**
	 * @brief Callback that MakeBlueprintRequestProcessor uses to handle un-authenticated requests.	  
	 */
	template <typename TRequestData, typename TResponseData, typename TSuccessCallback, typename TErrorCallback,
	          typename TCompleteCallback>
	void ProcessBlueprintRequest(const int32& ResponseCode, const FString& ContentAsString,
	                             const TUnrealRequestStatus RequestStatus,
	                             const int64& RequestId, TRequestData* RequestData,
	                             TSuccessCallback OnSuccess, TErrorCallback OnError, TCompleteCallback OnComplete)
	{
		StaticCheckForRequestType<TRequestData>();
		StaticCheckForResponseType<TResponseData>();

		// Update the context to pass into the response callbacks.
		auto Context = *InFlightRequestContexts.Find(RequestId);
		Context.ResponseCode = ResponseCode;


		// If the request was cancelled, we'll only run the OnComplete call 
		if (InFlightRequestsCancelled.Contains(RequestId))
		{
			UE_LOG(LogBeamBackend, Verbose, TEXT("Ignoring Request Response since it was cancelled. REQUEST_ID=%lld"),
			       RequestId);

			// Execute the handler if it's bound.
			const auto bExecutedCallsiteHandler = OnComplete.ExecuteIfBound(Context, RequestData);
			if (AlwaysLogCompleteResponses || !bExecutedCallsiteHandler)
			{
				UE_LOG(LogBeamBackend, Warning, TEXT("Beamable Request Canceled | REQUEST_ID=%lld, NUM_FAILURES=%d"),
				       RequestId, InFlightFailureCount.FindRef(RequestId));
			}

			// Update the context's status to completed so we can clean it up in the next tick of TickCleanUpRequests if no one depends on it.
			Context.BeamStatus = AS_Completed;
			InFlightRequestContexts[RequestId] = Context;
			return;
		}

		// Stores whether the request was successful
		const auto bWasSuccess = IsSuccessfulResponse(ResponseCode);


		// Get retry stuff
		auto CurrFailedCount = InFlightFailureCount.FindChecked(RequestId);
		const auto RetryConfig = Context.RetryConfiguration;
		const auto bShouldRetryIfFail = RetryConfig.RetryMaxAttempt == -1 || CurrFailedCount < RetryConfig.RetryMaxAttempt;

		// If it was an error, we'll compute this based on the error data.
		bool bWillRetry = !bWasSuccess && bShouldRetryIfFail;
		// Parse the appropriate response body...
		if (bWasSuccess)
		{
			// Parse the response body and store it in the full response data.
			auto SuccessData = NewObject<TResponseData>(RequestData);
			SuccessData->DeserializeRequestResponse(RequestData, ContentAsString);

			// Store it so wait handles can grab at it later
			InFlightResponseBodyData[Context] = SuccessData;

			// Run the callsite handler
			const auto ExecutedCallsiteHandler = OnSuccess.ExecuteIfBound(Context, RequestData, SuccessData);

			// We only log the response if no callsite is given or if we are configured to always run it.
			if (AlwaysLogSuccessResponses || !ExecutedCallsiteHandler)
			{
				const auto RequestType = RequestData->GetRequestType();
				UE_LOG(LogBeamBackend, Verbose,
				       TEXT(
					       "Beamable Request Successfull | REQUEST_ID=%lld, REQUEST_TYPE=%s, RESPONSE_CODE=%d, NUM_FAILURES=%d, RESPONSE_BODY=%s"
				       ), RequestId, *RequestType.Name, ResponseCode, CurrFailedCount,
				       *ContentAsString);
			}
		}
		else
		{
			// Otherwise, parse the body as an error response callback and store it in the full response data.
			FBeamErrorResponse ErrorData;
			FJsonObjectConverter::JsonObjectStringToUStruct(*ContentAsString, &ErrorData);

			// Now that we know we had an error, compute whether we should retry.
			bWillRetry &= RetryConfig.HttpResponseCodes.Contains(ResponseCode) || RetryConfig.CustomErrorCodes.Contains(ErrorData.error);

			// Store it so wait handles can grab at it later
			InFlightResponseErrorData[Context] = ErrorData;

			// Bump the failed count associated with this request id.
			CurrFailedCount += 1;
			InFlightFailureCount[RequestId] = CurrFailedCount;

			// If we should still retry (-1 == infinite retry)
			if (bWillRetry)
			{
				// Enqueue a request to try again
				FRequestToRetry Retry;
				Retry.RequestId = RequestId;
				Retry.IsBlueprintCompatible = 1;
				Retry.ResponseCode = ResponseCode;
				Retry.ErrorCode = ErrorData.error;
				EnqueuedRetries.Enqueue(Retry);
			}

			// Run the callsite handler, if any.
			const auto ExecutedCallsiteHandler = OnError.ExecuteIfBound(Context, RequestData, ErrorData);

			// We fallback to global handler only if we didn't run the callsite one OR if we are configured to always run it.
			bool bExecutedGlobalHandler = false;
			if ((AlwaysRunGlobalHandlers || !ExecutedCallsiteHandler) && (GlobalRequestErrorHandler.IsBound() || GlobalRequestErrorCodeHandler.IsBound()))
			{
				GlobalRequestErrorHandler.Broadcast(Context, ErrorData);
				const auto _ = GlobalRequestErrorCodeHandler.ExecuteIfBound(Context, ErrorData);

				bExecutedGlobalHandler = true;
			}

			// We log the error only if neither callback was set OR if we are configured to do so.
			if (AlwaysLogErrorResponses || (!bExecutedGlobalHandler && !ExecutedCallsiteHandler))
			{
				UE_LOG(LogBeamBackend, Error,
				       TEXT(
					       "Beamable Request Failed | REQUEST_ID=%lld, RESPONSE_CODE=%d, NUM_FAILURES=%d, WILL_RETRY=%s, RESPONSE_BODY=%s"
				       ), RequestId, ResponseCode,
				       CurrFailedCount,
				       bWillRetry ? TEXT("true") : TEXT("false"), *ContentAsString);
			}
		}

		// Clean up from InFlightRequests, only if we are not meant to retry it.
		if (bWasSuccess || !bWillRetry)
		{
			// Execute the handler if it's bound.
			const auto bExecutedCallsiteHandler = OnComplete.ExecuteIfBound(Context, RequestData);
			if (AlwaysLogCompleteResponses || !bExecutedCallsiteHandler)
			{
				UE_LOG(LogBeamBackend, Verbose, TEXT( "Beamable Request Completed | REQUEST_ID=%lld, RESPONSE_CODE=%d, WAS_SUCCESS=%s, NUM_FAILURES=%d" ),
				       RequestId, ResponseCode, bWasSuccess ? TEXT("true") : TEXT("false"), CurrFailedCount);
			}

			// Update the context's status to completed so we can clean it up in the next tick of TickCleanUpRequests if no one depends on it.
			Context.BeamStatus = AS_Completed;
			InFlightRequestContexts[RequestId] = Context;
		}
	}

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
	 * @param CallingContext A UObject that defines a context for the caller. Used to support multiple PIE sessions and read-only request cache.
	 * @return A function to be used as the lambda for the HttpRequest completion callback.
	 */
	template <typename TRequestData, typename TResponseData, typename TSuccessCallback, typename TErrorCallback,
	          typename TCompleteCallback>
	FBeamRequestProcessor MakeAuthenticatedBlueprintRequestProcessor(const int64& RequestId,
	                                                                 const FBeamRealmHandle& RealmHandle,
	                                                                 const FBeamAuthToken& AuthToken,
	                                                                 TRequestData* RequestData,
	                                                                 TSuccessCallback OnSuccess, TErrorCallback OnError,
	                                                                 TCompleteCallback OnComplete,
	                                                                 const UObject* CallingContext = nullptr)
	{
		StaticCheckForRequestType<TRequestData>();
		StaticCheckForResponseType<TResponseData>();

		UE_LOG(LogBeamBackend, Verbose,
		       TEXT("Request Preparation - Processor Preparation: Making Blueprint Authenticated Request Processor"));

		FBeamRequestProcessor BoundResponseHandler(
			// Capture, by-value, the Backend system, request id for this request and request data --- these are plain structs with no allocations.
			[this, RequestId, AuthToken, RealmHandle, RequestData, OnSuccess, OnError, OnComplete, CallingContext]

			// This just passes the captured data along to the Process function (we do this so we can unit test the process function in isolation).
		(const FHttpRequestPtr Request, const FHttpResponsePtr Response, bool bWasCompleted)
			{
#if WITH_EDITOR
				if (HandlePIESessionRequestGuard(Request, RequestId))
					return;
#endif

				const auto RequestType = RequestData->GetRequestType();

				EHttpRequestStatus::Type RequestStatus;
				int32 ResponseCode;
				FString ContentAsString;
				if (!ExtractDataFromResponse(Request, Response, bWasCompleted, RequestStatus, ResponseCode, ContentAsString))
				{
					UE_LOG(LogBeamBackend, Error, TEXT("Beamable Request Failed Parsing Response | REQUEST_ID=%lld, REQUEST_TYPE=%s"), RequestId, *RequestType.Name);
					return;
				}
				UE_LOG(LogBeamBackend, Verbose, TEXT("Beamable Request Parsed Response | REQUEST_ID=%lld, REQUEST_TYPE=%s"), RequestId, *RequestType.Name);

				// If it was a success, we try to cache the response.
				if (IsSuccessfulResponse(ResponseCode))
					UpdateResponseCache(RequestType, CallingContext, Request, ContentAsString);


				RunAuthenticatedBlueprintRequestProcessor<
					TRequestData, TResponseData, TSuccessCallback, TErrorCallback, TCompleteCallback>
				(ResponseCode, ContentAsString, RequestStatus, RequestId, RealmHandle, AuthToken, RequestData,
				 OnSuccess, OnError, OnComplete);
			});

		// We return the build processor function so the API request function can bind it to UnrealHttpRequest's response handler delegate.
		return BoundResponseHandler;
	}

	/**
	 * @brief Runs the blueprint-only version of the Beamable Request Processor implementation for authenticated requests.
	 * @tparam TRequestData A type that implements the FBeamBaseRequest struct.
	 * @tparam TResponseData A type that implements the FBeamBaseResponse struct.
	 * @tparam TSuccessCallback A Dynamic Delegate with two params (DECLARE_DYNAMIC_DELEGATE_TwoParams) that blueprints can define to handle the successful request.
	 * @tparam TErrorCallback A Dynamic Delegate with two params (DECLARE_DYNAMIC_DELEGATE_TwoParams) that blueprints can define to handle a irrecoverable error in the request.
	 * @tparam TCompleteCallback A Dynamic Delegate with one params (DECLARE_DYNAMIC_DELEGATE_OneParam) that blueprints can define to run after the request completes, be it an error or success.
	 * @param ResponseCode The result code you're running with. Typically, 200.
	 * @param ContentAsString The serialized response you received. 
	 * @param RequestStatus The status for the request. Typically, success.
	 * @param RequestId The Request Id generated by the UBeamBackend::CreateRequest function.
	 * @param RealmHandle The Realm (CID+PID) we are making the request to.
	 * @param AuthToken The AuthenticationToken we should be using to make the request.
	 * @param RequestData An instance of the request type.
	 * @param OnSuccess The callback to handle success.
	 * @param OnError The callback to handle irrecoverable errors.
	 * @param OnComplete The callback to run after success/errors have been handled.
	 */
	template <class TRequestData, class TResponseData, class TSuccessCallback, class TErrorCallback, class
	          TCompleteCallback>
	void RunAuthenticatedBlueprintRequestProcessor(const int32& ResponseCode, const FString& ContentAsString,
	                                               TUnrealRequestStatus RequestStatus, const int64& RequestId,
	                                               const FBeamRealmHandle& RealmHandle, const FBeamAuthToken& AuthToken,
	                                               TRequestData* RequestData, TSuccessCallback OnSuccess,
	                                               TErrorCallback OnError,
	                                               TCompleteCallback OnComplete)
	{
		ProcessAuthenticatedBlueprintRequest<TRequestData, TResponseData, TSuccessCallback, TErrorCallback,
		                                     TCompleteCallback>
		(ResponseCode, ContentAsString, RequestStatus, RequestId, RealmHandle, AuthToken, RequestData, OnSuccess,
		 OnError, OnComplete);

		// Run any registered callback for handling Request completion.
		TryTriggerRequestCompleteDelegates(RequestId);
	}

	/**
	 * @brief Callback that MakeAuthenticatedBlueprintRequestProcessor uses to handle authenticated requests. 
	 */
	template <typename TRequestData, typename TResponseData, typename TSuccessCallback, typename TErrorCallback,
	          typename TCompleteCallback>
	void ProcessAuthenticatedBlueprintRequest(const int32& ResponseCode, const FString& ContentAsString,
	                                          const TUnrealRequestStatus RequestStatus,
	                                          const int64& RequestId, const FBeamRealmHandle& RealmHandle,
	                                          const FBeamAuthToken& AuthToken,
	                                          TRequestData* RequestData, TSuccessCallback OnSuccess,
	                                          TErrorCallback OnError, TCompleteCallback OnComplete)
	{
		StaticCheckForRequestType<TRequestData>();
		StaticCheckForResponseType<TResponseData>();

		// Get any UserSlot that matches this Pid/Auth Token, if any		
		FBeamRealmUser User;
		FUserSlot UserSlot;
		FString NamespacedSlotId;
		const auto bWasMadeWithUserSlot = BeamUserSlots->GetUserDataWithRefreshTokenAndPid(
			AuthToken.RefreshToken, RealmHandle.Pid, User, UserSlot, NamespacedSlotId);

		// Create the context to pass into the callbacks	
		auto Context = *InFlightRequestContexts.Find(RequestId);
		Context.ResponseCode = ResponseCode;
		Context.UserSlot = bWasMadeWithUserSlot ? UserSlot : FUserSlot("");

		// If the request was cancelled, we'll only run the OnComplete call 
		if (InFlightRequestsCancelled.Contains(RequestId))
		{
			UE_LOG(LogBeamBackend, Verbose, TEXT("Ignoring Request Response since it was cancelled. REQUEST_ID=%lld"),
			       RequestId);

			// Execute the handler if it's bound.		
			const auto bExecutedCallsiteHandler = OnComplete.ExecuteIfBound(Context, RequestData);
			if (AlwaysLogCompleteResponses || !bExecutedCallsiteHandler)
			{
				UE_LOG(LogBeamBackend, Warning,
				       TEXT("Beamable Request Canceled | REQUEST_ID=%lld, USER_SLOT=%s, NUM_FAILURES=%d"),
				       RequestId, bWasMadeWithUserSlot ? *UserSlot.Name : *FString(TEXT("Made Without UserSlot")),
				       InFlightFailureCount.FindRef(RequestId));
			}

			// Update the context's status to completed so we can clean it up in the next tick of TickCleanUpRequests if no one depends on it.
			Context.BeamStatus = AS_Completed;
			InFlightRequestContexts[RequestId] = Context;
			return;
		}
		// Then, we handle success and error cases.

		// Get retry stuff
		auto CurrFailedCount = InFlightFailureCount.FindChecked(RequestId);
		const auto RetryConfig = Context.RetryConfiguration;
		const auto bShouldRetryIfFail = RetryConfig.RetryMaxAttempt == -1 || CurrFailedCount < RetryConfig.RetryMaxAttempt;

		// Stores whether the request was successful
		const auto bWasSuccess = IsSuccessfulResponse(ResponseCode);

		// If it was an error, we'll compute if we should re-auth/retry based on the error data.
		bool bWillRetry = !bWasSuccess && bShouldRetryIfFail;
		bool bWillReAuth = !bWasSuccess;
		// Parse the appropriate response body...
		if (bWasSuccess)
		{
			// Parse the response body and store it in the full response data.		
			auto SuccessData = NewObject<TResponseData>(RequestData);
			SuccessData->DeserializeRequestResponse(RequestData, ContentAsString);

			// Store it so wait handles can grab at it later
			InFlightResponseBodyData[Context] = SuccessData;

			// Run the callsite handler
			const auto ExecutedCallsiteHandler = OnSuccess.ExecuteIfBound(Context, RequestData, SuccessData);

			// We only log the response if no callsite is given or if we are configured to always run it.
			if (AlwaysLogSuccessResponses || !ExecutedCallsiteHandler)
			{
				const auto RequestType = RequestData->GetRequestType();
				UE_LOG(LogBeamBackend, Verbose, TEXT( "Beamable Request Successfull | REQUEST_ID=%lld, REQUEST_TYPE=%s, USER_SLOT=%s, RESPONSE_CODE=%d, NUM_FAILURES=%d, RESPONSE_BODY=%s" ),
				       RequestId, *RequestType.Name, bWasMadeWithUserSlot ? *UserSlot.Name : TEXT("Made Without UserSlot"), ResponseCode, CurrFailedCount, *ContentAsString);
			}
		}
		else
		{
			// Otherwise, parse the body as an error response callback and store it in the full response data.
			FBeamErrorResponse ErrorData;
			FJsonObjectConverter::JsonObjectStringToUStruct(*ContentAsString, &ErrorData);

			// Store it so wait handles can grab at it later
			InFlightResponseErrorData[Context] = ErrorData;

			// Now that we know we had an error, compute whether we should retry.		
			bWillReAuth &= AUTH_ERROR_CODE_RETRY_ALLOWED.Contains(ErrorData.error);
			bWillRetry &= RetryConfig.HttpResponseCodes.Contains(ResponseCode) || RetryConfig.CustomErrorCodes.Contains(ErrorData.error);
			// We always enqueue for retry if we need the re-auth, even if we are "out of retries". That's because Re-Auth retries don't count towards the retry limit.
			bWillRetry |= bWillReAuth;

			// Bump the failed count associated with this request id.					
			CurrFailedCount = bWillReAuth ? CurrFailedCount : CurrFailedCount + 1;
			InFlightFailureCount[RequestId] = CurrFailedCount;

			if (bWillRetry)
			{
				// Enqueue a request to try again
				FRequestToRetry Retry;
				Retry.RequestId = RequestId;
				Retry.AuthToken = AuthToken;
				Retry.RealmHandle = RealmHandle;
				Retry.IsBlueprintCompatible = 1;
				Retry.ResponseCode = ResponseCode;
				Retry.ErrorCode = ErrorData.error;
				EnqueuedRetries.Enqueue(Retry);
			}

			// Run callback with the Retrying state if we are going to retry AND it's not a 401 error.
			// 401 errors are a special case of errors --- we make a special re-authentication request when we get them and then follow up with the original request.
			// If the re-auth fail, this will run again but the retry configuration will be set to NOT RETRY ANYMORE and therefore the error callback will get run.
			if (!bWillReAuth)
			{
				// Run the callsite handler, if any.
				const auto ExecutedCallsiteHandler = OnError.ExecuteIfBound(Context, RequestData, ErrorData);

				// We fallback to global handler only if we didn't run the callsite one OR if we are configured to always run it.
				bool bExecutedGlobalHandler = false;
				if ((AlwaysRunGlobalHandlers || !ExecutedCallsiteHandler) && (GlobalRequestErrorHandler.IsBound() || GlobalRequestErrorCodeHandler.IsBound()))
				{
					GlobalRequestErrorHandler.Broadcast(Context, ErrorData);
					const auto _ = GlobalRequestErrorCodeHandler.ExecuteIfBound(Context, ErrorData);

					bExecutedGlobalHandler = true;
				}

				// We log the error only if neither callback was set OR if we are configured to do so.
				if (AlwaysLogErrorResponses || (!bExecutedGlobalHandler && !ExecutedCallsiteHandler))
				{
					UE_LOG(LogBeamBackend, Error,
					       TEXT(
						       "Beamable Request Failed | REQUEST_ID=%lld, USER_SLOT=%s, RESPONSE_CODE=%d, NUM_FAILURES=%d, WILL_RETRY=%s, RESPONSE_BODY=%s"
					       ),
					       RequestId, bWasMadeWithUserSlot ? *UserSlot.Name : TEXT("Made Without UserSlot"), ResponseCode,
					       CurrFailedCount, bWillRetry ? TEXT("true") : TEXT("false"),
					       *ContentAsString);
				}
			}
		}

		// Clean up from InFlightRequests, only if we are not meant to retry it.
		if (bWasSuccess || !bWillRetry)
		{
			// Execute the handler if it's bound.
			const auto bExecutedCallsiteHandler = OnComplete.ExecuteIfBound(Context, RequestData);
			if (AlwaysLogCompleteResponses || !bExecutedCallsiteHandler)
			{
				UE_LOG(LogBeamBackend, Verbose, TEXT( "Beamable Request Completed | REQUEST_ID=%lld, USER_SLOT=%s, RESPONSE_CODE=%d, WAS_SUCCESS=%s, NUM_FAILURES=%d" ),
				       RequestId, bWasMadeWithUserSlot ? *UserSlot.Name : TEXT("Made Without UserSlot"), ResponseCode, bWasSuccess ? TEXT("true") : TEXT("false"), CurrFailedCount);
			}

			// Update the context's status to completed so we can clean it up in the next tick of TickCleanUpRequests if no one depends on it.
			Context.BeamStatus = AS_Completed;
			InFlightRequestContexts[RequestId] = Context;
		}
	}

	/**
	 * @brief The code-only version of the Beamable Request Processor implementation. This generates 2 things:
	 * a function to be used as the lambda for the HttpRequest completion and a set of Future objects user-code can attach to.
	 * 
	 * @tparam TRequestData A type that implements the FBeamBaseRequest struct.
	 * @tparam TResponseData A type that implements the FBeamBaseResponse struct.
	 * @param RequestId The Request Id generated by the UBeamBackend::CreateRequest function.
	 * @param RequestData An instance of the request type.
	 * @param ResponseHandler A callback to handle the full response of this request. To handle success/error/retry, read from the TBeamFullResponse data.
	 * @param CallingContext A UObject that defines a context for the caller. Used to support multiple PIE sessions and read-only request cache.
	 * 
	 * @return The request processor function, with correctly captured variables and properly set up to handle errors, retry and other utilities.
	 */
	template <typename TRequestData, typename TResponseData>
	FBeamRequestProcessor MakeCodeRequestProcessor(const int64& RequestId, TRequestData* RequestData,
	                                               TBeamFullResponseHandler<TRequestData*, TResponseData*>
	                                               ResponseHandler, const UObject* CallingContext = nullptr)
	{
		StaticCheckForRequestType<TRequestData>();
		StaticCheckForResponseType<TResponseData>();

		UE_LOG(LogBeamBackend, Verbose,
		       TEXT("Request Preparation - Processor Preparation: Making Code Un-authenticated Request Processor"));

		// Get the handlers 
		auto OutProcessor = FBeamRequestProcessor(
			// Capture, by-value, the Backend system, request id for this request and request data --- these are plain structs with no allocations.
			[this, RequestId, RequestData, ResponseHandler, CallingContext]
			// This just passes the captured data along to the Process function (we do this so we can unit test the process function in isolation).
		(const FHttpRequestPtr Request, const FHttpResponsePtr Response, bool bWasCompleted)
			{
#if WITH_EDITOR
				if (HandlePIESessionRequestGuard(Request, RequestId))
					return;
#endif

				const auto RequestType = RequestData->GetRequestType();

				EHttpRequestStatus::Type RequestStatus;
				int32 ResponseCode;
				FString ContentAsString;
				if (!ExtractDataFromResponse(Request, Response, bWasCompleted, RequestStatus, ResponseCode, ContentAsString))
				{
					UE_LOG(LogBeamBackend, Error, TEXT("Beamable Request Failed Parsing Response | REQUEST_ID=%lld, REQUEST_TYPE=%s"), RequestId, *RequestType.Name);
					return;
				}
				UE_LOG(LogBeamBackend, Verbose, TEXT("Beamable Request Parsed Response | REQUEST_ID=%lld, REQUEST_TYPE=%s"), RequestId, *RequestType.Name);

				// If it was a success, we try to cache the response.
				if (IsSuccessfulResponse(ResponseCode))
					UpdateResponseCache(RequestType, CallingContext, Request, ContentAsString);

				RunCodeRequestProcessor<TRequestData, TResponseData>(ResponseCode, ContentAsString, RequestStatus,
				                                                     RequestId, RequestData, ResponseHandler);
			});

		// We return the build processor function so the API request function can bind it to UnrealHttpRequest's response handler delegate.
		return OutProcessor;
	}

	/**
	 * @brief Runs the code-only version of the Beamable Request Processor implementation for un-authenticated requests.
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
	void RunCodeRequestProcessor(const int32& ResponseCode, const FString& ContentAsString,
	                             const TUnrealRequestStatus RequestStatus,
	                             const int64& RequestId, TRequestData* RequestData,
	                             TBeamFullResponseHandler<TRequestData*, TResponseData*> ResponseHandler)
	{
		ProcessCodeRequest<TRequestData, TResponseData>(ResponseCode, ContentAsString, RequestStatus, RequestId,
		                                                RequestData, ResponseHandler);

		// Run any registered callback for handling Request completion.
		TryTriggerRequestCompleteDelegates(RequestId);
	}


	/**
	 * @brief Callback that MakeCodeRequestProcessor uses to handle requests that don't require authentication.	  
	 */
	template <typename TRequestData, typename TResponseData>
	void ProcessCodeRequest(const int32& ResponseCode, const FString& ContentAsString,
	                        const TUnrealRequestStatus RequestStatus,
	                        const int64& RequestId, TRequestData* RequestData,
	                        TBeamFullResponseHandler<TRequestData*, TResponseData*> ResponseHandler)
	{
		StaticCheckForRequestType<TRequestData>();
		StaticCheckForResponseType<TResponseData>();

		if (!RequestStatus)
		{
			// TODO Invoke Callback but mapped to Beamable specific signature.
			return;
		}

		auto FullResponse = FBeamFullResponse<TRequestData*, TResponseData*>();

		// Update and sets the request id for the request
		auto Context = *InFlightRequestContexts.Find(RequestId);
		Context.ResponseCode = ResponseCode;
		Context.UserSlot = FUserSlot("");
		FullResponse.Context = Context;

		// Store the Request's data into the full response
		FullResponse.RequestData = RequestData;

		const bool bIsCancelled = InFlightRequestsCancelled.Contains(RequestId);
		// Stores whether the request was successful, error or cancelled
		if (bIsCancelled)
			FullResponse.State = RS_Cancelled;
		else
			FullResponse.State = IsSuccessfulResponse(ResponseCode) ? RS_Success : RS_Error;

		// Get retry stuff
		auto CurrFailedCount = InFlightFailureCount.FindChecked(RequestId);
		const auto RetryConfig = Context.RetryConfiguration;
		const auto bShouldRetryIfFail = !bIsCancelled && (RetryConfig.RetryMaxAttempt == -1 || RetryConfig.RetryMaxAttempt > CurrFailedCount);

		// Stores which attempt we are in
		FullResponse.AttemptNumber = CurrFailedCount;

		// If it was an error, we'll compute this based on the error data.
		bool bWillRetry = !IsSuccessfulResponse(ResponseCode) && bShouldRetryIfFail;
		// Parse the appropriate response body...
		if (FullResponse.State == RS_Success)
		{
			// Parse the response body and store it in the full response data.				
			FullResponse.SuccessData = NewObject<TResponseData>(RequestData);
			FullResponse.SuccessData->DeserializeRequestResponse(RequestData, ContentAsString);

			// Store it so wait handles can grab at it later
			InFlightResponseBodyData[Context] = FullResponse.SuccessData;
		}
		else if (FullResponse.State == RS_Error)
		{
			// Otherwise, parse the body as an error response callback and store it in the full response data.				
			FJsonObjectConverter::JsonObjectStringToUStruct(*ContentAsString, &FullResponse.ErrorData);

			// Now that we know we had an error, compute whether we should retry.
			bWillRetry &= RetryConfig.HttpResponseCodes.Contains(ResponseCode) || RetryConfig.CustomErrorCodes.Contains(FullResponse.ErrorData.error);

			// Store it so wait handles can grab at it later
			InFlightResponseErrorData[Context] = FullResponse.ErrorData;

			// Bump the failed count associated with this request id.
			CurrFailedCount = CurrFailedCount + 1;
			InFlightFailureCount[RequestId] = CurrFailedCount;

			// If we should still retry (-1 == infinite retry)
			if (bWillRetry)
			{
				// Enqueue a request to try again
				FRequestToRetry Retry;
				Retry.RequestId = RequestId;
				Retry.IsBlueprintCompatible = 0;
				Retry.ResponseCode = ResponseCode;
				Retry.ErrorCode = FullResponse.ErrorData.error;
				EnqueuedRetries.Enqueue(Retry);

				FullResponse.State = RS_Retrying;
			}
		}

		// We run the response handler
		const auto bExecutedCallsiteHandler = ResponseHandler.ExecuteIfBound(FullResponse);

		// For un-authenticated requests, we always invoke the callback with retrying state.	
		if (bWillRetry)
		{
			// We run global handlers for this request if we are configured to always run them
			auto bRanGlobalHandlers = false;
			if (AlwaysRunGlobalHandlers || !bExecutedCallsiteHandler)
			{
				GlobalRequestErrorHandler.Broadcast(FullResponse.Context, FullResponse.ErrorData);
				const auto _ = GlobalRequestErrorCodeHandler.ExecuteIfBound(FullResponse.Context, FullResponse.ErrorData);
				bRanGlobalHandlers = true;
			}

			// We log if we are configured to do so or as a fallback if no handler is configured
			if (AlwaysLogErrorResponses || (!bExecutedCallsiteHandler && !bRanGlobalHandlers))
			{
				const auto RequestType = RequestData->GetRequestType();
				UE_LOG(LogBeamBackend, Error, TEXT( "Beamable Request Failed - Retrying | REQUEST_ID=%lld, REQUEST_TYPE=%s, RESPONSE_CODE=%d, NUM_FAILURES=%d, WILL_RETRY=%s, RESPONSE_BODY=%s" ),
				       RequestId, *RequestType.Name, ResponseCode, CurrFailedCount, bWillRetry ? TEXT("true") : TEXT("false"), *ContentAsString);
			}
		}
		// Only run the clean up and callbacks after we are done retrying.
		else
		{
			const auto RequestType = RequestData->GetRequestType();
			if (AlwaysLogCompleteResponses || !bExecutedCallsiteHandler)
			{
				// We only log the response for code if we are configured to always run it.
				if (AlwaysLogSuccessResponses && FullResponse.State == RS_Success)
				{
					UE_LOG(LogBeamBackend, Verbose, TEXT( "Beamable Request Successfull | REQUEST_ID=%lld, REQUEST_TYPE=%s, RESPONSE_CODE=%d, NUM_FAILURES=%d, RESPONSE_BODY=%s" ),
					       RequestId, *RequestType.Name, ResponseCode, CurrFailedCount, *ContentAsString);
				}

				// We log the error only if neither callback was set OR if we are configured to do so.
				if (AlwaysLogErrorResponses && FullResponse.State == RS_Error)
				{
					UE_LOG(LogBeamBackend, Error, TEXT( "Beamable Request Failed | REQUEST_ID=%lld, REQUEST_TYPE=%s, RESPONSE_CODE=%d, NUM_FAILURES=%d, RESPONSE_BODY=%s" ),
					       RequestId, *RequestType.Name, ResponseCode, CurrFailedCount, *ContentAsString);
				}

				const auto bWasSuccess = FullResponse.State == RS_Success;
				if (FullResponse.State == RS_Cancelled)
				{
					UE_LOG(LogBeamBackend, Warning, TEXT("Beamable Request Canceled | REQUEST_ID=%lld, REQUEST_TYPE=%s, WAS_SUCCESS=%s, NUM_FAILURES=%d"),
					       RequestId, *RequestType.Name, bWasSuccess ? TEXT("true") : TEXT("false"), InFlightFailureCount.FindRef(RequestId));
				}
				else
				{
					UE_LOG(LogBeamBackend, Verbose, TEXT("Beamable Request Completed | REQUEST_ID=%lld, REQUEST_TYPE=%s, WAS_SUCCESS=%s, NUM_FAILURES=%d"),
					       RequestId, *RequestType.Name, bWasSuccess ? TEXT("true") : TEXT("false"), InFlightFailureCount.FindRef(RequestId));
				}
			}

			// Update the context's status to completed so we can clean it up in the next tick of TickCleanUpRequests if no one depends on it.
			Context.BeamStatus = AS_Completed;
			InFlightRequestContexts[RequestId] = Context;
		}
	}

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
	 * @param CallingContext A UObject that defines a context for the caller. Used to support multiple PIE sessions and read-only request cache.  	 
	 * 
	 * @return The request processor function, with correctly captured variables and properly set up to handle errors, retry and other utilities.
	 */
	template <typename TRequestData, typename TResponseData>
	FBeamRequestProcessor MakeAuthenticatedCodeRequestProcessor(const int64& RequestId,
	                                                            const FBeamRealmHandle& RealmHandle,
	                                                            const FBeamAuthToken& AuthToken,
	                                                            TRequestData* RequestData,
	                                                            TBeamFullResponseHandler<TRequestData*, TResponseData*>
	                                                            ResponseHandler,
	                                                            const UObject* CallingContext = nullptr)
	{
		StaticCheckForRequestType<TRequestData>();
		StaticCheckForResponseType<TResponseData>();

		UE_LOG(LogBeamBackend, Verbose,
		       TEXT("Request Preparation - Processor Preparation: Making Code Authenticated Request Processor"));

		// Get the handlers 
		auto OutProcessor = FBeamRequestProcessor(
			// Capture, by-value, the Backend system, request id for this request and request data --- these are plain structs with no allocations.
			[this, RequestId, RealmHandle, AuthToken, RequestData, ResponseHandler, CallingContext]
			// This just passes the captured data along to the Process function (we do this so we can unit test the process function in isolation).
		(const FHttpRequestPtr Request, const FHttpResponsePtr Response, bool bWasCompleted)
			{
#if WITH_EDITOR
				if (HandlePIESessionRequestGuard(Request, RequestId))
					return;
#endif

				const auto RequestType = RequestData->GetRequestType();

				EHttpRequestStatus::Type RequestStatus;
				int32 ResponseCode;
				FString ContentAsString;
				if (!ExtractDataFromResponse(Request, Response, bWasCompleted, RequestStatus, ResponseCode, ContentAsString))
				{
					UE_LOG(LogBeamBackend, Error, TEXT("Beamable Request Failed Parsing Response | REQUEST_ID=%lld, REQUEST_TYPE=%s"), RequestId, *RequestType.Name);
					return;
				}
				UE_LOG(LogBeamBackend, Verbose, TEXT("Beamable Request Parsed Response | REQUEST_ID=%lld, REQUEST_TYPE=%s"), RequestId, *RequestType.Name);


				// If it was a success, we try to cache the response.
				if (IsSuccessfulResponse(ResponseCode))
					UpdateResponseCache(RequestType, CallingContext, Request, ContentAsString);

				RunAuthenticatedCodeRequestProcessor<TRequestData, TResponseData>(
					ResponseCode, ContentAsString, RequestStatus, RequestId, RealmHandle, AuthToken, RequestData,
					ResponseHandler);
			});

		// We return the build processor function so the API request function can bind it to UnrealHttpRequest's response handler delegate. 
		return OutProcessor;
	}

	/**
	 * @brief Runs the code-only version of the Beamable Request Processor implementation for authenticated requests.
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
	void RunAuthenticatedCodeRequestProcessor(const int32& ResponseCode, const FString& ContentAsString,
	                                          const TUnrealRequestStatus RequestStatus,
	                                          const int64& RequestId, const FBeamRealmHandle& RealmHandle,
	                                          const FBeamAuthToken& AuthToken, TRequestData* RequestData,
	                                          const TBeamFullResponseHandler<TRequestData*, TResponseData*>&
	                                          ResponseHandler)
	{
		ProcessAuthenticatedCodeRequest<TRequestData, TResponseData>(ResponseCode, ContentAsString, RequestStatus,
		                                                             RequestId, RealmHandle, AuthToken, RequestData,
		                                                             ResponseHandler);

		// Run any registered callback for handling Request completion.
		TryTriggerRequestCompleteDelegates(RequestId);
	}

	/**
	 * @brief Callback that MakeAuthenticatedCodeRequestProcessor uses to handle authenticated request's responses.
	 */
	template <typename TRequestData, typename TResponseData>
	void ProcessAuthenticatedCodeRequest(const int32& ResponseCode, const FString& ContentAsString,
	                                     const TUnrealRequestStatus RequestStatus, const int64& RequestId,
	                                     const FBeamRealmHandle& RealmHandle, const FBeamAuthToken& AuthToken,
	                                     TRequestData* RequestData,
	                                     const TBeamFullResponseHandler<TRequestData*, TResponseData*>&
	                                     ResponseHandler)
	{
		StaticCheckForRequestType<TRequestData>();
		StaticCheckForResponseType<TResponseData>();

		// Get any UserSlot that matches this Pid/Auth Token, if any
		FBeamRealmUser User;
		FUserSlot UserSlot;
		FString NamespacedSlotId;
		const auto bWasMadeWithUserSlot = BeamUserSlots->GetUserDataWithRefreshTokenAndPid(AuthToken.RefreshToken, RealmHandle.Pid, User, UserSlot, NamespacedSlotId);
		const auto UserSlotLog = bWasMadeWithUserSlot ? UserSlot.Name : TEXT("Made Without UserSlot");

		// Get retry stuff	
		auto FullResponse = FBeamFullResponse<TRequestData*, TResponseData*>();

		// Sets the request id for the request
		auto Context = *InFlightRequestContexts.Find(RequestId);
		Context.ResponseCode = ResponseCode;
		Context.UserSlot = bWasMadeWithUserSlot ? UserSlot : FUserSlot("");
		FullResponse.Context = Context;

		// Store the Request's data into the full response
		FullResponse.RequestData = RequestData;

		bool bIsCancelled = InFlightRequestsCancelled.Contains(RequestId);
		// Stores whether the request was successful, error or cancelled
		if (bIsCancelled)
			FullResponse.State = RS_Cancelled;
		else
			FullResponse.State = IsSuccessfulResponse(ResponseCode) ? RS_Success : RS_Error;

		auto CurrFailedCount = InFlightFailureCount.FindChecked(RequestId);
		const auto RetryConfig = Context.RetryConfiguration;
		const auto bShouldRetryIfFail = !bIsCancelled && (RetryConfig.RetryMaxAttempt == -1 || RetryConfig.RetryMaxAttempt > CurrFailedCount);

		// Stores which attempt we are in
		FullResponse.AttemptNumber = CurrFailedCount;

		// If it was an error, we'll compute whether we should re-auth/retry based on the error data.
		bool bWillRetry = !IsSuccessfulResponse(ResponseCode) && bShouldRetryIfFail;
		bool bWillReAuth = !IsSuccessfulResponse(ResponseCode);
		// Parse the appropriate response body...
		if (FullResponse.State == RS_Success)
		{
			// Parse the response body and store it in the full response data.						
			FullResponse.SuccessData = NewObject<TResponseData>(RequestData);
			FullResponse.SuccessData->DeserializeRequestResponse(RequestData, ContentAsString);

			// Store it so wait handles can grab at it later
			InFlightResponseBodyData[Context] = FullResponse.SuccessData;
		}
		else if (FullResponse.State == RS_Error)
		{
			// Otherwise, parse the body as an error response callback and store it in the full response data.				
			FJsonObjectConverter::JsonObjectStringToUStruct(*ContentAsString, &FullResponse.ErrorData);

			// Now that we know we had an error, compute whether we should retry.
			bWillReAuth &= AUTH_ERROR_CODE_RETRY_ALLOWED.Contains(FullResponse.ErrorData.error);
			bWillRetry &= RetryConfig.HttpResponseCodes.Contains(ResponseCode) || RetryConfig.CustomErrorCodes.Contains(FullResponse.ErrorData.error);
			// We always enqueue for retry if we need the re-auth, even if we are "out of retries". That's because Re-Auth retries don't count towards the retry limit.
			bWillRetry |= bWillReAuth;

			// Store it so wait handles can grab at it later
			InFlightResponseErrorData[Context] = FullResponse.ErrorData;

			// Bump the failed count associated with this request id.
			CurrFailedCount = bWillReAuth ? CurrFailedCount : CurrFailedCount + 1;
			InFlightFailureCount[RequestId] = CurrFailedCount;

			// If we should still retry (-1 == infinite retry)
			if (bWillRetry)
			{
				// Enqueue a request to try again
				FRequestToRetry Retry;
				Retry.RequestId = RequestId;
				Retry.AuthToken = AuthToken;
				Retry.RealmHandle = RealmHandle;
				Retry.IsBlueprintCompatible = 0;
				Retry.ResponseCode = ResponseCode;
				Retry.ErrorCode = FullResponse.ErrorData.error;
				EnqueuedRetries.Enqueue(Retry);

				// Set the state to retrying instead of error.
				FullResponse.State = RS_Retrying;
			}
		}

		// Execute the handler if it's bound.			
		if (bWillRetry)
		{
			// Run callback with the Retrying state if we are going to retry AND it's not one of the re-auth errors.
			// 401 errors are a special case of errors --- we make a special re-authentication request when we get them and then follow up with the original request.
			// If the re-auth fail, this will run again but the retry configuration will be set to NOT RETRY ANYMORE.
			if (!bWillReAuth)
			{
				// We run the response handler when we error --- we assume that they switch on FullResponse.State to handle only the error cases.
				const auto bExecutedCallsiteHandler = ResponseHandler.ExecuteIfBound(FullResponse);

				// We run global handlers for this request if we are configured to always run them
				auto bRanGlobalHandlers = false;
				if (AlwaysRunGlobalHandlers || !bExecutedCallsiteHandler)
				{
					GlobalRequestErrorHandler.Broadcast(FullResponse.Context, FullResponse.ErrorData);
					const auto _ = GlobalRequestErrorCodeHandler.ExecuteIfBound(FullResponse.Context, FullResponse.ErrorData);
					bRanGlobalHandlers = true;
				}

				// We log if we are configured to do so or as a fallback if no handler is configured
				if (AlwaysLogErrorResponses || (!bExecutedCallsiteHandler && !bRanGlobalHandlers))
				{
					const auto RequestType = RequestData->GetRequestType();
					UE_LOG(LogBeamBackend, Error,
					       TEXT( "Beamable Request Failed - Retrying | REQUEST_ID=%lld, REQUEST_TYPE=%s, USER_SLOT=%s, RESPONSE_CODE=%d, NUM_FAILURES=%d, WILL_RETRY=%s, RESPONSE_BODY=%s" ),
					       RequestId, *RequestType.Name, *UserSlotLog, ResponseCode, CurrFailedCount, bWillRetry ? TEXT("true") : TEXT("false"), *ContentAsString);
				}
			}
		}
		// Only run the clean up after we are done retrying.
		else
		{
			const auto RequestType = RequestData->GetRequestType();
			const auto bExecutedCallsiteHandler = ResponseHandler.ExecuteIfBound(FullResponse);
			if (AlwaysLogCompleteResponses || !bExecutedCallsiteHandler)
			{
				// We only log the response for code if we are configured to always run it.
				if (AlwaysLogSuccessResponses && FullResponse.State == RS_Success)
				{
					UE_LOG(LogBeamBackend, Verbose, TEXT( "Beamable Request Successfull | REQUEST_ID=%lld, REQUEST_TYPE=%s, USER_SLOT=%s, RESPONSE_CODE=%d, NUM_FAILURES=%d, RESPONSE_BODY=%s" ),
					       RequestId, *RequestType.Name, *UserSlotLog, ResponseCode, CurrFailedCount, *ContentAsString);
				}

				// We log the error only if neither callback was set OR if we are configured to do so.
				if (AlwaysLogErrorResponses && FullResponse.State == RS_Error)
				{
					UE_LOG(LogBeamBackend, Error,
					       TEXT( "Beamable Request Failed | REQUEST_ID=%lld, REQUEST_TYPE=%s, USER_SLOT=%s, RESPONSE_CODE=%d, NUM_FAILURES=%d, WILL_RETRY=%s, RESPONSE_BODY=%s" ),
					       RequestId, *RequestType.Name, *UserSlotLog, ResponseCode, CurrFailedCount, bWillRetry ? TEXT("true") : TEXT("false"), *ContentAsString);
				}

				const auto bWasSuccess = FullResponse.State == RS_Success;
				if (FullResponse.State == RS_Cancelled)
				{
					UE_LOG(LogBeamBackend, Warning, TEXT("Beamable Request Canceled | REQUEST_ID=%lld, REQUEST_TYPE=%s, USER_SLOT=%s, WAS_SUCCESS=%s, NUM_FAILURES=%d" ),
					       RequestId, *RequestType.Name, *UserSlotLog, bWasSuccess ? TEXT("true") : TEXT("false"), InFlightFailureCount.FindRef(RequestId));
				}
				else
				{
					UE_LOG(LogBeamBackend, Verbose, TEXT( "Beamable Request Completed | REQUEST_ID=%lld, REQUEST_TYPE=%s, USER_SLOT=%s, WAS_SUCCESS=%s, NUM_FAILURES=%d" ),
					       RequestId, *RequestType.Name, *UserSlotLog, bWasSuccess ? TEXT("true") : TEXT("false"), InFlightFailureCount.FindRef(RequestId));
				}
			}

			// Update the context's status to completed so we can clean it up in the next tick of TickCleanUpRequests if no one depends on it.
			Context.BeamStatus = AS_Completed;
			InFlightRequestContexts[RequestId] = Context;
		}
	}

	/*	 
		GENERIC-BEAM REQUEST FUNCTION
	*/

	/**
	 * @brief Creates a request that will not target a Beamable server and prepares it to be sent out. This does not bind the lambda --- see any auto-generated API to understand how to manually make
	 * a Beamable request.
	 * 
	 * @tparam TRequestData A type that implements the FBeamBaseRequest struct.
	 * @param OutRequestId  The RequestId assigned to the returned TUnrealRequest.	 
	 * @param RetryConfig The Retry Configuration for this request. 
	 * @param RequestData An instance of the request type.
	 * 
	 * @return A TUnrealRequest object that will be tracked by UBeamBackend.
	 */
	TUnrealRequestPtr CreateGenericBeamRequest(int64& OutRequestId, const FBeamRetryConfig& RetryConfig, const UGenericBeamRequest* RequestData);

	/*	 
		ROUTING KEYS
	*/

	/**
	 * @brief Builds the RoutingKeyMap for a particular set of services/routing targets and set them as the current map for all slots. 
	 */
	void SetRoutingKeyMap(TArray<FString> BeamoIds, TArray<FString> TargetKeys);

	/**
	 * @brief Builds the RoutingKeyMap for a particular set of services/routing targets and set them as the current map for a particular slot. 
	 */
	void SetRoutingKeyMap(FUserSlot Slot, TArray<FString> BeamoIds, TArray<FString> TargetKeys);

	/**
	 * @brief Sets a routing map string to be the routing map used for all slots, dedicated servers and non-authenticated requests.
	 */
	void SetRoutingKeyMap(FString RoutingKeyMap);

	/**
	 * @brief Sets a routing map string to be the routing map used for a particular slot. Setting the route for UBeamCoreSettings::GetOwnerPlayerSlot()'s, also sets it for dedicated servers
	 * and non-authenticated requests.
	 */
	void SetRoutingKeyMap(FUserSlot ForSlot, FString RoutingKeyMap);

	/*	 
		UTILITIES
	*/

	UFUNCTION(BlueprintCallable, Category="Beam|Requests", DisplayName="Did Timeout", meta=(ExpandBoolAsExecs="ReturnValue"))
	static bool IsRetryingTimeout(FBeamRequestContext Ctx);

	static bool IsSuccessfulResponse(int32 ResponseCode);

private:
	void UpdateResponseCache(const FRequestType& RequestType, const UObject* CallingContext, const FHttpRequestPtr& Request, const FString& Content);
	static bool ExtractDataFromResponse(const FHttpRequestPtr Request, const FHttpResponsePtr Response, const bool bWasRequestCompleted, EHttpRequestStatus::Type& OutRequestStatus,
	                                    int32& OutResponseCode, FString& OutResponseBody);

	/**
    ____           ___            __           __   _____                               
   / __ \___  ____/ (_)________ _/ /____  ____/ /  / ___/___  ______   _____  __________
  / / / / _ \/ __  / / ___/ __ `/ __/ _ \/ __  /   \__ \/ _ \/ ___/ | / / _ \/ ___/ ___/
 / /_/ /  __/ /_/ / / /__/ /_/ / /_/  __/ /_/ /   ___/ /  __/ /   | |/ /  __/ /  (__  ) 
/_____/\___/\__,_/_/\___/\__,_/\__/\___/\__,_/   /____/\___/_/    |___/\___/_/  /____/  
                                                                                        
	 */
public:
	/**
	 * @brief This must be set if DedicatedServerExecuteRequestImpl will be used (it'll use this to sign requests). When running in insecure devices (non-dedicated servers),
	 * this must always be empty.
	 */
	FString RealmSecret;

	/**
	 * @brief Used as delegate set in ExecuteRequestDelegate when running as a dedicated server. 
	 */
	UFUNCTION()
	void DedicatedServerExecuteRequestImpl(int64 ActiveRequestId, const UObject* CallingContext);

	/**
	 * Overrides the @link HEADER_AUTHORIZATION @endlink for the given request.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam")
	static void OverrideRequestAuthorization(TScriptInterface<IBeamBaseRequestInterface> Interface, FString AccessToken);

	/**
	 * Overrides the @link HEADER_GAMERTAG @endlink for the given request.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam")
	static void OverrideRequestGamerTag(TScriptInterface<IBeamBaseRequestInterface> Interface, FBeamGamerTag GamerTag);

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
public:
	/**
	* @brief Retry configuration data. Can be overriden at the request level. 
	*/
	UPROPERTY(BlueprintReadWrite, Category="Beam|Config")
	FBeamRetryConfig DefaultRetryConfig;

	/**
	 * @brief Key is the request struct type's GetName() call. Value can be set by users. 
	 */
	UPROPERTY(BlueprintReadOnly, Category="Beam|Config")
	TMap<FRequestType, FBeamRetryConfig> PerTypeRetryConfigs;

	/**
	 * @brief Key is the request struct type's GetName() call and the UserSlotId for which this configuration is set separated by '₢'.
	 * Value can be set by users.
	 */
	UPROPERTY(BlueprintReadOnly, Category="Beam|Config")
	TMap<FString, FBeamRetryConfig> PerUserPerTypeRetryConfig;

	/**
	 * @brief Key is the UserSlotId for which this configuration is set. Value can be set by users.
	 */
	UPROPERTY(BlueprintReadOnly, Category="Beam|Config")
	TMap<FUserSlot, FBeamRetryConfig> PerUserRetryConfig;

	/**
	 * @brief Gets the retry configuration associated with all requests of this type. 
	 * @param RequestType Any FBeamRequest::StaticStruct()->GetName() (basically the name of any request struct).
	 * In BP-Land, you can call a static function to get one of these.
	 * 
	 * @param Config The RetryConfiguration.
	 * 
	 * @return True, if the returned config was the one you asked for. False, if a fallback was returned (happens if you call this without ever having set the retry configuration).
	 */
	UFUNCTION(BlueprintGetter, Category="Beam|Config", meta=(AutoCreateRefTerm="RequestType"))
	bool GetRetryConfigForRequestType(const FRequestType& RequestType, FBeamRetryConfig& Config) const;

	/**
	 * @brief Gets the retry configuration associated with all requests made by this user.
	 * @param Slot Any valid UserSlot. 
	 * @param Config The RetryConfiguration.
	 * @return True, if the returned config was the one you asked for. False, if a fallback was returned (happens if you call this without ever having set the retry configuration).
	 */
	UFUNCTION(BlueprintGetter, Category="Beam|Config", meta=(AutoCreateRefTerm="Slot"))
	bool GetRetryConfigForUserSlot(const FUserSlot& Slot, FBeamRetryConfig& Config) const;

	/**
	 * @brief Gets the retry configuration associated with all requests of this type made by the given user slot.
	 * @param RequestType Any FBeamRequest::StaticStruct()->GetName() (basically the name of any request struct).
	 * @param Slot Any valid UserSlot. 
	 * @param Config The RetryConfiguration.
	 * @return True, if the returned config was the one you asked for. False, if a fallback was returned (happens if you call this without ever having set the retry configuration).
	 */
	UFUNCTION(BlueprintGetter, Category="Beam|Config", meta=(AutoCreateRefTerm="RequestType,Slot"))
	bool GetRetryConfigForUserSlotAndRequestType(const FRequestType& RequestType, const FUserSlot& Slot,
	                                             FBeamRetryConfig& Config) const;


	/**
	 * @brief Sets the retry configuration for a given request type's requests.
	 * @param RequestType The Request type whose retry configuration you wish to reset.
	 * @param RetryConfig The retry config you wish that request type to use.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Config", meta=(AutoCreateRefTerm="RequestType"))
	void SetRetryConfigForRequestType(const FRequestType& RequestType, const FBeamRetryConfig& RetryConfig);

	/**
	 * @brief Sets the retry configuration for a given user's requests. 
	 * @param Slot The user slot whose retry configuration you wish to set.
	 * @param RetryConfig The retry config you wish that user to use.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Config", meta=(AutoCreateRefTerm="Slot"))
	void SetRetryConfigForUserSlot(const FUserSlot Slot, const FBeamRetryConfig& RetryConfig);

	/**
	 * @brief Sets the retry configuration for a given user + request type combination's requests.
	 * @param Slot The user slot whose retry configuration you wish to set.
	 * @param RequestType The Request type whose retry configuration you wish to reset. 
	 * @param RetryConfig The retry config you wish that user + request type combination to use.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Config", meta=(AutoCreateRefTerm="RequestType,Slot"))
	void SetRetryConfigForUserSlotAndRequestType(const FUserSlot& Slot, const FRequestType& RequestType,
	                                             const FBeamRetryConfig& RetryConfig);

	/**
	 * @brief Resets the Retry Configuration for the given request type  back to the default retry configuration.
	 * @param RequestType The Request type whose retry configuration you wish to reset.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Config", meta=(AutoCreateRefTerm="RequestType"))
	void ResetRetryConfigForRequestType(const FRequestType& RequestType);

	/**
	 * @brief Resets the Retry Configuration for the given user back to the default retry configuration.
	 * @param Slot The user slot whose retry configuration you wish to reset.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Config", meta=(AutoCreateRefTerm="Slot"))
	void ResetRetryConfigForUserSlot(const FUserSlot& Slot);

	/**
	 * @brief Resets the Retry Configuration for the given user and request type combination back to the default retry configuration.	 
	 * @param Slot The user slot whose retry configuration you wish to reset.
	 * @param RequestType The Request type whose retry configuration you wish to reset.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Config", meta=(AutoCreateRefTerm="RequestType,Slot"))
	void ResetRetryConfigForUserSlotAndRequestType(const FUserSlot& Slot, const FRequestType& RequestType);

	/**
	 
	_____                            _   _       _ _         
  / ____|                          | | (_)     (_) |        
 | |     ___  _ __  _ __   ___  ___| |_ ___   ___| |_ _   _ 
 | |    / _ \| '_ \| '_ \ / _ \/ __| __| \ \ / / | __| | | |
 | |___| (_) | | | | | | |  __/ (__| |_| |\ V /| | |_| |_| |
  \_____\___/|_| |_|_| |_|\___|\___|\__|_| \_/ |_|\__|\__, |
													   __/ |
													  |___/ 
	 */


private:
	/**
	 * This is called in each of the Make______RequestProcess lambda to ensure that, after we leave PIE, every inflight request's response is automatically ignored when it arrives.
	 * Invoking the callbacks are likely to result in crashes since PIE is now closed and its memory is deallocated. 
	 */
	bool HandlePIESessionRequestGuard(TUnrealRequestPtr Request, int64 RequestId = -1);
};
