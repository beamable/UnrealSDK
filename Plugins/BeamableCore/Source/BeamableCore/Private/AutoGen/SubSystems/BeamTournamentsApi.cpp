
#include "AutoGen/SubSystems/BeamTournamentsApi.h"

void UBeamTournamentsApi::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Backend = Cast<UBeamBackend>(Collection.InitializeDependency(UBeamBackend::StaticClass()));
}

void UBeamTournamentsApi::Deinitialize()
{
	Super::Deinitialize();
}


void UBeamTournamentsApi::BP_PostSearchGroupsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostSearchGroupsRequest* RequestData,
                                                  const FOnPostSearchGroupsSuccess& OnSuccess, const FOnPostSearchGroupsError& OnError, const FOnPostSearchGroupsComplete& OnComplete,
                                                  int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UPostSearchGroupsRequest, UGetStatusForGroupsResponse, FOnPostSearchGroupsSuccess, FOnPostSearchGroupsError, FOnPostSearchGroupsComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamTournamentsApi::CPP_PostSearchGroupsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UPostSearchGroupsRequest* RequestData, const FOnPostSearchGroupsFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UPostSearchGroupsRequest, UGetStatusForGroupsResponse>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamTournamentsApi::BP_BasicTournamentsGetTournamentsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UBasicTournamentsGetTournamentsRequest* RequestData,
                                                  const FOnBasicTournamentsGetTournamentsSuccess& OnSuccess, const FOnBasicTournamentsGetTournamentsError& OnError, const FOnBasicTournamentsGetTournamentsComplete& OnComplete,
                                                  int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UBasicTournamentsGetTournamentsRequest, UTournamentQueryResponse, FOnBasicTournamentsGetTournamentsSuccess, FOnBasicTournamentsGetTournamentsError, FOnBasicTournamentsGetTournamentsComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamTournamentsApi::CPP_BasicTournamentsGetTournamentsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UBasicTournamentsGetTournamentsRequest* RequestData, const FOnBasicTournamentsGetTournamentsFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UBasicTournamentsGetTournamentsRequest, UTournamentQueryResponse>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamTournamentsApi::BP_PostScoreImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostScoreRequest* RequestData,
                                                  const FOnPostScoreSuccess& OnSuccess, const FOnPostScoreError& OnError, const FOnPostScoreComplete& OnComplete,
                                                  int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UPostScoreRequest, UEmptyResponse, FOnPostScoreSuccess, FOnPostScoreError, FOnPostScoreComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamTournamentsApi::CPP_PostScoreImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UPostScoreRequest* RequestData, const FOnPostScoreFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UPostScoreRequest, UEmptyResponse>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamTournamentsApi::BP_ObjectTournamentsGetTournamentsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UObjectTournamentsGetTournamentsRequest* RequestData,
                                                  const FOnObjectTournamentsGetTournamentsSuccess& OnSuccess, const FOnObjectTournamentsGetTournamentsError& OnError, const FOnObjectTournamentsGetTournamentsComplete& OnComplete,
                                                  int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UObjectTournamentsGetTournamentsRequest, UTournamentClientView, FOnObjectTournamentsGetTournamentsSuccess, FOnObjectTournamentsGetTournamentsError, FOnObjectTournamentsGetTournamentsComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamTournamentsApi::CPP_ObjectTournamentsGetTournamentsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UObjectTournamentsGetTournamentsRequest* RequestData, const FOnObjectTournamentsGetTournamentsFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UObjectTournamentsGetTournamentsRequest, UTournamentClientView>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}



void UBeamTournamentsApi::BP_PostTournamentsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UPostTournamentsRequest* RequestData, const FOnPostTournamentsSuccess& OnSuccess, const FOnPostTournamentsError& OnError, const FOnPostTournamentsComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPostTournamentsRequest, UPlayerStatus, FOnPostTournamentsSuccess, FOnPostTournamentsError, FOnPostTournamentsComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamTournamentsApi::CPP_PostTournamentsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UPostTournamentsRequest* RequestData, const FOnPostTournamentsFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPostTournamentsRequest, UPlayerStatus>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamTournamentsApi::BP_GetMeGroupImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UGetMeGroupRequest* RequestData, const FOnGetMeGroupSuccess& OnSuccess, const FOnGetMeGroupError& OnError, const FOnGetMeGroupComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UGetMeGroupRequest, UGetGroupStatusResponse, FOnGetMeGroupSuccess, FOnGetMeGroupError, FOnGetMeGroupComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamTournamentsApi::CPP_GetMeGroupImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UGetMeGroupRequest* RequestData, const FOnGetMeGroupFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UGetMeGroupRequest, UGetGroupStatusResponse>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamTournamentsApi::BP_GetRewardsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UGetRewardsRequest* RequestData, const FOnGetRewardsSuccess& OnSuccess, const FOnGetRewardsError& OnError, const FOnGetRewardsComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UGetRewardsRequest, URewardsResponse, FOnGetRewardsSuccess, FOnGetRewardsError, FOnGetRewardsComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamTournamentsApi::CPP_GetRewardsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UGetRewardsRequest* RequestData, const FOnGetRewardsFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UGetRewardsRequest, URewardsResponse>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamTournamentsApi::BP_PostRewardsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UPostRewardsRequest* RequestData, const FOnPostRewardsSuccess& OnSuccess, const FOnPostRewardsError& OnError, const FOnPostRewardsComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPostRewardsRequest, URewardsResponse, FOnPostRewardsSuccess, FOnPostRewardsError, FOnPostRewardsComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamTournamentsApi::CPP_PostRewardsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UPostRewardsRequest* RequestData, const FOnPostRewardsFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPostRewardsRequest, URewardsResponse>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamTournamentsApi::BP_GetGlobalImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UGetGlobalRequest* RequestData, const FOnGetGlobalSuccess& OnSuccess, const FOnGetGlobalError& OnError, const FOnGetGlobalComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UGetGlobalRequest, UGetStandingsResponse, FOnGetGlobalSuccess, FOnGetGlobalError, FOnGetGlobalComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamTournamentsApi::CPP_GetGlobalImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UGetGlobalRequest* RequestData, const FOnGetGlobalFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UGetGlobalRequest, UGetStandingsResponse>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamTournamentsApi::BP_GetStandingsGroupImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UGetStandingsGroupRequest* RequestData, const FOnGetStandingsGroupSuccess& OnSuccess, const FOnGetStandingsGroupError& OnError, const FOnGetStandingsGroupComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UGetStandingsGroupRequest, UGetStandingsResponse, FOnGetStandingsGroupSuccess, FOnGetStandingsGroupError, FOnGetStandingsGroupComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamTournamentsApi::CPP_GetStandingsGroupImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UGetStandingsGroupRequest* RequestData, const FOnGetStandingsGroupFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UGetStandingsGroupRequest, UGetStandingsResponse>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamTournamentsApi::BP_GetStandingsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UGetStandingsRequest* RequestData, const FOnGetStandingsSuccess& OnSuccess, const FOnGetStandingsError& OnError, const FOnGetStandingsComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UGetStandingsRequest, UGetStandingsResponse, FOnGetStandingsSuccess, FOnGetStandingsError, FOnGetStandingsComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamTournamentsApi::CPP_GetStandingsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UGetStandingsRequest* RequestData, const FOnGetStandingsFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UGetStandingsRequest, UGetStandingsResponse>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamTournamentsApi::BP_GetAdminPlayerImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UGetAdminPlayerRequest* RequestData, const FOnGetAdminPlayerSuccess& OnSuccess, const FOnGetAdminPlayerError& OnError, const FOnGetAdminPlayerComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UGetAdminPlayerRequest, UAdminGetPlayerStatusResponse, FOnGetAdminPlayerSuccess, FOnGetAdminPlayerError, FOnGetAdminPlayerComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamTournamentsApi::CPP_GetAdminPlayerImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UGetAdminPlayerRequest* RequestData, const FOnGetAdminPlayerFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UGetAdminPlayerRequest, UAdminGetPlayerStatusResponse>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamTournamentsApi::BP_PutAdminPlayerImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UPutAdminPlayerRequest* RequestData, const FOnPutAdminPlayerSuccess& OnSuccess, const FOnPutAdminPlayerError& OnError, const FOnPutAdminPlayerComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPutAdminPlayerRequest, UAdminPlayerStatus, FOnPutAdminPlayerSuccess, FOnPutAdminPlayerError, FOnPutAdminPlayerComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamTournamentsApi::CPP_PutAdminPlayerImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UPutAdminPlayerRequest* RequestData, const FOnPutAdminPlayerFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPutAdminPlayerRequest, UAdminPlayerStatus>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamTournamentsApi::BP_GetMeImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UBasicTournamentsGetMeRequest* RequestData, const FOnBasicTournamentsGetMeSuccess& OnSuccess, const FOnBasicTournamentsGetMeError& OnError, const FOnBasicTournamentsGetMeComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UBasicTournamentsGetMeRequest, UGetPlayerStatusResponse, FOnBasicTournamentsGetMeSuccess, FOnBasicTournamentsGetMeError, FOnBasicTournamentsGetMeComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamTournamentsApi::CPP_GetMeImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UBasicTournamentsGetMeRequest* RequestData, const FOnBasicTournamentsGetMeFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UBasicTournamentsGetMeRequest, UGetPlayerStatusResponse>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamTournamentsApi::BP_GetChampionsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UGetChampionsRequest* RequestData, const FOnGetChampionsSuccess& OnSuccess, const FOnGetChampionsError& OnError, const FOnGetChampionsComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UGetChampionsRequest, UGetChampionsResponse, FOnGetChampionsSuccess, FOnGetChampionsError, FOnGetChampionsComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamTournamentsApi::CPP_GetChampionsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UGetChampionsRequest* RequestData, const FOnGetChampionsFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UGetChampionsRequest, UGetChampionsResponse>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamTournamentsApi::BP_GetGroupsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UBasicTournamentsGetGroupsRequest* RequestData, const FOnBasicTournamentsGetGroupsSuccess& OnSuccess, const FOnBasicTournamentsGetGroupsError& OnError, const FOnBasicTournamentsGetGroupsComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UBasicTournamentsGetGroupsRequest, UGetGroupsResponse, FOnBasicTournamentsGetGroupsSuccess, FOnBasicTournamentsGetGroupsError, FOnBasicTournamentsGetGroupsComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamTournamentsApi::CPP_GetGroupsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UBasicTournamentsGetGroupsRequest* RequestData, const FOnBasicTournamentsGetGroupsFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UBasicTournamentsGetGroupsRequest, UGetGroupsResponse>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}




void UBeamTournamentsApi::CPP_PostSearchGroups(UPostSearchGroupsRequest* Request, const FOnPostSearchGroupsFullResponse& Handler) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UPostSearchGroupsRequest::StaticClass()->GetName(), RetryConfig);
	CPP_PostSearchGroupsImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamTournamentsApi::CPP_BasicTournamentsGetTournaments(UBasicTournamentsGetTournamentsRequest* Request, const FOnBasicTournamentsGetTournamentsFullResponse& Handler) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UBasicTournamentsGetTournamentsRequest::StaticClass()->GetName(), RetryConfig);
	CPP_BasicTournamentsGetTournamentsImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamTournamentsApi::CPP_PostScore(UPostScoreRequest* Request, const FOnPostScoreFullResponse& Handler) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UPostScoreRequest::StaticClass()->GetName(), RetryConfig);
	CPP_PostScoreImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamTournamentsApi::CPP_ObjectTournamentsGetTournaments(UObjectTournamentsGetTournamentsRequest* Request, const FOnObjectTournamentsGetTournamentsFullResponse& Handler) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UObjectTournamentsGetTournamentsRequest::StaticClass()->GetName(), RetryConfig);
	CPP_ObjectTournamentsGetTournamentsImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler);
}



void UBeamTournamentsApi::CPP_PostTournaments(const FUserSlot& UserSlotId, UPostTournamentsRequest* Request, const FOnPostTournamentsFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostTournamentsRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_PostTournamentsImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamTournamentsApi::CPP_GetMeGroup(const FUserSlot& UserSlotId, UGetMeGroupRequest* Request, const FOnGetMeGroupFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UGetMeGroupRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_GetMeGroupImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamTournamentsApi::CPP_GetRewards(const FUserSlot& UserSlotId, UGetRewardsRequest* Request, const FOnGetRewardsFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UGetRewardsRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_GetRewardsImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamTournamentsApi::CPP_PostRewards(const FUserSlot& UserSlotId, UPostRewardsRequest* Request, const FOnPostRewardsFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostRewardsRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_PostRewardsImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamTournamentsApi::CPP_GetGlobal(const FUserSlot& UserSlotId, UGetGlobalRequest* Request, const FOnGetGlobalFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UGetGlobalRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_GetGlobalImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamTournamentsApi::CPP_GetStandingsGroup(const FUserSlot& UserSlotId, UGetStandingsGroupRequest* Request, const FOnGetStandingsGroupFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UGetStandingsGroupRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_GetStandingsGroupImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamTournamentsApi::CPP_GetStandings(const FUserSlot& UserSlotId, UGetStandingsRequest* Request, const FOnGetStandingsFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UGetStandingsRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_GetStandingsImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamTournamentsApi::CPP_GetAdminPlayer(const FUserSlot& UserSlotId, UGetAdminPlayerRequest* Request, const FOnGetAdminPlayerFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UGetAdminPlayerRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_GetAdminPlayerImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamTournamentsApi::CPP_PutAdminPlayer(const FUserSlot& UserSlotId, UPutAdminPlayerRequest* Request, const FOnPutAdminPlayerFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPutAdminPlayerRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_PutAdminPlayerImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamTournamentsApi::CPP_GetMe(const FUserSlot& UserSlotId, UBasicTournamentsGetMeRequest* Request, const FOnBasicTournamentsGetMeFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UBasicTournamentsGetMeRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_GetMeImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamTournamentsApi::CPP_GetChampions(const FUserSlot& UserSlotId, UGetChampionsRequest* Request, const FOnGetChampionsFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UGetChampionsRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_GetChampionsImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamTournamentsApi::CPP_GetGroups(const FUserSlot& UserSlotId, UBasicTournamentsGetGroupsRequest* Request, const FOnBasicTournamentsGetGroupsFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UBasicTournamentsGetGroupsRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_GetGroupsImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}




void UBeamTournamentsApi::PostSearchGroups(UPostSearchGroupsRequest* Request, const FOnPostSearchGroupsSuccess& OnSuccess, const FOnPostSearchGroupsError& OnError, const FOnPostSearchGroupsComplete& OnComplete, FBeamRequestContext& OutRequestContext)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UPostSearchGroupsRequest::StaticClass()->GetName(), RetryConfig);	
	
	int64 OutRequestId = 0;
	BP_PostSearchGroupsImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, Backend->UnauthenticatedRequestsTargetRealm, -1, FUserSlot(), None};
}

		
void UBeamTournamentsApi::BasicTournamentsGetTournaments(UBasicTournamentsGetTournamentsRequest* Request, const FOnBasicTournamentsGetTournamentsSuccess& OnSuccess, const FOnBasicTournamentsGetTournamentsError& OnError, const FOnBasicTournamentsGetTournamentsComplete& OnComplete, FBeamRequestContext& OutRequestContext)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UBasicTournamentsGetTournamentsRequest::StaticClass()->GetName(), RetryConfig);	
	
	int64 OutRequestId = 0;
	BP_BasicTournamentsGetTournamentsImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, Backend->UnauthenticatedRequestsTargetRealm, -1, FUserSlot(), None};
}

		
void UBeamTournamentsApi::PostScore(UPostScoreRequest* Request, const FOnPostScoreSuccess& OnSuccess, const FOnPostScoreError& OnError, const FOnPostScoreComplete& OnComplete, FBeamRequestContext& OutRequestContext)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UPostScoreRequest::StaticClass()->GetName(), RetryConfig);	
	
	int64 OutRequestId = 0;
	BP_PostScoreImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, Backend->UnauthenticatedRequestsTargetRealm, -1, FUserSlot(), None};
}

		
void UBeamTournamentsApi::ObjectTournamentsGetTournaments(UObjectTournamentsGetTournamentsRequest* Request, const FOnObjectTournamentsGetTournamentsSuccess& OnSuccess, const FOnObjectTournamentsGetTournamentsError& OnError, const FOnObjectTournamentsGetTournamentsComplete& OnComplete, FBeamRequestContext& OutRequestContext)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UObjectTournamentsGetTournamentsRequest::StaticClass()->GetName(), RetryConfig);	
	
	int64 OutRequestId = 0;
	BP_ObjectTournamentsGetTournamentsImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, Backend->UnauthenticatedRequestsTargetRealm, -1, FUserSlot(), None};
}



void UBeamTournamentsApi::PostTournaments(FUserSlot UserSlot, UPostTournamentsRequest* Request, const FOnPostTournamentsSuccess& OnSuccess, const FOnPostTournamentsError& OnError, const FOnPostTournamentsComplete& OnComplete,  FBeamRequestContext& OutRequestContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostTournamentsRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_PostTournamentsImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, AuthenticatedUser.RealmHandle, -1, UserSlot, None};
}

		
void UBeamTournamentsApi::GetMeGroup(FUserSlot UserSlot, UGetMeGroupRequest* Request, const FOnGetMeGroupSuccess& OnSuccess, const FOnGetMeGroupError& OnError, const FOnGetMeGroupComplete& OnComplete,  FBeamRequestContext& OutRequestContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UGetMeGroupRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_GetMeGroupImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, AuthenticatedUser.RealmHandle, -1, UserSlot, None};
}

		
void UBeamTournamentsApi::GetRewards(FUserSlot UserSlot, UGetRewardsRequest* Request, const FOnGetRewardsSuccess& OnSuccess, const FOnGetRewardsError& OnError, const FOnGetRewardsComplete& OnComplete,  FBeamRequestContext& OutRequestContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UGetRewardsRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_GetRewardsImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, AuthenticatedUser.RealmHandle, -1, UserSlot, None};
}

		
void UBeamTournamentsApi::PostRewards(FUserSlot UserSlot, UPostRewardsRequest* Request, const FOnPostRewardsSuccess& OnSuccess, const FOnPostRewardsError& OnError, const FOnPostRewardsComplete& OnComplete,  FBeamRequestContext& OutRequestContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostRewardsRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_PostRewardsImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, AuthenticatedUser.RealmHandle, -1, UserSlot, None};
}

		
void UBeamTournamentsApi::GetGlobal(FUserSlot UserSlot, UGetGlobalRequest* Request, const FOnGetGlobalSuccess& OnSuccess, const FOnGetGlobalError& OnError, const FOnGetGlobalComplete& OnComplete,  FBeamRequestContext& OutRequestContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UGetGlobalRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_GetGlobalImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, AuthenticatedUser.RealmHandle, -1, UserSlot, None};
}

		
void UBeamTournamentsApi::GetStandingsGroup(FUserSlot UserSlot, UGetStandingsGroupRequest* Request, const FOnGetStandingsGroupSuccess& OnSuccess, const FOnGetStandingsGroupError& OnError, const FOnGetStandingsGroupComplete& OnComplete,  FBeamRequestContext& OutRequestContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UGetStandingsGroupRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_GetStandingsGroupImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, AuthenticatedUser.RealmHandle, -1, UserSlot, None};
}

		
void UBeamTournamentsApi::GetStandings(FUserSlot UserSlot, UGetStandingsRequest* Request, const FOnGetStandingsSuccess& OnSuccess, const FOnGetStandingsError& OnError, const FOnGetStandingsComplete& OnComplete,  FBeamRequestContext& OutRequestContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UGetStandingsRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_GetStandingsImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, AuthenticatedUser.RealmHandle, -1, UserSlot, None};
}

		
void UBeamTournamentsApi::GetAdminPlayer(FUserSlot UserSlot, UGetAdminPlayerRequest* Request, const FOnGetAdminPlayerSuccess& OnSuccess, const FOnGetAdminPlayerError& OnError, const FOnGetAdminPlayerComplete& OnComplete,  FBeamRequestContext& OutRequestContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UGetAdminPlayerRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_GetAdminPlayerImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, AuthenticatedUser.RealmHandle, -1, UserSlot, None};
}

		
void UBeamTournamentsApi::PutAdminPlayer(FUserSlot UserSlot, UPutAdminPlayerRequest* Request, const FOnPutAdminPlayerSuccess& OnSuccess, const FOnPutAdminPlayerError& OnError, const FOnPutAdminPlayerComplete& OnComplete,  FBeamRequestContext& OutRequestContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPutAdminPlayerRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_PutAdminPlayerImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, AuthenticatedUser.RealmHandle, -1, UserSlot, None};
}

		
void UBeamTournamentsApi::GetMe(FUserSlot UserSlot, UBasicTournamentsGetMeRequest* Request, const FOnBasicTournamentsGetMeSuccess& OnSuccess, const FOnBasicTournamentsGetMeError& OnError, const FOnBasicTournamentsGetMeComplete& OnComplete,  FBeamRequestContext& OutRequestContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UBasicTournamentsGetMeRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_GetMeImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, AuthenticatedUser.RealmHandle, -1, UserSlot, None};
}

		
void UBeamTournamentsApi::GetChampions(FUserSlot UserSlot, UGetChampionsRequest* Request, const FOnGetChampionsSuccess& OnSuccess, const FOnGetChampionsError& OnError, const FOnGetChampionsComplete& OnComplete,  FBeamRequestContext& OutRequestContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UGetChampionsRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_GetChampionsImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, AuthenticatedUser.RealmHandle, -1, UserSlot, None};
}

		
void UBeamTournamentsApi::GetGroups(FUserSlot UserSlot, UBasicTournamentsGetGroupsRequest* Request, const FOnBasicTournamentsGetGroupsSuccess& OnSuccess, const FOnBasicTournamentsGetGroupsError& OnError, const FOnBasicTournamentsGetGroupsComplete& OnComplete,  FBeamRequestContext& OutRequestContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UBasicTournamentsGetGroupsRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_GetGroupsImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, AuthenticatedUser.RealmHandle, -1, UserSlot, None};
}
	


void UBeamTournamentsApi::PostSearchGroupsWithRetry(const FBeamRetryConfig& RetryConfig, UPostSearchGroupsRequest* Request, const FOnPostSearchGroupsSuccess& OnSuccess, const FOnPostSearchGroupsError& OnError, const FOnPostSearchGroupsComplete& OnComplete, FBeamRequestContext& OutRequestContext)
{
	int64 OutRequestId = 0;
	BP_PostSearchGroupsImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, Backend->UnauthenticatedRequestsTargetRealm, -1, FUserSlot(), None}; 
}

		
void UBeamTournamentsApi::BasicTournamentsGetTournamentsWithRetry(const FBeamRetryConfig& RetryConfig, UBasicTournamentsGetTournamentsRequest* Request, const FOnBasicTournamentsGetTournamentsSuccess& OnSuccess, const FOnBasicTournamentsGetTournamentsError& OnError, const FOnBasicTournamentsGetTournamentsComplete& OnComplete, FBeamRequestContext& OutRequestContext)
{
	int64 OutRequestId = 0;
	BP_BasicTournamentsGetTournamentsImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, Backend->UnauthenticatedRequestsTargetRealm, -1, FUserSlot(), None}; 
}

		
void UBeamTournamentsApi::PostScoreWithRetry(const FBeamRetryConfig& RetryConfig, UPostScoreRequest* Request, const FOnPostScoreSuccess& OnSuccess, const FOnPostScoreError& OnError, const FOnPostScoreComplete& OnComplete, FBeamRequestContext& OutRequestContext)
{
	int64 OutRequestId = 0;
	BP_PostScoreImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, Backend->UnauthenticatedRequestsTargetRealm, -1, FUserSlot(), None}; 
}

		
void UBeamTournamentsApi::ObjectTournamentsGetTournamentsWithRetry(const FBeamRetryConfig& RetryConfig, UObjectTournamentsGetTournamentsRequest* Request, const FOnObjectTournamentsGetTournamentsSuccess& OnSuccess, const FOnObjectTournamentsGetTournamentsError& OnError, const FOnObjectTournamentsGetTournamentsComplete& OnComplete, FBeamRequestContext& OutRequestContext)
{
	int64 OutRequestId = 0;
	BP_ObjectTournamentsGetTournamentsImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, Backend->UnauthenticatedRequestsTargetRealm, -1, FUserSlot(), None}; 
}



void UBeamTournamentsApi::PostTournamentsWithRetry(FUserSlot UserSlot, const FBeamRetryConfig& RetryConfig, UPostTournamentsRequest* Request, const FOnPostTournamentsSuccess& OnSuccess, const FOnPostTournamentsError& OnError, const FOnPostTournamentsComplete& OnComplete, FBeamRequestContext& OutRequestContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser);	

	int64 OutRequestId;
	BP_PostTournamentsImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, AuthenticatedUser.RealmHandle, -1, UserSlot, None}; 
}

		
void UBeamTournamentsApi::GetMeGroupWithRetry(FUserSlot UserSlot, const FBeamRetryConfig& RetryConfig, UGetMeGroupRequest* Request, const FOnGetMeGroupSuccess& OnSuccess, const FOnGetMeGroupError& OnError, const FOnGetMeGroupComplete& OnComplete, FBeamRequestContext& OutRequestContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser);	

	int64 OutRequestId;
	BP_GetMeGroupImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, AuthenticatedUser.RealmHandle, -1, UserSlot, None}; 
}

		
void UBeamTournamentsApi::GetRewardsWithRetry(FUserSlot UserSlot, const FBeamRetryConfig& RetryConfig, UGetRewardsRequest* Request, const FOnGetRewardsSuccess& OnSuccess, const FOnGetRewardsError& OnError, const FOnGetRewardsComplete& OnComplete, FBeamRequestContext& OutRequestContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser);	

	int64 OutRequestId;
	BP_GetRewardsImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, AuthenticatedUser.RealmHandle, -1, UserSlot, None}; 
}

		
void UBeamTournamentsApi::PostRewardsWithRetry(FUserSlot UserSlot, const FBeamRetryConfig& RetryConfig, UPostRewardsRequest* Request, const FOnPostRewardsSuccess& OnSuccess, const FOnPostRewardsError& OnError, const FOnPostRewardsComplete& OnComplete, FBeamRequestContext& OutRequestContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser);	

	int64 OutRequestId;
	BP_PostRewardsImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, AuthenticatedUser.RealmHandle, -1, UserSlot, None}; 
}

		
void UBeamTournamentsApi::GetGlobalWithRetry(FUserSlot UserSlot, const FBeamRetryConfig& RetryConfig, UGetGlobalRequest* Request, const FOnGetGlobalSuccess& OnSuccess, const FOnGetGlobalError& OnError, const FOnGetGlobalComplete& OnComplete, FBeamRequestContext& OutRequestContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser);	

	int64 OutRequestId;
	BP_GetGlobalImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, AuthenticatedUser.RealmHandle, -1, UserSlot, None}; 
}

		
void UBeamTournamentsApi::GetStandingsGroupWithRetry(FUserSlot UserSlot, const FBeamRetryConfig& RetryConfig, UGetStandingsGroupRequest* Request, const FOnGetStandingsGroupSuccess& OnSuccess, const FOnGetStandingsGroupError& OnError, const FOnGetStandingsGroupComplete& OnComplete, FBeamRequestContext& OutRequestContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser);	

	int64 OutRequestId;
	BP_GetStandingsGroupImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, AuthenticatedUser.RealmHandle, -1, UserSlot, None}; 
}

		
void UBeamTournamentsApi::GetStandingsWithRetry(FUserSlot UserSlot, const FBeamRetryConfig& RetryConfig, UGetStandingsRequest* Request, const FOnGetStandingsSuccess& OnSuccess, const FOnGetStandingsError& OnError, const FOnGetStandingsComplete& OnComplete, FBeamRequestContext& OutRequestContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser);	

	int64 OutRequestId;
	BP_GetStandingsImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, AuthenticatedUser.RealmHandle, -1, UserSlot, None}; 
}

		
void UBeamTournamentsApi::GetAdminPlayerWithRetry(FUserSlot UserSlot, const FBeamRetryConfig& RetryConfig, UGetAdminPlayerRequest* Request, const FOnGetAdminPlayerSuccess& OnSuccess, const FOnGetAdminPlayerError& OnError, const FOnGetAdminPlayerComplete& OnComplete, FBeamRequestContext& OutRequestContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser);	

	int64 OutRequestId;
	BP_GetAdminPlayerImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, AuthenticatedUser.RealmHandle, -1, UserSlot, None}; 
}

		
void UBeamTournamentsApi::PutAdminPlayerWithRetry(FUserSlot UserSlot, const FBeamRetryConfig& RetryConfig, UPutAdminPlayerRequest* Request, const FOnPutAdminPlayerSuccess& OnSuccess, const FOnPutAdminPlayerError& OnError, const FOnPutAdminPlayerComplete& OnComplete, FBeamRequestContext& OutRequestContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser);	

	int64 OutRequestId;
	BP_PutAdminPlayerImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, AuthenticatedUser.RealmHandle, -1, UserSlot, None}; 
}

		
void UBeamTournamentsApi::GetMeWithRetry(FUserSlot UserSlot, const FBeamRetryConfig& RetryConfig, UBasicTournamentsGetMeRequest* Request, const FOnBasicTournamentsGetMeSuccess& OnSuccess, const FOnBasicTournamentsGetMeError& OnError, const FOnBasicTournamentsGetMeComplete& OnComplete, FBeamRequestContext& OutRequestContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser);	

	int64 OutRequestId;
	BP_GetMeImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, AuthenticatedUser.RealmHandle, -1, UserSlot, None}; 
}

		
void UBeamTournamentsApi::GetChampionsWithRetry(FUserSlot UserSlot, const FBeamRetryConfig& RetryConfig, UGetChampionsRequest* Request, const FOnGetChampionsSuccess& OnSuccess, const FOnGetChampionsError& OnError, const FOnGetChampionsComplete& OnComplete, FBeamRequestContext& OutRequestContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser);	

	int64 OutRequestId;
	BP_GetChampionsImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, AuthenticatedUser.RealmHandle, -1, UserSlot, None}; 
}

		
void UBeamTournamentsApi::GetGroupsWithRetry(FUserSlot UserSlot, const FBeamRetryConfig& RetryConfig, UBasicTournamentsGetGroupsRequest* Request, const FOnBasicTournamentsGetGroupsSuccess& OnSuccess, const FOnBasicTournamentsGetGroupsError& OnError, const FOnBasicTournamentsGetGroupsComplete& OnComplete, FBeamRequestContext& OutRequestContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser);	

	int64 OutRequestId;
	BP_GetGroupsImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, AuthenticatedUser.RealmHandle, -1, UserSlot, None}; 
}


