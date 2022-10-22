
#include "AutoGen/SubSystems/BeamGroupsApi.h"

void UBeamGroupsApi::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Backend = Cast<UBeamBackend>(Collection.InitializeDependency(UBeamBackend::StaticClass()));
}

void UBeamGroupsApi::Deinitialize()
{
	Super::Deinitialize();
}


void UBeamGroupsApi::BP_PostKickImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostKickRequest* RequestData,
                                                  const FOnPostKickSuccess& OnSuccess, const FOnPostKickError& OnError, const FOnPostKickComplete& OnComplete,
                                                  int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UPostKickRequest, UGroupMembershipResponse, FOnPostKickSuccess, FOnPostKickError, FOnPostKickComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig,TargetRealm, -1, FUserSlot(""), None};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamGroupsApi::CPP_PostKickImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UPostKickRequest* RequestData, const FOnPostKickFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UPostKickRequest, UGroupMembershipResponse>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamGroupsApi::BP_DeleteMemberImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UDeleteMemberRequest* RequestData,
                                                  const FOnDeleteMemberSuccess& OnSuccess, const FOnDeleteMemberError& OnError, const FOnDeleteMemberComplete& OnComplete,
                                                  int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UDeleteMemberRequest, UGroupMembershipResponse, FOnDeleteMemberSuccess, FOnDeleteMemberError, FOnDeleteMemberComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig,TargetRealm, -1, FUserSlot(""), None};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamGroupsApi::CPP_DeleteMemberImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UDeleteMemberRequest* RequestData, const FOnDeleteMemberFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UDeleteMemberRequest, UGroupMembershipResponse>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamGroupsApi::BP_GetGroupsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UObjectGroupsGetGroupsRequest* RequestData,
                                                  const FOnObjectGroupsGetGroupsSuccess& OnSuccess, const FOnObjectGroupsGetGroupsError& OnError, const FOnObjectGroupsGetGroupsComplete& OnComplete,
                                                  int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UObjectGroupsGetGroupsRequest, UGroup, FOnObjectGroupsGetGroupsSuccess, FOnObjectGroupsGetGroupsError, FOnObjectGroupsGetGroupsComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig,TargetRealm, -1, FUserSlot(""), None};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamGroupsApi::CPP_GetGroupsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UObjectGroupsGetGroupsRequest* RequestData, const FOnObjectGroupsGetGroupsFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UObjectGroupsGetGroupsRequest, UGroup>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamGroupsApi::BP_PutGroupsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPutGroupsRequest* RequestData,
                                                  const FOnPutGroupsSuccess& OnSuccess, const FOnPutGroupsError& OnError, const FOnPutGroupsComplete& OnComplete,
                                                  int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UPutGroupsRequest, UCommonResponse, FOnPutGroupsSuccess, FOnPutGroupsError, FOnPutGroupsComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig,TargetRealm, -1, FUserSlot(""), None};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamGroupsApi::CPP_PutGroupsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UPutGroupsRequest* RequestData, const FOnPutGroupsFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UPutGroupsRequest, UCommonResponse>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamGroupsApi::BP_DeleteGroupsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UDeleteGroupsRequest* RequestData,
                                                  const FOnDeleteGroupsSuccess& OnSuccess, const FOnDeleteGroupsError& OnError, const FOnDeleteGroupsComplete& OnComplete,
                                                  int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UDeleteGroupsRequest, UCommonResponse, FOnDeleteGroupsSuccess, FOnDeleteGroupsError, FOnDeleteGroupsComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig,TargetRealm, -1, FUserSlot(""), None};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamGroupsApi::CPP_DeleteGroupsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UDeleteGroupsRequest* RequestData, const FOnDeleteGroupsFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UDeleteGroupsRequest, UCommonResponse>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}



void UBeamGroupsApi::BP_PutRoleImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UObjectGroupsPutRoleRequest* RequestData, const FOnObjectGroupsPutRoleSuccess& OnSuccess, const FOnObjectGroupsPutRoleError& OnError, const FOnObjectGroupsPutRoleComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UObjectGroupsPutRoleRequest, UCommonResponse, FOnObjectGroupsPutRoleSuccess, FOnObjectGroupsPutRoleError, FOnObjectGroupsPutRoleComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamGroupsApi::CPP_PutRoleImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UObjectGroupsPutRoleRequest* RequestData, const FOnObjectGroupsPutRoleFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UObjectGroupsPutRoleRequest, UCommonResponse>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamGroupsApi::BP_PostApplyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UPostApplyRequest* RequestData, const FOnPostApplySuccess& OnSuccess, const FOnPostApplyError& OnError, const FOnPostApplyComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPostApplyRequest, UCommonResponse, FOnPostApplySuccess, FOnPostApplyError, FOnPostApplyComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamGroupsApi::CPP_PostApplyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UPostApplyRequest* RequestData, const FOnPostApplyFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPostApplyRequest, UCommonResponse>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamGroupsApi::BP_PostDonationsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UPostDonationsRequest* RequestData, const FOnPostDonationsSuccess& OnSuccess, const FOnPostDonationsError& OnError, const FOnPostDonationsComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPostDonationsRequest, UEmptyResponse, FOnPostDonationsSuccess, FOnPostDonationsError, FOnPostDonationsComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamGroupsApi::CPP_PostDonationsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UPostDonationsRequest* RequestData, const FOnPostDonationsFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPostDonationsRequest, UEmptyResponse>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamGroupsApi::BP_PutDonationsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UPutDonationsRequest* RequestData, const FOnPutDonationsSuccess& OnSuccess, const FOnPutDonationsError& OnError, const FOnPutDonationsComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPutDonationsRequest, UEmptyResponse, FOnPutDonationsSuccess, FOnPutDonationsError, FOnPutDonationsComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamGroupsApi::CPP_PutDonationsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UPutDonationsRequest* RequestData, const FOnPutDonationsFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPutDonationsRequest, UEmptyResponse>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamGroupsApi::BP_PutDonationsClaimImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UPutDonationsClaimRequest* RequestData, const FOnPutDonationsClaimSuccess& OnSuccess, const FOnPutDonationsClaimError& OnError, const FOnPutDonationsClaimComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPutDonationsClaimRequest, UEmptyResponse, FOnPutDonationsClaimSuccess, FOnPutDonationsClaimError, FOnPutDonationsClaimComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamGroupsApi::CPP_PutDonationsClaimImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UPutDonationsClaimRequest* RequestData, const FOnPutDonationsClaimFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPutDonationsClaimRequest, UEmptyResponse>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamGroupsApi::BP_PostInviteImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UPostInviteRequest* RequestData, const FOnPostInviteSuccess& OnSuccess, const FOnPostInviteError& OnError, const FOnPostInviteComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPostInviteRequest, UCommonResponse, FOnPostInviteSuccess, FOnPostInviteError, FOnPostInviteComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamGroupsApi::CPP_PostInviteImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UPostInviteRequest* RequestData, const FOnPostInviteFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPostInviteRequest, UCommonResponse>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamGroupsApi::BP_PostPetitionImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UPostPetitionRequest* RequestData, const FOnPostPetitionSuccess& OnSuccess, const FOnPostPetitionError& OnError, const FOnPostPetitionComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPostPetitionRequest, UCommonResponse, FOnPostPetitionSuccess, FOnPostPetitionError, FOnPostPetitionComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamGroupsApi::CPP_PostPetitionImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UPostPetitionRequest* RequestData, const FOnPostPetitionFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPostPetitionRequest, UCommonResponse>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}




void UBeamGroupsApi::CPP_PostKick(UPostKickRequest* Request, const FOnPostKickFullResponse& Handler) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UPostKickRequest::StaticClass()->GetName(), RetryConfig);
	CPP_PostKickImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamGroupsApi::CPP_DeleteMember(UDeleteMemberRequest* Request, const FOnDeleteMemberFullResponse& Handler) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UDeleteMemberRequest::StaticClass()->GetName(), RetryConfig);
	CPP_DeleteMemberImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamGroupsApi::CPP_GetGroups(UObjectGroupsGetGroupsRequest* Request, const FOnObjectGroupsGetGroupsFullResponse& Handler) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UObjectGroupsGetGroupsRequest::StaticClass()->GetName(), RetryConfig);
	CPP_GetGroupsImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamGroupsApi::CPP_PutGroups(UPutGroupsRequest* Request, const FOnPutGroupsFullResponse& Handler) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UPutGroupsRequest::StaticClass()->GetName(), RetryConfig);
	CPP_PutGroupsImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamGroupsApi::CPP_DeleteGroups(UDeleteGroupsRequest* Request, const FOnDeleteGroupsFullResponse& Handler) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UDeleteGroupsRequest::StaticClass()->GetName(), RetryConfig);
	CPP_DeleteGroupsImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler);
}



void UBeamGroupsApi::CPP_PutRole(const FUserSlot& UserSlotId, UObjectGroupsPutRoleRequest* Request, const FOnObjectGroupsPutRoleFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UObjectGroupsPutRoleRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_PutRoleImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamGroupsApi::CPP_PostApply(const FUserSlot& UserSlotId, UPostApplyRequest* Request, const FOnPostApplyFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostApplyRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_PostApplyImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamGroupsApi::CPP_PostDonations(const FUserSlot& UserSlotId, UPostDonationsRequest* Request, const FOnPostDonationsFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostDonationsRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_PostDonationsImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamGroupsApi::CPP_PutDonations(const FUserSlot& UserSlotId, UPutDonationsRequest* Request, const FOnPutDonationsFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPutDonationsRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_PutDonationsImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamGroupsApi::CPP_PutDonationsClaim(const FUserSlot& UserSlotId, UPutDonationsClaimRequest* Request, const FOnPutDonationsClaimFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPutDonationsClaimRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_PutDonationsClaimImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamGroupsApi::CPP_PostInvite(const FUserSlot& UserSlotId, UPostInviteRequest* Request, const FOnPostInviteFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostInviteRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_PostInviteImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamGroupsApi::CPP_PostPetition(const FUserSlot& UserSlotId, UPostPetitionRequest* Request, const FOnPostPetitionFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostPetitionRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_PostPetitionImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}




void UBeamGroupsApi::PostKick(UPostKickRequest* Request, const FOnPostKickSuccess& OnSuccess, const FOnPostKickError& OnError,
                                           const FOnPostKickComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UPostKickRequest::StaticClass()->GetName(), RetryConfig);
	BP_PostKickImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamGroupsApi::DeleteMember(UDeleteMemberRequest* Request, const FOnDeleteMemberSuccess& OnSuccess, const FOnDeleteMemberError& OnError,
                                           const FOnDeleteMemberComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UDeleteMemberRequest::StaticClass()->GetName(), RetryConfig);
	BP_DeleteMemberImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamGroupsApi::GetGroups(UObjectGroupsGetGroupsRequest* Request, const FOnObjectGroupsGetGroupsSuccess& OnSuccess, const FOnObjectGroupsGetGroupsError& OnError,
                                           const FOnObjectGroupsGetGroupsComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UObjectGroupsGetGroupsRequest::StaticClass()->GetName(), RetryConfig);
	BP_GetGroupsImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamGroupsApi::PutGroups(UPutGroupsRequest* Request, const FOnPutGroupsSuccess& OnSuccess, const FOnPutGroupsError& OnError,
                                           const FOnPutGroupsComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UPutGroupsRequest::StaticClass()->GetName(), RetryConfig);
	BP_PutGroupsImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamGroupsApi::DeleteGroups(UDeleteGroupsRequest* Request, const FOnDeleteGroupsSuccess& OnSuccess, const FOnDeleteGroupsError& OnError,
                                           const FOnDeleteGroupsComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UDeleteGroupsRequest::StaticClass()->GetName(), RetryConfig);
	BP_DeleteGroupsImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}



void UBeamGroupsApi::PutRole(const FUserSlot& UserSlotId, UObjectGroupsPutRoleRequest* Request, const FOnObjectGroupsPutRoleSuccess& OnSuccess, const FOnObjectGroupsPutRoleError& OnError,
                             const FOnObjectGroupsPutRoleComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UObjectGroupsPutRoleRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	BP_PutRoleImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamGroupsApi::PostApply(const FUserSlot& UserSlotId, UPostApplyRequest* Request, const FOnPostApplySuccess& OnSuccess, const FOnPostApplyError& OnError,
                             const FOnPostApplyComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostApplyRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	BP_PostApplyImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamGroupsApi::PostDonations(const FUserSlot& UserSlotId, UPostDonationsRequest* Request, const FOnPostDonationsSuccess& OnSuccess, const FOnPostDonationsError& OnError,
                             const FOnPostDonationsComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostDonationsRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	BP_PostDonationsImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamGroupsApi::PutDonations(const FUserSlot& UserSlotId, UPutDonationsRequest* Request, const FOnPutDonationsSuccess& OnSuccess, const FOnPutDonationsError& OnError,
                             const FOnPutDonationsComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPutDonationsRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	BP_PutDonationsImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamGroupsApi::PutDonationsClaim(const FUserSlot& UserSlotId, UPutDonationsClaimRequest* Request, const FOnPutDonationsClaimSuccess& OnSuccess, const FOnPutDonationsClaimError& OnError,
                             const FOnPutDonationsClaimComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPutDonationsClaimRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	BP_PutDonationsClaimImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamGroupsApi::PostInvite(const FUserSlot& UserSlotId, UPostInviteRequest* Request, const FOnPostInviteSuccess& OnSuccess, const FOnPostInviteError& OnError,
                             const FOnPostInviteComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostInviteRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	BP_PostInviteImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamGroupsApi::PostPetition(const FUserSlot& UserSlotId, UPostPetitionRequest* Request, const FOnPostPetitionSuccess& OnSuccess, const FOnPostPetitionError& OnError,
                             const FOnPostPetitionComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostPetitionRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	BP_PostPetitionImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}
	

