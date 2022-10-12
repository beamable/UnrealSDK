
#include "AutoGen/SubSystems/BeamAuthApi.h"

void UBeamAuthApi::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Backend = Cast<UBeamBackend>(Collection.InitializeDependency(UBeamBackend::StaticClass()));
}

void UBeamAuthApi::Deinitialize()
{
	Super::Deinitialize();
}


void UBeamAuthApi::BP_GetTokenImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetTokenRequest* RequestData,
                                                  const FOnGetTokenSuccess& OnSuccess, const FOnGetTokenError& OnError, const FOnGetTokenComplete& OnComplete,
                                                  int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UGetTokenRequest, UToken, FOnGetTokenSuccess, FOnGetTokenError, FOnGetTokenComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	const auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig,TargetRealm};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(RequestContext, ConnectivityStatus, OutRequestId);
}

void UBeamAuthApi::CPP_GetTokenImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UGetTokenRequest* RequestData, const FOnGetTokenFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UGetTokenRequest, UToken>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	const auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig, TargetRealm};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(RequestContext, ConnectivityStatus, OutRequestId);
}

		
void UBeamAuthApi::BP_AuthenticateImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UAuthenticateRequest* RequestData,
                                                  const FOnAuthenticateSuccess& OnSuccess, const FOnAuthenticateError& OnError, const FOnAuthenticateComplete& OnComplete,
                                                  int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UAuthenticateRequest, UTokenResponse, FOnAuthenticateSuccess, FOnAuthenticateError, FOnAuthenticateComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	const auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig,TargetRealm};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(RequestContext, ConnectivityStatus, OutRequestId);
}

void UBeamAuthApi::CPP_AuthenticateImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UAuthenticateRequest* RequestData, const FOnAuthenticateFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UAuthenticateRequest, UTokenResponse>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	const auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig, TargetRealm};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(RequestContext, ConnectivityStatus, OutRequestId);
}



void UBeamAuthApi::BP_GetTokenListImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UGetTokenListRequest* RequestData, const FOnGetTokenListSuccess& OnSuccess, const FOnGetTokenListError& OnError, const FOnGetTokenListComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UGetTokenListRequest, UListTokenResponse, FOnGetTokenListSuccess, FOnGetTokenListError, FOnGetTokenListComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	const auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig, TargetRealm};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(RequestContext, ConnectivityStatus, OutRequestId);
}

void UBeamAuthApi::CPP_GetTokenListImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UGetTokenListRequest* RequestData, const FOnGetTokenListFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UGetTokenListRequest, UListTokenResponse>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	const auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig, TargetRealm};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(RequestContext, ConnectivityStatus, OutRequestId);
}

		
void UBeamAuthApi::BP_PutTokenRevokeImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UPutTokenRevokeRequest* RequestData, const FOnPutTokenRevokeSuccess& OnSuccess, const FOnPutTokenRevokeError& OnError, const FOnPutTokenRevokeComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPutTokenRevokeRequest, UCommonResponse, FOnPutTokenRevokeSuccess, FOnPutTokenRevokeError, FOnPutTokenRevokeComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	const auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig, TargetRealm};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(RequestContext, ConnectivityStatus, OutRequestId);
}

void UBeamAuthApi::CPP_PutTokenRevokeImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UPutTokenRevokeRequest* RequestData, const FOnPutTokenRevokeFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPutTokenRevokeRequest, UCommonResponse>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	const auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig, TargetRealm};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(RequestContext, ConnectivityStatus, OutRequestId);
}




void UBeamAuthApi::CPP_GetToken(UGetTokenRequest* Request, const FOnGetTokenFullResponse& Handler) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UGetTokenRequest::StaticClass()->GetName(), RetryConfig);
	CPP_GetTokenImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamAuthApi::CPP_Authenticate(UAuthenticateRequest* Request, const FOnAuthenticateFullResponse& Handler) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UAuthenticateRequest::StaticClass()->GetName(), RetryConfig);
	CPP_AuthenticateImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler);
}



void UBeamAuthApi::CPP_GetTokenList(const FUserSlot& UserSlotId, UGetTokenListRequest* Request, const FOnGetTokenListFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UGetTokenListRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_GetTokenListImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamAuthApi::CPP_PutTokenRevoke(const FUserSlot& UserSlotId, UPutTokenRevokeRequest* Request, const FOnPutTokenRevokeFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPutTokenRevokeRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_PutTokenRevokeImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}




void UBeamAuthApi::GetToken(UGetTokenRequest* Request, const FOnGetTokenSuccess& OnSuccess, const FOnGetTokenError& OnError,
                                           const FOnGetTokenComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UGetTokenRequest::StaticClass()->GetName(), RetryConfig);
	BP_GetTokenImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamAuthApi::Authenticate(UAuthenticateRequest* Request, const FOnAuthenticateSuccess& OnSuccess, const FOnAuthenticateError& OnError,
                                           const FOnAuthenticateComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UAuthenticateRequest::StaticClass()->GetName(), RetryConfig);
	BP_AuthenticateImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}



void UBeamAuthApi::GetTokenList(const FUserSlot& UserSlotId, UGetTokenListRequest* Request, const FOnGetTokenListSuccess& OnSuccess, const FOnGetTokenListError& OnError,
                             const FOnGetTokenListComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UGetTokenListRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	BP_GetTokenListImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamAuthApi::PutTokenRevoke(const FUserSlot& UserSlotId, UPutTokenRevokeRequest* Request, const FOnPutTokenRevokeSuccess& OnSuccess, const FOnPutTokenRevokeError& OnError,
                             const FOnPutTokenRevokeComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPutTokenRevokeRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	BP_PutTokenRevokeImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}
	

