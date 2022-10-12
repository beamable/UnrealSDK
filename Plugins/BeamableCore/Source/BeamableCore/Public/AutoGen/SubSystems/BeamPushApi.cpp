
#include "AutoGen/SubSystems/BeamPushApi.h"

void UBeamPushApi::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Backend = Cast<UBeamBackend>(Collection.InitializeDependency(UBeamBackend::StaticClass()));
}

void UBeamPushApi::Deinitialize()
{
	Super::Deinitialize();
}




void UBeamPushApi::BP_PostRegisterImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UBasicPushPostRegisterRequest* RequestData, const FOnBasicPushPostRegisterSuccess& OnSuccess, const FOnBasicPushPostRegisterError& OnError, const FOnBasicPushPostRegisterComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UBasicPushPostRegisterRequest, UEmptyRsp, FOnBasicPushPostRegisterSuccess, FOnBasicPushPostRegisterError, FOnBasicPushPostRegisterComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	const auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig, TargetRealm};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(RequestContext, ConnectivityStatus, OutRequestId);
}

void UBeamPushApi::CPP_PostRegisterImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UBasicPushPostRegisterRequest* RequestData, const FOnBasicPushPostRegisterFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UBasicPushPostRegisterRequest, UEmptyRsp>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	const auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig, TargetRealm};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(RequestContext, ConnectivityStatus, OutRequestId);
}

		
void UBeamPushApi::BP_PostSendImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UPostSendRequest* RequestData, const FOnPostSendSuccess& OnSuccess, const FOnPostSendError& OnError, const FOnPostSendComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPostSendRequest, UEmptyRsp, FOnPostSendSuccess, FOnPostSendError, FOnPostSendComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	const auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig, TargetRealm};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(RequestContext, ConnectivityStatus, OutRequestId);
}

void UBeamPushApi::CPP_PostSendImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UPostSendRequest* RequestData, const FOnPostSendFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPostSendRequest, UEmptyRsp>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	const auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig, TargetRealm};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(RequestContext, ConnectivityStatus, OutRequestId);
}






void UBeamPushApi::CPP_PostRegister(const FUserSlot& UserSlotId, UBasicPushPostRegisterRequest* Request, const FOnBasicPushPostRegisterFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UBasicPushPostRegisterRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_PostRegisterImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamPushApi::CPP_PostSend(const FUserSlot& UserSlotId, UPostSendRequest* Request, const FOnPostSendFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostSendRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_PostSendImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}






void UBeamPushApi::PostRegister(const FUserSlot& UserSlotId, UBasicPushPostRegisterRequest* Request, const FOnBasicPushPostRegisterSuccess& OnSuccess, const FOnBasicPushPostRegisterError& OnError,
                             const FOnBasicPushPostRegisterComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UBasicPushPostRegisterRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	BP_PostRegisterImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamPushApi::PostSend(const FUserSlot& UserSlotId, UPostSendRequest* Request, const FOnPostSendSuccess& OnSuccess, const FOnPostSendError& OnError,
                             const FOnPostSendComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostSendRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	BP_PostSendImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}
	
