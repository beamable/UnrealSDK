
#include "AutoGen/SubSystems/BeamGroupUsersApi.h"

void UBeamGroupUsersApi::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Backend = Cast<UBeamBackend>(Collection.InitializeDependency(UBeamBackend::StaticClass()));
}

void UBeamGroupUsersApi::Deinitialize()
{
	Super::Deinitialize();
}


void UBeamGroupUsersApi::BP_GetAvailabilityImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetAvailabilityRequest* RequestData,
                                                  const FOnGetAvailabilitySuccess& OnSuccess, const FOnGetAvailabilityError& OnError, const FOnGetAvailabilityComplete& OnComplete,
                                                  int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UGetAvailabilityRequest, UAvailabilityResponse, FOnGetAvailabilitySuccess, FOnGetAvailabilityError, FOnGetAvailabilityComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig,TargetRealm, -1, FUserSlot(""), None};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamGroupUsersApi::CPP_GetAvailabilityImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UGetAvailabilityRequest* RequestData, const FOnGetAvailabilityFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UGetAvailabilityRequest, UAvailabilityResponse>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamGroupUsersApi::BP_GetRecommendedImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetRecommendedRequest* RequestData,
                                                  const FOnGetRecommendedSuccess& OnSuccess, const FOnGetRecommendedError& OnError, const FOnGetRecommendedComplete& OnComplete,
                                                  int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UGetRecommendedRequest, UGroupSearchResponse, FOnGetRecommendedSuccess, FOnGetRecommendedError, FOnGetRecommendedComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig,TargetRealm, -1, FUserSlot(""), None};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamGroupUsersApi::CPP_GetRecommendedImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UGetRecommendedRequest* RequestData, const FOnGetRecommendedFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UGetRecommendedRequest, UGroupSearchResponse>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamGroupUsersApi::BP_PostJoinImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostJoinRequest* RequestData,
                                                  const FOnPostJoinSuccess& OnSuccess, const FOnPostJoinError& OnError, const FOnPostJoinComplete& OnComplete,
                                                  int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UPostJoinRequest, UGroupMembershipResponse, FOnPostJoinSuccess, FOnPostJoinError, FOnPostJoinComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig,TargetRealm, -1, FUserSlot(""), None};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamGroupUsersApi::CPP_PostJoinImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UPostJoinRequest* RequestData, const FOnPostJoinFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UPostJoinRequest, UGroupMembershipResponse>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamGroupUsersApi::BP_DeleteJoinImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UDeleteJoinRequest* RequestData,
                                                  const FOnDeleteJoinSuccess& OnSuccess, const FOnDeleteJoinError& OnError, const FOnDeleteJoinComplete& OnComplete,
                                                  int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UDeleteJoinRequest, UGroupMembershipResponse, FOnDeleteJoinSuccess, FOnDeleteJoinError, FOnDeleteJoinComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig,TargetRealm, -1, FUserSlot(""), None};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamGroupUsersApi::CPP_DeleteJoinImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UDeleteJoinRequest* RequestData, const FOnDeleteJoinFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UDeleteJoinRequest, UGroupMembershipResponse>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamGroupUsersApi::BP_PostGroupImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostGroupRequest* RequestData,
                                                  const FOnPostGroupSuccess& OnSuccess, const FOnPostGroupError& OnError, const FOnPostGroupComplete& OnComplete,
                                                  int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UPostGroupRequest, UGroupCreateResponse, FOnPostGroupSuccess, FOnPostGroupError, FOnPostGroupComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig,TargetRealm, -1, FUserSlot(""), None};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamGroupUsersApi::CPP_PostGroupImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UPostGroupRequest* RequestData, const FOnPostGroupFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UPostGroupRequest, UGroupCreateResponse>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamGroupUsersApi::BP_GetSearchImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UObjectGroupUsersGetSearchRequest* RequestData,
                                                  const FOnObjectGroupUsersGetSearchSuccess& OnSuccess, const FOnObjectGroupUsersGetSearchError& OnError, const FOnObjectGroupUsersGetSearchComplete& OnComplete,
                                                  int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UObjectGroupUsersGetSearchRequest, UGroupSearchResponse, FOnObjectGroupUsersGetSearchSuccess, FOnObjectGroupUsersGetSearchError, FOnObjectGroupUsersGetSearchComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig,TargetRealm, -1, FUserSlot(""), None};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamGroupUsersApi::CPP_GetSearchImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UObjectGroupUsersGetSearchRequest* RequestData, const FOnObjectGroupUsersGetSearchFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UObjectGroupUsersGetSearchRequest, UGroupSearchResponse>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamGroupUsersApi::BP_GetGroupUsersImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetGroupUsersRequest* RequestData,
                                                  const FOnGetGroupUsersSuccess& OnSuccess, const FOnGetGroupUsersError& OnError, const FOnGetGroupUsersComplete& OnComplete,
                                                  int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UGetGroupUsersRequest, UGroupUser, FOnGetGroupUsersSuccess, FOnGetGroupUsersError, FOnGetGroupUsersComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig,TargetRealm, -1, FUserSlot(""), None};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamGroupUsersApi::CPP_GetGroupUsersImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UGetGroupUsersRequest* RequestData, const FOnGetGroupUsersFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UGetGroupUsersRequest, UGroupUser>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}






void UBeamGroupUsersApi::CPP_GetAvailability(UGetAvailabilityRequest* Request, const FOnGetAvailabilityFullResponse& Handler) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UGetAvailabilityRequest::StaticClass()->GetName(), RetryConfig);
	CPP_GetAvailabilityImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamGroupUsersApi::CPP_GetRecommended(UGetRecommendedRequest* Request, const FOnGetRecommendedFullResponse& Handler) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UGetRecommendedRequest::StaticClass()->GetName(), RetryConfig);
	CPP_GetRecommendedImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamGroupUsersApi::CPP_PostJoin(UPostJoinRequest* Request, const FOnPostJoinFullResponse& Handler) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UPostJoinRequest::StaticClass()->GetName(), RetryConfig);
	CPP_PostJoinImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamGroupUsersApi::CPP_DeleteJoin(UDeleteJoinRequest* Request, const FOnDeleteJoinFullResponse& Handler) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UDeleteJoinRequest::StaticClass()->GetName(), RetryConfig);
	CPP_DeleteJoinImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamGroupUsersApi::CPP_PostGroup(UPostGroupRequest* Request, const FOnPostGroupFullResponse& Handler) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UPostGroupRequest::StaticClass()->GetName(), RetryConfig);
	CPP_PostGroupImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamGroupUsersApi::CPP_GetSearch(UObjectGroupUsersGetSearchRequest* Request, const FOnObjectGroupUsersGetSearchFullResponse& Handler) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UObjectGroupUsersGetSearchRequest::StaticClass()->GetName(), RetryConfig);
	CPP_GetSearchImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamGroupUsersApi::CPP_GetGroupUsers(UGetGroupUsersRequest* Request, const FOnGetGroupUsersFullResponse& Handler) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UGetGroupUsersRequest::StaticClass()->GetName(), RetryConfig);
	CPP_GetGroupUsersImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler);
}






void UBeamGroupUsersApi::GetAvailability(UGetAvailabilityRequest* Request, const FOnGetAvailabilitySuccess& OnSuccess, const FOnGetAvailabilityError& OnError,
                                           const FOnGetAvailabilityComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UGetAvailabilityRequest::StaticClass()->GetName(), RetryConfig);
	BP_GetAvailabilityImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamGroupUsersApi::GetRecommended(UGetRecommendedRequest* Request, const FOnGetRecommendedSuccess& OnSuccess, const FOnGetRecommendedError& OnError,
                                           const FOnGetRecommendedComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UGetRecommendedRequest::StaticClass()->GetName(), RetryConfig);
	BP_GetRecommendedImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamGroupUsersApi::PostJoin(UPostJoinRequest* Request, const FOnPostJoinSuccess& OnSuccess, const FOnPostJoinError& OnError,
                                           const FOnPostJoinComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UPostJoinRequest::StaticClass()->GetName(), RetryConfig);
	BP_PostJoinImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamGroupUsersApi::DeleteJoin(UDeleteJoinRequest* Request, const FOnDeleteJoinSuccess& OnSuccess, const FOnDeleteJoinError& OnError,
                                           const FOnDeleteJoinComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UDeleteJoinRequest::StaticClass()->GetName(), RetryConfig);
	BP_DeleteJoinImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamGroupUsersApi::PostGroup(UPostGroupRequest* Request, const FOnPostGroupSuccess& OnSuccess, const FOnPostGroupError& OnError,
                                           const FOnPostGroupComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UPostGroupRequest::StaticClass()->GetName(), RetryConfig);
	BP_PostGroupImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamGroupUsersApi::GetSearch(UObjectGroupUsersGetSearchRequest* Request, const FOnObjectGroupUsersGetSearchSuccess& OnSuccess, const FOnObjectGroupUsersGetSearchError& OnError,
                                           const FOnObjectGroupUsersGetSearchComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UObjectGroupUsersGetSearchRequest::StaticClass()->GetName(), RetryConfig);
	BP_GetSearchImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamGroupUsersApi::GetGroupUsers(UGetGroupUsersRequest* Request, const FOnGetGroupUsersSuccess& OnSuccess, const FOnGetGroupUsersError& OnError,
                                           const FOnGetGroupUsersComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UGetGroupUsersRequest::StaticClass()->GetName(), RetryConfig);
	BP_GetGroupUsersImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}


	

