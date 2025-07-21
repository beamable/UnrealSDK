
#include "BeamableCore/Public/AutoGen/SubSystems/BeamSessionApi.h"
#include "BeamCoreSettings.h"


void UBeamSessionApi::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Backend = Cast<UBeamBackend>(Collection.InitializeDependency(UBeamBackend::StaticClass()));
	RequestTracker = Cast<UBeamRequestTracker>(Collection.InitializeDependency(UBeamRequestTracker::StaticClass()));
	ResponseCache = Cast<UBeamResponseCache>(Collection.InitializeDependency(UBeamResponseCache::StaticClass()));
	
}

void UBeamSessionApi::Deinitialize()
{
	Super::Deinitialize();
}




void UBeamSessionApi::BP_PostHeartbeatImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UPostHeartbeatRequest* RequestData, const FOnPostHeartbeatSuccess& OnSuccess, const FOnPostHeartbeatError& OnError, const FOnPostHeartbeatComplete& OnComplete, 
								int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);

	// If cached...
	if(FString CachedResponse; ResponseCache->TryHitResponseCache(RequestData, Request, CallingContext,  CachedResponse))
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Found data in cache.REQUEST_TYPE=%s\\n%s"), *RequestData->GetRequestType().Name, *CachedResponse);
		Backend->RunAuthenticatedBlueprintRequestProcessor<UPostHeartbeatRequest, USessionHeartbeat, FOnPostHeartbeatSuccess, FOnPostHeartbeatError, FOnPostHeartbeatComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPostHeartbeatRequest, USessionHeartbeat, FOnPostHeartbeatSuccess, FOnPostHeartbeatError, FOnPostHeartbeatComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamSessionApi::CPP_PostHeartbeatImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UPostHeartbeatRequest* RequestData, const FOnPostHeartbeatFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);
	
	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);

	// If cached...
	if(FString CachedResponse; ResponseCache->TryHitResponseCache(RequestData, Request, CallingContext,  CachedResponse))
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Found data in cache.REQUEST_TYPE=%s\\n%s"), *RequestData->GetRequestType().Name, *CachedResponse);
		Backend->RunAuthenticatedCodeRequestProcessor<UPostHeartbeatRequest, USessionHeartbeat>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPostHeartbeatRequest, USessionHeartbeat>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamSessionApi::BP_GetHistoryImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UGetHistoryRequest* RequestData, const FOnGetHistorySuccess& OnSuccess, const FOnGetHistoryError& OnError, const FOnGetHistoryComplete& OnComplete, 
								int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);

	// If cached...
	if(FString CachedResponse; ResponseCache->TryHitResponseCache(RequestData, Request, CallingContext,  CachedResponse))
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Found data in cache.REQUEST_TYPE=%s\\n%s"), *RequestData->GetRequestType().Name, *CachedResponse);
		Backend->RunAuthenticatedBlueprintRequestProcessor<UGetHistoryRequest, USessionHistoryResponse, FOnGetHistorySuccess, FOnGetHistoryError, FOnGetHistoryComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UGetHistoryRequest, USessionHistoryResponse, FOnGetHistorySuccess, FOnGetHistoryError, FOnGetHistoryComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamSessionApi::CPP_GetHistoryImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UGetHistoryRequest* RequestData, const FOnGetHistoryFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);
	
	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);

	// If cached...
	if(FString CachedResponse; ResponseCache->TryHitResponseCache(RequestData, Request, CallingContext,  CachedResponse))
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Found data in cache.REQUEST_TYPE=%s\\n%s"), *RequestData->GetRequestType().Name, *CachedResponse);
		Backend->RunAuthenticatedCodeRequestProcessor<UGetHistoryRequest, USessionHistoryResponse>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UGetHistoryRequest, USessionHistoryResponse>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamSessionApi::BP_GetStatusImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UBasicSessionGetStatusRequest* RequestData, const FOnBasicSessionGetStatusSuccess& OnSuccess, const FOnBasicSessionGetStatusError& OnError, const FOnBasicSessionGetStatusComplete& OnComplete, 
								int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);

	// If cached...
	if(FString CachedResponse; ResponseCache->TryHitResponseCache(RequestData, Request, CallingContext,  CachedResponse))
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Found data in cache.REQUEST_TYPE=%s\\n%s"), *RequestData->GetRequestType().Name, *CachedResponse);
		Backend->RunAuthenticatedBlueprintRequestProcessor<UBasicSessionGetStatusRequest, UOnlineStatusResponses, FOnBasicSessionGetStatusSuccess, FOnBasicSessionGetStatusError, FOnBasicSessionGetStatusComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UBasicSessionGetStatusRequest, UOnlineStatusResponses, FOnBasicSessionGetStatusSuccess, FOnBasicSessionGetStatusError, FOnBasicSessionGetStatusComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamSessionApi::CPP_GetStatusImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UBasicSessionGetStatusRequest* RequestData, const FOnBasicSessionGetStatusFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);
	
	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);

	// If cached...
	if(FString CachedResponse; ResponseCache->TryHitResponseCache(RequestData, Request, CallingContext,  CachedResponse))
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Found data in cache.REQUEST_TYPE=%s\\n%s"), *RequestData->GetRequestType().Name, *CachedResponse);
		Backend->RunAuthenticatedCodeRequestProcessor<UBasicSessionGetStatusRequest, UOnlineStatusResponses>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UBasicSessionGetStatusRequest, UOnlineStatusResponses>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamSessionApi::BP_GetClientHistoryImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UGetClientHistoryRequest* RequestData, const FOnGetClientHistorySuccess& OnSuccess, const FOnGetClientHistoryError& OnError, const FOnGetClientHistoryComplete& OnComplete, 
								int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);

	// If cached...
	if(FString CachedResponse; ResponseCache->TryHitResponseCache(RequestData, Request, CallingContext,  CachedResponse))
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Found data in cache.REQUEST_TYPE=%s\\n%s"), *RequestData->GetRequestType().Name, *CachedResponse);
		Backend->RunAuthenticatedBlueprintRequestProcessor<UGetClientHistoryRequest, USessionClientHistoryResponse, FOnGetClientHistorySuccess, FOnGetClientHistoryError, FOnGetClientHistoryComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UGetClientHistoryRequest, USessionClientHistoryResponse, FOnGetClientHistorySuccess, FOnGetClientHistoryError, FOnGetClientHistoryComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamSessionApi::CPP_GetClientHistoryImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UGetClientHistoryRequest* RequestData, const FOnGetClientHistoryFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);
	
	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);

	// If cached...
	if(FString CachedResponse; ResponseCache->TryHitResponseCache(RequestData, Request, CallingContext,  CachedResponse))
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Found data in cache.REQUEST_TYPE=%s\\n%s"), *RequestData->GetRequestType().Name, *CachedResponse);
		Backend->RunAuthenticatedCodeRequestProcessor<UGetClientHistoryRequest, USessionClientHistoryResponse>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UGetClientHistoryRequest, USessionClientHistoryResponse>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamSessionApi::BP_PostSessionImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UPostSessionRequest* RequestData, const FOnPostSessionSuccess& OnSuccess, const FOnPostSessionError& OnError, const FOnPostSessionComplete& OnComplete, 
								int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);

	// If cached...
	if(FString CachedResponse; ResponseCache->TryHitResponseCache(RequestData, Request, CallingContext,  CachedResponse))
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Found data in cache.REQUEST_TYPE=%s\\n%s"), *RequestData->GetRequestType().Name, *CachedResponse);
		Backend->RunAuthenticatedBlueprintRequestProcessor<UPostSessionRequest, UStartSessionResponse, FOnPostSessionSuccess, FOnPostSessionError, FOnPostSessionComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPostSessionRequest, UStartSessionResponse, FOnPostSessionSuccess, FOnPostSessionError, FOnPostSessionComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamSessionApi::CPP_PostSessionImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UPostSessionRequest* RequestData, const FOnPostSessionFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);
	
	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);

	// If cached...
	if(FString CachedResponse; ResponseCache->TryHitResponseCache(RequestData, Request, CallingContext,  CachedResponse))
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Found data in cache.REQUEST_TYPE=%s\\n%s"), *RequestData->GetRequestType().Name, *CachedResponse);
		Backend->RunAuthenticatedCodeRequestProcessor<UPostSessionRequest, UStartSessionResponse>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPostSessionRequest, UStartSessionResponse>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}






void UBeamSessionApi::CPP_PostHeartbeat(const FUserSlot& UserSlot, UPostHeartbeatRequest* Request, const FOnPostHeartbeatFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostHeartbeatRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_PostHeartbeatImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamSessionApi::CPP_GetHistory(const FUserSlot& UserSlot, UGetHistoryRequest* Request, const FOnGetHistoryFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UGetHistoryRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_GetHistoryImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamSessionApi::CPP_GetStatus(const FUserSlot& UserSlot, UBasicSessionGetStatusRequest* Request, const FOnBasicSessionGetStatusFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UBasicSessionGetStatusRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_GetStatusImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamSessionApi::CPP_GetClientHistory(const FUserSlot& UserSlot, UGetClientHistoryRequest* Request, const FOnGetClientHistoryFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UGetClientHistoryRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_GetClientHistoryImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamSessionApi::CPP_PostSession(const FUserSlot& UserSlot, UPostSessionRequest* Request, const FOnPostSessionFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostSessionRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_PostSessionImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}






void UBeamSessionApi::PostHeartbeat(FUserSlot UserSlot, UPostHeartbeatRequest* Request, const FOnPostHeartbeatSuccess& OnSuccess, const FOnPostHeartbeatError& OnError, const FOnPostHeartbeatComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostHeartbeatRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_PostHeartbeatImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamSessionApi::GetHistory(FUserSlot UserSlot, UGetHistoryRequest* Request, const FOnGetHistorySuccess& OnSuccess, const FOnGetHistoryError& OnError, const FOnGetHistoryComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UGetHistoryRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_GetHistoryImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamSessionApi::GetStatus(FUserSlot UserSlot, UBasicSessionGetStatusRequest* Request, const FOnBasicSessionGetStatusSuccess& OnSuccess, const FOnBasicSessionGetStatusError& OnError, const FOnBasicSessionGetStatusComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UBasicSessionGetStatusRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_GetStatusImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamSessionApi::GetClientHistory(FUserSlot UserSlot, UGetClientHistoryRequest* Request, const FOnGetClientHistorySuccess& OnSuccess, const FOnGetClientHistoryError& OnError, const FOnGetClientHistoryComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UGetClientHistoryRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_GetClientHistoryImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamSessionApi::PostSession(FUserSlot UserSlot, UPostSessionRequest* Request, const FOnPostSessionSuccess& OnSuccess, const FOnPostSessionError& OnError, const FOnPostSessionComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostSessionRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_PostSessionImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

