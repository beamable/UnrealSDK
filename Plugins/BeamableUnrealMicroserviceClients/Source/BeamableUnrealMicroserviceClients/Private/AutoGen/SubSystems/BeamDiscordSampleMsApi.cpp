
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamDiscordSampleMsApi.h"
#include "BeamCoreSettings.h"


void UBeamDiscordSampleMsApi::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Backend = Cast<UBeamBackend>(Collection.InitializeDependency(UBeamBackend::StaticClass()));
	RequestTracker = Cast<UBeamRequestTracker>(Collection.InitializeDependency(UBeamRequestTracker::StaticClass()));
	ResponseCache = Cast<UBeamResponseCache>(Collection.InitializeDependency(UBeamResponseCache::StaticClass()));
	MicroserviceName = TEXT("DiscordSampleMs");
}

void UBeamDiscordSampleMsApi::Deinitialize()
{
	Super::Deinitialize();
}


void UBeamDiscordSampleMsApi::BP_UpdateFromDiscordImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, UDiscordSampleMsUpdateFromDiscordRequest* RequestData,
                                                  const FOnDiscordSampleMsUpdateFromDiscordSuccess& OnSuccess, const FOnDiscordSampleMsUpdateFromDiscordError& OnError, const FOnDiscordSampleMsUpdateFromDiscordComplete& OnComplete,
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
		Backend->RunBlueprintRequestProcessor<UDiscordSampleMsUpdateFromDiscordRequest, UDiscordSampleMsUpdateFromDiscordResponse, FOnDiscordSampleMsUpdateFromDiscordSuccess, FOnDiscordSampleMsUpdateFromDiscordError, FOnDiscordSampleMsUpdateFromDiscordComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{			
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UDiscordSampleMsUpdateFromDiscordRequest, UDiscordSampleMsUpdateFromDiscordResponse, FOnDiscordSampleMsUpdateFromDiscordSuccess, FOnDiscordSampleMsUpdateFromDiscordError, FOnDiscordSampleMsUpdateFromDiscordComplete>
			(OutRequestId, RequestData, OnSuccess, OnError, OnComplete, CallingContext);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
		Backend->SendPreparedRequest(OutRequestId, CallingContext);		
	}	
}

void UBeamDiscordSampleMsApi::CPP_UpdateFromDiscordImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig,
                                               UDiscordSampleMsUpdateFromDiscordRequest* RequestData, const FOnDiscordSampleMsUpdateFromDiscordFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
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
		Backend->RunCodeRequestProcessor<UDiscordSampleMsUpdateFromDiscordRequest, UDiscordSampleMsUpdateFromDiscordResponse>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, RequestData, Handler);			
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UDiscordSampleMsUpdateFromDiscordRequest, UDiscordSampleMsUpdateFromDiscordResponse>
			(OutRequestId, RequestData, Handler, CallingContext);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamDiscordSampleMsApi::BP_UpdateUserWhitelistedStatusImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, UDiscordSampleMsUpdateUserWhitelistedStatusRequest* RequestData,
                                                  const FOnDiscordSampleMsUpdateUserWhitelistedStatusSuccess& OnSuccess, const FOnDiscordSampleMsUpdateUserWhitelistedStatusError& OnError, const FOnDiscordSampleMsUpdateUserWhitelistedStatusComplete& OnComplete,
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
		Backend->RunBlueprintRequestProcessor<UDiscordSampleMsUpdateUserWhitelistedStatusRequest, UDiscordWhitelistedInfo, FOnDiscordSampleMsUpdateUserWhitelistedStatusSuccess, FOnDiscordSampleMsUpdateUserWhitelistedStatusError, FOnDiscordSampleMsUpdateUserWhitelistedStatusComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{			
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UDiscordSampleMsUpdateUserWhitelistedStatusRequest, UDiscordWhitelistedInfo, FOnDiscordSampleMsUpdateUserWhitelistedStatusSuccess, FOnDiscordSampleMsUpdateUserWhitelistedStatusError, FOnDiscordSampleMsUpdateUserWhitelistedStatusComplete>
			(OutRequestId, RequestData, OnSuccess, OnError, OnComplete, CallingContext);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
		Backend->SendPreparedRequest(OutRequestId, CallingContext);		
	}	
}

void UBeamDiscordSampleMsApi::CPP_UpdateUserWhitelistedStatusImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig,
                                               UDiscordSampleMsUpdateUserWhitelistedStatusRequest* RequestData, const FOnDiscordSampleMsUpdateUserWhitelistedStatusFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
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
		Backend->RunCodeRequestProcessor<UDiscordSampleMsUpdateUserWhitelistedStatusRequest, UDiscordWhitelistedInfo>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, RequestData, Handler);			
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UDiscordSampleMsUpdateUserWhitelistedStatusRequest, UDiscordWhitelistedInfo>
			(OutRequestId, RequestData, Handler, CallingContext);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}






void UBeamDiscordSampleMsApi::CPP_UpdateFromDiscord(UDiscordSampleMsUpdateFromDiscordRequest* Request, const FOnDiscordSampleMsUpdateFromDiscordFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UDiscordSampleMsUpdateFromDiscordRequest::StaticClass()->GetName(), RetryConfig);
	
    int64 OutRequestId;
	CPP_UpdateFromDiscordImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, FUserSlot(), AS_None};
}

		
void UBeamDiscordSampleMsApi::CPP_UpdateUserWhitelistedStatus(UDiscordSampleMsUpdateUserWhitelistedStatusRequest* Request, const FOnDiscordSampleMsUpdateUserWhitelistedStatusFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UDiscordSampleMsUpdateUserWhitelistedStatusRequest::StaticClass()->GetName(), RetryConfig);
	
    int64 OutRequestId;
	CPP_UpdateUserWhitelistedStatusImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, FUserSlot(), AS_None};
}






void UBeamDiscordSampleMsApi::UpdateFromDiscord(UDiscordSampleMsUpdateFromDiscordRequest* Request, const FOnDiscordSampleMsUpdateFromDiscordSuccess& OnSuccess, const FOnDiscordSampleMsUpdateFromDiscordError& OnError, const FOnDiscordSampleMsUpdateFromDiscordComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UDiscordSampleMsUpdateFromDiscordRequest::StaticClass()->GetName(), RetryConfig);	
	
	int64 OutRequestId = 0;
	BP_UpdateFromDiscordImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, FUserSlot(), AS_None};
}

		
void UBeamDiscordSampleMsApi::UpdateUserWhitelistedStatus(UDiscordSampleMsUpdateUserWhitelistedStatusRequest* Request, const FOnDiscordSampleMsUpdateUserWhitelistedStatusSuccess& OnSuccess, const FOnDiscordSampleMsUpdateUserWhitelistedStatusError& OnError, const FOnDiscordSampleMsUpdateUserWhitelistedStatusComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UDiscordSampleMsUpdateUserWhitelistedStatusRequest::StaticClass()->GetName(), RetryConfig);	
	
	int64 OutRequestId = 0;
	BP_UpdateUserWhitelistedStatusImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, FUserSlot(), AS_None};
}



