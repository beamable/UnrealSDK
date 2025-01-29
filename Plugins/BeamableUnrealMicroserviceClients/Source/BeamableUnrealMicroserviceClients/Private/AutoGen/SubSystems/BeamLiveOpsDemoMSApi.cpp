
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




void UBeamLiveOpsDemoMSApi::BP_PrepareNewPlayerImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                ULiveOpsDemoMSPrepareNewPlayerRequest* RequestData, const FOnLiveOpsDemoMSPrepareNewPlayerSuccess& OnSuccess, const FOnLiveOpsDemoMSPrepareNewPlayerError& OnError, const FOnLiveOpsDemoMSPrepareNewPlayerComplete& OnComplete, 
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
		Backend->RunAuthenticatedBlueprintRequestProcessor<ULiveOpsDemoMSPrepareNewPlayerRequest, ULiveOpsDemoMSPrepareNewPlayerResponse, FOnLiveOpsDemoMSPrepareNewPlayerSuccess, FOnLiveOpsDemoMSPrepareNewPlayerError, FOnLiveOpsDemoMSPrepareNewPlayerComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<ULiveOpsDemoMSPrepareNewPlayerRequest, ULiveOpsDemoMSPrepareNewPlayerResponse, FOnLiveOpsDemoMSPrepareNewPlayerSuccess, FOnLiveOpsDemoMSPrepareNewPlayerError, FOnLiveOpsDemoMSPrepareNewPlayerComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId);	
	}
}

void UBeamLiveOpsDemoMSApi::CPP_PrepareNewPlayerImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              ULiveOpsDemoMSPrepareNewPlayerRequest* RequestData, const FOnLiveOpsDemoMSPrepareNewPlayerFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
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
		Backend->RunAuthenticatedCodeRequestProcessor<ULiveOpsDemoMSPrepareNewPlayerRequest, ULiveOpsDemoMSPrepareNewPlayerResponse>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<ULiveOpsDemoMSPrepareNewPlayerRequest, ULiveOpsDemoMSPrepareNewPlayerResponse>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId);	
	}
}

		
void UBeamLiveOpsDemoMSApi::BP_UpgradeItemImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                ULiveOpsDemoMSUpgradeItemRequest* RequestData, const FOnLiveOpsDemoMSUpgradeItemSuccess& OnSuccess, const FOnLiveOpsDemoMSUpgradeItemError& OnError, const FOnLiveOpsDemoMSUpgradeItemComplete& OnComplete, 
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
		Backend->RunAuthenticatedBlueprintRequestProcessor<ULiveOpsDemoMSUpgradeItemRequest, ULiveOpsDemoMSUpgradeItemResponse, FOnLiveOpsDemoMSUpgradeItemSuccess, FOnLiveOpsDemoMSUpgradeItemError, FOnLiveOpsDemoMSUpgradeItemComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<ULiveOpsDemoMSUpgradeItemRequest, ULiveOpsDemoMSUpgradeItemResponse, FOnLiveOpsDemoMSUpgradeItemSuccess, FOnLiveOpsDemoMSUpgradeItemError, FOnLiveOpsDemoMSUpgradeItemComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId);	
	}
}

void UBeamLiveOpsDemoMSApi::CPP_UpgradeItemImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              ULiveOpsDemoMSUpgradeItemRequest* RequestData, const FOnLiveOpsDemoMSUpgradeItemFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
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
		Backend->RunAuthenticatedCodeRequestProcessor<ULiveOpsDemoMSUpgradeItemRequest, ULiveOpsDemoMSUpgradeItemResponse>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<ULiveOpsDemoMSUpgradeItemRequest, ULiveOpsDemoMSUpgradeItemResponse>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId);	
	}
}

		
void UBeamLiveOpsDemoMSApi::BP_IncrementStatImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                ULiveOpsDemoMSIncrementStatRequest* RequestData, const FOnLiveOpsDemoMSIncrementStatSuccess& OnSuccess, const FOnLiveOpsDemoMSIncrementStatError& OnError, const FOnLiveOpsDemoMSIncrementStatComplete& OnComplete, 
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
		Backend->RunAuthenticatedBlueprintRequestProcessor<ULiveOpsDemoMSIncrementStatRequest, ULiveOpsDemoMSIncrementStatResponse, FOnLiveOpsDemoMSIncrementStatSuccess, FOnLiveOpsDemoMSIncrementStatError, FOnLiveOpsDemoMSIncrementStatComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<ULiveOpsDemoMSIncrementStatRequest, ULiveOpsDemoMSIncrementStatResponse, FOnLiveOpsDemoMSIncrementStatSuccess, FOnLiveOpsDemoMSIncrementStatError, FOnLiveOpsDemoMSIncrementStatComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId);	
	}
}

void UBeamLiveOpsDemoMSApi::CPP_IncrementStatImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              ULiveOpsDemoMSIncrementStatRequest* RequestData, const FOnLiveOpsDemoMSIncrementStatFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
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
		Backend->RunAuthenticatedCodeRequestProcessor<ULiveOpsDemoMSIncrementStatRequest, ULiveOpsDemoMSIncrementStatResponse>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<ULiveOpsDemoMSIncrementStatRequest, ULiveOpsDemoMSIncrementStatResponse>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId);	
	}
}

		
void UBeamLiveOpsDemoMSApi::BP_GetSamlpeStatImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                ULiveOpsDemoMSGetSamlpeStatRequest* RequestData, const FOnLiveOpsDemoMSGetSamlpeStatSuccess& OnSuccess, const FOnLiveOpsDemoMSGetSamlpeStatError& OnError, const FOnLiveOpsDemoMSGetSamlpeStatComplete& OnComplete, 
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
		Backend->RunAuthenticatedBlueprintRequestProcessor<ULiveOpsDemoMSGetSamlpeStatRequest, ULiveOpsDemoMSGetSamlpeStatResponse, FOnLiveOpsDemoMSGetSamlpeStatSuccess, FOnLiveOpsDemoMSGetSamlpeStatError, FOnLiveOpsDemoMSGetSamlpeStatComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<ULiveOpsDemoMSGetSamlpeStatRequest, ULiveOpsDemoMSGetSamlpeStatResponse, FOnLiveOpsDemoMSGetSamlpeStatSuccess, FOnLiveOpsDemoMSGetSamlpeStatError, FOnLiveOpsDemoMSGetSamlpeStatComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId);	
	}
}

void UBeamLiveOpsDemoMSApi::CPP_GetSamlpeStatImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              ULiveOpsDemoMSGetSamlpeStatRequest* RequestData, const FOnLiveOpsDemoMSGetSamlpeStatFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
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
		Backend->RunAuthenticatedCodeRequestProcessor<ULiveOpsDemoMSGetSamlpeStatRequest, ULiveOpsDemoMSGetSamlpeStatResponse>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<ULiveOpsDemoMSGetSamlpeStatRequest, ULiveOpsDemoMSGetSamlpeStatResponse>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId);	
	}
}






void UBeamLiveOpsDemoMSApi::CPP_PrepareNewPlayer(const FUserSlot& UserSlot, ULiveOpsDemoMSPrepareNewPlayerRequest* Request, const FOnLiveOpsDemoMSPrepareNewPlayerFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(ULiveOpsDemoMSPrepareNewPlayerRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_PrepareNewPlayerImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, AuthenticatedUser.RealmHandle, -1, UserSlot, AS_None};
}

		
void UBeamLiveOpsDemoMSApi::CPP_UpgradeItem(const FUserSlot& UserSlot, ULiveOpsDemoMSUpgradeItemRequest* Request, const FOnLiveOpsDemoMSUpgradeItemFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(ULiveOpsDemoMSUpgradeItemRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_UpgradeItemImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, AuthenticatedUser.RealmHandle, -1, UserSlot, AS_None};
}

		
void UBeamLiveOpsDemoMSApi::CPP_IncrementStat(const FUserSlot& UserSlot, ULiveOpsDemoMSIncrementStatRequest* Request, const FOnLiveOpsDemoMSIncrementStatFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(ULiveOpsDemoMSIncrementStatRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_IncrementStatImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, AuthenticatedUser.RealmHandle, -1, UserSlot, AS_None};
}

		
void UBeamLiveOpsDemoMSApi::CPP_GetSamlpeStat(const FUserSlot& UserSlot, ULiveOpsDemoMSGetSamlpeStatRequest* Request, const FOnLiveOpsDemoMSGetSamlpeStatFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(ULiveOpsDemoMSGetSamlpeStatRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_GetSamlpeStatImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, AuthenticatedUser.RealmHandle, -1, UserSlot, AS_None};
}






void UBeamLiveOpsDemoMSApi::PrepareNewPlayer(FUserSlot UserSlot, ULiveOpsDemoMSPrepareNewPlayerRequest* Request, const FOnLiveOpsDemoMSPrepareNewPlayerSuccess& OnSuccess, const FOnLiveOpsDemoMSPrepareNewPlayerError& OnError, const FOnLiveOpsDemoMSPrepareNewPlayerComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(ULiveOpsDemoMSPrepareNewPlayerRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_PrepareNewPlayerImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, AuthenticatedUser.RealmHandle, -1, UserSlot, AS_None};
}

		
void UBeamLiveOpsDemoMSApi::UpgradeItem(FUserSlot UserSlot, ULiveOpsDemoMSUpgradeItemRequest* Request, const FOnLiveOpsDemoMSUpgradeItemSuccess& OnSuccess, const FOnLiveOpsDemoMSUpgradeItemError& OnError, const FOnLiveOpsDemoMSUpgradeItemComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(ULiveOpsDemoMSUpgradeItemRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_UpgradeItemImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, AuthenticatedUser.RealmHandle, -1, UserSlot, AS_None};
}

		
void UBeamLiveOpsDemoMSApi::IncrementStat(FUserSlot UserSlot, ULiveOpsDemoMSIncrementStatRequest* Request, const FOnLiveOpsDemoMSIncrementStatSuccess& OnSuccess, const FOnLiveOpsDemoMSIncrementStatError& OnError, const FOnLiveOpsDemoMSIncrementStatComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(ULiveOpsDemoMSIncrementStatRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_IncrementStatImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, AuthenticatedUser.RealmHandle, -1, UserSlot, AS_None};
}

		
void UBeamLiveOpsDemoMSApi::GetSamlpeStat(FUserSlot UserSlot, ULiveOpsDemoMSGetSamlpeStatRequest* Request, const FOnLiveOpsDemoMSGetSamlpeStatSuccess& OnSuccess, const FOnLiveOpsDemoMSGetSamlpeStatError& OnError, const FOnLiveOpsDemoMSGetSamlpeStatComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(ULiveOpsDemoMSGetSamlpeStatRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_GetSamlpeStatImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, AuthenticatedUser.RealmHandle, -1, UserSlot, AS_None};
}

