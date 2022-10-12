
#include "AutoGen/SubSystems/BeamMatchmakingApi.h"

void UBeamMatchmakingApi::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Backend = Cast<UBeamBackend>(Collection.InitializeDependency(UBeamBackend::StaticClass()));
}

void UBeamMatchmakingApi::Deinitialize()
{
	Super::Deinitialize();
}




void UBeamMatchmakingApi::BP_PutTickImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UPutTickRequest* RequestData, const FOnPutTickSuccess& OnSuccess, const FOnPutTickError& OnError, const FOnPutTickComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPutTickRequest, UEmptyResponse, FOnPutTickSuccess, FOnPutTickError, FOnPutTickComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	const auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig, TargetRealm};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(RequestContext, ConnectivityStatus, OutRequestId);
}

void UBeamMatchmakingApi::CPP_PutTickImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UPutTickRequest* RequestData, const FOnPutTickFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPutTickRequest, UEmptyResponse>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	const auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig, TargetRealm};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(RequestContext, ConnectivityStatus, OutRequestId);
}

		
void UBeamMatchmakingApi::BP_GetMatchImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UGetMatchRequest* RequestData, const FOnGetMatchSuccess& OnSuccess, const FOnGetMatchError& OnError, const FOnGetMatchComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UGetMatchRequest, UMatchUpdate, FOnGetMatchSuccess, FOnGetMatchError, FOnGetMatchComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	const auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig, TargetRealm};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(RequestContext, ConnectivityStatus, OutRequestId);
}

void UBeamMatchmakingApi::CPP_GetMatchImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UGetMatchRequest* RequestData, const FOnGetMatchFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UGetMatchRequest, UMatchUpdate>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	const auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig, TargetRealm};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(RequestContext, ConnectivityStatus, OutRequestId);
}

		
void UBeamMatchmakingApi::BP_PostMatchImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UPostMatchRequest* RequestData, const FOnPostMatchSuccess& OnSuccess, const FOnPostMatchError& OnError, const FOnPostMatchComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPostMatchRequest, UMatchUpdate, FOnPostMatchSuccess, FOnPostMatchError, FOnPostMatchComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	const auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig, TargetRealm};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(RequestContext, ConnectivityStatus, OutRequestId);
}

void UBeamMatchmakingApi::CPP_PostMatchImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UPostMatchRequest* RequestData, const FOnPostMatchFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPostMatchRequest, UMatchUpdate>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	const auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig, TargetRealm};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(RequestContext, ConnectivityStatus, OutRequestId);
}

		
void UBeamMatchmakingApi::BP_DeleteMatchImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UDeleteMatchRequest* RequestData, const FOnDeleteMatchSuccess& OnSuccess, const FOnDeleteMatchError& OnError, const FOnDeleteMatchComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UDeleteMatchRequest, UEmptyResponse, FOnDeleteMatchSuccess, FOnDeleteMatchError, FOnDeleteMatchComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	const auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig, TargetRealm};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(RequestContext, ConnectivityStatus, OutRequestId);
}

void UBeamMatchmakingApi::CPP_DeleteMatchImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UDeleteMatchRequest* RequestData, const FOnDeleteMatchFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UDeleteMatchRequest, UEmptyResponse>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	const auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig, TargetRealm};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(RequestContext, ConnectivityStatus, OutRequestId);
}






void UBeamMatchmakingApi::CPP_PutTick(const FUserSlot& UserSlotId, UPutTickRequest* Request, const FOnPutTickFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPutTickRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_PutTickImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamMatchmakingApi::CPP_GetMatch(const FUserSlot& UserSlotId, UGetMatchRequest* Request, const FOnGetMatchFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UGetMatchRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_GetMatchImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamMatchmakingApi::CPP_PostMatch(const FUserSlot& UserSlotId, UPostMatchRequest* Request, const FOnPostMatchFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostMatchRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_PostMatchImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamMatchmakingApi::CPP_DeleteMatch(const FUserSlot& UserSlotId, UDeleteMatchRequest* Request, const FOnDeleteMatchFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UDeleteMatchRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_DeleteMatchImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}






void UBeamMatchmakingApi::PutTick(const FUserSlot& UserSlotId, UPutTickRequest* Request, const FOnPutTickSuccess& OnSuccess, const FOnPutTickError& OnError,
                             const FOnPutTickComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPutTickRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	BP_PutTickImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamMatchmakingApi::GetMatch(const FUserSlot& UserSlotId, UGetMatchRequest* Request, const FOnGetMatchSuccess& OnSuccess, const FOnGetMatchError& OnError,
                             const FOnGetMatchComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UGetMatchRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	BP_GetMatchImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamMatchmakingApi::PostMatch(const FUserSlot& UserSlotId, UPostMatchRequest* Request, const FOnPostMatchSuccess& OnSuccess, const FOnPostMatchError& OnError,
                             const FOnPostMatchComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostMatchRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	BP_PostMatchImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamMatchmakingApi::DeleteMatch(const FUserSlot& UserSlotId, UDeleteMatchRequest* Request, const FOnDeleteMatchSuccess& OnSuccess, const FOnDeleteMatchError& OnError,
                             const FOnDeleteMatchComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UDeleteMatchRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	BP_DeleteMatchImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}
	

