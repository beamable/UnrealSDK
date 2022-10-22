// Fill out your copyright notice in the Description page of Project Settings.


#include "BeamBackend/BeamBackend.h"

#include "BeamBackendTestCallbacks.h"
#include "BeamCoreSettings.h"
#include "BeamLogging.h"
#include "HttpModule.h"
#include "JsonObjectConverter.h"
#include "Interfaces/IHttpResponse.h"
#include "Misc/DefaultValueHelper.h"
#include "RawAPIs/BeamSharedTypes.h"

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
const TArray<int> UBeamBackend::NON_AUTH_REQUESTS_RETRY_ALLOWED_ERRORS = TArray<int>{503, 504};
const TArray<int> UBeamBackend::AUTH_REQUESTS_RETRY_ALLOWED_ERRORS = TArray<int>{401, 503, 504};

void UBeamBackend::Initialize(FSubsystemCollectionBase& Collection)
{
	UE_LOG(LogBeamBackend, Warning, TEXT("Initializing UBeamBackend Subsystem!"));

	// Initializing InFlightRequestID to -1 since we increment, then use it.
	InFlightRequestId = new long();
	*InFlightRequestId = -1;

	WaitHandleId = new long();
	*WaitHandleId = -1;

	// Set up the retry ticking to run at 15 ticks / second TODO: expose these as settings
	RetryQueueTickHandle = FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateUObject(this, &UBeamBackend::TickRetryQueue), 4 / 60);

	// Set up the retry ticking to run at 30 ticks / second TODO: expose these as settings
	WaitHandleTickHandle = FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateUObject(this, &UBeamBackend::TickWaitHandles), 2 / 60);

	// Set up the cleanup ticking to run at 1 tick / second TODO: expose these as settings
	CleanupRequestsTickHandle = FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateUObject(this, &UBeamBackend::TickCleanUp), 1);

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
	InFlightRequestsToDependedOnMap.Reserve(16);

	// Initialize a buffer of 4 wait handles
	ActiveWaitHandles.Reserve(4);
	ActiveWaitHandleCallbacks.Reserve(4);
	ActiveDependenciesForWaitHandles.Reserve(4);


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
	FTSTicker::GetCoreTicker().RemoveTicker(WaitHandleTickHandle);
	FTSTicker::GetCoreTicker().RemoveTicker(CleanupRequestsTickHandle);

	delete InFlightRequestId;
	delete WaitHandleId;
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
	static_assert(TIsDerivedFrom<TResponseData, FBeamJsonSerializable>::Value, "TResponseData must be a FBeamBaseResponse type.");
	static_assert(TIsDerivedFrom<TResponseData, UObject>::Value, "TResponseData must be a UObject type.");
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
	PrepareBeamableRequestVerbRouteBody<TRequestData>(Req, RequestData, BeamEnvironment->Data->APIUrl);

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
	PrepareBeamableRequestVerbRouteBody<TRequestData>(Req, RequestData, BeamEnvironment->Data->APIUrl);

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

	if (!Cid.IsEmpty())
		Request->SetHeader(HEADER_CLIENT_ID, Cid);

	if (!Pid.IsEmpty())
		Request->SetHeader(HEADER_PROJECT_ID, Pid);

	UE_LOG(LogBeamBackend, Verbose, TEXT("Request Preparation - Headers: CID=%s PID=%s"), *Cid, *Pid);
}

void UBeamBackend::PrepareBeamableRequestToRealmWithAuthToken(const TUnrealRequestPtr& Request,
                                                              const FBeamRealmHandle& RealmHandle,
                                                              const FBeamAuthToken& AuthToken)
{
	PrepareBeamableRequestToRealm(Request, RealmHandle);

	const auto AuthTokenHeader = FString::Format(*HEADER_VALUE_AUTHORIZATION, {AuthToken.AccessToken});
	Request->SetHeader(HEADER_AUTHORIZATION, AuthTokenHeader);
	const auto ScopeHeader = RealmHandle.Pid.IsEmpty() ? RealmHandle.Cid : FString::Format(TEXT("{0}.{1}"), {RealmHandle.Cid, RealmHandle.Pid});
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
	FString Route = TargetBeamableUrl, Verb = "", Body = "";
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
                                                                  TSuccessCallback OnSuccess, TErrorCallback OnError, TCompleteCallback OnComplete)
{
	StaticCheckForRequestType<TRequestData>();
	StaticCheckForResponseType<TResponseData>();

	UE_LOG(LogBeamBackend, Verbose, TEXT("Request Preparation - Processor Preparation: Making Blueprint Un-authenticated Request Processor"));

	FBeamRequestProcessor BoundResponseHandler(
		// Capture, by-value, the Backend system, request id for this request and request data --- these are plain structs with no allocations.
		[this, RequestId, RequestData, OnSuccess, OnError, OnComplete]

		// This just passes the captured data along to the Process function (we do this so we can unit test the process function in isolation).
	(const FHttpRequestPtr Request, const FHttpResponsePtr Response, const bool)
		{
			if (!Response.IsValid())
			{
				UE_LOG(LogBeamBackend, Error, TEXT("Beamable Request Failed Parsing Response | REQUEST_ID=%d"), RequestId);
				return;
			}

			// Get the response contents
			const auto ResponseCode = Response->GetResponseCode();
			const auto ContentAsString = Response->GetContentAsString();
			const auto RequestStatus = Request->GetStatus();
			ProcessBlueprintRequest<TRequestData, TResponseData, TSuccessCallback, TErrorCallback, TCompleteCallback>
				(ResponseCode, ContentAsString, RequestStatus, RequestId, RequestData, OnSuccess, OnError, OnComplete);
		});

	// We return the build processor function so the API request function can bind it to UnrealHttpRequest's response handler delegate.
	return BoundResponseHandler;
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

	// Get retry stuff
	const auto CurrFailedCount = InFlightFailureCount.FindChecked(RequestId);
	const auto RetryConfig = Context->RetryConfiguration;
	const auto ShouldRetryIfFail = RetryConfig.RetryMaxAttempt == -1 || CurrFailedCount < RetryConfig.RetryMaxAttempt;
	const auto bWillRetry = ShouldRetryIfFail && NON_AUTH_REQUESTS_RETRY_ALLOWED_ERRORS.Contains(ResponseCode);


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

	// Parse the appropriate response body...
	if (bWasSuccess)
	{
		// Parse the response body and store it in the full response data.
		auto SuccessData = NewObject<TResponseData>(RequestData);
		SuccessData->OuterOwner = RequestData;
		SuccessData->BeamDeserialize(ContentAsString);

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
                                                                               TRequestData* RequestData, TSuccessCallback OnSuccess, TErrorCallback OnError, TCompleteCallback OnComplete)
{
	StaticCheckForRequestType<TRequestData>();
	StaticCheckForResponseType<TResponseData>();

	UE_LOG(LogBeamBackend, Verbose, TEXT("Request Preparation - Processor Preparation: Making Blueprint Authenticated Request Processor"));

	FBeamRequestProcessor BoundResponseHandler(
		// Capture, by-value, the Backend system, request id for this request and request data --- these are plain structs with no allocations.
		[this, RequestId, AuthToken, RealmHandle, RequestData, OnSuccess, OnError, OnComplete]

		// This just passes the captured data along to the Process function (we do this so we can unit test the process function in isolation).
	(const FHttpRequestPtr Request, const FHttpResponsePtr Response, bool)
		{
			if (!Response.IsValid())
			{
				UE_LOG(LogBeamBackend, Error, TEXT("Beamable Request Failed Parsing Response | REQUEST_ID=%d"), RequestId);
				return;
			}

			// Get the response contents
			const auto ResponseCode = Response->GetResponseCode();
			const auto ContentAsString = Response->GetContentAsString();
			const auto RequestStatus = Request->GetStatus();
			ProcessAuthenticatedBlueprintRequest<TRequestData, TResponseData, TSuccessCallback, TErrorCallback, TCompleteCallback>
				(ResponseCode, ContentAsString, RequestStatus, RequestId, RealmHandle, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		});

	// We return the build processor function so the API request function can bind it to UnrealHttpRequest's response handler delegate.
	return BoundResponseHandler;
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

	// Whether or not the request should be retried
	const auto bWillRetry = !bWasSuccess && bShouldRetryIfFail && AUTH_REQUESTS_RETRY_ALLOWED_ERRORS.Contains(ResponseCode);
	const auto bWillReAuth = ResponseCode == 401 && bShouldRetryIfFail;

	// Parse the appropriate response body...
	if (bWasSuccess)
	{
		// Parse the response body and store it in the full response data.
		// Parse the response body and store it in the full response data.
		auto SuccessData = NewObject<TResponseData>(RequestData);
		SuccessData->OuterOwner = RequestData;
		SuccessData->BeamDeserialize(ContentAsString);

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
                                                             TBeamFullResponseHandler<TRequestData*, TResponseData*> ResponseHandler)
{
	StaticCheckForRequestType<TRequestData>();
	StaticCheckForResponseType<TResponseData>();

	UE_LOG(LogBeamBackend, Verbose, TEXT("Request Preparation - Processor Preparation: Making Code Un-authenticated Request Processor"));

	// Get the handlers 
	auto OutProcessor = FBeamRequestProcessor(
		// Capture, by-value, the Backend system, request id for this request and request data --- these are plain structs with no allocations.
		[this, RequestId, RequestData, ResponseHandler]
		// This just passes the captured data along to the Process function (we do this so we can unit test the process function in isolation).
	(const FHttpRequestPtr Request, const FHttpResponsePtr Response, bool)
		{
			if (!Response.IsValid())
			{
				UE_LOG(LogBeamBackend, Error, TEXT("Beamable Request Failed Parsing Response | REQUEST_ID=%d"), RequestId);
				return;
			}

			const auto ResponseCode = Response->GetResponseCode();
			const auto ContentAsString = Response->GetContentAsString();
			const auto RequestStatus = Request->GetStatus();
			ProcessCodeRequest<TRequestData, TResponseData>(ResponseCode, ContentAsString, RequestStatus, RequestId, RequestData, ResponseHandler);
		});

	// We return the build processor function so the API request function can bind it to UnrealHttpRequest's response handler delegate.
	return OutProcessor;
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
	const auto bWillRetry = bShouldRetryIfFail && NON_AUTH_REQUESTS_RETRY_ALLOWED_ERRORS.Contains(ResponseCode);

	// Stores which attempt we are in
	FullResponse.AttemptNumber = CurrFailedCount;

	// Parse the appropriate response body...
	if (FullResponse.State == Success)
	{
		// Parse the response body and store it in the full response data.				
		FullResponse.SuccessData = NewObject<TResponseData>(RequestData);
		FullResponse.SuccessData->OuterOwner = RequestData;
		FullResponse.SuccessData->BeamDeserialize(ContentAsString);

		// Store it so wait handles can grab at it later
		InFlightResponseBodyData[*Context] = FullResponse.SuccessData;
	}
	else if (FullResponse.State == Error)
	{
		// Otherwise, parse the body as an error response callback and store it in the full response data.				
		FJsonObjectConverter::JsonObjectStringToUStruct(*ContentAsString, &FullResponse.ErrorData);

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
                                                                          TRequestData* RequestData, TBeamFullResponseHandler<TRequestData*, TResponseData*> ResponseHandler)
{
	StaticCheckForRequestType<TRequestData>();
	StaticCheckForResponseType<TResponseData>();

	UE_LOG(LogBeamBackend, Verbose, TEXT("Request Preparation - Processor Preparation: Making Code Authenticated Request Processor"));

	// Get the handlers 
	auto OutProcessor = FBeamRequestProcessor(
		// Capture, by-value, the Backend system, request id for this request and request data --- these are plain structs with no allocations.
		[this, RequestId, RealmHandle, AuthToken, RequestData, ResponseHandler]
		// This just passes the captured data along to the Process function (we do this so we can unit test the process function in isolation).
	(const FHttpRequestPtr Request, const FHttpResponsePtr Response, bool)
		{
			if (!Response.IsValid())
			{
				UE_LOG(LogBeamBackend, Error, TEXT("Beamable Request Failed Parsing Response | REQUEST_ID=%d"), RequestId);
				return;
			}
			const auto ResponseCode = Response->GetResponseCode();
			const auto ContentAsString = Response->GetContentAsString();
			const auto RequestStatus = Request->GetStatus();
			ProcessAuthenticatedCodeRequest<TRequestData, TResponseData>(ResponseCode, ContentAsString, RequestStatus, RequestId, RealmHandle, AuthToken, RequestData, ResponseHandler);
		});

	// We return the build processor function so the API request function can bind it to UnrealHttpRequest's response handler delegate. 
	return OutProcessor;
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
	const auto bWillRetry = bShouldRetryIfFail && AUTH_REQUESTS_RETRY_ALLOWED_ERRORS.Contains(ResponseCode);
	const auto bWillReAuth = ResponseCode == 401 && bShouldRetryIfFail;

	// Stores which attempt we are in
	FullResponse.AttemptNumber = CurrFailedCount;

	// Parse the appropriate response body...
	if (FullResponse.State == Success)
	{
		// Parse the response body and store it in the full response data.						
		FullResponse.SuccessData = NewObject<TResponseData>(RequestData);
		FullResponse.SuccessData->OuterOwner = RequestData;
		FullResponse.SuccessData->BeamDeserialize(ContentAsString);

		// Store it so wait handles can grab at it later
		InFlightResponseBodyData[*Context] = FullResponse.SuccessData;
	}
	else if (FullResponse.State == Error)
	{
		// Otherwise, parse the body as an error response callback and store it in the full response data.				
		FJsonObjectConverter::JsonObjectStringToUStruct(*ContentAsString, &FullResponse.ErrorData);

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
			EnqueuedRetries.Enqueue(Retry);

			// Set the state to retrying instead of error.
			FullResponse.State = Retrying;
		}
	}

	// Execute the handler if it's bound.			
	if (bWillRetry)
	{
		// Run callback with the Retrying state if we are going to retry AND it's not a 401 error.
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
			const auto ReqRealmHandle = RequestToRetry.RealmHandle;
			const auto ReqAuthToken = RequestToRetry.AuthToken;

			auto& FailedReq = InFlightRequests.FindChecked(ReqId);

			// 401 Unauthorized ("InvalidTokenError") and 403 Forbidden ("ExpiredTokenError") special-case handling.
			// Basically, our Auth model requires us to 
			if (RequestToRetry.ResponseCode == 401)// || RequestToRetry.ResponseCode == 403)
			{
				// Make sure that any request to Beamable that fails due to unauthorized access actually sent a user in the first place. 
				check(!ReqAuthToken.RefreshToken.IsEmpty())

				// Create Login Refresh Token Request.
				TUnrealRequestPtr ReAuthRequest = FHttpModule::Get().CreateRequest();
				PrepareBeamableRequestToRealm(ReAuthRequest, ReqRealmHandle);

				ULoginRefreshTokenRequest* Request = NewObject<ULoginRefreshTokenRequest>();
				Request->RefreshToken = ReqAuthToken.RefreshToken;
				Request->GrantType = "refresh_token";
				PrepareBeamableRequestVerbRouteBody(ReAuthRequest, Request, BeamEnvironment->Data->APIUrl);

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
							NewToken.AccessToken = LoginRefreshTokenResponse->Body->AccessToken;
							NewToken.RefreshToken = LoginRefreshTokenResponse->Body->RefreshToken;
							NewToken.ExpiresIn = LoginRefreshTokenResponse->Body->ExpiresIn;

							// Delete this after we've parsed it.							
							LoginRefreshTokenResponse->ConditionalBeginDestroy();

							// If it was made with a user slot, we need to make sure the new tokens are set up in that slot.
							// The reason that we simply assume there'll always be a UserSlot is to make integration tests
							if (WasMadeWithUserSlot)
							{
								UE_LOG(LogBeamBackend, Verbose, TEXT("Identified User Slot and Re-authing it. REQUEST_ID=%d, USER_SLOT=%s"), ReqId, *UserSlot.Name);
								// Re-auth the user at the found slot so that subsequent requests use the new token rather than this one.
								BeamUserSlots->SaveUserAtSlot(UserSlot, NewToken.AccessToken, NewToken.RefreshToken, NewToken.ExpiresIn,
								                              RealmUserData.RealmHandle.Cid, RealmUserData.RealmHandle.Pid);
							}
							// Then, we just fix the request up and send it along.						
							PrepareBeamableRequestToRealmWithAuthToken(FailedReq, ReqRealmHandle, NewToken);

							// Send out the request with new authentication headers.
							FailedReq->ProcessRequest();

							// Replace the InFlightRequest with the new instance of the HttpRequest.
							InFlightRequests[ReqId] = FailedReq;
						}
						// In case of unsuccessful re-auth, we shoot out an event (BP and/or Code-specific ones) saying that a request X failed due to
						// re-authentication. This is the single stateful MulticastDelegate that we have and it has the following assumptions:
						// - The user will call a function we pass into the delegate to tell us they are done handling the failure.
						//   - Calling this function will invalidate the request AND the UserSlot.
						//   - Any data associated with either will no longer be accessible via UBeamBackend and UBeamUserSlot's APIs.
						//   - Users can handle this by, for example, "displaying a popup asking for re-authentication".
						// - During the failure handling call, the RequestId is still active and can be used to retrieve any InFlightRequest data from UBeamBackend.
						// - During the failure handling call, the UserSlot data is still active and can be used to retrieve any data associated with it from UBeamUserSlots.
						//   - If no user slot is provided, it'll be an empty string.
						// I think it's worth allowing users to configure when any bound delegates get removed. For example, whenever a new world is added, ...
						//   GEngine->OnWorldAdded()
						// ...would allow for users to use level blueprints to subscribe to this effectively defining ("when a user fails re-auth in this level, this is what happens".
						// This could be on/off by default --- when off, users must manage this state themselves via UBeamBackend::AddUserAuthFailedHandler,
						// UBeamBackend::ClearUserAuthFailedHandlers and UBeamBackend::RemoveUserAuthFailedHandlers						
						else
						{
							UE_LOG(LogBeamBackend, Verbose, TEXT("Discarding Request since the user failed to re-authenticated. REQUEST_ID=%d"), ReqId);

							// If the failed re-auth was made using a user slot, we clear that slot.
							if (WasMadeWithUserSlot)
							{
								BeamUserSlots->ClearUserAtSlot(UserSlot);
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

			// 503 Service Unavailable and 504 Gateway Timeout are the types of errors that make sense retrying at all.
			// Other errors (such as 400 Bad Request) won't even show up in the retry flow as we filter them out and fail them at the first attempt.
			else if (RequestToRetry.ResponseCode == 503 || RequestToRetry.ResponseCode == 504)
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
				ensureAlwaysMsgf(false, TEXT("This request should not have been enqueued for retry, but it was. REQUEST_ID=%d, VERB=%s, ROUTE=%s, BODY=%s"),
				                 ProcessingReq.RequestToRetry.RequestId, *Route, *Verb, *Body);
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

bool UBeamBackend::TickWaitHandles(float)
{
	for (auto& ActiveWaitHandle : ActiveWaitHandles)
	{
		if (ActiveWaitHandle.Status == Completed)
		{
			UE_LOG(LogBeamBackend, Verbose, TEXT("Beamable WaitHandle | WaitHandle is already completed and awaiting clean up. WAIT_HANDLE=%llu"), ActiveWaitHandle.WaitHandleId);
			continue;
		}

		TArray<FBeamRequestId> DependedOnIds;
		ActiveDependenciesForWaitHandles.MultiFind(ActiveWaitHandle, DependedOnIds);

		// We sort the dependencies so that they are returned in the order they were made.
		DependedOnIds.Sort();

		// Handle the All case: Basically, all the dependency nodes need to be completed in order for us to fire off the wait event.
		if (ActiveWaitHandle.Mode == All)
		{
			auto bAreAllDepsDone = true;
			for (const auto& DependedOnId : DependedOnIds)
			{
				const auto& DependedOnCtx = InFlightRequestContexts.FindRef(DependedOnId);
				bAreAllDepsDone = bAreAllDepsDone && DependedOnCtx.BeamStatus == Completed;
			}

			// If all dependencies are done, let's call the WaitCompleted callback with all the dependencies correctly set up!
			if (bAreAllDepsDone)
			{
				TArray<FBeamRequestContext> Contexts;
				TArray<TScriptInterface<IBeamBaseRequestInterface>> RequestData;
				TArray<UObject*> ResponseBodies;
				TArray<FBeamErrorResponse> ResponseErrors;

				// String builder so we can log all the ids
				FString IdList;
				IdList.Reserve(DependedOnIds.Num() * 2);

				// Go through ids
				for (const auto& DependedOnId : DependedOnIds)
				{
					const auto DependedOnContext = InFlightRequestContexts.FindRef(DependedOnId);

					Contexts.Add(DependedOnContext);
					RequestData.Add(InFlightRequestData.FindRef(DependedOnContext));
					ResponseBodies.Add(InFlightResponseBodyData.FindRef(DependedOnContext));
					ResponseErrors.Add(InFlightResponseErrorData.FindRef(DependedOnContext));
					IdList += FString::Printf(TEXT("%llu, "), DependedOnId);
				}

				UE_LOG(LogBeamBackend, Verbose, TEXT("Beamable WaitHandles | Completed WAIT_HANDLE=%llu, REQUEST_IDS=[%s]"), ActiveWaitHandle.WaitHandleId, *IdList);

				const auto& OnComplete = ActiveWaitHandleCallbacks.FindRef(ActiveWaitHandle);
				auto _ = OnComplete.ExecuteIfBound(Contexts, RequestData, ResponseBodies, ResponseErrors);
				ActiveWaitHandle.Status = Completed;
			}
		}
	}

	return true;
}

bool UBeamBackend::TickCleanUp(float)
{
	DECLARE_SCOPE_CYCLE_COUNTER(TEXT("UBeamBackend.TickCleanup"), STATID_TickBeamBackend, STATGROUP_BeamBackend)

	// We start by cleaning up all the WaitHandle's that have completed
	TArray<FBeamRequestWaitHandle> WaitHandlesToCleanUp;
	for (const auto& ActiveWaitHandle : ActiveWaitHandles)
	{
		if (ActiveWaitHandle.Status == Completed)
			WaitHandlesToCleanUp.Add(ActiveWaitHandle);
	}

	for (const auto& HandleToCleanUp : WaitHandlesToCleanUp)
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Beamable CleanUp | Cleaning Up Data associated with WaitHandle. WAIT_HANDLE_ID=%llu"), HandleToCleanUp.WaitHandleId);

		// Clear the handle from active ones
		if (ActiveWaitHandles.Contains(HandleToCleanUp)) ActiveWaitHandles.Remove(HandleToCleanUp);

		// Clear them from the map we keep tying Reqs to the Handles that depend on them
		TArray<FBeamRequestId> DependedOnIds;
		ActiveDependenciesForWaitHandles.MultiFind(HandleToCleanUp, DependedOnIds);
		for (const auto& DependedOnId : DependedOnIds)
		{
			if (InFlightRequestsToDependedOnMap.Contains(DependedOnId))
				InFlightRequestsToDependedOnMap.RemoveSingle(DependedOnId, HandleToCleanUp);
		}

		// Clear the handle from the map of dependencies for them.
		ActiveDependenciesForWaitHandles.Remove(HandleToCleanUp);

		// Clear the callback associated with the handle
		ActiveWaitHandleCallbacks.Remove(HandleToCleanUp);
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

	// We filter out all requests that have WaitHandles depending on them that have yet to be completed.
	for (int i = ReqIdsToCleanUp.Num() - 1; i >= 0; --i)
	{
		const auto& IdToCleanUp = ReqIdsToCleanUp[i];
		if (InFlightRequestsToDependedOnMap.Contains(IdToCleanUp))
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
			if (InFlightRequestData.Contains(Ctx)) InFlightRequestData.Remove(Ctx);
			if (InFlightResponseBodyData.Contains(Ctx)) InFlightResponseBodyData.Remove(Ctx);
			if (InFlightResponseErrorData.Contains(Ctx)) InFlightResponseBodyData.Remove(Ctx);

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

__          __   _ _     _____                            _   
\ \        / /  (_) |   |  __ \                          | |  
\ \  /\  / /_ _ _| |_  | |__) |___  __ _ _   _  ___  ___| |_ 
\ \/  \/ / _` | | __| |  _  // _ \/ _` | | | |/ _ \/ __| __|
\  /\  / (_| | | |_  | | \ \  __/ (_| | |_| |  __/\__ \ |_ 
 \/  \/ \__,_|_|\__| |_|  \_\___|\__, |\__,_|\___||___/\__|
									| |                    
									|_|                    
*/

FBeamRequestWaitHandle UBeamBackend::WaitAll(const TArray<FBeamRequestContext>& Contexts, FOnWaitComplete OnComplete)
{
	// Ensures we get a valid Next Id even if requests get made from multiple threads.
	const auto NextId = _InterlockedIncrement(WaitHandleId);
	const auto WaitHandle = FBeamRequestWaitHandle{NextId, this, All};

	ActiveWaitHandles.Add(WaitHandle);

	for (const auto& Context : Contexts)
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Adding WaitHandle with dependency. WAIT_HANDLE=%llu, REQUEST_ID=%llu"), NextId, Context.RequestId);

		ActiveDependenciesForWaitHandles.AddUnique(WaitHandle, Context.RequestId);
		InFlightRequestsToDependedOnMap.AddUnique(Context.RequestId, WaitHandle);
	}

	ActiveWaitHandleCallbacks.Add(WaitHandle, OnComplete);

	return WaitHandle;
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
	const int64&, UBeamMockGetRequest*, FOnMockSuccess, FOnMockError, FOnMockComplete);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor<UBeamMockGetRequest, UBeamMockGetRequestResponse>(
	const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBeamMockGetRequest*, FOnMockSuccess, FOnMockError, FOnMockComplete);
template FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64&, UBeamMockGetRequest*, TBeamFullResponseHandler<UBeamMockGetRequest*, UBeamMockGetRequestResponse*>);
template FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64&, const FBeamRealmHandle&, const FBeamAuthToken&, UBeamMockGetRequest*,
                                                                                   TBeamFullResponseHandler<UBeamMockGetRequest*, UBeamMockGetRequestResponse*>);

/**
 * Here we'll include the RequestTemplates.gen.cpp file --- this file has all the declarations for the template functions...
 */
#include "AutoGen/Special/TemplateSpecializations.cpp"
