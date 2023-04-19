
#include "BeamableUnreal/AutoGen/SubSystems/BeamStandaloneMicroserviceMsApi.h"
#include "BeamCoreSettings.h"


void UBeamStandaloneMicroserviceMsApi::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Backend = Cast<UBeamBackend>(Collection.InitializeDependency(UBeamBackend::StaticClass()));
	RequestTracker = Cast<UBeamRequestTracker>(Collection.InitializeDependency(UBeamRequestTracker::StaticClass()));
	ResponseCache = Cast<UBeamResponseCache>(Collection.InitializeDependency(UBeamResponseCache::StaticClass()));
}

void UBeamStandaloneMicroserviceMsApi::Deinitialize()
{
	Super::Deinitialize();
}


void UBeamStandaloneMicroserviceMsApi::BP_AddImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UStandaloneMicroserviceMsAddRequest* RequestData,
                                                  const FOnStandaloneMicroserviceMsAddSuccess& OnSuccess, const FOnStandaloneMicroserviceMsAddError& OnError, const FOnStandaloneMicroserviceMsAddComplete& OnComplete,
                                                  int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateMicroserviceRequest(OutRequestId, TargetRealm, RetryConfig, RequestData, Prefix);

	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);

	// If cached...
	if(FString CachedResponse; ResponseCache->TryHitResponseCache(RequestData, Request, CallingContext,  CachedResponse))
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Found data in cache.REQUEST_TYPE=%s\\n%s"), *RequestData->GetRequestType().Name, *CachedResponse);
		Backend->RunBlueprintRequestProcessor<UStandaloneMicroserviceMsAddRequest, UStandaloneMicroserviceMsAddResponse, FOnStandaloneMicroserviceMsAddSuccess, FOnStandaloneMicroserviceMsAddError, FOnStandaloneMicroserviceMsAddComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{			
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UStandaloneMicroserviceMsAddRequest, UStandaloneMicroserviceMsAddResponse, FOnStandaloneMicroserviceMsAddSuccess, FOnStandaloneMicroserviceMsAddError, FOnStandaloneMicroserviceMsAddComplete>
			(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
		Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);		
	}	
}

void UBeamStandaloneMicroserviceMsApi::CPP_AddImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UStandaloneMicroserviceMsAddRequest* RequestData, const FOnStandaloneMicroserviceMsAddFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateMicroserviceRequest(OutRequestId, TargetRealm, RetryConfig, RequestData, Prefix);

	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);

	// If cached...
	if(FString CachedResponse; ResponseCache->TryHitResponseCache(RequestData, Request, CallingContext,  CachedResponse))
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Found data in cache.REQUEST_TYPE=%s\\n%s"), *RequestData->GetRequestType().Name, *CachedResponse);
		Backend->RunCodeRequestProcessor<UStandaloneMicroserviceMsAddRequest, UStandaloneMicroserviceMsAddResponse>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, RequestData, Handler);			
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UStandaloneMicroserviceMsAddRequest, UStandaloneMicroserviceMsAddResponse>
			(OutRequestId, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);	
	}
}



void UBeamStandaloneMicroserviceMsApi::BP_JoinNumbersAsStringImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UStandaloneMicroserviceMsJoinNumbersAsStringRequest* RequestData, const FOnStandaloneMicroserviceMsJoinNumbersAsStringSuccess& OnSuccess, const FOnStandaloneMicroserviceMsJoinNumbersAsStringError& OnError, const FOnStandaloneMicroserviceMsJoinNumbersAsStringComplete& OnComplete, 
								int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateMicroserviceAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData, Prefix);

	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);

	// If cached...
	if(FString CachedResponse; ResponseCache->TryHitResponseCache(RequestData, Request, CallingContext,  CachedResponse))
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Found data in cache.REQUEST_TYPE=%s\\n%s"), *RequestData->GetRequestType().Name, *CachedResponse);
		Backend->RunAuthenticatedBlueprintRequestProcessor<UStandaloneMicroserviceMsJoinNumbersAsStringRequest, UStandaloneMicroserviceMsJoinNumbersAsStringResponse, FOnStandaloneMicroserviceMsJoinNumbersAsStringSuccess, FOnStandaloneMicroserviceMsJoinNumbersAsStringError, FOnStandaloneMicroserviceMsJoinNumbersAsStringComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UStandaloneMicroserviceMsJoinNumbersAsStringRequest, UStandaloneMicroserviceMsJoinNumbersAsStringResponse, FOnStandaloneMicroserviceMsJoinNumbersAsStringSuccess, FOnStandaloneMicroserviceMsJoinNumbersAsStringError, FOnStandaloneMicroserviceMsJoinNumbersAsStringComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);	
	}
}

void UBeamStandaloneMicroserviceMsApi::CPP_JoinNumbersAsStringImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UStandaloneMicroserviceMsJoinNumbersAsStringRequest* RequestData, const FOnStandaloneMicroserviceMsJoinNumbersAsStringFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	const auto Request = Backend->CreateMicroserviceAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData, Prefix);
	
	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);

	// If cached...
	if(FString CachedResponse; ResponseCache->TryHitResponseCache(RequestData, Request, CallingContext,  CachedResponse))
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Found data in cache.REQUEST_TYPE=%s\\n%s"), *RequestData->GetRequestType().Name, *CachedResponse);
		Backend->RunAuthenticatedCodeRequestProcessor<UStandaloneMicroserviceMsJoinNumbersAsStringRequest, UStandaloneMicroserviceMsJoinNumbersAsStringResponse>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UStandaloneMicroserviceMsJoinNumbersAsStringRequest, UStandaloneMicroserviceMsJoinNumbersAsStringResponse>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);	
	}
}

		
void UBeamStandaloneMicroserviceMsApi::BP_AlwaysTrueImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UStandaloneMicroserviceMsAlwaysTrueRequest* RequestData, const FOnStandaloneMicroserviceMsAlwaysTrueSuccess& OnSuccess, const FOnStandaloneMicroserviceMsAlwaysTrueError& OnError, const FOnStandaloneMicroserviceMsAlwaysTrueComplete& OnComplete, 
								int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateMicroserviceAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData, Prefix);

	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);

	// If cached...
	if(FString CachedResponse; ResponseCache->TryHitResponseCache(RequestData, Request, CallingContext,  CachedResponse))
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Found data in cache.REQUEST_TYPE=%s\\n%s"), *RequestData->GetRequestType().Name, *CachedResponse);
		Backend->RunAuthenticatedBlueprintRequestProcessor<UStandaloneMicroserviceMsAlwaysTrueRequest, UStandaloneMicroserviceMsAlwaysTrueResponse, FOnStandaloneMicroserviceMsAlwaysTrueSuccess, FOnStandaloneMicroserviceMsAlwaysTrueError, FOnStandaloneMicroserviceMsAlwaysTrueComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UStandaloneMicroserviceMsAlwaysTrueRequest, UStandaloneMicroserviceMsAlwaysTrueResponse, FOnStandaloneMicroserviceMsAlwaysTrueSuccess, FOnStandaloneMicroserviceMsAlwaysTrueError, FOnStandaloneMicroserviceMsAlwaysTrueComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);	
	}
}

void UBeamStandaloneMicroserviceMsApi::CPP_AlwaysTrueImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UStandaloneMicroserviceMsAlwaysTrueRequest* RequestData, const FOnStandaloneMicroserviceMsAlwaysTrueFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	const auto Request = Backend->CreateMicroserviceAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData, Prefix);
	
	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);

	// If cached...
	if(FString CachedResponse; ResponseCache->TryHitResponseCache(RequestData, Request, CallingContext,  CachedResponse))
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Found data in cache.REQUEST_TYPE=%s\\n%s"), *RequestData->GetRequestType().Name, *CachedResponse);
		Backend->RunAuthenticatedCodeRequestProcessor<UStandaloneMicroserviceMsAlwaysTrueRequest, UStandaloneMicroserviceMsAlwaysTrueResponse>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UStandaloneMicroserviceMsAlwaysTrueRequest, UStandaloneMicroserviceMsAlwaysTrueResponse>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);	
	}
}




void UBeamStandaloneMicroserviceMsApi::CPP_Add(UStandaloneMicroserviceMsAddRequest* Request, const FOnStandaloneMicroserviceMsAddFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UStandaloneMicroserviceMsAddRequest::StaticClass()->GetName(), RetryConfig);
	
    int64 OutRequestId;
	CPP_AddImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, FUserSlot(), None};
}



void UBeamStandaloneMicroserviceMsApi::CPP_JoinNumbersAsString(const FUserSlot& UserSlot, UStandaloneMicroserviceMsJoinNumbersAsStringRequest* Request, const FOnStandaloneMicroserviceMsJoinNumbersAsStringFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UStandaloneMicroserviceMsJoinNumbersAsStringRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_JoinNumbersAsStringImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, AuthenticatedUser.RealmHandle, -1, UserSlot, None};
}

		
void UBeamStandaloneMicroserviceMsApi::CPP_AlwaysTrue(const FUserSlot& UserSlot, UStandaloneMicroserviceMsAlwaysTrueRequest* Request, const FOnStandaloneMicroserviceMsAlwaysTrueFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UStandaloneMicroserviceMsAlwaysTrueRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_AlwaysTrueImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, AuthenticatedUser.RealmHandle, -1, UserSlot, None};
}




void UBeamStandaloneMicroserviceMsApi::Add(UStandaloneMicroserviceMsAddRequest* Request, const FOnStandaloneMicroserviceMsAddSuccess& OnSuccess, const FOnStandaloneMicroserviceMsAddError& OnError, const FOnStandaloneMicroserviceMsAddComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UStandaloneMicroserviceMsAddRequest::StaticClass()->GetName(), RetryConfig);	
	
	int64 OutRequestId = 0;
	BP_AddImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, FUserSlot(), None};
}



void UBeamStandaloneMicroserviceMsApi::JoinNumbersAsString(FUserSlot UserSlot, UStandaloneMicroserviceMsJoinNumbersAsStringRequest* Request, const FOnStandaloneMicroserviceMsJoinNumbersAsStringSuccess& OnSuccess, const FOnStandaloneMicroserviceMsJoinNumbersAsStringError& OnError, const FOnStandaloneMicroserviceMsJoinNumbersAsStringComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UStandaloneMicroserviceMsJoinNumbersAsStringRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_JoinNumbersAsStringImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, AuthenticatedUser.RealmHandle, -1, UserSlot, None};
}

		
void UBeamStandaloneMicroserviceMsApi::AlwaysTrue(FUserSlot UserSlot, UStandaloneMicroserviceMsAlwaysTrueRequest* Request, const FOnStandaloneMicroserviceMsAlwaysTrueSuccess& OnSuccess, const FOnStandaloneMicroserviceMsAlwaysTrueError& OnError, const FOnStandaloneMicroserviceMsAlwaysTrueComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UStandaloneMicroserviceMsAlwaysTrueRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_AlwaysTrueImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, AuthenticatedUser.RealmHandle, -1, UserSlot, None};
}

