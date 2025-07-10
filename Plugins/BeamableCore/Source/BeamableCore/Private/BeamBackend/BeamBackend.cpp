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
#include "Kismet/GameplayStatics.h"

const FString UBeamBackend::HEADER_CONTENT_TYPE = FString(TEXT("Content-Type"));
const FString UBeamBackend::HEADER_ACCEPT = FString(TEXT("Accept"));
const FString UBeamBackend::HEADER_VALUE_ACCEPT_CONTENT_TYPE = FString(TEXT("application/json"));
// C#-Stack => application/vnd.beamable.v1+json
const FString UBeamBackend::HEADER_AUTHORIZATION = FString(TEXT("Authorization"));
const FString UBeamBackend::HEADER_VALUE_AUTHORIZATION = FString(TEXT("Bearer {0}"));
const FString UBeamBackend::HEADER_REQUEST_SCOPE = FString(TEXT("X-BEAM-SCOPE"));
const FString UBeamBackend::HEADER_ROUTING_KEY_MAP = FString(TEXT("X-BEAM-SERVICE-ROUTING-KEY"));
const FString UBeamBackend::HEADER_CLIENT_ID = FString(TEXT("X-KS-CLIENTID"));
const FString UBeamBackend::HEADER_PROJECT_ID = FString(TEXT("X-KS-PROJECTID"));
const FString UBeamBackend::HEADER_GAMERTAG = FString(TEXT("X-BEAM-GAMERTAG"));
const FString UBeamBackend::HEADER_SIGNATURE = FString(TEXT("X-BEAM-SIGNATURE"));
const FString UBeamBackend::HEADER_TIMEOUT = FString(TEXT("X-BEAM-TIMEOUT"));


const FString UBeamBackend::HEADER_BEAMABLE_VERSION = FString(TEXT("X-BEAM-SDK-VERSION"));
const FString UBeamBackend::HEADER_UNREAL_VERSION = FString(TEXT("X-BEAM-USER-AGENT-VERSION"));
const FString UBeamBackend::HEADER_ENGINE_TYPE = FString(TEXT("X-BEAM-USER-AGENT"));
const FString UBeamBackend::HEADER_APPLICATION_VERSION = FString(TEXT("X-BEAM-GAME-VERSION"));

const TArray<FString> UBeamBackend::AUTH_ERROR_CODE_RETRY_ALLOWED = TArray<FString>{
	TEXT("InvalidTokenError"), TEXT("TokenValidationError"), TEXT("ExpiredTokenError")
};

void UBeamBackend::Initialize(FSubsystemCollectionBase& Collection)
{
	UE_LOG(LogBeamBackend, Log, TEXT("Initializing UBeamBackend Subsystem!"));

	// Initializing InFlightRequestID to -1 since we increment, then use it.
	InFlightRequestId = -1;

	// Set up the retry ticking to run at 15 ticks / second TODO: expose these as settings
	RetryQueueTickHandle = FTSTicker::GetCoreTicker().AddTicker(
		FTickerDelegate::CreateUObject(this, &UBeamBackend::TickRetryQueue), 4 / 60);

	// Get subsystem dependency...
	BeamEnvironment = Cast<UBeamEnvironment>(Collection.InitializeDependency(UBeamEnvironment::StaticClass()));
	BeamUserSlots = Cast<UBeamUserSlots>(Collection.InitializeDependency(UBeamUserSlots::StaticClass()));

	// Initialize a buffer of 16 simultaneous requests.
	InFlightRequests.Reserve(1024 * 4);
	InFlightRequestContexts.Reserve(1024 * 4);
	InFlightFailureCount.Reserve(1024 * 4);
	InFlightRequestsCancelled.Reserve(1024 * 4);
	InFlightProcessingRequests.Reserve(1024 * 4);


	const auto ExecuteRequestImpl = GET_FUNCTION_NAME_CHECKED(UBeamBackend, DefaultExecuteRequestImpl);
	ExecuteRequestDelegate.BindUFunction(this, ExecuteRequestImpl);

	// Prepares the default retry configuration	
	DefaultRetryConfig = GetDefault<UBeamCoreSettings>()->FallbackRetryConfiguration;
	AlwaysRunGlobalHandlers = GetDefault<UBeamCoreSettings>()->AlwaysRunGlobalErrorHandlers;
	AlwaysLogSuccessResponses = GetDefault<UBeamCoreSettings>()->AlwaysLogSuccessResponses;
	AlwaysLogErrorResponses = GetDefault<UBeamCoreSettings>()->AlwaysLogErrorResponses;
	AlwaysLogCompleteResponses = GetDefault<UBeamCoreSettings>()->AlwaysLogCompletedResponses;

	// There are some things you can't test in PIE-mode and instead you must run as a Standalone Game.
	// There is no way for us to programatically set the routing key map like we do for regular PIE so...
	// In order to work with locally running microservices in this mode, this needs to be set via CommandLine or EnvVar.
	// See our docs for more information on how to configure this.
#if !UE_BUILD_SHIPPING
	FString RoutingKeyMap;
	if (!FParse::Value(FCommandLine::Get(), TEXT("beamable-routing-key-map="), RoutingKeyMap, false))
	{
		RoutingKeyMap = FPlatformMisc::GetEnvironmentVariable(TEXT("BEAMABLE_ROUTING_KEY_MAP"));
		if (!RoutingKeyMap.IsEmpty())
		{
			SetRoutingKeyMap(RoutingKeyMap);
			UE_LOG(LogBeamBackend, Display, TEXT("Parsed Routing Key from EnvVar | ROUTING_KEY_MAP=%s, NUM=%d"), *RoutingKeyMap, CurrentRoutingKeyMaps.Num());						
		}
	}
	else
	{
		SetRoutingKeyMap(RoutingKeyMap);
		UE_LOG(LogBeamBackend, Display, TEXT("Parsed Routing Key from CLArgs | ROUTING_KEY_MAP=%s, NUM=%d, FOR_OWNER=%s"), *RoutingKeyMap, CurrentRoutingKeyMaps.Num(), *CurrentRoutingKeyMaps[GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot()]);		
	}
#endif
}

void UBeamBackend::Deinitialize()
{
	FTSTicker::GetCoreTicker().RemoveTicker(RetryQueueTickHandle);
}

void UBeamBackend::UpdatePieState()
{
	const int32 MaxPieWorlds = 4;
	bIsInPIE = false;
	for (int i = 0; i < MaxPieWorlds; ++i)
	{
		bIsInPIE |= GEngine->GetWorldContextFromPIEInstance(i) != nullptr;
	}
}

bool UBeamBackend::IsInPIE() const
{
	return bIsInPIE;
}

FString UBeamBackend::GetProjectAppVersion() const
{
	FString AppVersion;
	GConfig->GetString(
		TEXT("/Script/EngineSettings.GeneralProjectSettings"),
		TEXT("ProjectVersion"),
		AppVersion,
		GGameIni
	);

	return AppVersion;
}

void UBeamBackend::TryTriggerRequestCompleteDelegates(const int64& RequestId)
{
	if (InFlightRequestContexts.Find(RequestId)->BeamStatus == AS_Completed)
	{
		UE_LOG(LogBeamBackend, Verbose,
		       TEXT("Checking OnRequestIdCompleted Delegates | REQUEST_ID=%lld, DELEGATE_COUNT=%d"), RequestId,
		       TickOnRequestIdCompletedDelegates.Num());
		for (const auto& OnRequestIdCompleted : TickOnRequestIdCompletedDelegates)
		{
			const auto bDidRun = OnRequestIdCompleted.ExecuteIfBound(RequestId);
			UE_LOG(LogBeamBackend, Verbose,
			       TEXT("Tried to invoke OnRequestIdCompleted Delegate | REQUEST_ID=%lld, DID_RUN=%s"), RequestId,
			       bDidRun ? TEXT("true") : TEXT("false"));
		}

		// After all request complete delegates have run, we try to clean up request data
		const auto _ = CleanUpRequestData();
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

TUnrealRequestPtr UBeamBackend::CreateUnpreparedRequest(int64& OutRequestId, const FBeamRetryConfig& RetryConfig)
{
	// Ensures we get a valid Next Id even if requests get made from multiple threads.
	const auto NextId = ++InFlightRequestId;
	OutRequestId = NextId;

	// Creates a request with the specified timeout.
	auto Req = FHttpModule::Get().CreateRequest();

	// We set the regular timeout to 0 so that we disable UE's bTimedOut checks which makes request objects unusable.
	Req->SetTimeout(0);

	// We set the activity timeout to the requested timeout since the regular timeout was deprecated in UE 5.4
	// In UE 5.4, the regular timeout will prevent the request object from being reused after a timeout.
	// Using ActivityTimeout makes it possible to reuse this request object (which is important for our retry logic --- see TickRetryQueue)
	Req->SetActivityTimeout(RetryConfig.Timeout);

	// Set the timeout header so that Beamable's Gateway itself knows how long
	long long timeoutInMilliseconds = RetryConfig.Timeout * 1000;
	// the value should not be lower than 10_000
	if (timeoutInMilliseconds >= 10000)
	{
		Req->SetHeader(FString(HEADER_TIMEOUT), FString::Printf(TEXT("%lld"), timeoutInMilliseconds));
	}

	UE_LOG(LogBeamBackend, Verbose, TEXT("Request Preparation: TIMEOUT_HEADER=%lld"), RetryConfig.Timeout);

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
	if (!InFlightRequests.Contains(RequestId) || InFlightRequests.FindChecked(RequestId)->GetStatus() ==
		EHttpRequestStatus::NotStarted)
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
		return InFlightFailureCount[RequestId];

	return 0;
}


void UBeamBackend::PrepareBeamableRequestToRealm(const TUnrealRequestPtr& UnrealRequest, const FBeamRealmHandle& RealmHandle)
{
	UnrealRequest->SetHeader(HEADER_CONTENT_TYPE, HEADER_VALUE_ACCEPT_CONTENT_TYPE);
	UnrealRequest->SetHeader(HEADER_ACCEPT, HEADER_VALUE_ACCEPT_CONTENT_TYPE);

	// Checking if it's running in a packing build or in the editor.
	if (FApp::IsGame())
	{		
		// So we know this request comes from Unreal or an UnrealServer (dedicated server builds).
		if (IsRunningDedicatedServer()) UnrealRequest->SetHeader(HEADER_ENGINE_TYPE, FString::Printf(TEXT("UnrealServer-%s"), *UGameplayStatics::GetPlatformName()));
		else UnrealRequest->SetHeader(HEADER_ENGINE_TYPE, FString::Printf(TEXT("Unreal-%s"), *UGameplayStatics::GetPlatformName()));
	}
	else
	{
		UnrealRequest->SetHeader(HEADER_ENGINE_TYPE, FString::Printf(TEXT("UnrealEditor-%s"), *UGameplayStatics::GetPlatformName()));
	}

	UnrealRequest->SetHeader(HEADER_BEAMABLE_VERSION, BeamEnvironment->Data->Version.ToString());
	UnrealRequest->SetHeader(HEADER_UNREAL_VERSION, FEngineVersion::Current().ToString());
	UnrealRequest->SetHeader(HEADER_APPLICATION_VERSION, GetProjectAppVersion());


	const auto Cid = RealmHandle.Cid;
	const auto Pid = RealmHandle.Pid;

	if (!Cid.AsString.IsEmpty())
	{
		const auto ScopeHeader = RealmHandle.Pid.AsString.IsEmpty()
			                         ? RealmHandle.Cid.AsString
			                         : FString::Format(
				                         TEXT("{0}.{1}"), {RealmHandle.Cid.AsString, RealmHandle.Pid.AsString});
		UnrealRequest->SetHeader(HEADER_REQUEST_SCOPE, ScopeHeader);
		UE_LOG(LogBeamBackend, Verbose, TEXT("Request Preparation: SCOPE_HEADER=%s"), *ScopeHeader);
	}
	else
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Request Preparation: Skipped SCOPE_HEADER as no CID was found."));
	}
}


void UBeamBackend::PrepareBeamableRequestToRealmWithAuthToken(const TUnrealRequestPtr& UnrealRequest,
                                                              const FBeamRealmHandle& RealmHandle,
                                                              const FBeamAuthToken& AuthToken)
{
	PrepareBeamableRequestToRealm(UnrealRequest, RealmHandle);

	if (!IsRunningDedicatedServer())
	{
		// For non-dedicated servers, we add an authorization header with the auth token. 
		const auto AuthTokenHeader = FString::Format(*HEADER_VALUE_AUTHORIZATION, {AuthToken.AccessToken});
		UnrealRequest->SetHeader(HEADER_AUTHORIZATION, AuthTokenHeader);

		UE_LOG(LogBeamBackend, Verbose, TEXT("Request Preparation - Auth: AUTH_HEADER=%s"), *AuthTokenHeader);
	}
	else
	{
		// For dedicated servers, we don't add the Authorization header as we sign the request right before we send it along (see DedicatedServerExecuteRequestImpl)
		// This will likely change once we have server auth tokens supported in both our backend stacks...
		// When that happens, signed requests will likely be removed from the UE SDK in favor of these due to the improved perf characteristics of sending requests authorized via tokens.
		const auto DedicatedServerRealm = GetDefault<UBeamCoreSettings>()->TargetRealm;
		const auto ScopeHeader = DedicatedServerRealm.Pid.AsString.IsEmpty()
			                         ? DedicatedServerRealm.Cid.AsString
			                         : FString::Format(
				                         TEXT("{0}.{1}"), {
					                         DedicatedServerRealm.Cid.AsString, DedicatedServerRealm.Pid.AsString
				                         });
		UnrealRequest->SetHeader(HEADER_REQUEST_SCOPE, ScopeHeader);
		UE_LOG(LogBeamBackend, Verbose, TEXT("Request Preparation - Target Realm Header: SCOPE_HEADER=%s"),
		       *ScopeHeader);
	}
}

void UBeamBackend::PrepareBeamableRequestToRealmWithRoutingKey(const TUnrealRequestPtr& Request, FUserSlot Slot)
{
	const auto OwnerUserSlot = GetDefault<UBeamCoreSettings>()->GetOwnerPlayerSlot();
	if (IsRunningDedicatedServer())
	{
		// For dedicated servers, we set the routing key of whatever is the one for the OwnerUserSlot.		
		FString RoutingKey = TEXT("No RoutingKey Set.");
		if (CurrentRoutingKeyMaps.Contains(OwnerUserSlot))
		{
			RoutingKey = CurrentRoutingKeyMaps[OwnerUserSlot];
			Request->SetHeader(HEADER_ROUTING_KEY_MAP, RoutingKey);
		}
		UE_LOG(LogBeamBackend, Verbose, TEXT("Request Preparation - Set Routing Key Map: ROUTING_KEY_MAP=%s"), *RoutingKey);
	}
	else
	{
		// For unauthenticated requests, we also use the RoutingKey set for the OwnerUser.
		if (Slot.Name.IsEmpty())
			Slot = OwnerUserSlot;

		// For non-dedicated servers, we set the routing key for the given slot.		
		FString RoutingKey = TEXT("No RoutingKey Set.");
		if (CurrentRoutingKeyMaps.Contains(Slot))
		{
			RoutingKey = CurrentRoutingKeyMaps[Slot];
			Request->SetHeader(HEADER_ROUTING_KEY_MAP, RoutingKey);
		}
		UE_LOG(LogBeamBackend, Verbose, TEXT("Request Preparation - Set Routing Key Map: ROUTING_KEY_MAP=%s"), *RoutingKey);
	}
}

bool UBeamBackend::HandlePIESessionRequestGuard(TUnrealRequestPtr Request, int64 RequestId)
{
	UpdatePieState();
	if (!bIsInPIE && InFlightPIERequests.Contains(Request))
	{
		InFlightPIERequests.Remove(Request);

		// Flag the request as completed so that it gets cleaned up on the next tick
		if (RequestId != -1)
		{
			FBeamRequestContext& RequestContext = *InFlightRequestContexts.Find(RequestId);
			RequestContext.BeamStatus = AS_Completed;
		}

		UE_LOG(LogBeamBackend, Warning, TEXT("Ignoring Beamable Request made during terminated PIE Session | REQUEST_ID=%lld"), RequestId);
		return true;
	}
	return false;
}

void UBeamBackend::DefaultExecuteRequestImpl(int64 ActiveRequestId, const UObject* CallingContext)
{
	UE_LOG(LogBeamBackend, Verbose, TEXT("Sending Request via Unreal HttpRequest's ProcessRequest. REQUEST_ID=%llu"),
	       ActiveRequestId);
	if (InFlightRequests[ActiveRequestId]->ProcessRequest())
	{
		auto Context = InFlightRequestContexts.FindRef(ActiveRequestId);
		Context.BeamStatus = AS_InFlight;
		InFlightRequestContexts[ActiveRequestId] = Context;
	}
}

void UBeamBackend::ExtractUrlForSignature(const FString& FullUrl, FString& Url)
{
	Url = FullUrl.RightChop(FullUrl.Find(TEXT("/"),
	                                     ESearchCase::IgnoreCase, ESearchDir::FromStart,
	                                     FullUrl.Find(TEXT(".")) - 1)
	);
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

		// Log the failed request and add it to the list of requests we have to retry.
		UE_LOG(LogBeamBackend, Verbose, TEXT("Beamable Retry Queue | Failed Request so we are waiting for %.2f before trying again. REQUEST_ID=%lld, ERROR_CODE=%s"),
		       TimeToWait, ReqId, *FailedRequestCtx.ErrorCode);
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
			const auto ReqContext = InFlightRequestContexts.FindChecked(ReqId);
			const auto RetryConfig = ReqContext.RetryConfiguration;
			const auto ReqRealmHandle = RequestToRetry.RealmHandle;
			const auto ReqAuthToken = RequestToRetry.AuthToken;

			auto& FailedReq = InFlightRequests.FindChecked(ReqId);

			// If the FailedReq object is not valid, something really bad happened and we need a bug report.
			ensureAlwaysMsgf(FailedReq.IsValid(),
			                 TEXT(
				                 "Beamable Retry Queue | Failed Request Object is no longer valid. This should never happen! Please turn-on Verbose logging for `LogBeamBackend` and report a bug to Beamable!"
			                 ));
			ensureAlwaysMsgf(FailedReq->GetStatus() != EHttpRequestStatus::Processing,
			                 TEXT(
				                 "Beamable Retry Queue | Failed Request Object is still being processed. This should never happen! Please turn-on Verbose logging for `LogBeamBackend` and report a bug to Beamable!"
			                 ));
			ensureAlwaysMsgf(ReqContext.BeamStatus == AS_InFlight,
			                 TEXT(
				                 "Beamable Retry Queue | This request was already completed. This should never happen! Please turn-on Verbose logging for `LogBeamBackend` and report a bug to Beamable! REQUEST_ID=%lld"
			                 ), ReqContext.RequestId);

			// If any of these custom errors, we need to re-auth via the refresh token. So we make that request and, when it gets back, we run the original request again.
			// "InvalidTokenError", "TokenValidationError", "ExpiredTokenError"
			if (AUTH_ERROR_CODE_RETRY_ALLOWED.Contains(RequestToRetry.ErrorCode))
			{
				// Make sure that any request to Beamable that fails due to unauthorized access actually sent a user in the first place. 
				check(!ReqAuthToken.RefreshToken.IsEmpty())

				// Create Login Refresh Token Request.
				TUnrealRequestPtr ReAuthRequest = FHttpModule::Get().CreateRequest();
				PrepareBeamableRequestToRealm(ReAuthRequest, ReqRealmHandle);
				PrepareBeamableRequestToRealmWithRoutingKey(ReAuthRequest, ReqContext.UserSlot);

				ULoginRefreshTokenRequest* Request = NewObject<ULoginRefreshTokenRequest>();
				Request->RefreshToken = ReqAuthToken.RefreshToken;
				Request->GrantType = "refresh_token";
				PrepareBeamableRequestVerbRouteBody(ReAuthRequest, Request, BeamEnvironment->GetAPIUrl());

				ReAuthRequest->OnProcessRequestComplete().BindLambda(
					[this, ReqId, ReqAuthToken, ReqRealmHandle, &FailedReq]
				(const FHttpRequestPtr Request, const FHttpResponsePtr Response, bool)

					{
						// Checks if the request was made using a user-slot or if people manually passed in the realm handle and refresh tokens.
						FBeamRealmUser RealmUserData;
						FUserSlot UserSlot;
						FString NamespacedSlotId;
						const auto WasMadeWithUserSlot = BeamUserSlots->GetUserDataWithRefreshTokenAndPid(
							ReqAuthToken.RefreshToken, ReqRealmHandle.Pid, RealmUserData, UserSlot, NamespacedSlotId);

						const auto ResponseCode = Response->GetResponseCode();
						const auto ResponseBody = Response->GetContentAsString();

						// Handle a successful re-authentication
						if (IsSuccessfulResponse(ResponseCode))
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
								FUserSlot NonNamespacedSlot;
								UBeamUserSlots::GetSlotIdFromNamespacedSlotId(UserSlot.Name, NonNamespacedSlot);
								UE_LOG(LogBeamBackend, Verbose, TEXT("Identified User Slot and Re-authing it. REQUEST_ID=%lld, USER_SLOT=%s"), ReqId, *NonNamespacedSlot.Name);
								// Re-auth the user at the found slot so that subsequent requests use the new token rather than this one.
								BeamUserSlots->SetAuthenticationDataAtNamespacedSlot(NamespacedSlotId, NewToken.AccessToken, NewToken.RefreshToken, FDateTime::UtcNow().ToUnixTimestamp(),
								                                                     NewToken.ExpiresIn, RealmUserData.RealmHandle.Cid, RealmUserData.RealmHandle.Pid);
								BeamUserSlots->SetGamerTagAtSlot(NamespacedSlotId, RealmUserData.GamerTag, this);
								BeamUserSlots->SetEmailAtSlot(NamespacedSlotId, RealmUserData.Email, this);
								BeamUserSlots->SetExternalIdsAtSlot(NamespacedSlotId, RealmUserData.ExternalIdentities, this);
								BeamUserSlots->SaveSlot(NamespacedSlotId, this);
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
							UE_LOG(LogBeamBackend, Verbose, TEXT("Discarding Request since the user failed to re-authenticated. REQUEST_ID=%lld" ), ReqId);

							// If the failed re-auth was made using a user slot, we clear that slot.
							if (WasMadeWithUserSlot)
							{
								BeamUserSlots->ClearUserAtSlot(UserSlot, USCR_FailedAuthentication, true);
								UE_LOG(LogBeamBackend, Verbose, TEXT("Invalidated user data as the user failed to re-authenticated. USER_SLOT=%s" ), *UserSlot.Name);
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
							Context->BeamStatus = AS_Completed;
						}
					});

				ReAuthRequest->ProcessRequest();
			}

			// If we match a HTTP Response Code OR a custom beamable error code, it means we should retry and so we do.
			else if (RetryConfig.HttpResponseCodes.Contains(RequestToRetry.ResponseCode) || RetryConfig.CustomErrorCodes.Contains(RequestToRetry.ErrorCode))
			{
				// If we should just retry, simply send out the request again.
				UE_LOG(LogBeamBackend, Verbose, TEXT("Beamable Retry Queue | Failed Request so we are resending it! REQUEST_STATUS=%d."), FailedReq->GetStatus());
				FailedReq->ProcessRequest();
			}

			// If we reach this point, it means that a valid request got in here that shouldn't have gotten here.
			else
			{
				const auto Route = FailedReq->GetURL();
				const auto Verb = FailedReq->GetVerb();
				const auto Body = FString(UTF8_TO_TCHAR(FailedReq->GetContent().GetData()));
				ensureAlwaysMsgf(
					false,
					TEXT(
						"Beamable Retry Queue | This request should not have been enqueued for retry, but it was. This should never happen! This should never happen! Please turn-on Verbose logging for `LogBeamBackend` and report a bug to Beamable! REQUEST_ID=%lld, VERB=%s, ROUTE=%s, BODY=%s, RETRY_RESP_CODES=%s, RETRY_ERR_CODES=%s"
					),
					ProcessingReq.RequestToRetry.RequestId, *Route, *Verb, *Body,
					*FString::JoinBy(RetryConfig.HttpResponseCodes, TEXT(","), [](int64 c) { return FString::FromInt(c); }),
					*FString::Join(RetryConfig.CustomErrorCodes, TEXT(",")));
			}

			RetriesSentOut.Add(InFlightProcessingRequest.Key);
		}
	}

	// Clear all retries that were sent out	
	TArray<FString> RetriesSentOutStr;
	for (auto SentOut : RetriesSentOut)
	{
		InFlightProcessingRequests.Remove(SentOut);
		RetriesSentOutStr.Add(FString::Printf(TEXT("%ld"), SentOut));
	}

	// Log out all requests that were actually sent out and removed from the InFlightProcessingRequests list.
	if (RetriesSentOutStr.Num() > 0)
	{
		UE_LOG(LogBeamBackend, Verbose,
		       TEXT("Beamable Retry Queue | Successfully sent out these requests. REQ_IDS=[%s]"),
		       *FString::Join(RetriesSentOutStr, TEXT(",")));
	}

	// Return true to keep this ticking...
	return true;
}

bool UBeamBackend::CleanUpRequestData()
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
		if (Ctx.BeamStatus == AS_Completed)
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
	TArray<FString> ReqIdsToCleanUpStr;
	for (const auto& IdToCleanUp : ReqIdsToCleanUp)
	{
		UE_LOG(LogBeamBackend, Verbose,
		       TEXT("Beamable CleanUp | Cleaning up all Request Data associated with Request. REQUEST_ID=%llu"),
		       IdToCleanUp);

		ReqIdsToCleanUpStr.Add(FString::Printf(TEXT("%lld"), IdToCleanUp));

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

	UE_LOG(LogBeamBackend, Verbose,
	       TEXT("Beamable CleanUp | Successfully cleaned up all Request Data. REQ_IDS=[%s]"),
	       *FString::Join(ReqIdsToCleanUpStr, TEXT(",")));

	// Return true since we don't ever want to stop cleaning up requests
	return true;
}

void UBeamBackend::UpdateResponseCache(const FRequestType& RequestType, const UObject* CallingContext, const FHttpRequestPtr& Request, const FString& Content)
{
	GEngine->GetEngineSubsystem<UBeamResponseCache>()->UpdateResponseCache(RequestType, CallingContext, Request, Content);
}

bool UBeamBackend::ExtractDataFromResponse(const FHttpRequestPtr Request, const FHttpResponsePtr Response, const bool bWasRequestCompleted, EHttpRequestStatus::Type& OutRequestStatus,
                                           int32& OutResponseCode, FString& OutResponseBody)
{
	OutRequestStatus = Request->GetStatus();
	if (bWasRequestCompleted)
	{
		// Get the response contents
		if (Response.IsValid())
		{
			OutResponseCode = Response->GetResponseCode();
			OutResponseBody = Response->GetContentAsString();
		}
		else
		{
			return false;
		}
	}
	else
	{
		if (!Response.IsValid())
		{
			OutResponseCode = 408;
			OutResponseBody = FString(R"({ "status": 408, "error": "NoResponse", "service": "", "message": "Null Response Found" })");
		}
		else if (Response->GetFailureReason() == EHttpFailureReason::ConnectionError)
		{
			OutResponseCode = 408;
			OutResponseBody = FString(R"({ "status": 408, "error": "ConnectionError", "service": "", "message": "Failed to connect" })");
		}
		else if (Response->GetFailureReason() == EHttpFailureReason::TimedOut)
		{
			OutResponseCode = 408;
			OutResponseBody = FString(R"({ "status": 408, "error": "Timeout", "service": "Gateway", "message": "Timeout" })");
		}
		else
		{
			OutResponseCode = 408;
			OutResponseBody = FString(R"({ "status": 408, "error": "Timeout", "service": "Gateway", "message": "Timeout" })");
		}
	}
	return true;
}



/**
	____           ___            __           __   _____                               
   / __ \___  ____/ (_)________ _/ /____  ____/ /  / ___/___  ______   _____  __________
  / / / / _ \/ __  / / ___/ __ `/ __/ _ \/ __  /   \__ \/ _ \/ ___/ | / / _ \/ ___/ ___/
 / /_/ /  __/ /_/ / / /__/ /_/ / /_/  __/ /_/ /   ___/ /  __/ /   | |/ /  __/ /  (__  ) 
/_____/\___/\__,_/_/\___/\__,_/\__/\___/\__,_/   /____/\___/_/    |___/\___/_/  /____/  
																						
*/


void UBeamBackend::DedicatedServerExecuteRequestImpl(int64 ActiveRequestId, const UObject* CallingContext)
{
	UE_LOG(LogBeamBackend, Verbose,
	       TEXT("Sending Signed Request via Unreal HttpRequest's ProcessRequest . REQUEST_ID=%llu"), ActiveRequestId);

	const auto HttpRequest = InFlightRequests[ActiveRequestId];

	// Build and set the signature prior to sending the request along.
	const auto Version = TEXT("1");
	const auto Pid = GetDefault<UBeamCoreSettings>()->TargetRealm.Pid.AsString;
	const auto Secret = RealmSecret;
	// A full URL looks like this: https://dev.api.beamable.com/object/stats/game.public.player.1595037680985091/
	// We are just getting the route (minus the domain) by finding the first forward slash after the '.' character.	
	const auto FullUrl = HttpRequest->GetURL();

	FString Url;
	ExtractUrlForSignature(FullUrl, Url);

	// Get the body as a UTF16 string so we can compose the signature 
	const auto BodyUTF8 = reinterpret_cast<const UTF8CHAR*>(HttpRequest->GetContent().GetData());
	const auto Body = FString(TStringConversion<FUTF8ToTCHAR_Convert>(BodyUTF8, HttpRequest->GetContentLength()));

	// Create an MD5 Hash of the UTF-8 representation of this string. 
	const auto SigPartsUTF16 = Secret + Pid + Version + Url + Body;
	const auto SigParts = TStringConversion<FTCHARToUTF8_Convert>(*SigPartsUTF16);
	uint8 Digest[16];
	FMD5 Md5Gen;
	Md5Gen.Update(reinterpret_cast<const unsigned char*>(SigParts.Get()), SigParts.Length());
	Md5Gen.Final(Digest);

	// Encode it into a Base64 string and set it as the signature header.
	const auto Signature = FBase64::Encode(Digest, 16);
	HttpRequest->SetHeader(HEADER_SIGNATURE, Signature);

	UE_LOG(LogBeamBackend, Verbose, TEXT(
		       "Sending Signed Request via Unreal HttpRequest's ProcessRequest."
		       " REQUEST_ID=%llu, SCOPE=%s, PID=%s, URL=%s, BODY=%s, REALM_SECRET=%s, SIG_PARTS=%s, SIGNATURE=%s"
	       ), ActiveRequestId, *HttpRequest->GetHeader(HEADER_REQUEST_SCOPE), *Pid, *Url, *Body, *Secret, *SigPartsUTF16, *Signature)

	if (HttpRequest->ProcessRequest())
	{
		auto Context = InFlightRequestContexts.FindRef(ActiveRequestId);
		Context.BeamStatus = AS_InFlight;
		InFlightRequestContexts[ActiveRequestId] = Context;
	}
}

void UBeamBackend::OverrideRequestAuthorization(TScriptInterface<IBeamBaseRequestInterface> Interface, FString AccessToken)
{
	const auto AuthTokenHeader = FString::Format(*HEADER_VALUE_AUTHORIZATION, {AccessToken});
	Interface->CustomHeaders.Add(HEADER_AUTHORIZATION, AuthTokenHeader);
}

void UBeamBackend::OverrideRequestGamerTag(TScriptInterface<IBeamBaseRequestInterface> Interface, FBeamGamerTag GamerTag)
{
	Interface->CustomHeaders.Add(HEADER_GAMERTAG, GamerTag.AsString);
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

bool UBeamBackend::IsRetryingTimeout(FBeamRequestContext Ctx)
{
	const auto bIsTimeout = Ctx.ResponseCode == 408;

	const auto Conf = Ctx.RetryConfiguration;
	const auto FailCount = GetSelf()->GetRequestFailureCount(Ctx.RequestId);

	return bIsTimeout && FailCount <= Ctx.RetryConfiguration.RetryMaxAttempt;
}

bool UBeamBackend::IsSuccessfulResponse(int32 ResponseCode)
{
	return ResponseCode >= 200 && ResponseCode < 300;
}

/*	 
	GENERIC-BEAM REQUEST FUNCTION
*/

TUnrealRequestPtr UBeamBackend::CreateGenericBeamRequest(int64& OutRequestId, const FBeamRetryConfig& RetryConfig, const UGenericBeamRequest* RequestData)
{
	UE_LOG(LogBeamBackend, Verbose, TEXT("Request Preparation - Preparing NonBeam Request: VERB=%s, URI=%s, BODY=%s"), *RequestData->Verb, *RequestData->URL, *RequestData->Body);

	// Ensures we get a valid Next Id even if requests get made from multiple threads.
	int64 ReqId;
	auto Req = CreateUnpreparedRequest(ReqId, RetryConfig);
	PrepareBeamableRequestVerbRouteBody(Req, RequestData, RequestData->URL);

	const auto RequestContext = FBeamRequestContext{ReqId, RetryConfig, FBeamRealmHandle{}, -1, FUserSlot(""), AS_None};

	// Keep track of this request and it's data. 
	InFlightRequestContexts.Add(ReqId, RequestContext);
	InFlightRequestData.Add(RequestContext, TScriptInterface<IBeamBaseRequestInterface>(const_cast<UGenericBeamRequest*>(RequestData)));

	// Store make sure we have a slot waiting for the response/error value to be added
	InFlightResponseBodyData.Add(RequestContext, nullptr);
	InFlightResponseErrorData.Add(RequestContext, FBeamErrorResponse{});


	INC_DWORD_STAT(STATID_RequestStarted)
	OutRequestId = ReqId;
	return Req;
}

/*	 
	ROUTING KEYS
*/

void UBeamBackend::SetRoutingKeyMap(TArray<FString> BeamoIds, TArray<FString> TargetKeys)
{
	ensureAlwaysMsgf(BeamoIds.Num() == TargetKeys.Num(), TEXT("These arrays must have the same number of elements; they're pairs."));

	TArray<FString> Mappings;
	for (int i = 0; i < BeamoIds.Num(); i++)
	{
		Mappings.Add(BeamoIds[i] + TEXT(":") + TargetKeys[i]);
	}

	SetRoutingKeyMap(FString::Join(Mappings, TEXT(",")));
}

void UBeamBackend::SetRoutingKeyMap(FUserSlot Slot, TArray<FString> BeamoIds, TArray<FString> TargetKeys)
{
	ensureAlwaysMsgf(BeamoIds.Num() == TargetKeys.Num(), TEXT("These arrays must have the same number of elements; they're pairs."));

	TArray<FString> Mappings;
	for (int i = 0; i < BeamoIds.Num(); i++)
	{
		Mappings.Add(BeamoIds[i] + TEXT(":") + TargetKeys[i]);
	}

	SetRoutingKeyMap(Slot, FString::Join(Mappings, TEXT(",")));
}

void UBeamBackend::SetRoutingKeyMap(FString RoutingKeyMap)
{
	const auto AllRuntimeSlots = GetDefault<UBeamCoreSettings>()->RuntimeUserSlots;
	for (FString Slot : AllRuntimeSlots)
		SetRoutingKeyMap(Slot, RoutingKeyMap);

	const auto AllDeveloperSlots = GetDefault<UBeamCoreSettings>()->DeveloperUserSlots;
	for (FString Slot : AllDeveloperSlots)
		SetRoutingKeyMap(Slot, RoutingKeyMap);
}

void UBeamBackend::SetRoutingKeyMap(FUserSlot ForSlot, FString RoutingKeyMap)
{
	CurrentRoutingKeyMaps.Add(ForSlot, RoutingKeyMap);
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
		UE_LOG(LogBeamBackend, Verbose,
		       TEXT("Falling back to Default Retry Configuration when getting config for Request Type!\nREQUEST_TYPE=%s"
		       ), *RequestType.Name);
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
		UE_LOG(LogBeamBackend, Verbose,
		       TEXT("Falling back to Default Retry Configuration when getting config for User Slot!\nUSER_SLOT=%s"),
		       *Slot.Name);
		Config = DefaultRetryConfig;
	}

	return bUserHasSpecialConfig;
}

bool UBeamBackend::GetRetryConfigForUserSlotAndRequestType(const FRequestType& RequestType, const FUserSlot& Slot,
                                                           FBeamRetryConfig& Config) const
{
	// If there's a retry config for this specific type of request and this specific user slot...
	const auto bUserHasSpecialConfigForRequestType = PerUserPerTypeRetryConfig.Contains(
		RequestType.Name + "₢" + Slot.Name);
	if (bUserHasSpecialConfigForRequestType)
	{
		UE_LOG(LogBeamBackend, Verbose,
		       TEXT("Found Config for User Slot and Request Type!\nUSER_SLOT=%s, REQUEST_TYPE=%s"), *Slot.Name,
		       *RequestType.Name);
		Config = PerUserPerTypeRetryConfig.FindRef(RequestType.Name + "₢" + Slot.Name);
	}
	else
	{
		// If there's a retry config for this specific type of request...
		if (PerTypeRetryConfigs.Contains(RequestType))
		{
			UE_LOG(LogBeamBackend, Verbose,
			       TEXT(
				       "Falling back to RequestType-only Config when getting config for User Slot and Request Type!\nUSER_SLOT=%s, REQUEST_TYPE=%s"
			       ), *Slot.Name,
			       *RequestType.Name);
			Config = PerTypeRetryConfigs.FindRef(RequestType);
		}
		else
		{
			// If there's a retry config for requests from this user...
			if (PerUserRetryConfig.Contains(Slot.Name))
			{
				UE_LOG(LogBeamBackend, Verbose,
				       TEXT(
					       "Falling back to User-only Config when getting config for User Slot and Request Type!\nUSER_SLOT=%s, REQUEST_TYPE=%s"
				       ), *Slot.Name,
				       *RequestType.Name);
				Config = PerUserRetryConfig.FindRef(Slot.Name);
			}
			else
			{
				UE_LOG(LogBeamBackend, Verbose,
				       TEXT(
					       "Falling back to Default Retry Configuration when getting config for User Slot and Request Type!\nUSER_SLOT=%s, REQUEST_TYPE=%s"
				       ), *Slot.Name,
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
	UE_LOG(LogBeamBackend, Verbose, TEXT("Setting retry config for RequestType.\nREQUEST_TYPE=%s, Config=%s"),
	       *RequestType.Name, *RetryString);
}

void UBeamBackend::SetRetryConfigForUserSlot(const FUserSlot Slot, const FBeamRetryConfig& RetryConfig)
{
	if (!PerUserRetryConfig.Contains(Slot))
		PerUserRetryConfig.Add(Slot, RetryConfig);
	else
		PerUserRetryConfig[Slot] = RetryConfig;

	FString RetryString;
	FJsonObjectConverter::UStructToJsonObjectString(RetryConfig, RetryString);
	UE_LOG(LogBeamBackend, Verbose, TEXT("Setting retry config for UserSlot.\nUSER_SLOT=%s, RETRY_CONFIG=%s"),
	       *Slot.Name, *RetryString);
}

void UBeamBackend::SetRetryConfigForUserSlotAndRequestType(const FUserSlot& Slot, const FRequestType& RequestType,
                                                           const FBeamRetryConfig& RetryConfig)
{
	const auto Key = RequestType.Name + "₢" + Slot.Name;
	if (!PerUserPerTypeRetryConfig.Contains(Key))
		PerUserPerTypeRetryConfig.Add(Key, RetryConfig);
	else
		PerUserPerTypeRetryConfig[Key] = RetryConfig;

	FString RetryString;
	FJsonObjectConverter::UStructToJsonObjectString(RetryConfig, RetryString);
	UE_LOG(LogBeamBackend, Verbose,
	       TEXT("Setting retry config for UserSlot and RequestType.\nUSER_SLOT=%s, REQUEST_TYPE=%s, RETRY_CONFIG=%s"),
	       *Slot.Name, *RequestType.Name, *RetryString);
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

	UE_LOG(LogBeamBackend, Verbose,
	       TEXT("Reseting retry config for UserSlot and Request Type.\nUSER_SLOT=%s, REQUEST_TYPE=%s"), *Slot.Name,
	       *RequestType.Name);
}
