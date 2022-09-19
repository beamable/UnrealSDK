// Fill out your copyright notice in the Description page of Project Settings.


#include "BeamBackend.h"

#include "BeamCoreSettings.h"
#include "BeamUserSlots.h"
#include "HttpModule.h"
#include "JsonObjectConverter.h"
#include "Interfaces/IHttpResponse.h"
#include "Misc/DefaultValueHelper.h"
#include "RawAPIs/BeamSharedTypes.h"

const FString UBeamBackend::ACCEPT_HEADER = FString::Printf(TEXT("application/json"));
const TArray<int> UBeamBackend::RETRY_ALLOWED_ERRORS = TArray<int>{401, 403, 503, 504};

void UBeamBackend::Initialize(FSubsystemCollectionBase& Collection)
{
	UE_LOG(LogBeamBackend, Warning, TEXT("Initializing UBeamBackend Subsystem!"));

	// Initializing InFlightRequestID to -1 since we increment, then use it.
	InFlightRequestId = new long();
	*InFlightRequestId = -1;

	// TODO: Define time offset for ticking so we don't tick every frame 
	TickDelegateHandle = FTSTicker::GetCoreTicker()
		.AddTicker(FTickerDelegate::CreateUObject(this, &UBeamBackend::TickRetryQueue));

	// Get subsystem dependency...
	BeamEnvironment = Cast<UBeamEnvironment>(Collection.InitializeDependency(UBeamEnvironment::StaticClass()));
	BeamUserSlots = Cast<UBeamUserSlots>(Collection.InitializeDependency(UBeamUserSlots::StaticClass()));


	// Initialize a buffer of 16 simultaneous requests.
	InFlightRequests.Reserve(16);

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
	FTSTicker::GetCoreTicker().RemoveTicker(TickDelegateHandle);

	delete InFlightRequestId;
}


template <typename TRequestData>
void UBeamBackend::StaticCheckForRequestType()
{
	static_assert(TIsDerivedFrom<TRequestData, FBeamBaseRequest>::Value, "TRequestData must be a FBeamBaseRequest type.");
}

template <typename TResponseData>
void UBeamBackend::StaticCheckForResponseType()
{
	static_assert(TIsDerivedFrom<TResponseData, FBeamBaseResponse>::Value, "TRequestData must be a FBeamBaseResponse type.");
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

template <typename TRequestData>
TUnrealRequestPtr UBeamBackend::CreateRequest(int64& OutRequestId, const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const TRequestData& RequestData)
{
	StaticCheckForRequestType<TRequestData>();

	// Ensures we get a valid Next Id even if requests get made from multiple threads.
	auto Req = CreateUnpreparedRequest(OutRequestId, RetryConfig);
	PrepareBeamableRequestToRealm(Req, TargetRealm);
	PrepareBeamableRequestVerbRouteBody<TRequestData>(Req, RequestData, BeamEnvironment->Data->APIUrl);
	return Req;
}

template <typename TRequestData>
TUnrealRequestPtr UBeamBackend::CreateAuthenticatedRequest(int64& OutRequestId, const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                                           const TRequestData& RequestData)
{
	StaticCheckForRequestType<TRequestData>();

	// Ensures we get a valid Next Id even if requests get made from multiple threads.
	auto Req = CreateUnpreparedRequest(OutRequestId, RetryConfig);
	PrepareBeamableRequestToRealmWithAuthToken(Req, TargetRealm, AuthToken);
	PrepareBeamableRequestVerbRouteBody<TRequestData>(Req, RequestData, BeamEnvironment->Data->APIUrl);
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
	InFlightRetryConfigs.Add(OutRequestId, RetryConfig);
	InFlightFailureCount.Add(OutRequestId, 0);
	return Req;
}

void UBeamBackend::DiscardUnsentRequest(const int64& RequestId)
{
	InFlightRequests.Remove(RequestId);
	InFlightRetryConfigs.Remove(RequestId);
	InFlightFailureCount.Remove(RequestId);
}


void UBeamBackend::CancelRequest(int64 RequestId)
{
	if (InFlightRequests.FindChecked(RequestId)->GetStatus() == EHttpRequestStatus::NotStarted)
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


void UBeamBackend::PrepareBeamableRequestToRealm(const TUnrealRequestPtr& Request, const FBeamRealmHandle& RealmHandle)
{
	Request->SetHeader(TEXT("Content-Type"), ACCEPT_HEADER);
	Request->SetHeader(TEXT("Accept"), ACCEPT_HEADER);

	const auto Cid = RealmHandle.Cid;
	const auto Pid = RealmHandle.Pid;

	if (!Cid.IsEmpty())
		Request->SetHeader(TEXT("X-KS-CLIENTID"), Cid);

	if (!Pid.IsEmpty())
		Request->SetHeader(TEXT("X-KS-PROJECTID"), Pid);

	UE_LOG(LogBeamBackend, Display, TEXT("Preparing to Send Request: CID=%s PID=%s"), *Cid, *Pid);
}

void UBeamBackend::PrepareBeamableRequestToRealmWithAuthToken(const TUnrealRequestPtr& Request,
                                                              const FBeamRealmHandle& RealmHandle,
                                                              const FBeamAuthToken& AuthToken)
{
	PrepareBeamableRequestToRealm(Request, RealmHandle);

	const auto AuthTokenHeader = FString::Printf(TEXT("Bearer %s"), *AuthToken.AccessToken);
	Request->SetHeader(TEXT("Authorization"), AuthTokenHeader);

	UE_LOG(LogBeamBackend, Display, TEXT("Preparing to Send Request: AUTH_HEADER=%s"), *AuthTokenHeader);
}


template <typename TRequestData>
void UBeamBackend::PrepareBeamableRequestVerbRouteBody(const TUnrealRequestPtr& Request, const TRequestData& RequestData, const FString& TargetBeamableUrl)
{
	StaticCheckForRequestType<TRequestData>();

	// Build Route --- this is determined by the environment we are in plus some other stuff
	// Build verb --- this is solely determined by the type of request we are making.
	// Build body from the request object
	FString Route = TargetBeamableUrl, Verb = "", Body = "";
	RequestData.BuildRoute(Route);
	RequestData.BuildVerb(Verb);
	RequestData.BuildBody(Body);

	// Set the Verb/Route/Body...
	Request->SetURL(Route);
	Request->SetVerb(Verb);
	Request->SetContentAsString(Body);

	UE_LOG(LogBeamBackend, Display, TEXT("Preparing to Send Request: VERB=%s ROUTE=%s, BODY=%s"), *Verb, *Route, *Body);
}


template <typename TRequestData, typename TResponseData, typename TSuccessCallback, typename TErrorCallback, typename TCompleteCallback>
FBeamRequestProcessor UBeamBackend::MakeBlueprintRequestProcessor(const int64& RequestId, const TRequestData& RequestData,
                                                                  TSuccessCallback OnSuccess, TErrorCallback OnError, TCompleteCallback OnComplete)
{
	StaticCheckForRequestType<TRequestData>();
	StaticCheckForResponseType<TResponseData>();

	FBeamRequestProcessor BoundResponseHandler(
		// Capture, by-value, the Backend system, request id for this request and request data --- these are plain structs with no allocations.
		[this, RequestId, RequestData, OnSuccess, OnError, OnComplete]

		// This just passes the captured data along to the Process function (we do this so we can unit test the process function in isolation).
	(FHttpRequestPtr, const FHttpResponsePtr Response, const bool bSent)
		{
			// Get the response contents
			const auto ResponseCode = Response->GetResponseCode();
			const auto ContentAsString = Response->GetContentAsString();

			ProcessBlueprintRequest<TRequestData, TResponseData, TSuccessCallback, TErrorCallback, TCompleteCallback>
				(ResponseCode, ContentAsString, bSent, RequestId, RequestData, OnSuccess, OnError, OnComplete);
		});

	// We return the build processor function so the API request function can bind it to UnrealHttpRequest's response handler delegate.
	return BoundResponseHandler;
}

template <typename TRequestData, typename TResponseData, typename TSuccessCallback, typename TErrorCallback, typename TCompleteCallback>
void UBeamBackend::ProcessBlueprintRequest(const int32& ResponseCode, const FString& ContentAsString, const bool bWasSent,
                                           const int64& RequestId, const TRequestData& RequestData,
                                           TSuccessCallback OnSuccess, TErrorCallback OnError, TCompleteCallback OnComplete)
{
	StaticCheckForRequestType<TRequestData>();
	StaticCheckForResponseType<TResponseData>();

	// Get retry stuff
	const auto CurrFailedCount = InFlightFailureCount.FindChecked(RequestId);
	const auto RetryConfig = InFlightRetryConfigs.FindChecked(RequestId);
	const auto ShouldRetryIfFail = RetryConfig.RetryMaxAttempt == -1 || CurrFailedCount < RetryConfig.RetryMaxAttempt;
	const auto bWillRetry = ShouldRetryIfFail && RETRY_ALLOWED_ERRORS.Contains(ResponseCode);

	// If the request was cancelled, we'll only run the OnComplete call 
	if (InFlightRequestsCancelled.Contains(RequestId))
	{
		UE_LOG(LogBeamBackend, Display, TEXT("Ignoring Request Response since it was cancelled. REQUEST_ID=%d"), RequestId);

		// Execute the handler if it's bound.
		const auto bExecutedCallsiteHandler = OnComplete.ExecuteIfBound(RequestId, RequestData);
		if (AlwaysLogCompleteResponses || !bExecutedCallsiteHandler)
		{
			UE_LOG(LogBeamBackend, Display, TEXT("Beamable Request Canceled | REQUEST_ID=%d, WAS_SUCCESS=%s, NUM_FAILURES=%d"), RequestId, InFlightFailureCount.FindRef(RequestId));
		}

		// Clean request up from InFlightRequest map
		InFlightRequests.Remove(RequestId);

		// Clean retry config up for this request
		InFlightRetryConfigs.Remove(RequestId);

		// Clean up Failed Counts on this request id.				
		InFlightFailureCount.Remove(RequestId);

		// Clean up the Request cancelled data.
		InFlightRequestsCancelled.Remove(RequestId);

		return;
	}

	// If the request was not sent, TODO we need to call the OnError+OnComplete callback informing that was the case and, hopefully, why.
	if (!bWasSent)
	{
		return;
	}

	// Stores whether or not the request was successful
	const auto bWasSuccess = ResponseCode == 200;

	// Parse the appropriate response body...
	if (bWasSuccess)
	{
		// Parse the response body and store it in the full response data.
		auto SuccessData = TResponseData();
		SuccessData.ResponseCode = ResponseCode;
		SuccessData.Body.BeamDeserialize(ContentAsString);

		// Run the callsite handler
		const auto ExecutedCallsiteHandler = OnSuccess.ExecuteIfBound(RequestId, RequestData, SuccessData);

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

		// If we should still retry (-1 == infinite retry)
		if (bWillRetry)
		{
			// Bump the failed count associated with this request id.					
			InFlightFailureCount[RequestId] = CurrFailedCount + 1;

			// Enqueue a request to try again
			FRequestToRetry Retry;
			Retry.RequestId = RequestId;
			Retry.IsBlueprint = 1;
			EnqueuedRetries.Enqueue(Retry);
		}

		// Run the callsite handler, if any.
		const auto ExecutedCallsiteHandler = OnError.ExecuteIfBound(RequestId, RequestData, ErrorData);

		// We fallback to global handler only if we didn't run the callsite one OR if we are configured to always run it.
		bool bExecutedGlobalHandler = false;
		if (AlwaysRunGlobalHandlers || !ExecutedCallsiteHandler && (GlobalRequestErrorHandler.IsBound() || GlobalRequestErrorCodeHandler.IsBound()))
		{
			GlobalRequestErrorHandler.Broadcast(RequestId, ErrorData);
			const auto _ = GlobalRequestErrorCodeHandler.ExecuteIfBound(RequestId, ErrorData);

			bExecutedGlobalHandler = true;
		}

		// We log the error only if neither callback was set OR if we are configured to do so.
		if (AlwaysLogErrorResponses || !bExecutedGlobalHandler && !ExecutedCallsiteHandler)
		{
			UE_LOG(LogBeamBackend, Display, TEXT("Beamable Request Failed | REQUEST_ID=%d, RESPONSE_CODE=%d, NUM_FAILURES=%d, WILL_RETRY=%s, RESPONSE_BODY=%s"), RequestId, ResponseCode,
			       CurrFailedCount,
			       bWillRetry ? TEXT("true") : TEXT("false"), *ContentAsString);
		}
	}

	// Clean up from InFlightRequests, only if we are not meant to retry it.
	if (bWasSuccess || !bWillRetry)
	{
		// Execute the handler if it's bound.
		const auto bExecutedCallsiteHandler = OnComplete.ExecuteIfBound(RequestId, RequestData);
		if (AlwaysLogCompleteResponses || !bExecutedCallsiteHandler)
		{
			UE_LOG(LogBeamBackend, Display, TEXT("Beamable Request Completed | REQUEST_ID=%d, RESPONSE_CODE=%d, WAS_SUCCESS=%s, NUM_FAILURES=%d"),
			       RequestId, ResponseCode, bWasSuccess ? TEXT("true") : TEXT("false"), CurrFailedCount);
		}

		// Clean request up from InFlightRequest map
		InFlightRequests.Remove(RequestId);

		// Clean retry config up for this request
		InFlightRetryConfigs.Remove(RequestId);

		// Clean up Failed Counts on this request id.				
		InFlightFailureCount.Remove(RequestId);
	}
}

template <typename TRequestData, typename TResponseData, typename TSuccessCallback, typename TErrorCallback, typename TCompleteCallback>
FBeamRequestProcessor UBeamBackend::MakeAuthenticatedBlueprintRequestProcessor(const int64& RequestId, const FBeamRealmHandle& RealmHandle, const FBeamAuthToken& AuthToken,
                                                                               const TRequestData& RequestData, TSuccessCallback OnSuccess, TErrorCallback OnError, TCompleteCallback OnComplete)
{
	StaticCheckForRequestType<TRequestData>();
	StaticCheckForResponseType<TResponseData>();

	FBeamRequestProcessor BoundResponseHandler(
		// Capture, by-value, the Backend system, request id for this request and request data --- these are plain structs with no allocations.
		[this, RequestId, AuthToken, RealmHandle, RequestData, OnSuccess, OnError, OnComplete]

		// This just passes the captured data along to the Process function (we do this so we can unit test the process function in isolation).
	(FHttpRequestPtr, FHttpResponsePtr response, bool sent)
		{
			// Get the response contents
			const auto ResponseCode = response->GetResponseCode();
			const auto ContentAsString = response->GetContentAsString();

			ProcessAuthenticatedBlueprintRequest<TRequestData, TResponseData, TSuccessCallback, TErrorCallback, TCompleteCallback>
				(ResponseCode, ContentAsString, sent, RequestId, RealmHandle, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		});

	// We return the build processor function so the API request function can bind it to UnrealHttpRequest's response handler delegate.
	return BoundResponseHandler;
}

template <typename TRequestData, typename TResponseData, typename TSuccessCallback, typename TErrorCallback, typename TCompleteCallback>
void UBeamBackend::ProcessAuthenticatedBlueprintRequest(const int32& ResponseCode, const FString& ContentAsString, const bool bWasSent,
                                                        const int64& RequestId, const FBeamRealmHandle& RealmHandle, const FBeamAuthToken& AuthToken,
                                                        const TRequestData& RequestData, TSuccessCallback OnSuccess, TErrorCallback OnError, TCompleteCallback OnComplete)
{
	StaticCheckForRequestType<TRequestData>();
	StaticCheckForResponseType<TResponseData>();

	// Get any UserSlot that matches this Pid/Auth Token, if any		
	FBeamRealmUser User;
	FUserSlot UserSlot;
	const auto bWasMadeWithUserSlot = BeamUserSlots->GetUserDataWithRefreshTokenAndPid(AuthToken.RefreshToken, RealmHandle.Pid, User, UserSlot);

	// If the request was cancelled, we'll only run the OnComplete call 
	if (InFlightRequestsCancelled.Contains(RequestId))
	{
		UE_LOG(LogBeamBackend, Display, TEXT("Ignoring Request Response since it was cancelled. REQUEST_ID=%d"), RequestId);

		// Execute the handler if it's bound.		
		const auto bExecutedCallsiteHandler = OnComplete.ExecuteIfBound(RequestId, RequestData);
		if (AlwaysLogCompleteResponses || !bExecutedCallsiteHandler)
		{
			UE_LOG(LogBeamBackend, Display, TEXT("Beamable Request Canceled | REQUEST_ID=%d, USER_SLOT=%s, WAS_SUCCESS=%s, NUM_FAILURES=%d"),
			       RequestId, bWasMadeWithUserSlot ? *UserSlot.SlotName : TEXT("Made Without UserSlot"), InFlightFailureCount.FindRef(RequestId));
		}

		// Clean request up from InFlightRequest map
		InFlightRequests.Remove(RequestId);

		// Clean retry config up for this request
		InFlightRetryConfigs.Remove(RequestId);

		// Clean up Failed Counts on this request id.				
		InFlightFailureCount.Remove(RequestId);

		// Clean up the Request cancelled data.
		InFlightRequestsCancelled.Remove(RequestId);

		return;
	}
	// Then, we handle success and error cases.


	// Get retry stuff
	const auto CurrFailedCount = InFlightFailureCount.FindChecked(RequestId);
	const auto RetryConfig = InFlightRetryConfigs.FindChecked(RequestId);
	const auto bShouldRetryIfFail = RetryConfig.RetryMaxAttempt == -1 || CurrFailedCount < RetryConfig.RetryMaxAttempt;

	// Whether or not the request should be retried
	const auto bWillRetry = bShouldRetryIfFail && RETRY_ALLOWED_ERRORS.Contains(ResponseCode);

	// If the request was not sent, TODO we need to call the OnError+OnComplete callback informing that was the case and, hopefully, why.
	if (!bWasSent)
	{
		return;
	}

	// Stores whether or not the request was successful
	const auto bWasSuccess = ResponseCode == 200;

	// Parse the appropriate response body...
	if (bWasSuccess)
	{
		// Parse the response body and store it in the full response data.
		auto SuccessData = TResponseData();
		SuccessData.ResponseCode = ResponseCode;
		SuccessData.Body.BeamDeserialize(ContentAsString);

		// Run the callsite handler
		const auto ExecutedCallsiteHandler = OnSuccess.ExecuteIfBound(RequestId, RequestData, SuccessData);

		// We only log the response if no callsite is given or if we are configured to always run it.
		if (AlwaysLogSuccessResponses || !ExecutedCallsiteHandler)
		{
			UE_LOG(LogBeamBackend, Display, TEXT("Beamable Request Successfull | REQUEST_ID=%d, USER_SLOT=%s, RESPONSE_CODE=%d, NUM_FAILURES=%d, RESPONSE_BODY=%s"),
			       RequestId, bWasMadeWithUserSlot ? *UserSlot.SlotName : TEXT("Made Without UserSlot"), ResponseCode, CurrFailedCount, *ContentAsString);
		}
	}
	else
	{
		// Otherwise, parse the body as an error response callback and store it in the full response data.
		FBeamErrorResponse ErrorData;
		FJsonObjectConverter::JsonObjectStringToUStruct(*ContentAsString, &ErrorData);

		if (bWillRetry)
		{
			// Bump the failed count associated with this request id.					
			InFlightFailureCount[RequestId] = CurrFailedCount + 1;

			// Enqueue a request to try again
			FRequestToRetry Retry;
			Retry.RequestId = RequestId;
			Retry.AuthToken = AuthToken;
			Retry.RealmHandle = RealmHandle;
			Retry.IsBlueprint = 1;
			EnqueuedRetries.Enqueue(Retry);
		}

		// Run the callsite handler, if any.
		const auto ExecutedCallsiteHandler = OnError.ExecuteIfBound(RequestId, RequestData, ErrorData);

		// We fallback to global handler only if we didn't run the callsite one OR if we are configured to always run it.
		bool bExecutedGlobalHandler = false;
		if (AlwaysRunGlobalHandlers || !ExecutedCallsiteHandler && (GlobalRequestErrorHandler.IsBound() || GlobalRequestErrorCodeHandler.IsBound()))
		{
			GlobalRequestErrorHandler.Broadcast(RequestId, ErrorData);
			const auto _ = GlobalRequestErrorCodeHandler.ExecuteIfBound(RequestId, ErrorData);

			bExecutedGlobalHandler = true;
		}

		// We log the error only if neither callback was set OR if we are configured to do so.
		if (AlwaysLogErrorResponses || !bExecutedGlobalHandler && !ExecutedCallsiteHandler)
		{
			UE_LOG(LogBeamBackend, Display, TEXT("Beamable Request Failed | REQUEST_ID=%d, USER_SLOT=%s, RESPONSE_CODE=%d, NUM_FAILURES=%d, WILL_RETRY=%s, RESPONSE_BODY=%s"),
			       RequestId, bWasMadeWithUserSlot ? *UserSlot.SlotName : TEXT("Made Without UserSlot"), ResponseCode, CurrFailedCount, bWillRetry ? TEXT("true") : TEXT("false"),
			       *ContentAsString);
		}
	}

	// Clean up from InFlightRequests, only if we are not meant to retry it.
	if (bWasSuccess || !bWillRetry)
	{
		// Execute the handler if it's bound.
		const auto bExecutedCallsiteHandler = OnComplete.ExecuteIfBound(RequestId, RequestData);
		if (AlwaysLogCompleteResponses || !bExecutedCallsiteHandler)
		{
			UE_LOG(LogBeamBackend, Display, TEXT("Beamable Request Completed | REQUEST_ID=%d, USER_SLOT=%s, RESPONSE_CODE=%d, WAS_SUCCESS=%s, NUM_FAILURES=%d"),
			       RequestId, bWasMadeWithUserSlot ? *UserSlot.SlotName : TEXT("Made Without UserSlot"), ResponseCode, bWasSuccess ? TEXT("true") : TEXT("false"), CurrFailedCount);
		}

		// Clean request up from InFlightRequest map
		InFlightRequests.Remove(RequestId);

		// Clean retry config up for this request
		InFlightRetryConfigs.Remove(RequestId);

		// Clean up Failed Counts on this request id.				
		InFlightFailureCount.Remove(RequestId);
	}
}

template <typename TRequestData, typename TResponseData>
FBeamRequestProcessor UBeamBackend::MakeCodeRequestProcessor(const int64& RequestId, const TRequestData& RequestData,
                                                             TBeamFullResponseHandler<TRequestData, TResponseData> ResponseHandler)
{
	StaticCheckForRequestType<TRequestData>();
	StaticCheckForResponseType<TResponseData>();

	// Get the handlers 
	auto OutProcessor = FBeamRequestProcessor(
		// Capture, by-value, the Backend system, request id for this request and request data --- these are plain structs with no allocations.
		[this, RequestId, RequestData, ResponseHandler]
		// This just passes the captured data along to the Process function (we do this so we can unit test the process function in isolation).
	(FHttpRequestPtr, FHttpResponsePtr response, bool sent)
		{
			const auto ResponseCode = response->GetResponseCode();
			const auto ContentAsString = response->GetContentAsString();

			ProcessCodeRequest<TRequestData, TResponseData>(ResponseCode, ContentAsString, sent, RequestId, RequestData, ResponseHandler);
		});

	// We return the build processor function so the API request function can bind it to UnrealHttpRequest's response handler delegate.
	return OutProcessor;
}

template <typename TRequestData, typename TResponseData>
void UBeamBackend::ProcessCodeRequest(const int32& ResponseCode, const FString& ContentAsString, const bool bWasSent,
                                      const int64& RequestId, const TRequestData& RequestData, TBeamFullResponseHandler<TRequestData, TResponseData> ResponseHandler)
{
	StaticCheckForRequestType<TRequestData>();
	StaticCheckForResponseType<TResponseData>();

	if (!bWasSent)
	{
		// TODO Invoke Callback but mapped to Beamable specific signature.
		return;
	}

	// Get retry stuff
	const auto CurrFailedCount = InFlightFailureCount.FindChecked(RequestId);
	const auto RetryConfig = InFlightRetryConfigs.FindChecked(RequestId);
	const auto bShouldRetryIfFail = RetryConfig.RetryMaxAttempt == -1 || RetryConfig.RetryMaxAttempt > CurrFailedCount;
	const auto bWillRetry = bShouldRetryIfFail && RETRY_ALLOWED_ERRORS.Contains(ResponseCode);

	auto FullResponse = FBeamFullResponse<TRequestData, TResponseData>();

	// Sets the request id for the request
	FullResponse.RequestId = RequestId;

	// Store the Request's data into the full response
	FullResponse.RequestData = RequestData;

	// Stores whether or not the request was successful, error or cancelled
	if (InFlightRequestsCancelled.Contains(RequestId))
		FullResponse.State = Cancelled;
	else
		FullResponse.State = ResponseCode == 200 ? Success : Error;

	// Stores which attempt we are in
	FullResponse.AttemptNumber = CurrFailedCount;

	// Parse the appropriate response body...
	if (FullResponse.State == Success)
	{
		// Parse the response body and store it in the full response data.
		FullResponse.SuccessData = TResponseData();
		FullResponse.SuccessData.ResponseCode = ResponseCode;
		FullResponse.SuccessData.Body.BeamDeserialize(ContentAsString);
	}
	else if (FullResponse.State == Error)
	{
		// Otherwise, parse the body as an error response callback and store it in the full response data.				
		FJsonObjectConverter::JsonObjectStringToUStruct(*ContentAsString, &FullResponse.ErrorData);

		// If we should still retry (-1 == infinite retry)
		if (bWillRetry)
		{
			// Bump the failed count associated with this request id.					
			InFlightFailureCount[RequestId] = CurrFailedCount + 1;

			// Enqueue a request to try again
			FRequestToRetry Retry;
			Retry.RequestId = RequestId;
			EnqueuedRetries.Enqueue(Retry);
		}

		// We run the response handler when we error --- we assume that they switch on FullResponse.State to handle only the error cases.
		const auto bExecutedCallsiteHandler = ResponseHandler.ExecuteIfBound(FullResponse);

		// We run global handlers for this request if we are configured to always run them
		auto bRanGlobalHandlers = false;
		if (AlwaysRunGlobalHandlers || !bExecutedCallsiteHandler)
		{
			GlobalRequestErrorHandler.Broadcast(RequestId, FullResponse.ErrorData);
			const auto _ = GlobalRequestErrorCodeHandler.ExecuteIfBound(RequestId, FullResponse.ErrorData);
			bRanGlobalHandlers = true;
		}

		// We log if we are configured to do so or as a fallback if no handler is configured
		if (AlwaysLogErrorResponses || (!bExecutedCallsiteHandler && !bRanGlobalHandlers))
		{
			UE_LOG(LogBeamBackend, Display, TEXT("Beamable Request Failed | REQUEST_ID=%d, RESPONSE_CODE=%d, NUM_FAILURES=%d, WILL_RETRY=%s, RESPONSE_BODY=%s"),
			       RequestId, ResponseCode, CurrFailedCount, bWillRetry ? TEXT("true") : TEXT("false"), *ContentAsString);
		}
	}

	// Only run the clean up after we are done retrying.
	if (!bWillRetry)
	{
		// Execute the handler if it's bound.
		const auto bExecutedCallsiteHandler = ResponseHandler.ExecuteIfBound(FullResponse);
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
				UE_LOG(LogBeamBackend, Display, TEXT("Beamable Request Failed | REQUEST_ID=%d, RESPONSE_CODE=%d, NUM_FAILURES=%d, WILL_RETRY=%s, RESPONSE_BODY=%s"),
				       RequestId, ResponseCode, CurrFailedCount, bWillRetry ? TEXT("true") : TEXT("false"), *ContentAsString);
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

		// Clean request up from InFlightRequest map
		InFlightRequests.Remove(RequestId);

		// Clean retry config up for this request
		InFlightRetryConfigs.Remove(RequestId);

		// Clean up Failed Counts on this request id.				
		InFlightFailureCount.Remove(RequestId);

		// Clean up from cancelled list if the request...				
		InFlightRequestsCancelled.Remove(RequestId);
	}
}


template <typename TRequestData, typename TResponseData>
FBeamRequestProcessor UBeamBackend::MakeAuthenticatedCodeRequestProcessor(const int64& RequestId, const FBeamRealmHandle& RealmHandle, const FBeamAuthToken& AuthToken,
                                                                          const TRequestData& RequestData, TBeamFullResponseHandler<TRequestData, TResponseData> ResponseHandler)
{
	StaticCheckForRequestType<TRequestData>();
	StaticCheckForResponseType<TResponseData>();

	// Get the handlers 
	auto OutProcessor = FBeamRequestProcessor(
		// Capture, by-value, the Backend system, request id for this request and request data --- these are plain structs with no allocations.
		[this, RequestId, RealmHandle, AuthToken, RequestData, ResponseHandler]
		// This just passes the captured data along to the Process function (we do this so we can unit test the process function in isolation).
	(FHttpRequestPtr, FHttpResponsePtr response, bool sent)
		{
			const auto ResponseCode = response->GetResponseCode();
			const auto ContentAsString = response->GetContentAsString();
			ProcessAuthenticatedCodeRequest<TRequestData, TResponseData>(ResponseCode, ContentAsString, sent, RequestId, RealmHandle, AuthToken, RequestData, ResponseHandler);
		});

	// We return the build processor function so the API request function can bind it to UnrealHttpRequest's response handler delegate. 
	return OutProcessor;
}

template <typename TRequestData, typename TResponseData>
void UBeamBackend::ProcessAuthenticatedCodeRequest(const int32& ResponseCode, const FString& ContentAsString, const bool bWasSent,
                                                   const int64& RequestId, const FBeamRealmHandle& RealmHandle, const FBeamAuthToken& AuthToken, const TRequestData& RequestData,
                                                   const TBeamFullResponseHandler<TRequestData, TResponseData>& ResponseHandler)
{
	StaticCheckForRequestType<TRequestData>();
	StaticCheckForResponseType<TResponseData>();

	// Get any UserSlot that matches this Pid/Auth Token, if any
	FBeamRealmUser User;
	FUserSlot UserSlot;
	const auto bWasMadeWithUserSlot = BeamUserSlots->GetUserDataWithRefreshTokenAndPid(AuthToken.RefreshToken, RealmHandle.Pid, User, UserSlot);
	const auto UserSlotLog = bWasMadeWithUserSlot ? UserSlot.SlotName : TEXT("Made Without UserSlot");

	if (!bWasSent)
	{
		// TODO Invoke Callback but mapped to Beamable specific signature.
		return;
	}

	// Get retry stuff
	const auto CurrFailedCount = InFlightFailureCount.FindChecked(RequestId);
	const auto RetryConfig = InFlightRetryConfigs.FindChecked(RequestId);
	const auto bShouldRetryIfFail = RetryConfig.RetryMaxAttempt == -1 || RetryConfig.RetryMaxAttempt > CurrFailedCount;
	const auto bWillRetry = bShouldRetryIfFail && RETRY_ALLOWED_ERRORS.Contains(ResponseCode);
	auto FullResponse = FBeamFullResponse<TRequestData, TResponseData>();

	// Sets the request id for the request
	FullResponse.RequestId = RequestId;

	// Store the Request's data into the full response
	FullResponse.RequestData = RequestData;

	// Stores whether or not the request was successful, error or cancelled
	if (InFlightRequestsCancelled.Contains(RequestId))
		FullResponse.State = Cancelled;
	else
		FullResponse.State = ResponseCode == 200 ? Success : Error;

	// Stores which attempt we are in
	FullResponse.AttemptNumber = CurrFailedCount;

	// Parse the appropriate response body...
	if (FullResponse.State == Success)
	{
		// Parse the response body and store it in the full response data.
		FullResponse.SuccessData = TResponseData();
		FullResponse.SuccessData.ResponseCode = ResponseCode;
		FullResponse.SuccessData.Body.BeamDeserialize(ContentAsString);
	}
	else if (FullResponse.State == Error)
	{
		// Otherwise, parse the body as an error response callback and store it in the full response data.				
		FJsonObjectConverter::JsonObjectStringToUStruct(*ContentAsString, &FullResponse.ErrorData);

		// If we should still retry (-1 == infinite retry)
		if (bWillRetry)
		{
			// Bump the failed count associated with this request id.					
			InFlightFailureCount[RequestId] = CurrFailedCount + 1;

			// Enqueue a request to try again
			FRequestToRetry Retry;
			Retry.RequestId = RequestId;
			Retry.AuthToken = AuthToken;
			Retry.RealmHandle = RealmHandle;
			EnqueuedRetries.Enqueue(Retry);
		}

		// We run the response handler when we error --- we assume that they switch on FullResponse.State to handle only the error cases.
		const auto bExecutedCallsiteHandler = ResponseHandler.ExecuteIfBound(FullResponse);

		// We run global handlers for this request if we are configured to always run them
		auto bRanGlobalHandlers = false;
		if (AlwaysRunGlobalHandlers || !bExecutedCallsiteHandler)
		{
			GlobalRequestErrorHandler.Broadcast(RequestId, FullResponse.ErrorData);
			const auto _ = GlobalRequestErrorCodeHandler.ExecuteIfBound(RequestId, FullResponse.ErrorData);
			bRanGlobalHandlers = true;
		}

		// We log if we are configured to do so or as a fallback if no handler is configured
		if (AlwaysLogErrorResponses || (!bExecutedCallsiteHandler && !bRanGlobalHandlers))
		{
			UE_LOG(LogBeamBackend, Display, TEXT("Beamable Request Failed | REQUEST_ID=%d, USER_SLOT=%s, RESPONSE_CODE=%d, NUM_FAILURES=%d, WILL_RETRY=%s, RESPONSE_BODY=%s"),
			       RequestId, *UserSlotLog, ResponseCode, CurrFailedCount, bWillRetry ? TEXT("true") : TEXT("false"),
			       *ContentAsString);
		}
	}

	if (!bWillRetry)
	{
		// Execute the handler if it's bound.
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
				UE_LOG(LogBeamBackend, Display, TEXT("Beamable Request Failed | REQUEST_ID=%d, USER_SLOT=%s, RESPONSE_CODE=%d, NUM_FAILURES=%d, WILL_RETRY=%s, RESPONSE_BODY=%s"),
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


		// Clean request up from InFlightRequest map
		InFlightRequests.Remove(RequestId);

		// Clean retry config up for this request
		InFlightRetryConfigs.Remove(RequestId);

		// Clean up Failed Counts on this request id.				
		InFlightFailureCount.Remove(RequestId);

		// Clean up from cancelled list if the request was cancelled...
		InFlightRequestsCancelled.Remove(RequestId);
	}
}

void UBeamBackend::DefaultExecuteRequestImpl(const FBeamRequestContext& RequestContext, FBeamConnectivity& Connectivity, int64 ActiveRequestId)
{
	UE_LOG(LogBeamBackend, Display, TEXT("Sending Request via Unreal HttpRequest's ProcessRequest."));
	InFlightRequests[ActiveRequestId]->ProcessRequest();
}


bool UBeamBackend::TickRetryQueue(float DeltaTime)
{
	FRequestToRetry FailedRequestCtx;
	while (EnqueuedRetries.Dequeue(FailedRequestCtx))
	{
		const auto ReqId = FailedRequestCtx.RequestId;
		const auto ReqAuthToken = FailedRequestCtx.AuthToken;

		// Get the retry configuration for the given request
		const auto RetryConfig = InFlightRetryConfigs.FindChecked(ReqId);
		const auto CurrRetryIdx = InFlightFailureCount.FindChecked(ReqId) - 1;
		const auto TimeToWait = CurrRetryIdx >= RetryConfig.RetryFalloffValues.Num()
			                        ? RetryConfig.RetryFalloffValues[RetryConfig.RetryFalloffValues.Num() - 1]
			                        : RetryConfig.RetryFalloffValues[CurrRetryIdx];

		UE_LOG(LogBeamBackend, Warning, TEXT("Failed Request so we are waiting for %.2f before trying again."), TimeToWait);
		InFlightProcessingRequests.Add(ReqId, FProcessingRequestRetry{FailedRequestCtx, TimeToWait, 0.0f});
	}

	// Wait for curr time in the exponential back-off scale.
	TArray<long> RetriesSentOut;
	for (auto& InFlightProcessingRequest : InFlightProcessingRequests)
	{
		const auto ProcessingReq = InFlightProcessingRequest.Value;
		if (ProcessingReq.AccumulatedTime < ProcessingReq.TimeToWait)
		{
			InFlightProcessingRequest.Value.AccumulatedTime += DeltaTime;
		}
		else
		{
			const auto RequestToRetry = InFlightProcessingRequest.Value.RetryHandle;
			const auto ReqId = RequestToRetry.RequestId;
			const auto ReqRealmHandle = RequestToRetry.RealmHandle;
			const auto ReqAuthToken = RequestToRetry.AuthToken;

			auto& FailedReq = InFlightRequests.FindChecked(ReqId);

			// 401 Unauthorized ("InvalidTokenError") and 403 Forbidden ("ExpiredTokenError") special-case handling.
			// Basically, our Auth model requires us to 
			if (FailedReq->GetResponse()->GetResponseCode() == 401 || FailedReq->GetResponse()->GetResponseCode() == 403)
			{
				// Make sure that any request to Beamable that fails due to unauthorized access actually sent a user in the first place. 
				check(!ReqAuthToken.RefreshToken.IsEmpty())

				// Create Login Refresh Token Request.
				TUnrealRequestPtr ReAuthRequest = FHttpModule::Get().CreateRequest();
				PrepareBeamableRequestToRealm(ReAuthRequest, ReqRealmHandle);
				FLoginRefreshTokenRequest Request;
				Request.Body.RefreshToken = ReqAuthToken.RefreshToken;
				PrepareBeamableRequestVerbRouteBody(ReAuthRequest, Request, BeamEnvironment->Data->APIUrl);

				ReAuthRequest->OnProcessRequestComplete().BindLambda([this, ReqId, ReqAuthToken, ReqRealmHandle, &FailedReq]
				(FHttpRequestPtr, FHttpResponsePtr response, bool sent)
					{
						if (!sent)
						{
							UE_LOG(LogBeamBackend, Display, TEXT("Failed to send re-auth request. REQUEST_ID=%d"), ReqId);
							// TODO: if we fail here --- we need to tell users so they can handle the "User Failed to Reauth" case
							return;
						}

						const auto ResponseCode = response->GetResponseCode();
						const auto ResponseBody = response->GetContentAsString();

						// Checks if the request was made using a user-slot or if people manually passed in the realm handle and refresh tokens.
						FBeamRealmUser RealmUserData;
						FUserSlot UserSlot;
						const auto WasMadeWithUserSlot = BeamUserSlots->GetUserDataWithRefreshTokenAndPid(ReqAuthToken.RefreshToken, ReqRealmHandle.Pid, RealmUserData, UserSlot);

						// Handle a successful re-authentication
						if (ResponseCode == 200)
						{
							// Extract the data from the response
							FTokenResponse TokenResponse;
							TokenResponse.BeamDeserialize(ResponseBody);

							// Create a new token from the token response so we can re-send the request with valid credentials
							FBeamAuthToken NewToken;
							NewToken.AccessToken = TokenResponse.AccessToken;
							NewToken.RefreshToken = TokenResponse.RefreshToken;
							NewToken.ExpiresIn = TokenResponse.ExpiresIn;

							// If it was made with a user slot, we need to make sure the new tokens are set up in that slot.
							// The reason that we simply assume there'll always be a UserSlot is to make integration tests
							if (WasMadeWithUserSlot)
							{
								UE_LOG(LogBeamBackend, Display, TEXT("Identified User Slot and Re-authing it. REQUEST_ID=%d, USER_SLOT=%s"), ReqId, *UserSlot.SlotName);
								// Re-auth the user at the found slot so that subsequent requests use the new token rather than this one.
								BeamUserSlots->AuthenticateUserAtSlot(UserSlot, NewToken.AccessToken, NewToken.RefreshToken, NewToken.ExpiresIn,
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
							UE_LOG(LogBeamBackend, Display, TEXT("Discarding Request since the user failed to re-authenticated. REQUEST_ID=%d"), ReqId);

							// If the failed re-auth was made using a user slot, we clear that slot.
							if (WasMadeWithUserSlot)
							{
								// TODO: Invoke multi-cast delegate to enable global handling of de-auth in cause our customers want to do it...
								// TODO: We should only do this for the UserSlot case.								

								BeamUserSlots->ClearUserAtSlot(UserSlot);
								UE_LOG(LogBeamBackend, Display, TEXT("Invalidated user data as the user failed to re-authenticated. USER_SLOT=%s"), *UserSlot.SlotName);
							}

							// Clean request up from InFlightRequest map
							InFlightRequests.Remove(ReqId);

							// Clean retry config up for this request
							InFlightRetryConfigs.Remove(ReqId);

							// Clean up Failed Counts on this request id.				
							InFlightFailureCount.Remove(ReqId);

							// Clean up the Request cancelled data.
							InFlightRequestsCancelled.Remove(ReqId);
						}
					});

				ReAuthRequest->ProcessRequest();
			}

			// 503 Service Unavailable and 504 Gateway Timeout are the types of errors that make sense retrying at all.
			// Other errors (such as 400 Bad Request) won't even show up in the retry flow as we filter them out and fail them at the first attempt.
			else if (FailedReq->GetResponse()->GetResponseCode() == 503 || FailedReq->GetResponse()->GetResponseCode() == 504)
			{
				// If we should just retry, simply send out the request again.
				UE_LOG(LogBeamBackend, Warning, TEXT("Failed Request so we are resending it!!!!."));
				FailedReq->ProcessRequest();
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

template <typename TRequestData>
void UBeamBackend::GetRetryConfig(const FUserSlot& UserSlotId, FBeamRetryConfig& Config)
{
	StaticCheckForRequestType<TRequestData>();

	const auto RequestType = FRequestType{TRequestData::StaticStruct()->GetName()};
	// If there's a retry config for this specific type of request and this specific user slot...
	if (PerUserPerTypeRetryConfig.Contains(RequestType.RequestName + "₢" + UserSlotId.SlotName))
		Config = PerUserPerTypeRetryConfig.FindRef(RequestType.RequestName + "₢" + UserSlotId.SlotName);
		// If there's a retry config for this specific type of request...
	else if (PerTypeRetryConfigs.Contains(RequestType))
		Config = PerTypeRetryConfigs.FindRef(RequestType);
		// If there's a retry config for requests from this user...
	else if (PerUserRetryConfig.Contains(UserSlotId.SlotName))
		Config = PerUserRetryConfig.FindRef(UserSlotId.SlotName);
		// Otherwise, just use the default one.
	else
		Config = DefaultRetryConfig;
}

template <typename TRequestData>
void UBeamBackend::GetRetryConfig(FBeamRetryConfig& Config)
{
	StaticCheckForRequestType<TRequestData>();

	const auto RequestType = TRequestData::StaticStruct()->GetName();
	// If there's a retry config for this specific type of request...
	if (PerTypeRetryConfigs.Contains(RequestType))
		Config = PerTypeRetryConfigs.FindRef(RequestType);
		// Otherwise, just use the default one.
	else
		Config = DefaultRetryConfig;
}

void UBeamBackend::SetRetryConfigForRequestType(const FRequestType& RequestType, const FBeamRetryConfig& RetryConfig)
{
	if (!PerTypeRetryConfigs.Contains(RequestType))
		PerTypeRetryConfigs.Add(RequestType, RetryConfig);
	else
		PerTypeRetryConfigs[RequestType] = RetryConfig;
}

void UBeamBackend::SetRetryConfigForUser(const FUserSlot UserSlot, const FBeamRetryConfig& RetryConfig)
{
	if (!PerUserRetryConfig.Contains(UserSlot))
		PerUserRetryConfig.Add(UserSlot, RetryConfig);
	else
		PerUserRetryConfig[UserSlot] = RetryConfig;
}

void UBeamBackend::SetRetryConfigForUserAndRequestType(const FUserSlot& UserSlot, const FRequestType& RequestType, const FBeamRetryConfig& RetryConfig)
{
	const auto Key = RequestType.RequestName + "₢" + UserSlot.SlotName;
	if (!PerUserPerTypeRetryConfig.Contains(Key))
		PerUserPerTypeRetryConfig.Add(Key, RetryConfig);
	else
		PerUserPerTypeRetryConfig[Key] = RetryConfig;
}

void UBeamBackend::ResetRetryConfigForRequestType(const FRequestType& RequestType)
{
	if (PerTypeRetryConfigs.Contains(RequestType))
		PerTypeRetryConfigs.Remove(RequestType);
}

void UBeamBackend::ResetRetryConfigForUser(const FUserSlot& UserSlot)
{
	if (PerUserRetryConfig.Contains(UserSlot))
		PerUserRetryConfig.Remove(UserSlot);
}

void UBeamBackend::ResetRetryConfigForUserAndRequestType(const FUserSlot& UserSlot, const FRequestType& RequestType)
{
	const auto Key = RequestType.RequestName + "₢" + UserSlot.SlotName;
	if (PerUserPerTypeRetryConfig.Contains(Key))
		PerUserPerTypeRetryConfig.Remove(Key);
}
