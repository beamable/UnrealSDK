// Fill out your copyright notice in the Description page of Project Settings.


#include "BeamBackend/BeamBackend.h"

#include "BeamBackendTestCallbacks.h"
#include "BeamCoreSettings.h"
#include "BeamLogging.h"
#include "HttpModule.h"
#include "JsonObjectConverter.h"
#include "Interfaces/IHttpResponse.h"
#include "Misc/DefaultValueHelper.h"
#include "BeamBackend/BeamCustomRequests.h"
#include "BeamBackend/ResponseCache/BeamResponseCache.h"

DECLARE_STATS_GROUP(TEXT("BeamBackend"), STATGROUP_BeamBackend, STATCAT_Backend)

DECLARE_DWORD_ACCUMULATOR_STAT(TEXT("RequestsStarted"), STATID_RequestStarted, STATGROUP_BeamBackend)
DECLARE_DWORD_ACCUMULATOR_STAT(TEXT("RequestsSucceeded"), STATID_RequestSucceeded, STATGROUP_BeamBackend)
DECLARE_DWORD_ACCUMULATOR_STAT(TEXT("RequestsFailed"), STATID_RequestFailed, STATGROUP_BeamBackend)
DECLARE_DWORD_ACCUMULATOR_STAT(TEXT("RequestsCancelled"), STATID_RequestCancelled, STATGROUP_BeamBackend)


const FString UBeamBackend::HEADER_CONTENT_TYPE = FString(TEXT("Content-Type"));
const FString UBeamBackend::HEADER_ACCEPT = FString(TEXT("Accept"));
const FString UBeamBackend::HEADER_VALUE_ACCEPT_CONTENT_TYPE = FString(TEXT("application/json"));
const FString UBeamBackend::HEADER_AUTHORIZATION = FString(TEXT("Authorization"));
const FString UBeamBackend::HEADER_REQUEST_SCOPE = FString(TEXT("X-DE-SCOPE"));
const FString UBeamBackend::HEADER_VALUE_AUTHORIZATION = FString(TEXT("Bearer {0}"));
const FString UBeamBackend::HEADER_CLIENT_ID = FString(TEXT("X-KS-CLIENTID"));
const FString UBeamBackend::HEADER_PROJECT_ID = FString(TEXT("X-KS-PROJECTID"));
const TArray<FString> UBeamBackend::AUTH_ERROR_CODE_RETRY_ALLOWED = TArray<FString>{TEXT("InvalidTokenError"), TEXT("TokenValidationError"), TEXT("ExpiredTokenError")};

void UBeamBackend::Initialize(FSubsystemCollectionBase& Collection)
{
	UE_LOG(LogBeamBackend, Warning, TEXT("Initializing UBeamBackend Subsystem!"));

	// Initializing InFlightRequestID to -1 since we increment, then use it.
	InFlightRequestId = new long();
	*InFlightRequestId = -1;

	// Set up the retry ticking to run at 15 ticks / second TODO: expose these as settings
	RetryQueueTickHandle = FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateUObject(this, &UBeamBackend::TickRetryQueue), 4 / 60);

	// Set up the cleanup ticking to run at 1 tick every 5 minutes TODO: expose these as settings
	CleanupRequestsTickHandle = FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateUObject(this, &UBeamBackend::TickCleanUp), 60 * 5);

	// Get subsystem dependency...
	BeamEnvironment = Cast<UBeamEnvironment>(Collection.InitializeDependency(UBeamEnvironment::StaticClass()));
	BeamUserSlots = Cast<UBeamUserSlots>(Collection.InitializeDependency(UBeamUserSlots::StaticClass()));

	// Assumes we are connected to the internet until first request fails.
	CurrentConnectivityStatus = FBeamConnectivity{true, FDateTime::UtcNow().GetTicks()};

	// Initialize a buffer of 16 simultaneous requests.
	InFlightRequests.Reserve(16);
	InFlightRequestContexts.Reserve(16);
	InFlightFailureCount.Reserve(16);
	InFlightRequestsCancelled.Reserve(16);
	InFlightProcessingRequests.Reserve(16);


	// Binds the default implementation to the DefaultExecuteRequestImpl method of the subsystem.
	ExecuteRequestDelegate.BindUFunction(this, "DefaultExecuteRequestImpl");

	// Prepares the default retry configuration	
	DefaultRetryConfig = GetDefault<UBeamCoreSettings>()->FallbackRetryConfiguration;
	AlwaysRunGlobalHandlers = GetDefault<UBeamCoreSettings>()->AlwaysRunGlobalErrorHandlers;
	AlwaysLogSuccessResponses = GetDefault<UBeamCoreSettings>()->AlwaysLogSuccessResponses;
	AlwaysLogErrorResponses = GetDefault<UBeamCoreSettings>()->AlwaysLogErrorResponses;
	AlwaysLogCompleteResponses = GetDefault<UBeamCoreSettings>()->AlwaysLogCompletedResponses;
}

void UBeamBackend::Deinitialize()
{
	FTSTicker::GetCoreTicker().RemoveTicker(RetryQueueTickHandle);

	FTSTicker::GetCoreTicker().RemoveTicker(CleanupRequestsTickHandle);

	delete InFlightRequestId;
}


template <typename TRequestData>
void UBeamBackend::StaticCheckForRequestType()
{
	static_assert(TIsDerivedFrom<TRequestData, IBeamBaseRequestInterface>::Value, "TRequestData must be a IBeamBaseRequestInterface type.");
	static_assert(TIsDerivedFrom<TRequestData, UObject>::Value, "TRequestData must be a UObject type.");
}

template <typename TResponseData>
void UBeamBackend::StaticCheckForResponseType()
{
	static_assert(TIsDerivedFrom<TResponseData, IBeamBaseResponseBodyInterface>::Value, "TResponseData must be a IBeamBaseResponseBodyInterface type.");	
	static_assert(TIsDerivedFrom<TResponseData, UObject>::Value, "TResponseData must be a UObject type.");
}


void UBeamBackend::TryTriggerRequestCompleteDelegates(const int64& RequestId)
{
	if (InFlightRequestContexts.Find(RequestId)->BeamStatus == Completed)
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Checking OnRequestIdCompleted Delegates | REQUEST_ID=%d, DELEGATE_COUNT=%d"), RequestId, TickOnRequestIdCompletedDelegates.Num());
		for (const auto& OnRequestIdCompleted : TickOnRequestIdCompletedDelegates)
		{
			const auto bDidRun = OnRequestIdCompleted.ExecuteIfBound(RequestId);
			UE_LOG(LogBeamBackend, Verbose, TEXT("Tried to invoke OnRequestIdCompleted Delegate | REQUEST_ID=%d, DID_RUN=%s"), RequestId, bDidRun ? TEXT("true") : TEXT("false"));
		}
	}
}

void UBeamBackend::UpdateConnectivity(const FBeamRequestContext& RequestContext, const TUnrealRequestStatus RequestStatus, const FRequestType RequestType)
{
	if (RequestStatus == EHttpRequestStatus::Succeeded || RequestStatus == EHttpRequestStatus::Failed)
	{
		if (!CurrentConnectivityStatus.IsConnected)
		{
			GlobalConnectivityChangedHandler.Broadcast(RequestContext, RequestType, true);
			GlobalConnectivityChangedCodeHandler.Broadcast(RequestContext, RequestType, true);
		}
		CurrentConnectivityStatus.IsConnected = true;
		CurrentConnectivityStatus.LastTimeSinceSuccessfulRequest = FDateTime::UtcNow().GetTicks();
	}
	else if (RequestStatus == EHttpRequestStatus::Failed_ConnectionError)
	{
		if (CurrentConnectivityStatus.IsConnected == true)
		{
			GlobalConnectivityChangedHandler.Broadcast(RequestContext, RequestType, false);
			GlobalConnectivityChangedCodeHandler.Broadcast(RequestContext, RequestType, false);
		}
		CurrentConnectivityStatus.IsConnected = false;
	}
}

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


template <class TRequestData>
TUnrealRequestPtr UBeamBackend::CreateRequest(int64& OutRequestId, const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const TRequestData* RequestData)
{
	StaticCheckForRequestType<TRequestData>();

	// Ensures we get a valid Next Id even if requests get made from multiple threads.
	int64 ReqId;
	auto Req = CreateUnpreparedRequest(ReqId, RetryConfig);
	PrepareBeamableRequestToRealm(Req, TargetRealm);
	PrepareBeamableRequestVerbRouteBody<TRequestData>(Req, RequestData, BeamEnvironment->GetAPIUrl());

	const auto RequestContext = FBeamRequestContext{ReqId, RetryConfig, TargetRealm, -1, FUserSlot(""), None};

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

template <typename TRequestData>
TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64& OutRequestId, const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                                           const TRequestData* RequestData)
{
	StaticCheckForRequestType<TRequestData>();

	// Ensures we get a valid Next Id even if requests get made from multiple threads.
	int64 ReqId;
	auto Req = CreateUnpreparedRequest(ReqId, RetryConfig);
	PrepareBeamableRequestToRealmWithAuthToken(Req, TargetRealm, AuthToken);
	PrepareBeamableRequestVerbRouteBody<TRequestData>(Req, RequestData, BeamEnvironment->GetAPIUrl());

	// Add to the InFlight request list
	FUserSlot OutUserSlot;
	FBeamRealmUser OutUserData;
	BeamUserSlots->GetUserDataWithRefreshTokenAndPid(AuthToken.RefreshToken, TargetRealm.Pid, OutUserData, OutUserSlot);

	const auto RequestContext = FBeamRequestContext{ReqId, RetryConfig, TargetRealm, -1, OutUserSlot, None};

	// Keep track of this request and it's data. 
	InFlightRequestContexts.Add(ReqId, RequestContext);
	InFlightRequestData.Add(RequestContext, TScriptInterface<IBeamBaseRequestInterface>(const_cast<TRequestData*>(RequestData)));

	// Store make sure we have a slot waiting for the response/error value to be added
	InFlightResponseBodyData.Add(RequestContext, nullptr);
	InFlightResponseErrorData.Add(RequestContext, FBeamErrorResponse{});

	OutRequestId = ReqId;
	return Req;
}

TUnrealRequestPtr UBeamBackend::CreateUnpreparedRequest(int64& OutRequestId, const FBeamRetryConfig& RetryConfig)
{
	// Ensures we get a valid Next Id even if requests get made from multiple threads.
	const auto NextId = _InterlockedIncrement(InFlightRequestId);
	OutRequestId = NextId;

	// Creates a request with the specified timeout.
	auto Req = FHttpModule::Get().CreateRequest();
	Req->SetTimeout(RetryConfig.Timeout);

	// Prepares the Backend system to handle this request.
	InFlightRequests.Add(OutRequestId, Req);
	InFlightFailureCount.Add(OutRequestId, 0);
	return Req;
}

void UBeamBackend::DiscardUnsentRequest(const int64& RequestId)
{
	InFlightRequests.Remove(RequestId);
	InFlightRequestContexts.Remove(RequestId);
	InFlightFailureCount.Remove(RequestId);
}


void UBeamBackend::CancelRequest(int64 RequestId)
{
	if (!InFlightRequests.Contains(RequestId) || InFlightRequests.FindChecked(RequestId)->GetStatus() == EHttpRequestStatus::NotStarted)
		DiscardUnsentRequest(RequestId);
	else if (!InFlightRequestsCancelled.Contains(RequestId))
		InFlightRequestsCancelled.Add(RequestId);
}

bool UBeamBackend::IsRequestCancelled(int64 RequestId) const
{
	return InFlightRequestsCancelled.Contains(RequestId);
}

int UBeamBackend::GetRequestFailureCount(int64 RequestId) const
{
	if (InFlightFailureCount.Contains(RequestId))
		InFlightFailureCount[RequestId];

	return 0;
}

bool UBeamBackend::IsConnected() const
{
	return CurrentConnectivityStatus.IsConnected;
}

void UBeamBackend::PrepareBeamableRequestToRealm(const TUnrealRequestPtr& Request, const FBeamRealmHandle& RealmHandle)
{
	Request->SetHeader(HEADER_CONTENT_TYPE, HEADER_VALUE_ACCEPT_CONTENT_TYPE);
	Request->SetHeader(HEADER_ACCEPT, HEADER_VALUE_ACCEPT_CONTENT_TYPE);

	const auto Cid = RealmHandle.Cid;
	const auto Pid = RealmHandle.Pid;

	if (!Cid.AsString.IsEmpty())
		Request->SetHeader(HEADER_CLIENT_ID, Cid.AsString);

	if (!Pid.AsString.IsEmpty())
		Request->SetHeader(HEADER_PROJECT_ID, Pid.AsString);

	UE_LOG(LogBeamBackend, Verbose, TEXT("Request Preparation - Headers: CID=%s PID=%s"), *Request->GetHeader(HEADER_CLIENT_ID), *Request->GetHeader(HEADER_PROJECT_ID));
}

void UBeamBackend::PrepareBeamableRequestToRealmWithAuthToken(const TUnrealRequestPtr& Request,
                                                              const FBeamRealmHandle& RealmHandle,
                                                              const FBeamAuthToken& AuthToken)
{
	PrepareBeamableRequestToRealm(Request, RealmHandle);

	const auto AuthTokenHeader = FString::Format(*HEADER_VALUE_AUTHORIZATION, {AuthToken.AccessToken});
	Request->SetHeader(HEADER_AUTHORIZATION, AuthTokenHeader);
	const auto ScopeHeader = RealmHandle.Pid.AsString.IsEmpty() ? RealmHandle.Cid.AsString : FString::Format(TEXT("{0}.{1}"), {RealmHandle.Cid.AsString, RealmHandle.Pid.AsString});
	Request->SetHeader(HEADER_REQUEST_SCOPE, ScopeHeader);

	UE_LOG(LogBeamBackend, Verbose, TEXT("Request Preparation - Auth: AUTH_HEADER=%s, SCOPE_HEADER=%s"), *AuthTokenHeader, *ScopeHeader);
}


template <typename TRequestData>
void UBeamBackend::PrepareBeamableRequestVerbRouteBody(const TUnrealRequestPtr& Request, const TRequestData* RequestData, const FString& TargetBeamableUrl)
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

	UE_LOG(LogBeamBackend, Verbose, TEXT("Request Preparation - Verb, Route and Body: VERB=%s ROUTE=%s, BODY=%s"), *Verb, *Route, *Body);
}


template <typename TRequestData, typename TResponseData, typename TSuccessCallback, typename TErrorCallback, typename TCompleteCallback>
FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor(const int64& RequestId, TRequestData* RequestData,
                                                                  TSuccessCallback OnSuccess, TErrorCallback OnError, TCompleteCallback OnComplete,
                                                                  const UObject* CallingContext)
{
	StaticCheckForRequestType<TRequestData>();
	StaticCheckForResponseType<TResponseData>();

	UE_LOG(LogBeamBackend, Verbose, TEXT("Request Preparation - Processor Preparation: Making Blueprint Un-authenticated Request Processor"));

	FBeamRequestProcessor BoundResponseHandler(
		// Capture, by-value, the Backend system, request id for this request and request data --- these are plain structs with no allocations.
		[this, RequestId, RequestData, OnSuccess, OnError, OnComplete, CallingContext]

		// This just passes the captured data along to the Process function (we do this so we can unit test the process function in isolation).
	(const FHttpRequestPtr Request, const FHttpResponsePtr Response, const bool)
		{
			if (!Response.IsValid())
			{
				UE_LOG(LogBeamBackend, Error, TEXT("Beamable Request Failed Parsing Response | REQUEST_ID=%lld"), RequestId);
				return;
			}
			UE_LOG(LogBeamBackend, Verbose, TEXT("Beamable Request Parsed Response | REQUEST_ID=%lld"), RequestId);
			
			// Get the response contents
			const auto ResponseCode = Response->GetResponseCode();
			const auto ContentAsString = Response->GetContentAsString();
			const auto RequestStatus = Request->GetStatus();

			// If it was a success, we try to cache the response.
			if (ResponseCode == 200)
				GEngine->GetEngineSubsystem<UBeamResponseCache>()->UpdateResponseCache(RequestData->GetRequestType(), CallingContext, Request, ContentAsString);

			RunBlueprintRequestProcessor<TRequestData, TResponseData, TSuccessCallback, TErrorCallback, TCompleteCallback>
				(ResponseCode, ContentAsString, RequestStatus, RequestId, RequestData, OnSuccess, OnError, OnComplete);
		});

	// We return the build processor function so the API request function can bind it to UnrealHttpRequest's response handler delegate.
	return BoundResponseHandler;
}

template <typename TRequestData, typename TResponseData, typename TSuccessCallback, typename TErrorCallback, typename TCompleteCallback>
void UBeamBackend::RunBlueprintRequestProcessor(const int32& ResponseCode, const FString& ContentAsString, const TUnrealRequestStatus RequestStatus,
                                                const int64& RequestId, TRequestData* RequestData,
                                                TSuccessCallback OnSuccess, TErrorCallback OnError, TCompleteCallback OnComplete)
{
	ProcessBlueprintRequest<TRequestData, TResponseData, TSuccessCallback, TErrorCallback, TCompleteCallback>
		(ResponseCode, ContentAsString, RequestStatus, RequestId, RequestData, OnSuccess, OnError, OnComplete);

	// Run any registered callback for handling Request completion.
	TryTriggerRequestCompleteDelegates(RequestId);
}


template <typename TRequestData, typename TResponseData, typename TSuccessCallback, typename TErrorCallback, typename TCompleteCallback>
void UBeamBackend::ProcessBlueprintRequest(const int32& ResponseCode, const FString& ContentAsString, const TUnrealRequestStatus RequestStatus,
                                           const int64& RequestId, TRequestData* RequestData,
                                           TSuccessCallback OnSuccess, TErrorCallback OnError, TCompleteCallback OnComplete)
{
	StaticCheckForRequestType<TRequestData>();
	StaticCheckForResponseType<TResponseData>();

	// Update the context to pass into the response callbacks.
	auto Context = InFlightRequestContexts.Find(RequestId);
	Context->ResponseCode = ResponseCode;


	// If the request was cancelled, we'll only run the OnComplete call 
	if (InFlightRequestsCancelled.Contains(RequestId))
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Ignoring Request Response since it was cancelled. REQUEST_ID=%d"), RequestId);

		// Execute the handler if it's bound.
		const auto bExecutedCallsiteHandler = OnComplete.ExecuteIfBound(*Context, RequestData);
		if (AlwaysLogCompleteResponses || !bExecutedCallsiteHandler)
		{
			UE_LOG(LogBeamBackend, Display, TEXT("Beamable Request Canceled | REQUEST_ID=%d, NUM_FAILURES=%d"), RequestId, InFlightFailureCount.FindRef(RequestId));
		}

		// Update the context's status to completed so we can clean it up in the next tick of TickCleanUpRequests if no one depends on it.
		Context->BeamStatus = Completed;

		return;
	}

	// Stores whether or not the request was successful
	const auto bWasSuccess = ResponseCode == 200;


	// Get retry stuff
	const auto CurrFailedCount = InFlightFailureCount.FindChecked(RequestId);
	const auto RetryConfig = Context->RetryConfiguration;
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
		InFlightResponseBodyData[*Context] = SuccessData;

		// Run the callsite handler
		const auto ExecutedCallsiteHandler = OnSuccess.ExecuteIfBound(*Context, RequestData, SuccessData);

		// We only log the response if no callsite is given or if we are configured to always run it.
		if (AlwaysLogSuccessResponses || !ExecutedCallsiteHandler)
		{
			UE_LOG(LogBeamBackend, Display, TEXT("Beamable Request Successfull | REQUEST_ID=%d, RESPONSE_CODE=%d, NUM_FAILURES=%d, RESPONSE_BODY=%s"), RequestId, ResponseCode, CurrFailedCount,
			       *ContentAsString);
		}
	}
	else
	{
		// Otherwise, parse the body as an error response callback and store it in the full response data.
		FBeamErrorResponse ErrorData;
		FJsonObjectConverter::JsonObjectStringToUStruct(*ContentAsString, &ErrorData);

		// Now that we know we had an error, compute whether or not we should retry.
		bWillRetry &= RetryConfig.HttpResponseCodes.Contains(ResponseCode) || RetryConfig.CustomErrorCodes.Contains(ErrorData.error);

		// Store it so wait handles can grab at it later
		InFlightResponseErrorData[*Context] = ErrorData;

		// Bump the failed count associated with this request id.					
		InFlightFailureCount[RequestId] = CurrFailedCount + 1;

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
		const auto ExecutedCallsiteHandler = OnError.ExecuteIfBound(*Context, RequestData, ErrorData);

		// We fallback to global handler only if we didn't run the callsite one OR if we are configured to always run it.
		bool bExecutedGlobalHandler = false;
		if (AlwaysRunGlobalHandlers || !ExecutedCallsiteHandler && (GlobalRequestErrorHandler.IsBound() || GlobalRequestErrorCodeHandler.IsBound()))
		{
			GlobalRequestErrorHandler.Broadcast(*Context, ErrorData);
			const auto _ = GlobalRequestErrorCodeHandler.ExecuteIfBound(*Context, ErrorData);

			bExecutedGlobalHandler = true;
		}

		// We log the error only if neither callback was set OR if we are configured to do so.
		if (AlwaysLogErrorResponses || !bExecutedGlobalHandler && !ExecutedCallsiteHandler)
		{
			UE_LOG(LogBeamBackend, Error, TEXT("Beamable Request Failed | REQUEST_ID=%d, RESPONSE_CODE=%d, NUM_FAILURES=%d, WILL_RETRY=%s, RESPONSE_BODY=%s"), RequestId, ResponseCode,
			       CurrFailedCount,
			       bWillRetry ? TEXT("true") : TEXT("false"), *ContentAsString);
		}
	}

	// Clean up from InFlightRequests, only if we are not meant to retry it.
	if (bWasSuccess || !bWillRetry)
	{
		// Update Connectivity Status
		UpdateConnectivity(*Context, RequestStatus, FRequestType{TRequestData::StaticClass()->GetName()});

		// Execute the handler if it's bound.
		const auto bExecutedCallsiteHandler = OnComplete.ExecuteIfBound(*Context, RequestData);
		if (AlwaysLogCompleteResponses || !bExecutedCallsiteHandler)
		{
			UE_LOG(LogBeamBackend, Display, TEXT("Beamable Request Completed | REQUEST_ID=%d, RESPONSE_CODE=%d, WAS_SUCCESS=%s, NUM_FAILURES=%d"),
			       RequestId, ResponseCode, bWasSuccess ? TEXT("true") : TEXT("false"), CurrFailedCount);
		}

		// Update the context's status to completed so we can clean it up in the next tick of TickCleanUpRequests if no one depends on it.
		Context->BeamStatus = Completed;
	}
}


template <typename TRequestData, typename TResponseData, typename TSuccessCallback, typename TErrorCallback, typename TCompleteCallback>
FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor(const int64& RequestId, const FBeamRealmHandle& RealmHandle, const FBeamAuthToken& AuthToken,
                                                                               TRequestData* RequestData, TSuccessCallback OnSuccess, TErrorCallback OnError, TCompleteCallback OnComplete,
                                                                               const UObject* CallingContext)
{
	StaticCheckForRequestType<TRequestData>();
	StaticCheckForResponseType<TResponseData>();

	UE_LOG(LogBeamBackend, Verbose, TEXT("Request Preparation - Processor Preparation: Making Blueprint Authenticated Request Processor"));

	FBeamRequestProcessor BoundResponseHandler(
		// Capture, by-value, the Backend system, request id for this request and request data --- these are plain structs with no allocations.
		[this, RequestId, AuthToken, RealmHandle, RequestData, OnSuccess, OnError, OnComplete, CallingContext]

		// This just passes the captured data along to the Process function (we do this so we can unit test the process function in isolation).
	(const FHttpRequestPtr Request, const FHttpResponsePtr Response, bool)
		{
			if (!Response.IsValid())
			{
				UE_LOG(LogBeamBackend, Error, TEXT("Beamable Request Failed Parsing Response | REQUEST_ID=%lld"), RequestId);
				return;
			}
			UE_LOG(LogBeamBackend, Verbose, TEXT("Beamable Request Parsed Response | REQUEST_ID=%lld"), RequestId);

			// Get the response contents
			const auto ResponseCode = Response->GetResponseCode();
			const auto ContentAsString = Response->GetContentAsString();
			const auto RequestStatus = Request->GetStatus();

			// If it was a success, we try to cache the response.
			if (ResponseCode == 200)
				GEngine->GetEngineSubsystem<UBeamResponseCache>()->UpdateResponseCache(RequestData->GetRequestType(), CallingContext, Request, ContentAsString);

			RunAuthenticatedBlueprintRequestProcessor<TRequestData, TResponseData, TSuccessCallback, TErrorCallback, TCompleteCallback>
				(ResponseCode, ContentAsString, RequestStatus, RequestId, RealmHandle, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		});

	// We return the build processor function so the API request function can bind it to UnrealHttpRequest's response handler delegate.
	return BoundResponseHandler;
}

template <typename TRequestData, typename TResponseData, typename TSuccessCallback, typename TErrorCallback, typename TCompleteCallback>
void UBeamBackend::RunAuthenticatedBlueprintRequestProcessor(const int32& ResponseCode, const FString& ContentAsString, const TUnrealRequestStatus RequestStatus,
                                                             const int64& RequestId, const FBeamRealmHandle& RealmHandle, const FBeamAuthToken& AuthToken,
                                                             TRequestData* RequestData, TSuccessCallback OnSuccess, TErrorCallback OnError, TCompleteCallback OnComplete)
{
	ProcessAuthenticatedBlueprintRequest<TRequestData, TResponseData, TSuccessCallback, TErrorCallback, TCompleteCallback>
		(ResponseCode, ContentAsString, RequestStatus, RequestId, RealmHandle, AuthToken, RequestData, OnSuccess, OnError, OnComplete);

	// Run any registered callback for handling Request completion.
	TryTriggerRequestCompleteDelegates(RequestId);
}

template <typename TRequestData, typename TResponseData, typename TSuccessCallback, typename TErrorCallback, typename TCompleteCallback>
void UBeamBackend::ProcessAuthenticatedBlueprintRequest(const int32& ResponseCode, const FString& ContentAsString, const TUnrealRequestStatus RequestStatus,
                                                        const int64& RequestId, const FBeamRealmHandle& RealmHandle, const FBeamAuthToken& AuthToken,
                                                        TRequestData* RequestData, TSuccessCallback OnSuccess, TErrorCallback OnError, TCompleteCallback OnComplete)
{
	StaticCheckForRequestType<TRequestData>();
	StaticCheckForResponseType<TResponseData>();

	// Get any UserSlot that matches this Pid/Auth Token, if any		
	FBeamRealmUser User;
	FUserSlot UserSlot;
	const auto bWasMadeWithUserSlot = BeamUserSlots->GetUserDataWithRefreshTokenAndPid(AuthToken.RefreshToken, RealmHandle.Pid, User, UserSlot);

	// Create the context to pass into the callbacks	
	auto Context = InFlightRequestContexts.Find(RequestId);
	Context->ResponseCode = ResponseCode;
	Context->UserSlot = bWasMadeWithUserSlot ? UserSlot : FUserSlot("");

	// If the request was cancelled, we'll only run the OnComplete call 
	if (InFlightRequestsCancelled.Contains(RequestId))
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Ignoring Request Response since it was cancelled. REQUEST_ID=%d"), RequestId);

		// Execute the handler if it's bound.		
		const auto bExecutedCallsiteHandler = OnComplete.ExecuteIfBound(*Context, RequestData);
		if (AlwaysLogCompleteResponses || !bExecutedCallsiteHandler)
		{
			UE_LOG(LogBeamBackend, Display, TEXT("Beamable Request Canceled | REQUEST_ID=%d, USER_SLOT=%s, NUM_FAILURES=%d"),
			       RequestId, bWasMadeWithUserSlot ? *UserSlot.Name : *FString(TEXT("Made Without UserSlot")), InFlightFailureCount.FindRef(RequestId));
		}

		// Update the context's status to completed so we can clean it up in the next tick of TickCleanUpRequests if no one depends on it.
		Context->BeamStatus = Completed;

		return;
	}
	// Then, we handle success and error cases.

	// Get retry stuff
	const auto CurrFailedCount = InFlightFailureCount.FindChecked(RequestId);
	const auto RetryConfig = Context->RetryConfiguration;
	const auto bShouldRetryIfFail = RetryConfig.RetryMaxAttempt == -1 || CurrFailedCount < RetryConfig.RetryMaxAttempt;

	// Stores whether or not the request was successful
	const auto bWasSuccess = ResponseCode == 200;

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
		InFlightResponseBodyData[*Context] = SuccessData;

		// Run the callsite handler
		const auto ExecutedCallsiteHandler = OnSuccess.ExecuteIfBound(*Context, RequestData, SuccessData);

		// We only log the response if no callsite is given or if we are configured to always run it.
		if (AlwaysLogSuccessResponses || !ExecutedCallsiteHandler)
		{
			UE_LOG(LogBeamBackend, Display, TEXT("Beamable Request Successfull | REQUEST_ID=%d, USER_SLOT=%s, RESPONSE_CODE=%d, NUM_FAILURES=%d, RESPONSE_BODY=%s"),
			       RequestId, bWasMadeWithUserSlot ? *UserSlot.Name : TEXT("Made Without UserSlot"), ResponseCode, CurrFailedCount, *ContentAsString);
		}
	}
	else
	{
		// Otherwise, parse the body as an error response callback and store it in the full response data.
		FBeamErrorResponse ErrorData;
		FJsonObjectConverter::JsonObjectStringToUStruct(*ContentAsString, &ErrorData);

		// Store it so wait handles can grab at it later
		InFlightResponseErrorData[*Context] = ErrorData;

		// Now that we know we had an error, compute whether or not we should retry.		
		bWillReAuth &= AUTH_ERROR_CODE_RETRY_ALLOWED.Contains(ErrorData.error);
		bWillRetry &= RetryConfig.HttpResponseCodes.Contains(ResponseCode) || RetryConfig.CustomErrorCodes.Contains(ErrorData.error);
		// We always enqueue for retry if we need the re-auth, even if we are "out of retries". That's because Re-Auth retries don't count towards the retry limit.
		bWillRetry |= bWillReAuth;

		// Bump the failed count associated with this request id.					
		InFlightFailureCount[RequestId] = bWillReAuth ? CurrFailedCount : CurrFailedCount + 1;

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
			const auto ExecutedCallsiteHandler = OnError.ExecuteIfBound(*Context, RequestData, ErrorData);

			// We fallback to global handler only if we didn't run the callsite one OR if we are configured to always run it.
			bool bExecutedGlobalHandler = false;
			if (AlwaysRunGlobalHandlers || !ExecutedCallsiteHandler && (GlobalRequestErrorHandler.IsBound() || GlobalRequestErrorCodeHandler.IsBound()))
			{
				GlobalRequestErrorHandler.Broadcast(*Context, ErrorData);
				const auto _ = GlobalRequestErrorCodeHandler.ExecuteIfBound(*Context, ErrorData);

				bExecutedGlobalHandler = true;
			}

			// We log the error only if neither callback was set OR if we are configured to do so.
			if (AlwaysLogErrorResponses || !bExecutedGlobalHandler && !ExecutedCallsiteHandler)
			{
				UE_LOG(LogBeamBackend, Error, TEXT("Beamable Request Failed | REQUEST_ID=%d, USER_SLOT=%s, RESPONSE_CODE=%d, NUM_FAILURES=%d, WILL_RETRY=%s, RESPONSE_BODY=%s"),
				       RequestId, bWasMadeWithUserSlot ? *UserSlot.Name : TEXT("Made Without UserSlot"), ResponseCode, CurrFailedCount, bWillRetry ? TEXT("true") : TEXT("false"),
				       *ContentAsString);
			}
		}
	}

	// Clean up from InFlightRequests, only if we are not meant to retry it.
	if (bWasSuccess || !bWillRetry)
	{
		// Update Connectivity Status
		UpdateConnectivity(*Context, RequestStatus, FRequestType{TRequestData::StaticClass()->GetName()});

		// Execute the handler if it's bound.
		const auto bExecutedCallsiteHandler = OnComplete.ExecuteIfBound(*Context, RequestData);
		if (AlwaysLogCompleteResponses || !bExecutedCallsiteHandler)
		{
			UE_LOG(LogBeamBackend, Display, TEXT("Beamable Request Completed | REQUEST_ID=%d, USER_SLOT=%s, RESPONSE_CODE=%d, WAS_SUCCESS=%s, NUM_FAILURES=%d"),
			       RequestId, bWasMadeWithUserSlot ? *UserSlot.Name : TEXT("Made Without UserSlot"), ResponseCode, bWasSuccess ? TEXT("true") : TEXT("false"), CurrFailedCount);
		}

		// Update the context's status to completed so we can clean it up in the next tick of TickCleanUpRequests if no one depends on it.
		Context->BeamStatus = Completed;
	}
}

template <typename TRequestData, typename TResponseData>
FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64& RequestId, TRequestData* RequestData,
                                                             TBeamFullResponseHandler<TRequestData*, TResponseData*> ResponseHandler, const UObject* CallingContext)
{
	StaticCheckForRequestType<TRequestData>();
	StaticCheckForResponseType<TResponseData>();

	UE_LOG(LogBeamBackend, Verbose, TEXT("Request Preparation - Processor Preparation: Making Code Un-authenticated Request Processor"));

	// Get the handlers 
	auto OutProcessor = FBeamRequestProcessor(
		// Capture, by-value, the Backend system, request id for this request and request data --- these are plain structs with no allocations.
		[this, RequestId, RequestData, ResponseHandler, CallingContext]
		// This just passes the captured data along to the Process function (we do this so we can unit test the process function in isolation).
	(const FHttpRequestPtr Request, const FHttpResponsePtr Response, bool)
		{
			if (!Response.IsValid())
			{
				UE_LOG(LogBeamBackend, Error, TEXT("Beamable Request Failed Parsing Response | REQUEST_ID=%lld"), RequestId);
				return;
			}
			UE_LOG(LogBeamBackend, Verbose, TEXT("Beamable Request Parsed Response | REQUEST_ID=%lld"), RequestId);
			
			const auto ResponseCode = Response->GetResponseCode();
			const auto ContentAsString = Response->GetContentAsString();
			const auto RequestStatus = Request->GetStatus();

			// If it was a success, we try to cache the response.
			if (ResponseCode == 200)
				GEngine->GetEngineSubsystem<UBeamResponseCache>()->UpdateResponseCache(RequestData->GetRequestType(), CallingContext, Request, ContentAsString);

			RunCodeRequestProcessor<TRequestData, TResponseData>(ResponseCode, ContentAsString, RequestStatus, RequestId, RequestData, ResponseHandler);
		});

	// We return the build processor function so the API request function can bind it to UnrealHttpRequest's response handler delegate.
	return OutProcessor;
}

template <typename TRequestData, typename TResponseData>
void UBeamBackend::RunCodeRequestProcessor(const int32& ResponseCode, const FString& ContentAsString, const TUnrealRequestStatus RequestStatus,
                                           const int64& RequestId, TRequestData* RequestData, TBeamFullResponseHandler<TRequestData*, TResponseData*> ResponseHandler)
{
	ProcessCodeRequest<TRequestData, TResponseData>(ResponseCode, ContentAsString, RequestStatus, RequestId, RequestData, ResponseHandler);

	// Run any registered callback for handling Request completion.
	TryTriggerRequestCompleteDelegates(RequestId);
}

template <typename TRequestData, typename TResponseData>
void UBeamBackend::ProcessCodeRequest(const int32& ResponseCode, const FString& ContentAsString, const TUnrealRequestStatus RequestStatus,
                                      const int64& RequestId, TRequestData* RequestData, TBeamFullResponseHandler<TRequestData*, TResponseData*> ResponseHandler)
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
	auto Context = InFlightRequestContexts.Find(RequestId);
	Context->ResponseCode = ResponseCode;
	Context->UserSlot = FUserSlot("");
	FullResponse.Context = *Context;

	// Store the Request's data into the full response
	FullResponse.RequestData = RequestData;

	const bool bIsCancelled = InFlightRequestsCancelled.Contains(RequestId);
	// Stores whether or not the request was successful, error or cancelled
	if (bIsCancelled)
		FullResponse.State = Cancelled;
	else
		FullResponse.State = ResponseCode == 200 ? Success : Error;

	// Get retry stuff
	const auto CurrFailedCount = InFlightFailureCount.FindChecked(RequestId);
	const auto RetryConfig = Context->RetryConfiguration;
	const auto bShouldRetryIfFail = !bIsCancelled && RetryConfig.RetryMaxAttempt == -1 || RetryConfig.RetryMaxAttempt > CurrFailedCount;


	// Stores which attempt we are in
	FullResponse.AttemptNumber = CurrFailedCount;
		
	// If it was an error, we'll compute this based on the error data.
	bool bWillRetry = ResponseCode != 200 && bShouldRetryIfFail;
	// Parse the appropriate response body...
	if (FullResponse.State == Success)
	{
		// Parse the response body and store it in the full response data.				
		FullResponse.SuccessData = NewObject<TResponseData>(RequestData);
		FullResponse.SuccessData->DeserializeRequestResponse(RequestData, ContentAsString);

		// Store it so wait handles can grab at it later
		InFlightResponseBodyData[*Context] = FullResponse.SuccessData;
	}
	else if (FullResponse.State == Error)
	{
		// Otherwise, parse the body as an error response callback and store it in the full response data.				
		FJsonObjectConverter::JsonObjectStringToUStruct(*ContentAsString, &FullResponse.ErrorData);

		// Now that we know we had an error, compute whether or not we should retry.
		bWillRetry &= RetryConfig.HttpResponseCodes.Contains(ResponseCode) || RetryConfig.CustomErrorCodes.Contains(FullResponse.ErrorData.error);

		// Store it so wait handles can grab at it later
		InFlightResponseErrorData[*Context] = FullResponse.ErrorData;

		// Bump the failed count associated with this request id.					
		InFlightFailureCount[RequestId] = CurrFailedCount + 1;

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

			FullResponse.State = Retrying;
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
			UE_LOG(LogBeamBackend, Error, TEXT("Beamable Request Failed - Retrying | REQUEST_ID=%d, RESPONSE_CODE=%d, NUM_FAILURES=%d, WILL_RETRY=%s, RESPONSE_BODY=%s"),
			       RequestId, ResponseCode, CurrFailedCount, bWillRetry ? TEXT("true") : TEXT("false"), *ContentAsString);
		}
	}
	// Only run the clean up and callbacks after we are done retrying.
	else
	{
		// Update Connectivity Status
		UpdateConnectivity(FullResponse.Context, RequestStatus, FRequestType{TRequestData::StaticClass()->GetName()});

		if (AlwaysLogCompleteResponses || !bExecutedCallsiteHandler)
		{
			// We only log the response for code if we are configured to always run it.
			if (AlwaysLogSuccessResponses && FullResponse.State == Success)
			{
				UE_LOG(LogBeamBackend, Display, TEXT("Beamable Request Successfull | REQUEST_ID=%d, RESPONSE_CODE=%d, NUM_FAILURES=%d, RESPONSE_BODY=%s"),
				       RequestId, ResponseCode, CurrFailedCount, *ContentAsString);
			}

			// We log the error only if neither callback was set OR if we are configured to do so.
			if (AlwaysLogErrorResponses && FullResponse.State == Error)
			{
				UE_LOG(LogBeamBackend, Error, TEXT("Beamable Request Failed | REQUEST_ID=%d, RESPONSE_CODE=%d, NUM_FAILURES=%d, RESPONSE_BODY=%s"),
				       RequestId, ResponseCode, CurrFailedCount, *ContentAsString);
			}

			const auto bWasSuccess = FullResponse.State == Success;
			if (FullResponse.State == Cancelled)
			{
				UE_LOG(LogBeamBackend, Display, TEXT("Beamable Request Canceled | REQUEST_ID=%d, WAS_SUCCESS=%s, NUM_FAILURES=%d"),
				       RequestId, bWasSuccess ? TEXT("true") : TEXT("false"), InFlightFailureCount.FindRef(RequestId));
			}
			else
			{
				UE_LOG(LogBeamBackend, Display, TEXT("Beamable Request Completed | REQUEST_ID=%d, WAS_SUCCESS=%s, NUM_FAILURES=%d"),
				       RequestId, bWasSuccess ? TEXT("true") : TEXT("false"), InFlightFailureCount.FindRef(RequestId));
			}
		}

		// Update the context's status to completed so we can clean it up in the next tick of TickCleanUpRequests if no one depends on it.
		Context->BeamStatus = Completed;
	}
}


template <typename TRequestData, typename TResponseData>
FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64& RequestId, const FBeamRealmHandle& RealmHandle, const FBeamAuthToken& AuthToken,
                                                                          TRequestData* RequestData, TBeamFullResponseHandler<TRequestData*, TResponseData*> ResponseHandler,
                                                                          const UObject* CallingContext)
{
	StaticCheckForRequestType<TRequestData>();
	StaticCheckForResponseType<TResponseData>();

	UE_LOG(LogBeamBackend, Verbose, TEXT("Request Preparation - Processor Preparation: Making Code Authenticated Request Processor"));

	// Get the handlers 
	auto OutProcessor = FBeamRequestProcessor(
		// Capture, by-value, the Backend system, request id for this request and request data --- these are plain structs with no allocations.
		[this, RequestId, RealmHandle, AuthToken, RequestData, ResponseHandler, CallingContext]
		// This just passes the captured data along to the Process function (we do this so we can unit test the process function in isolation).
	(const FHttpRequestPtr Request, const FHttpResponsePtr Response, bool)
		{
			if (!Response.IsValid())
			{
				UE_LOG(LogBeamBackend, Error, TEXT("Beamable Request Failed Parsing Response | REQUEST_ID=%lld"), RequestId);
				return;
			}
			UE_LOG(LogBeamBackend, Verbose, TEXT("Beamable Request Parsed Response | REQUEST_ID=%lld"), RequestId);
			
			const auto ResponseCode = Response->GetResponseCode();
			const auto ContentAsString = Response->GetContentAsString();
			const auto RequestStatus = Request->GetStatus();

			// If it was a success, we try to cache the response.
			if (ResponseCode == 200)
				GEngine->GetEngineSubsystem<UBeamResponseCache>()->UpdateResponseCache(RequestData->GetRequestType(), CallingContext, Request, ContentAsString);

			RunAuthenticatedCodeRequestProcessor<TRequestData, TResponseData>(ResponseCode, ContentAsString, RequestStatus, RequestId, RealmHandle, AuthToken, RequestData, ResponseHandler);
		});

	// We return the build processor function so the API request function can bind it to UnrealHttpRequest's response handler delegate. 
	return OutProcessor;
}

template <typename TRequestData, typename TResponseData>
void UBeamBackend::RunAuthenticatedCodeRequestProcessor(const int32& ResponseCode, const FString& ContentAsString, const TUnrealRequestStatus RequestStatus,
                                                        const int64& RequestId, const FBeamRealmHandle& RealmHandle, const FBeamAuthToken& AuthToken, TRequestData* RequestData,
                                                        const TBeamFullResponseHandler<TRequestData*, TResponseData*>& ResponseHandler)
{
	ProcessAuthenticatedCodeRequest<TRequestData, TResponseData>(ResponseCode, ContentAsString, RequestStatus, RequestId, RealmHandle, AuthToken, RequestData, ResponseHandler);

	// Run any registered callback for handling Request completion.
	TryTriggerRequestCompleteDelegates(RequestId);
}

template <typename TRequestData, typename TResponseData>
void UBeamBackend::ProcessAuthenticatedCodeRequest(const int32& ResponseCode, const FString& ContentAsString, const TUnrealRequestStatus RequestStatus,
                                                   const int64& RequestId, const FBeamRealmHandle& RealmHandle, const FBeamAuthToken& AuthToken, TRequestData* RequestData,
                                                   const TBeamFullResponseHandler<TRequestData*, TResponseData*>& ResponseHandler)
{
	StaticCheckForRequestType<TRequestData>();
	StaticCheckForResponseType<TResponseData>();

	// Get any UserSlot that matches this Pid/Auth Token, if any
	FBeamRealmUser User;
	FUserSlot UserSlot;
	const auto bWasMadeWithUserSlot = BeamUserSlots->GetUserDataWithRefreshTokenAndPid(AuthToken.RefreshToken, RealmHandle.Pid, User, UserSlot);
	const auto UserSlotLog = bWasMadeWithUserSlot ? UserSlot.Name : TEXT("Made Without UserSlot");

	// Get retry stuff	
	auto FullResponse = FBeamFullResponse<TRequestData*, TResponseData*>();

	// Sets the request id for the request
	auto Context = InFlightRequestContexts.Find(RequestId);
	Context->ResponseCode = ResponseCode;
	Context->UserSlot = bWasMadeWithUserSlot ? UserSlot : FUserSlot("");
	FullResponse.Context = *Context;

	// Store the Request's data into the full response
	FullResponse.RequestData = RequestData;

	bool bIsCancelled = InFlightRequestsCancelled.Contains(RequestId);
	// Stores whether or not the request was successful, error or cancelled
	if (bIsCancelled)
		FullResponse.State = Cancelled;
	else
		FullResponse.State = ResponseCode == 200 ? Success : Error;

	const auto CurrFailedCount = InFlightFailureCount.FindChecked(RequestId);
	const auto RetryConfig = Context->RetryConfiguration;
	const auto bShouldRetryIfFail = !bIsCancelled && RetryConfig.RetryMaxAttempt == -1 || RetryConfig.RetryMaxAttempt > CurrFailedCount;


	// Stores which attempt we are in
	FullResponse.AttemptNumber = CurrFailedCount;

	// If it was an error, we'll compute whether we should re-auth/retry based on the error data.
	bool bWillRetry = ResponseCode != 200 && bShouldRetryIfFail;
	bool bWillReAuth = ResponseCode != 200;
	// Parse the appropriate response body...
	if (FullResponse.State == Success)
	{
		// Parse the response body and store it in the full response data.						
		FullResponse.SuccessData = NewObject<TResponseData>(RequestData);
		FullResponse.SuccessData->DeserializeRequestResponse(RequestData, ContentAsString);

		// Store it so wait handles can grab at it later
		InFlightResponseBodyData[*Context] = FullResponse.SuccessData;		
	}
	else if (FullResponse.State == Error)
	{
		// Otherwise, parse the body as an error response callback and store it in the full response data.				
		FJsonObjectConverter::JsonObjectStringToUStruct(*ContentAsString, &FullResponse.ErrorData);

		// Now that we know we had an error, compute whether or not we should retry.
		bWillReAuth &= AUTH_ERROR_CODE_RETRY_ALLOWED.Contains(FullResponse.ErrorData.error);
		bWillRetry &= RetryConfig.HttpResponseCodes.Contains(ResponseCode) || RetryConfig.CustomErrorCodes.Contains(FullResponse.ErrorData.error);
		// We always enqueue for retry if we need the re-auth, even if we are "out of retries". That's because Re-Auth retries don't count towards the retry limit.
		bWillRetry |= bWillReAuth;

		// Store it so wait handles can grab at it later
		InFlightResponseErrorData[*Context] = FullResponse.ErrorData;

		// Bump the failed count associated with this request id.					
		InFlightFailureCount[RequestId] = bWillReAuth ? CurrFailedCount : CurrFailedCount + 1;

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
			FullResponse.State = Retrying;
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
				UE_LOG(LogBeamBackend, Error, TEXT("Beamable Request Failed - Retrying | REQUEST_ID=%d, USER_SLOT=%s, RESPONSE_CODE=%d, NUM_FAILURES=%d, WILL_RETRY=%s, RESPONSE_BODY=%s"),
				       RequestId, *UserSlotLog, ResponseCode, CurrFailedCount, bWillRetry ? TEXT("true") : TEXT("false"),
				       *ContentAsString);
			}
		}
	}
	// Only run the clean up after we are done retrying.
	else
	{
		// Update Connectivity Status
		UpdateConnectivity(FullResponse.Context, RequestStatus, FRequestType{TRequestData::StaticClass()->GetName()});

		const auto bExecutedCallsiteHandler = ResponseHandler.ExecuteIfBound(FullResponse);
		if (AlwaysLogCompleteResponses || !bExecutedCallsiteHandler)
		{
			// We only log the response for code if we are configured to always run it.
			if (AlwaysLogSuccessResponses && FullResponse.State == Success)
			{
				UE_LOG(LogBeamBackend, Display, TEXT("Beamable Request Successfull | REQUEST_ID=%d, USER_SLOT=%s, RESPONSE_CODE=%d, NUM_FAILURES=%d, RESPONSE_BODY=%s"),
				       RequestId, *UserSlotLog, ResponseCode, CurrFailedCount, *ContentAsString);
			}

			// We log the error only if neither callback was set OR if we are configured to do so.
			if (AlwaysLogErrorResponses && FullResponse.State == Error)
			{
				UE_LOG(LogBeamBackend, Error, TEXT("Beamable Request Failed | REQUEST_ID=%d, USER_SLOT=%s, RESPONSE_CODE=%d, NUM_FAILURES=%d, WILL_RETRY=%s, RESPONSE_BODY=%s"),
				       RequestId, *UserSlotLog, ResponseCode, CurrFailedCount, bWillRetry ? TEXT("true") : TEXT("false"), *ContentAsString);
			}

			const auto bWasSuccess = FullResponse.State == Success;
			if (FullResponse.State == Cancelled)
			{
				UE_LOG(LogBeamBackend, Display, TEXT("Beamable Request Canceled | REQUEST_ID=%d, USER_SLOT=%s, WAS_SUCCESS=%s, NUM_FAILURES=%d"),
				       RequestId, *UserSlotLog, bWasSuccess ? TEXT("true") : TEXT("false"), InFlightFailureCount.FindRef(RequestId));
			}
			else
			{
				UE_LOG(LogBeamBackend, Display, TEXT("Beamable Request Completed | REQUEST_ID=%d, USER_SLOT=%s, WAS_SUCCESS=%s, NUM_FAILURES=%d"),
				       RequestId, *UserSlotLog, bWasSuccess ? TEXT("true") : TEXT("false"), InFlightFailureCount.FindRef(RequestId));
			}
		}

		// Update the context's status to completed so we can clean it up in the next tick of TickCleanUpRequests if no one depends on it.
		Context->BeamStatus = Completed;
	}
}

void UBeamBackend::DefaultExecuteRequestImpl(int64 ActiveRequestId, FBeamConnectivity& Connectivity)
{
	UE_LOG(LogBeamBackend, Verbose, TEXT("Sending Request via Unreal HttpRequest's ProcessRequest. REQUEST_ID=%llu"), ActiveRequestId);
	if (InFlightRequests[ActiveRequestId]->ProcessRequest())
	{
		auto Context = InFlightRequestContexts.FindRef(ActiveRequestId);
		Context.BeamStatus = InFlight;
		InFlightRequestContexts[ActiveRequestId] = Context;
	}
}


bool UBeamBackend::TickRetryQueue(float DeltaTime)
{
	DECLARE_SCOPE_CYCLE_COUNTER(TEXT("UBeamBackend.TickRetry"), STATID_TickBeamBackend, STATGROUP_BeamBackend)

	FRequestToRetry FailedRequestCtx;
	while (EnqueuedRetries.Dequeue(FailedRequestCtx))
	{
		const auto ReqId = FailedRequestCtx.RequestId;
		const auto ReqAuthToken = FailedRequestCtx.AuthToken;

		// Get the retry configuration for the given request
		const auto RetryConfig = InFlightRequestContexts.FindChecked(ReqId).RetryConfiguration;
		const auto CurrRetryIdx = InFlightFailureCount.FindChecked(ReqId) - 1;
		const auto RetryFalloffIdx = CurrRetryIdx >= RetryConfig.RetryFalloffValues.Num() ? RetryConfig.RetryFalloffValues.Num() - 1 : CurrRetryIdx;
		const auto TimeToWait = RetryFalloffIdx >= 0 ? RetryConfig.RetryFalloffValues[CurrRetryIdx] : 0;

		UE_LOG(LogBeamBackend, Verbose, TEXT("Failed Request so we are waiting for %.2f before trying again."), TimeToWait);
		InFlightProcessingRequests.Add(ReqId, FProcessingRequestRetry{FailedRequestCtx, TimeToWait, 0.0f});
	}

	// Wait for curr time in the exponential back-off scale.
	TArray<long> RetriesSentOut;
	for (auto& InFlightProcessingRequest : InFlightProcessingRequests)
	{
		auto& ProcessingReq = InFlightProcessingRequest.Value;
		ProcessingReq.AccumulatedTime += DeltaTime;
		if (ProcessingReq.AccumulatedTime >= ProcessingReq.TimeToWait)
		{
			const auto RequestToRetry = InFlightProcessingRequest.Value.RequestToRetry;
			const auto ReqId = RequestToRetry.RequestId;
			const auto RetryConfig = InFlightRequestContexts.FindChecked(ReqId).RetryConfiguration;
			const auto ReqRealmHandle = RequestToRetry.RealmHandle;
			const auto ReqAuthToken = RequestToRetry.AuthToken;

			auto& FailedReq = InFlightRequests.FindChecked(ReqId);

			// If any of these custom errors, we need to re-auth via the refresh token. So we make that request and, when it gets back, we run the original request again.
			// "InvalidTokenError", "TokenValidationError", "ExpiredTokenError"
			if (AUTH_ERROR_CODE_RETRY_ALLOWED.Contains(RequestToRetry.ErrorCode))
			{
				// Make sure that any request to Beamable that fails due to unauthorized access actually sent a user in the first place. 
				check(!ReqAuthToken.RefreshToken.IsEmpty())

				// Create Login Refresh Token Request.
				TUnrealRequestPtr ReAuthRequest = FHttpModule::Get().CreateRequest();
				PrepareBeamableRequestToRealm(ReAuthRequest, ReqRealmHandle);

				ULoginRefreshTokenRequest* Request = NewObject<ULoginRefreshTokenRequest>();
				Request->RefreshToken = ReqAuthToken.RefreshToken;
				Request->GrantType = "refresh_token";
				PrepareBeamableRequestVerbRouteBody(ReAuthRequest, Request, BeamEnvironment->GetAPIUrl());

				ReAuthRequest->OnProcessRequestComplete().BindLambda([this, ReqId, ReqAuthToken, ReqRealmHandle, &FailedReq]
				(const FHttpRequestPtr Request, const FHttpResponsePtr Response, bool)

					{
						// Checks if the request was made using a user-slot or if people manually passed in the realm handle and refresh tokens.
						FBeamRealmUser RealmUserData;
						FUserSlot UserSlot;
						const auto WasMadeWithUserSlot = BeamUserSlots->GetUserDataWithRefreshTokenAndPid(ReqAuthToken.RefreshToken, ReqRealmHandle.Pid, RealmUserData, UserSlot);

						const auto RequestStatus = Request->GetStatus();
						// Update Connectivity Status
						if (RequestStatus == EHttpRequestStatus::Succeeded || RequestStatus == EHttpRequestStatus::Failed)
						{
							CurrentConnectivityStatus.IsConnected = true;
							CurrentConnectivityStatus.LastTimeSinceSuccessfulRequest = FDateTime::UtcNow().GetTicks();
						}
						else if (RequestStatus == EHttpRequestStatus::Failed_ConnectionError)
						{
							CurrentConnectivityStatus.IsConnected = false;
						}

						const auto ResponseCode = Response->GetResponseCode();
						const auto ResponseBody = Response->GetContentAsString();

						// Handle a successful re-authentication
						if (ResponseCode == 200)
						{
							// Extract the data from the response
							ULoginRefreshTokenResponse* LoginRefreshTokenResponse = NewObject<ULoginRefreshTokenResponse>();
							// This gets passed into all NewObject calls in the deserialization process. It's not great that we are allocating, but... it's not frequent enough to matter much.
							// For normal requests, this is usually the Request Object the user created
							// (which will usually be tied to a blueprint or sub-system and be disposed after the request finishes TODO unless the user explicitly tells us otherwise).
							// Here, we assign to the OuterOwner what is typically the default parameter to the NewObject --- this is because this request is an exception.							
							LoginRefreshTokenResponse->OuterOwner = GetTransientPackage();
							LoginRefreshTokenResponse->BeamDeserialize(ResponseBody);

							// Create a new token from the token response so we can re-send the request with valid credentials
							FBeamAuthToken NewToken;
							NewToken.AccessToken = LoginRefreshTokenResponse->Body->AccessToken.Val;
							NewToken.RefreshToken = LoginRefreshTokenResponse->Body->RefreshToken.Val;
							NewToken.ExpiresIn = LoginRefreshTokenResponse->Body->ExpiresIn;

							// Delete this after we've parsed it.							
							LoginRefreshTokenResponse->ConditionalBeginDestroy();

							// If it was made with a user slot, we need to make sure the new tokens are set up in that slot.
							// The reason that we simply assume there'll always be a UserSlot is to make integration tests
							if (WasMadeWithUserSlot)
							{
								UE_LOG(LogBeamBackend, Verbose, TEXT("Identified User Slot and Re-authing it. REQUEST_ID=%d, USER_SLOT=%s"), ReqId, *UserSlot.Name);
								// Re-auth the user at the found slot so that subsequent requests use the new token rather than this one.
								BeamUserSlots->SetAuthenticationDataAtSlot(UserSlot, NewToken.AccessToken, NewToken.RefreshToken, NewToken.ExpiresIn,
								                                           RealmUserData.RealmHandle.Cid, RealmUserData.RealmHandle.Pid, this);
								BeamUserSlots->SetGamerTagAtSlot(UserSlot, RealmUserData.GamerTag, this);
								BeamUserSlots->SetEmailAtSlot(UserSlot, RealmUserData.Email, this);
								BeamUserSlots->TriggerUserAuthenticatedIntoSlot(UserSlot, this);
							}
							// Then, we just fix the request up and send it along.						
							PrepareBeamableRequestToRealmWithAuthToken(FailedReq, ReqRealmHandle, NewToken);

							// Send out the request with new authentication headers.
							FailedReq->ProcessRequest();

							// Replace the InFlightRequest with the new instance of the HttpRequest.
							InFlightRequests[ReqId] = FailedReq;
						}
						// In case of unsuccessful re-auth, we clear the user slot. That will trigger a global callback with the information necessary to handle
						// a re-authentication failure. This is the single stateful MulticastDelegate that we have and it has the following assumptions:
						// - During the failure handling call, the RequestId is still active and can be used to retrieve any InFlightRequest data from UBeamBackend.
						// - During the failure handling call, the UserSlot data is no longer active -- you do have access to the FBeamRealmUser.
						//   - If the request was not made with a user slot is provided, we don't trigger this callback.
						// I think it's worth allowing users to configure when any bound delegates get removed. For example, whenever a new world is added, ...
						//   GEngine->OnWorldAdded()
						// ...would allow for users to use level blueprints to subscribe to this effectively defining ("when a user fails re-auth in this level, this is what happens".												
						else
						{
							UE_LOG(LogBeamBackend, Verbose, TEXT("Discarding Request since the user failed to re-authenticated. REQUEST_ID=%d"), ReqId);

							// If the failed re-auth was made using a user slot, we clear that slot.
							if (WasMadeWithUserSlot)
							{
								BeamUserSlots->ClearUserAtSlot(UserSlot, FailedAutomaticAuthentication, true);
								UE_LOG(LogBeamBackend, Verbose, TEXT("Invalidated user data as the user failed to re-authenticated. USER_SLOT=%s"), *UserSlot.Name);
							}

							// Make it so it'll fail immediately instead of trying to the request again and then re-process the request.
							// This is an extremely rare case and should not impact request numbers for our customers.
							// This will make the original request fail with a 401-Error Code that people not using UserSlots can check for and
							// handle this edge case.
							const auto Context = InFlightRequestContexts.Find(ReqId);
							auto& RetryConfig = Context->RetryConfiguration;
							RetryConfig.RetryMaxAttempt = 0;
							FailedReq->ProcessRequest();

							// Update the context's status to completed so we can clean it up in the next tick of TickCleanUpRequests if no one depends on it.
							Context->BeamStatus = Completed;
						}
					});

				ReAuthRequest->ProcessRequest();
			}

			// If we match a HTTP Response Code OR a custom beamable error code, it means we should retry and so we do.
			else if (RetryConfig.HttpResponseCodes.Contains(RequestToRetry.ResponseCode) || RetryConfig.CustomErrorCodes.Contains(RequestToRetry.ErrorCode))
			{
				// If we should just retry, simply send out the request again.
				UE_LOG(LogBeamBackend, Verbose, TEXT("Failed Request so we are resending it!!!!."));
				FailedReq->ProcessRequest();
			}
			else
			{
				const auto Route = FailedReq->GetURL();
				const auto Verb = FailedReq->GetVerb();
				const auto Body = FString(UTF8_TO_TCHAR(FailedReq->GetContent().GetData()));
				ensureAlwaysMsgf(false, TEXT("This request should not have been enqueued for retry, but it was. REQUEST_ID=%d, VERB=%s, ROUTE=%s, BODY=%s, RETRY_RESP_CODES=%s, RETRY_ERR_CODES=%s"),
				                 ProcessingReq.RequestToRetry.RequestId, *Route, *Verb, *Body,
				                 *FString::JoinBy(RetryConfig.HttpResponseCodes, TEXT(","), [](int64 c) { return FString::FromInt(c); }),
				                 *FString::Join(RetryConfig.CustomErrorCodes, TEXT(",")));
			}

			RetriesSentOut.Add(InFlightProcessingRequest.Key);
		}
	}

	// Clear all retries that were sent out
	for (auto SentOut : RetriesSentOut)
		InFlightProcessingRequests.Remove(SentOut);

	// Return true to keep this ticking...
	return true;
}

bool UBeamBackend::TickCleanUp(float)
{
	DECLARE_SCOPE_CYCLE_COUNTER(TEXT("UBeamBackend.TickCleanup"), STATID_TickBeamBackend, STATGROUP_BeamBackend)

	// We start by getting, from other subsystems that have registered themselves here, a list of RequestIds they depend on.
	TArray<FBeamRequestId> ExternalDependenciesOnRequests;
	for (const auto& OnGetInUseRequestDelegate : TickOnBackendCleanUpDelegates)
	{
		OnGetInUseRequestDelegate.ExecuteIfBound(ExternalDependenciesOnRequests);
	}

	// Build a list of all requests that can be cleaned up
	TArray<FBeamRequestId> ReqIdsToCleanUp;
	for (const auto& Kvp : InFlightRequestContexts)
	{
		const auto Ctx = Kvp.Value;
		if (Ctx.BeamStatus == Completed)
		{
			ReqIdsToCleanUp.Add(Kvp.Key);
		}
	}

	// We filter out all requests that other subsystems tell us we can't clean-up yet.
	for (int i = ReqIdsToCleanUp.Num() - 1; i >= 0; --i)
	{
		const auto& IdToCleanUp = ReqIdsToCleanUp[i];
		if (ExternalDependenciesOnRequests.Contains(IdToCleanUp))
			ReqIdsToCleanUp.RemoveAt(i);
	}


	// Clean up all associated data with requests that are ready to be cleaned up.
	for (const auto& IdToCleanUp : ReqIdsToCleanUp)
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Beamable CleanUp | Cleaning up all Request Data associated with Request. REQUEST_ID=%llu"), IdToCleanUp);

		if (InFlightRequests.Contains(IdToCleanUp))
			InFlightRequests.Remove(IdToCleanUp);

		if (InFlightRequestContexts.Contains(IdToCleanUp))
		{
			// Get the context
			auto Ctx = InFlightRequestContexts.FindRef(IdToCleanUp);

			// Clean up the Active Request and Response data associated with the Request Id.
			InFlightRequestData.Remove(Ctx);
			InFlightResponseBodyData.Remove(Ctx);
			InFlightResponseErrorData.Remove(Ctx);

			// Clean up the Request Context.
			InFlightRequestContexts.Remove(IdToCleanUp);
		}

		if (InFlightFailureCount.Contains(IdToCleanUp))
			InFlightFailureCount.Remove(IdToCleanUp);

		if (InFlightRequestsCancelled.Contains(IdToCleanUp))
			InFlightRequestsCancelled.Remove(IdToCleanUp);
	}

	// Return true since we don't ever want to stop cleaning up requests
	return true;
}

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


bool UBeamBackend::GetRetryConfigForRequestType(const FRequestType& RequestType, FBeamRetryConfig& Config) const
{
	const auto bRequestHasSpecialConfig = PerTypeRetryConfigs.Contains(RequestType);
	// If there's a retry config for this specific type of request...
	if (bRequestHasSpecialConfig)
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Found Config for Request Type!\nREQUEST_TYPE=%s"), *RequestType.Name);
		Config = PerTypeRetryConfigs.FindRef(RequestType);
	}
	else
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Falling back to Default Retry Configuration when getting config for Request Type!\nREQUEST_TYPE=%s"), *RequestType.Name);
		Config = DefaultRetryConfig;
	}

	return bRequestHasSpecialConfig;
}

bool UBeamBackend::GetRetryConfigForUserSlot(const FUserSlot& Slot, FBeamRetryConfig& Config) const
{
	const auto bUserHasSpecialConfig = PerUserRetryConfig.Contains(Slot);
	// If there's a retry config for this specific type of request...
	if (bUserHasSpecialConfig)
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Found Config for User Slot!\nUSER_SLOT=%s"), *Slot.Name);
		Config = PerUserRetryConfig.FindRef(Slot);
	}
	else
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Falling back to Default Retry Configuration when getting config for User Slot!\nUSER_SLOT=%s"), *Slot.Name);
		Config = DefaultRetryConfig;
	}

	return bUserHasSpecialConfig;
}

bool UBeamBackend::GetRetryConfigForUserSlotAndRequestType(const FRequestType& RequestType, const FUserSlot& Slot, FBeamRetryConfig& Config) const
{
	// If there's a retry config for this specific type of request and this specific user slot...
	const auto bUserHasSpecialConfigForRequestType = PerUserPerTypeRetryConfig.Contains(RequestType.Name + "₢" + Slot.Name);
	if (bUserHasSpecialConfigForRequestType)
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Found Config for User Slot and Request Type!\nUSER_SLOT=%s, REQUEST_TYPE=%s"), *Slot.Name, *RequestType.Name);
		Config = PerUserPerTypeRetryConfig.FindRef(RequestType.Name + "₢" + Slot.Name);
	}
	else
	{
		// If there's a retry config for this specific type of request...
		if (PerTypeRetryConfigs.Contains(RequestType))
		{
			UE_LOG(LogBeamBackend, Verbose, TEXT("Falling back to RequestType-only Config when getting config for User Slot and Request Type!\nUSER_SLOT=%s, REQUEST_TYPE=%s"), *Slot.Name,
			       *RequestType.Name);
			Config = PerTypeRetryConfigs.FindRef(RequestType);
		}
		else
		{
			// If there's a retry config for requests from this user...
			if (PerUserRetryConfig.Contains(Slot.Name))
			{
				UE_LOG(LogBeamBackend, Verbose, TEXT("Falling back to User-only Config when getting config for User Slot and Request Type!\nUSER_SLOT=%s, REQUEST_TYPE=%s"), *Slot.Name,
				       *RequestType.Name);
				Config = PerUserRetryConfig.FindRef(Slot.Name);
			}
			else
			{
				UE_LOG(LogBeamBackend, Verbose, TEXT("Falling back to Default Retry Configuration when getting config for User Slot and Request Type!\nUSER_SLOT=%s, REQUEST_TYPE=%s"), *Slot.Name,
				       *RequestType.Name);
				Config = DefaultRetryConfig; // Otherwise, just use the default one.
			}
		}
	}

	return bUserHasSpecialConfigForRequestType;
}

void UBeamBackend::SetRetryConfigForRequestType(const FRequestType& RequestType, const FBeamRetryConfig& RetryConfig)
{
	if (!PerTypeRetryConfigs.Contains(RequestType))
		PerTypeRetryConfigs.Add(RequestType, RetryConfig);
	else
		PerTypeRetryConfigs[RequestType] = RetryConfig;

	FString RetryString;
	FJsonObjectConverter::UStructToJsonObjectString(RetryConfig, RetryString);
	UE_LOG(LogBeamBackend, Verbose, TEXT("Setting retry config for RequestType.\nREQUEST_TYPE=%s, Config=%s"), *RequestType.Name, *RetryString);
}

void UBeamBackend::SetRetryConfigForUserSlot(const FUserSlot Slot, const FBeamRetryConfig& RetryConfig)
{
	if (!PerUserRetryConfig.Contains(Slot))
		PerUserRetryConfig.Add(Slot, RetryConfig);
	else
		PerUserRetryConfig[Slot] = RetryConfig;

	FString RetryString;
	FJsonObjectConverter::UStructToJsonObjectString(RetryConfig, RetryString);
	UE_LOG(LogBeamBackend, Verbose, TEXT("Setting retry config for UserSlot.\nUSER_SLOT=%s, RETRY_CONFIG=%s"), *Slot.Name, *RetryString);
}

void UBeamBackend::SetRetryConfigForUserSlotAndRequestType(const FUserSlot& Slot, const FRequestType& RequestType, const FBeamRetryConfig& RetryConfig)
{
	const auto Key = RequestType.Name + "₢" + Slot.Name;
	if (!PerUserPerTypeRetryConfig.Contains(Key))
		PerUserPerTypeRetryConfig.Add(Key, RetryConfig);
	else
		PerUserPerTypeRetryConfig[Key] = RetryConfig;

	FString RetryString;
	FJsonObjectConverter::UStructToJsonObjectString(RetryConfig, RetryString);
	UE_LOG(LogBeamBackend, Verbose, TEXT("Setting retry config for UserSlot and RequestType.\nUSER_SLOT=%s, REQUEST_TYPE=%s, RETRY_CONFIG=%s"), *Slot.Name, *RequestType.Name, *RetryString);
}

void UBeamBackend::ResetRetryConfigForRequestType(const FRequestType& RequestType)
{
	if (PerTypeRetryConfigs.Contains(RequestType))
		PerTypeRetryConfigs.Remove(RequestType);

	UE_LOG(LogBeamBackend, Verbose, TEXT("Reseting retry config for RequestType.\nREQUEST_TYPE=%s"), *RequestType.Name);
}

void UBeamBackend::ResetRetryConfigForUserSlot(const FUserSlot& Slot)
{
	if (PerUserRetryConfig.Contains(Slot))
		PerUserRetryConfig.Remove(Slot);

	UE_LOG(LogBeamBackend, Verbose, TEXT("Reseting retry config for UserSlot.\nUSER_SLOT=%s"), *Slot.Name);
}

void UBeamBackend::ResetRetryConfigForUserSlotAndRequestType(const FUserSlot& Slot, const FRequestType& RequestType)
{
	const auto Key = RequestType.Name + "₢" + Slot.Name;
	if (PerUserPerTypeRetryConfig.Contains(Key))
		PerUserPerTypeRetryConfig.Remove(Key);

	UE_LOG(LogBeamBackend, Verbose, TEXT("Reseting retry config for UserSlot and Request Type.\nUSER_SLOT=%s, REQUEST_TYPE=%s"), *Slot.Name, *RequestType.Name);
}


/**
 * Here we define the mock request types we have for test coverage.
 */
template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UBeamMockGetRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UBeamMockGetRequest*);
template TUnrealRequestPtr UBeamBackend::CreateRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const UBeamMockPostRequest*);
template TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64&, const FBeamRealmHandle&, const FBeamRetryConfig&, const FBeamAuthToken&, const UBeamMockPostRequest*);

template FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor<UBeamMockGetRequest, UBeamMockGetRequestResponse>(
	const int64&, UBeamMockGetRequest*, FOnMockSuccess, FOnMockError, FOnMockComplete, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UBeamMockGetRequest, UBeamMockGetRequestResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBeamMockGetRequest*, FOnMockSuccess, FOnMockError, FOnMockComplete, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UBeamMockGetRequest*, TBeamFullResponseHandler<UBeamMockGetRequest*, UBeamMockGetRequestResponse*>, const UObject*);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBeamMockGetRequest*,
                                                                                   TBeamFullResponseHandler<UBeamMockGetRequest*, UBeamMockGetRequestResponse*>, const UObject*);



/**
 * Here we'll include the RequestTemplates.gen.cpp file --- this file has all the declarations for the template functions...
 */
#include "AutoGen/Special/TemplateSpecializations.cpp"
