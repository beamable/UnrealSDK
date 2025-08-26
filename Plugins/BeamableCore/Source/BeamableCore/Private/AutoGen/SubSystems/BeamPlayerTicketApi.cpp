
#include "BeamableCore/Public/AutoGen/SubSystems/BeamPlayerTicketApi.h"
#include "BeamCoreSettings.h"


void UBeamPlayerTicketApi::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Backend = Cast<UBeamBackend>(Collection.InitializeDependency(UBeamBackend::StaticClass()));
	RequestTracker = Cast<UBeamRequestTracker>(Collection.InitializeDependency(UBeamRequestTracker::StaticClass()));
	ResponseCache = Cast<UBeamResponseCache>(Collection.InitializeDependency(UBeamResponseCache::StaticClass()));
	
}

void UBeamPlayerTicketApi::Deinitialize()
{
	Super::Deinitialize();
}




void UBeamPlayerTicketApi::BP_GetMatchmakingTicketsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UGetMatchmakingTicketsRequest* RequestData, const FOnGetMatchmakingTicketsSuccess& OnSuccess, const FOnGetMatchmakingTicketsError& OnError, const FOnGetMatchmakingTicketsComplete& OnComplete, 
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
		Backend->RunAuthenticatedBlueprintRequestProcessor<UGetMatchmakingTicketsRequest, UTicketQueryResponse, FOnGetMatchmakingTicketsSuccess, FOnGetMatchmakingTicketsError, FOnGetMatchmakingTicketsComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UGetMatchmakingTicketsRequest, UTicketQueryResponse, FOnGetMatchmakingTicketsSuccess, FOnGetMatchmakingTicketsError, FOnGetMatchmakingTicketsComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamPlayerTicketApi::CPP_GetMatchmakingTicketsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UGetMatchmakingTicketsRequest* RequestData, const FOnGetMatchmakingTicketsFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
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
		Backend->RunAuthenticatedCodeRequestProcessor<UGetMatchmakingTicketsRequest, UTicketQueryResponse>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UGetMatchmakingTicketsRequest, UTicketQueryResponse>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}






void UBeamPlayerTicketApi::CPP_GetMatchmakingTickets(const FUserSlot& UserSlot, UGetMatchmakingTicketsRequest* Request, const FOnGetMatchmakingTicketsFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UGetMatchmakingTicketsRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_GetMatchmakingTicketsImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}






void UBeamPlayerTicketApi::GetMatchmakingTickets(FUserSlot UserSlot, UGetMatchmakingTicketsRequest* Request, const FOnGetMatchmakingTicketsSuccess& OnSuccess, const FOnGetMatchmakingTicketsError& OnError, const FOnGetMatchmakingTicketsComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UGetMatchmakingTicketsRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_GetMatchmakingTicketsImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

