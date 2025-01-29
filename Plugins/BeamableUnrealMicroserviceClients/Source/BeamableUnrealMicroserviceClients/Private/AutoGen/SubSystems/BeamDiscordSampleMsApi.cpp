
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




void UBeamDiscordSampleMsApi::BP_UpdateFromDiscordImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UDiscordSampleMsUpdateFromDiscordRequest* RequestData, const FOnDiscordSampleMsUpdateFromDiscordSuccess& OnSuccess, const FOnDiscordSampleMsUpdateFromDiscordError& OnError, const FOnDiscordSampleMsUpdateFromDiscordComplete& OnComplete, 
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
		Backend->RunAuthenticatedBlueprintRequestProcessor<UDiscordSampleMsUpdateFromDiscordRequest, UDiscordSampleMsUpdateFromDiscordResponse, FOnDiscordSampleMsUpdateFromDiscordSuccess, FOnDiscordSampleMsUpdateFromDiscordError, FOnDiscordSampleMsUpdateFromDiscordComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UDiscordSampleMsUpdateFromDiscordRequest, UDiscordSampleMsUpdateFromDiscordResponse, FOnDiscordSampleMsUpdateFromDiscordSuccess, FOnDiscordSampleMsUpdateFromDiscordError, FOnDiscordSampleMsUpdateFromDiscordComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId);	
	}
}

void UBeamDiscordSampleMsApi::CPP_UpdateFromDiscordImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UDiscordSampleMsUpdateFromDiscordRequest* RequestData, const FOnDiscordSampleMsUpdateFromDiscordFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
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
		Backend->RunAuthenticatedCodeRequestProcessor<UDiscordSampleMsUpdateFromDiscordRequest, UDiscordSampleMsUpdateFromDiscordResponse>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UDiscordSampleMsUpdateFromDiscordRequest, UDiscordSampleMsUpdateFromDiscordResponse>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId);	
	}
}

		
void UBeamDiscordSampleMsApi::BP_UpdateUserWhitelistedStatusImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UDiscordSampleMsUpdateUserWhitelistedStatusRequest* RequestData, const FOnDiscordSampleMsUpdateUserWhitelistedStatusSuccess& OnSuccess, const FOnDiscordSampleMsUpdateUserWhitelistedStatusError& OnError, const FOnDiscordSampleMsUpdateUserWhitelistedStatusComplete& OnComplete, 
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
		Backend->RunAuthenticatedBlueprintRequestProcessor<UDiscordSampleMsUpdateUserWhitelistedStatusRequest, UDiscordWhitelistedInfo, FOnDiscordSampleMsUpdateUserWhitelistedStatusSuccess, FOnDiscordSampleMsUpdateUserWhitelistedStatusError, FOnDiscordSampleMsUpdateUserWhitelistedStatusComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UDiscordSampleMsUpdateUserWhitelistedStatusRequest, UDiscordWhitelistedInfo, FOnDiscordSampleMsUpdateUserWhitelistedStatusSuccess, FOnDiscordSampleMsUpdateUserWhitelistedStatusError, FOnDiscordSampleMsUpdateUserWhitelistedStatusComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId);	
	}
}

void UBeamDiscordSampleMsApi::CPP_UpdateUserWhitelistedStatusImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UDiscordSampleMsUpdateUserWhitelistedStatusRequest* RequestData, const FOnDiscordSampleMsUpdateUserWhitelistedStatusFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
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
		Backend->RunAuthenticatedCodeRequestProcessor<UDiscordSampleMsUpdateUserWhitelistedStatusRequest, UDiscordWhitelistedInfo>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UDiscordSampleMsUpdateUserWhitelistedStatusRequest, UDiscordWhitelistedInfo>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId);	
	}
}






void UBeamDiscordSampleMsApi::CPP_UpdateFromDiscord(const FUserSlot& UserSlot, UDiscordSampleMsUpdateFromDiscordRequest* Request, const FOnDiscordSampleMsUpdateFromDiscordFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UDiscordSampleMsUpdateFromDiscordRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_UpdateFromDiscordImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, AuthenticatedUser.RealmHandle, -1, UserSlot, AS_None};
}

		
void UBeamDiscordSampleMsApi::CPP_UpdateUserWhitelistedStatus(const FUserSlot& UserSlot, UDiscordSampleMsUpdateUserWhitelistedStatusRequest* Request, const FOnDiscordSampleMsUpdateUserWhitelistedStatusFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UDiscordSampleMsUpdateUserWhitelistedStatusRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_UpdateUserWhitelistedStatusImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, AuthenticatedUser.RealmHandle, -1, UserSlot, AS_None};
}






void UBeamDiscordSampleMsApi::UpdateFromDiscord(FUserSlot UserSlot, UDiscordSampleMsUpdateFromDiscordRequest* Request, const FOnDiscordSampleMsUpdateFromDiscordSuccess& OnSuccess, const FOnDiscordSampleMsUpdateFromDiscordError& OnError, const FOnDiscordSampleMsUpdateFromDiscordComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UDiscordSampleMsUpdateFromDiscordRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_UpdateFromDiscordImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, AuthenticatedUser.RealmHandle, -1, UserSlot, AS_None};
}

		
void UBeamDiscordSampleMsApi::UpdateUserWhitelistedStatus(FUserSlot UserSlot, UDiscordSampleMsUpdateUserWhitelistedStatusRequest* Request, const FOnDiscordSampleMsUpdateUserWhitelistedStatusSuccess& OnSuccess, const FOnDiscordSampleMsUpdateUserWhitelistedStatusError& OnError, const FOnDiscordSampleMsUpdateUserWhitelistedStatusComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UDiscordSampleMsUpdateUserWhitelistedStatusRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_UpdateUserWhitelistedStatusImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, AuthenticatedUser.RealmHandle, -1, UserSlot, AS_None};
}

