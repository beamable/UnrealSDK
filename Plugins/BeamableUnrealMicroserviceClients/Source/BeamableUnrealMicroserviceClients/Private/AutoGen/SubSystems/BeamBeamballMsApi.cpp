
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamBeamballMsApi.h"
#include "BeamCoreSettings.h"


void UBeamBeamballMsApi::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Backend = Cast<UBeamBackend>(Collection.InitializeDependency(UBeamBackend::StaticClass()));
	RequestTracker = Cast<UBeamRequestTracker>(Collection.InitializeDependency(UBeamRequestTracker::StaticClass()));
	ResponseCache = Cast<UBeamResponseCache>(Collection.InitializeDependency(UBeamResponseCache::StaticClass()));
	MicroserviceName = TEXT("BeamballMs");
}

void UBeamBeamballMsApi::Deinitialize()
{
	Super::Deinitialize();
}


void UBeamBeamballMsApi::BP_ProcessMatchResultImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, UBeamballMsProcessMatchResultRequest* RequestData,
                                                  const FOnBeamballMsProcessMatchResultSuccess& OnSuccess, const FOnBeamballMsProcessMatchResultError& OnError, const FOnBeamballMsProcessMatchResultComplete& OnComplete,
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
		Backend->RunBlueprintRequestProcessor<UBeamballMsProcessMatchResultRequest, UBeamballMsProcessMatchResultResponse, FOnBeamballMsProcessMatchResultSuccess, FOnBeamballMsProcessMatchResultError, FOnBeamballMsProcessMatchResultComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{			
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UBeamballMsProcessMatchResultRequest, UBeamballMsProcessMatchResultResponse, FOnBeamballMsProcessMatchResultSuccess, FOnBeamballMsProcessMatchResultError, FOnBeamballMsProcessMatchResultComplete>
			(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
		Backend->SendPreparedRequest(OutRequestId, CallingContext);		
	}	
}

void UBeamBeamballMsApi::CPP_ProcessMatchResultImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig,
                                               UBeamballMsProcessMatchResultRequest* RequestData, const FOnBeamballMsProcessMatchResultFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
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
		Backend->RunCodeRequestProcessor<UBeamballMsProcessMatchResultRequest, UBeamballMsProcessMatchResultResponse>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, RequestData, Handler);			
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UBeamballMsProcessMatchResultRequest, UBeamballMsProcessMatchResultResponse>
			(OutRequestId, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}






void UBeamBeamballMsApi::CPP_ProcessMatchResult(UBeamballMsProcessMatchResultRequest* Request, const FOnBeamballMsProcessMatchResultFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UBeamballMsProcessMatchResultRequest::StaticClass()->GetName(), RetryConfig);
	
    int64 OutRequestId;
	CPP_ProcessMatchResultImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, FUserSlot(), AS_None};
}






void UBeamBeamballMsApi::ProcessMatchResult(UBeamballMsProcessMatchResultRequest* Request, const FOnBeamballMsProcessMatchResultSuccess& OnSuccess, const FOnBeamballMsProcessMatchResultError& OnError, const FOnBeamballMsProcessMatchResultComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UBeamballMsProcessMatchResultRequest::StaticClass()->GetName(), RetryConfig);	
	
	int64 OutRequestId = 0;
	BP_ProcessMatchResultImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, FUserSlot(), AS_None};
}



