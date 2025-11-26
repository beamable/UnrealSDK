
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamLiveOpsDemoMSApi.h"
#include "BeamCoreSettings.h"


void UBeamLiveOpsDemoMSApi::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Backend = Cast<UBeamBackend>(Collection.InitializeDependency(UBeamBackend::StaticClass()));
	RequestTracker = Cast<UBeamRequestTracker>(Collection.InitializeDependency(UBeamRequestTracker::StaticClass()));
	ResponseCache = Cast<UBeamResponseCache>(Collection.InitializeDependency(UBeamResponseCache::StaticClass()));
	MicroserviceName = TEXT("LiveOpsDemoMS");
}

void UBeamLiveOpsDemoMSApi::Deinitialize()
{
	Super::Deinitialize();
}


void UBeamLiveOpsDemoMSApi::BP_UpgradeItemImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, ULiveOpsDemoMSUpgradeItemRequest* RequestData,
                                                  const FOnLiveOpsDemoMSUpgradeItemSuccess& OnSuccess, const FOnLiveOpsDemoMSUpgradeItemError& OnError, const FOnLiveOpsDemoMSUpgradeItemComplete& OnComplete,
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
		Backend->RunBlueprintRequestProcessor<ULiveOpsDemoMSUpgradeItemRequest, ULiveOpsDemoMSUpgradeItemResponse, FOnLiveOpsDemoMSUpgradeItemSuccess, FOnLiveOpsDemoMSUpgradeItemError, FOnLiveOpsDemoMSUpgradeItemComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{			
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<ULiveOpsDemoMSUpgradeItemRequest, ULiveOpsDemoMSUpgradeItemResponse, FOnLiveOpsDemoMSUpgradeItemSuccess, FOnLiveOpsDemoMSUpgradeItemError, FOnLiveOpsDemoMSUpgradeItemComplete>
			(OutRequestId, RequestData, OnSuccess, OnError, OnComplete, CallingContext);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
		Backend->SendPreparedRequest(OutRequestId, CallingContext);		
	}	
}

void UBeamLiveOpsDemoMSApi::CPP_UpgradeItemImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig,
                                               ULiveOpsDemoMSUpgradeItemRequest* RequestData, const FOnLiveOpsDemoMSUpgradeItemFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
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
		Backend->RunCodeRequestProcessor<ULiveOpsDemoMSUpgradeItemRequest, ULiveOpsDemoMSUpgradeItemResponse>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, RequestData, Handler);			
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeCodeRequestProcessor<ULiveOpsDemoMSUpgradeItemRequest, ULiveOpsDemoMSUpgradeItemResponse>
			(OutRequestId, RequestData, Handler, CallingContext);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamLiveOpsDemoMSApi::BP_IncrementStatImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, ULiveOpsDemoMSIncrementStatRequest* RequestData,
                                                  const FOnLiveOpsDemoMSIncrementStatSuccess& OnSuccess, const FOnLiveOpsDemoMSIncrementStatError& OnError, const FOnLiveOpsDemoMSIncrementStatComplete& OnComplete,
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
		Backend->RunBlueprintRequestProcessor<ULiveOpsDemoMSIncrementStatRequest, ULiveOpsDemoMSIncrementStatResponse, FOnLiveOpsDemoMSIncrementStatSuccess, FOnLiveOpsDemoMSIncrementStatError, FOnLiveOpsDemoMSIncrementStatComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{			
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<ULiveOpsDemoMSIncrementStatRequest, ULiveOpsDemoMSIncrementStatResponse, FOnLiveOpsDemoMSIncrementStatSuccess, FOnLiveOpsDemoMSIncrementStatError, FOnLiveOpsDemoMSIncrementStatComplete>
			(OutRequestId, RequestData, OnSuccess, OnError, OnComplete, CallingContext);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
		Backend->SendPreparedRequest(OutRequestId, CallingContext);		
	}	
}

void UBeamLiveOpsDemoMSApi::CPP_IncrementStatImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig,
                                               ULiveOpsDemoMSIncrementStatRequest* RequestData, const FOnLiveOpsDemoMSIncrementStatFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
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
		Backend->RunCodeRequestProcessor<ULiveOpsDemoMSIncrementStatRequest, ULiveOpsDemoMSIncrementStatResponse>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, RequestData, Handler);			
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeCodeRequestProcessor<ULiveOpsDemoMSIncrementStatRequest, ULiveOpsDemoMSIncrementStatResponse>
			(OutRequestId, RequestData, Handler, CallingContext);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamLiveOpsDemoMSApi::BP_GetSampleStatImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, ULiveOpsDemoMSGetSampleStatRequest* RequestData,
                                                  const FOnLiveOpsDemoMSGetSampleStatSuccess& OnSuccess, const FOnLiveOpsDemoMSGetSampleStatError& OnError, const FOnLiveOpsDemoMSGetSampleStatComplete& OnComplete,
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
		Backend->RunBlueprintRequestProcessor<ULiveOpsDemoMSGetSampleStatRequest, ULiveOpsDemoMSGetSampleStatResponse, FOnLiveOpsDemoMSGetSampleStatSuccess, FOnLiveOpsDemoMSGetSampleStatError, FOnLiveOpsDemoMSGetSampleStatComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{			
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<ULiveOpsDemoMSGetSampleStatRequest, ULiveOpsDemoMSGetSampleStatResponse, FOnLiveOpsDemoMSGetSampleStatSuccess, FOnLiveOpsDemoMSGetSampleStatError, FOnLiveOpsDemoMSGetSampleStatComplete>
			(OutRequestId, RequestData, OnSuccess, OnError, OnComplete, CallingContext);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
		Backend->SendPreparedRequest(OutRequestId, CallingContext);		
	}	
}

void UBeamLiveOpsDemoMSApi::CPP_GetSampleStatImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig,
                                               ULiveOpsDemoMSGetSampleStatRequest* RequestData, const FOnLiveOpsDemoMSGetSampleStatFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
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
		Backend->RunCodeRequestProcessor<ULiveOpsDemoMSGetSampleStatRequest, ULiveOpsDemoMSGetSampleStatResponse>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, RequestData, Handler);			
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeCodeRequestProcessor<ULiveOpsDemoMSGetSampleStatRequest, ULiveOpsDemoMSGetSampleStatResponse>
			(OutRequestId, RequestData, Handler, CallingContext);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}






void UBeamLiveOpsDemoMSApi::CPP_UpgradeItem(ULiveOpsDemoMSUpgradeItemRequest* Request, const FOnLiveOpsDemoMSUpgradeItemFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(ULiveOpsDemoMSUpgradeItemRequest::StaticClass()->GetName(), RetryConfig);
	
    int64 OutRequestId;
	CPP_UpgradeItemImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, FUserSlot(), AS_None};
}

		
void UBeamLiveOpsDemoMSApi::CPP_IncrementStat(ULiveOpsDemoMSIncrementStatRequest* Request, const FOnLiveOpsDemoMSIncrementStatFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(ULiveOpsDemoMSIncrementStatRequest::StaticClass()->GetName(), RetryConfig);
	
    int64 OutRequestId;
	CPP_IncrementStatImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, FUserSlot(), AS_None};
}

		
void UBeamLiveOpsDemoMSApi::CPP_GetSampleStat(ULiveOpsDemoMSGetSampleStatRequest* Request, const FOnLiveOpsDemoMSGetSampleStatFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(ULiveOpsDemoMSGetSampleStatRequest::StaticClass()->GetName(), RetryConfig);
	
    int64 OutRequestId;
	CPP_GetSampleStatImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, FUserSlot(), AS_None};
}






void UBeamLiveOpsDemoMSApi::UpgradeItem(ULiveOpsDemoMSUpgradeItemRequest* Request, const FOnLiveOpsDemoMSUpgradeItemSuccess& OnSuccess, const FOnLiveOpsDemoMSUpgradeItemError& OnError, const FOnLiveOpsDemoMSUpgradeItemComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(ULiveOpsDemoMSUpgradeItemRequest::StaticClass()->GetName(), RetryConfig);	
	
	int64 OutRequestId = 0;
	BP_UpgradeItemImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, FUserSlot(), AS_None};
}

		
void UBeamLiveOpsDemoMSApi::IncrementStat(ULiveOpsDemoMSIncrementStatRequest* Request, const FOnLiveOpsDemoMSIncrementStatSuccess& OnSuccess, const FOnLiveOpsDemoMSIncrementStatError& OnError, const FOnLiveOpsDemoMSIncrementStatComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(ULiveOpsDemoMSIncrementStatRequest::StaticClass()->GetName(), RetryConfig);	
	
	int64 OutRequestId = 0;
	BP_IncrementStatImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, FUserSlot(), AS_None};
}

		
void UBeamLiveOpsDemoMSApi::GetSampleStat(ULiveOpsDemoMSGetSampleStatRequest* Request, const FOnLiveOpsDemoMSGetSampleStatSuccess& OnSuccess, const FOnLiveOpsDemoMSGetSampleStatError& OnError, const FOnLiveOpsDemoMSGetSampleStatComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(ULiveOpsDemoMSGetSampleStatRequest::StaticClass()->GetName(), RetryConfig);	
	
	int64 OutRequestId = 0;
	BP_GetSampleStatImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, FUserSlot(), AS_None};
}



