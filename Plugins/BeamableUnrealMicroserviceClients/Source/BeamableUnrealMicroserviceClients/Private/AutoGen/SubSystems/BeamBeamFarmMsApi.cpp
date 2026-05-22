
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SubSystems/BeamBeamFarmMsApi.h"
#include "BeamCoreSettings.h"


void UBeamBeamFarmMsApi::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Backend = Cast<UBeamBackend>(Collection.InitializeDependency(UBeamBackend::StaticClass()));
	RequestTracker = Cast<UBeamRequestTracker>(Collection.InitializeDependency(UBeamRequestTracker::StaticClass()));
	ResponseCache = Cast<UBeamResponseCache>(Collection.InitializeDependency(UBeamResponseCache::StaticClass()));
	MicroserviceName = TEXT("BeamFarmMs");
}

void UBeamBeamFarmMsApi::Deinitialize()
{
	Super::Deinitialize();
}




void UBeamBeamFarmMsApi::BP_PlantSeedImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UBeamFarmMsPlantSeedRequest* RequestData, const FOnBeamFarmMsPlantSeedSuccess& OnSuccess, const FOnBeamFarmMsPlantSeedError& OnError, const FOnBeamFarmMsPlantSeedComplete& OnComplete, 
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
		Backend->RunAuthenticatedBlueprintRequestProcessor<UBeamFarmMsPlantSeedRequest, UPlantResult, FOnBeamFarmMsPlantSeedSuccess, FOnBeamFarmMsPlantSeedError, FOnBeamFarmMsPlantSeedComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UBeamFarmMsPlantSeedRequest, UPlantResult, FOnBeamFarmMsPlantSeedSuccess, FOnBeamFarmMsPlantSeedError, FOnBeamFarmMsPlantSeedComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete, CallingContext);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamBeamFarmMsApi::CPP_PlantSeedImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UBeamFarmMsPlantSeedRequest* RequestData, const FOnBeamFarmMsPlantSeedFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
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
		Backend->RunAuthenticatedCodeRequestProcessor<UBeamFarmMsPlantSeedRequest, UPlantResult>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UBeamFarmMsPlantSeedRequest, UPlantResult>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler, CallingContext);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamBeamFarmMsApi::BP_CollectHarvestImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UBeamFarmMsCollectHarvestRequest* RequestData, const FOnBeamFarmMsCollectHarvestSuccess& OnSuccess, const FOnBeamFarmMsCollectHarvestError& OnError, const FOnBeamFarmMsCollectHarvestComplete& OnComplete, 
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
		Backend->RunAuthenticatedBlueprintRequestProcessor<UBeamFarmMsCollectHarvestRequest, UCollectResult, FOnBeamFarmMsCollectHarvestSuccess, FOnBeamFarmMsCollectHarvestError, FOnBeamFarmMsCollectHarvestComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UBeamFarmMsCollectHarvestRequest, UCollectResult, FOnBeamFarmMsCollectHarvestSuccess, FOnBeamFarmMsCollectHarvestError, FOnBeamFarmMsCollectHarvestComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete, CallingContext);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamBeamFarmMsApi::CPP_CollectHarvestImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UBeamFarmMsCollectHarvestRequest* RequestData, const FOnBeamFarmMsCollectHarvestFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
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
		Backend->RunAuthenticatedCodeRequestProcessor<UBeamFarmMsCollectHarvestRequest, UCollectResult>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UBeamFarmMsCollectHarvestRequest, UCollectResult>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler, CallingContext);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamBeamFarmMsApi::BP_MutateImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UBeamFarmMsMutateRequest* RequestData, const FOnBeamFarmMsMutateSuccess& OnSuccess, const FOnBeamFarmMsMutateError& OnError, const FOnBeamFarmMsMutateComplete& OnComplete, 
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
		Backend->RunAuthenticatedBlueprintRequestProcessor<UBeamFarmMsMutateRequest, UMutationResult, FOnBeamFarmMsMutateSuccess, FOnBeamFarmMsMutateError, FOnBeamFarmMsMutateComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UBeamFarmMsMutateRequest, UMutationResult, FOnBeamFarmMsMutateSuccess, FOnBeamFarmMsMutateError, FOnBeamFarmMsMutateComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete, CallingContext);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamBeamFarmMsApi::CPP_MutateImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UBeamFarmMsMutateRequest* RequestData, const FOnBeamFarmMsMutateFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
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
		Backend->RunAuthenticatedCodeRequestProcessor<UBeamFarmMsMutateRequest, UMutationResult>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UBeamFarmMsMutateRequest, UMutationResult>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler, CallingContext);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamBeamFarmMsApi::BP_RegisterGroundItemImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UBeamFarmMsRegisterGroundItemRequest* RequestData, const FOnBeamFarmMsRegisterGroundItemSuccess& OnSuccess, const FOnBeamFarmMsRegisterGroundItemError& OnError, const FOnBeamFarmMsRegisterGroundItemComplete& OnComplete, 
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
		Backend->RunAuthenticatedBlueprintRequestProcessor<UBeamFarmMsRegisterGroundItemRequest, URegisterGroundItemResult, FOnBeamFarmMsRegisterGroundItemSuccess, FOnBeamFarmMsRegisterGroundItemError, FOnBeamFarmMsRegisterGroundItemComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UBeamFarmMsRegisterGroundItemRequest, URegisterGroundItemResult, FOnBeamFarmMsRegisterGroundItemSuccess, FOnBeamFarmMsRegisterGroundItemError, FOnBeamFarmMsRegisterGroundItemComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete, CallingContext);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamBeamFarmMsApi::CPP_RegisterGroundItemImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UBeamFarmMsRegisterGroundItemRequest* RequestData, const FOnBeamFarmMsRegisterGroundItemFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
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
		Backend->RunAuthenticatedCodeRequestProcessor<UBeamFarmMsRegisterGroundItemRequest, URegisterGroundItemResult>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UBeamFarmMsRegisterGroundItemRequest, URegisterGroundItemResult>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler, CallingContext);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamBeamFarmMsApi::BP_CollectGroundItemImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UBeamFarmMsCollectGroundItemRequest* RequestData, const FOnBeamFarmMsCollectGroundItemSuccess& OnSuccess, const FOnBeamFarmMsCollectGroundItemError& OnError, const FOnBeamFarmMsCollectGroundItemComplete& OnComplete, 
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
		Backend->RunAuthenticatedBlueprintRequestProcessor<UBeamFarmMsCollectGroundItemRequest, UCollectGroundItemResult, FOnBeamFarmMsCollectGroundItemSuccess, FOnBeamFarmMsCollectGroundItemError, FOnBeamFarmMsCollectGroundItemComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UBeamFarmMsCollectGroundItemRequest, UCollectGroundItemResult, FOnBeamFarmMsCollectGroundItemSuccess, FOnBeamFarmMsCollectGroundItemError, FOnBeamFarmMsCollectGroundItemComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete, CallingContext);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamBeamFarmMsApi::CPP_CollectGroundItemImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UBeamFarmMsCollectGroundItemRequest* RequestData, const FOnBeamFarmMsCollectGroundItemFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
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
		Backend->RunAuthenticatedCodeRequestProcessor<UBeamFarmMsCollectGroundItemRequest, UCollectGroundItemResult>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UBeamFarmMsCollectGroundItemRequest, UCollectGroundItemResult>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler, CallingContext);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}






void UBeamBeamFarmMsApi::CPP_PlantSeed(const FUserSlot& UserSlot, UBeamFarmMsPlantSeedRequest* Request, const FOnBeamFarmMsPlantSeedFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UBeamFarmMsPlantSeedRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_PlantSeedImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamFarmMsApi::CPP_CollectHarvest(const FUserSlot& UserSlot, UBeamFarmMsCollectHarvestRequest* Request, const FOnBeamFarmMsCollectHarvestFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UBeamFarmMsCollectHarvestRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_CollectHarvestImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamFarmMsApi::CPP_Mutate(const FUserSlot& UserSlot, UBeamFarmMsMutateRequest* Request, const FOnBeamFarmMsMutateFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UBeamFarmMsMutateRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_MutateImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamFarmMsApi::CPP_RegisterGroundItem(const FUserSlot& UserSlot, UBeamFarmMsRegisterGroundItemRequest* Request, const FOnBeamFarmMsRegisterGroundItemFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UBeamFarmMsRegisterGroundItemRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_RegisterGroundItemImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamFarmMsApi::CPP_CollectGroundItem(const FUserSlot& UserSlot, UBeamFarmMsCollectGroundItemRequest* Request, const FOnBeamFarmMsCollectGroundItemFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UBeamFarmMsCollectGroundItemRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_CollectGroundItemImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}






void UBeamBeamFarmMsApi::PlantSeed(FUserSlot UserSlot, UBeamFarmMsPlantSeedRequest* Request, const FOnBeamFarmMsPlantSeedSuccess& OnSuccess, const FOnBeamFarmMsPlantSeedError& OnError, const FOnBeamFarmMsPlantSeedComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UBeamFarmMsPlantSeedRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_PlantSeedImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamFarmMsApi::CollectHarvest(FUserSlot UserSlot, UBeamFarmMsCollectHarvestRequest* Request, const FOnBeamFarmMsCollectHarvestSuccess& OnSuccess, const FOnBeamFarmMsCollectHarvestError& OnError, const FOnBeamFarmMsCollectHarvestComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UBeamFarmMsCollectHarvestRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_CollectHarvestImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamFarmMsApi::Mutate(FUserSlot UserSlot, UBeamFarmMsMutateRequest* Request, const FOnBeamFarmMsMutateSuccess& OnSuccess, const FOnBeamFarmMsMutateError& OnError, const FOnBeamFarmMsMutateComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UBeamFarmMsMutateRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_MutateImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamFarmMsApi::RegisterGroundItem(FUserSlot UserSlot, UBeamFarmMsRegisterGroundItemRequest* Request, const FOnBeamFarmMsRegisterGroundItemSuccess& OnSuccess, const FOnBeamFarmMsRegisterGroundItemError& OnError, const FOnBeamFarmMsRegisterGroundItemComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UBeamFarmMsRegisterGroundItemRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_RegisterGroundItemImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamFarmMsApi::CollectGroundItem(FUserSlot UserSlot, UBeamFarmMsCollectGroundItemRequest* Request, const FOnBeamFarmMsCollectGroundItemSuccess& OnSuccess, const FOnBeamFarmMsCollectGroundItemError& OnError, const FOnBeamFarmMsCollectGroundItemComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UBeamFarmMsCollectGroundItemRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_CollectGroundItemImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

