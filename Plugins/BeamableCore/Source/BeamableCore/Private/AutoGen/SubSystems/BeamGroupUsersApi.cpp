
#include "AutoGen/SubSystems/BeamGroupUsersApi.h"
#include "BeamCoreSettings.h"


void UBeamGroupUsersApi::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Backend = Cast<UBeamBackend>(Collection.InitializeDependency(UBeamBackend::StaticClass()));
	RequestTracker = Cast<UBeamRequestTracker>(Collection.InitializeDependency(UBeamRequestTracker::StaticClass()));
}

void UBeamGroupUsersApi::Deinitialize()
{
	Super::Deinitialize();
}


void UBeamGroupUsersApi::BP_GetAvailabilityImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetAvailabilityRequest* RequestData,
                                                  const FOnGetAvailabilitySuccess& OnSuccess, const FOnGetAvailabilityError& OnError, const FOnGetAvailabilityComplete& OnComplete,
                                                  int64& OutRequestId, FBeamOperationHandle OpHandle) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UGetAvailabilityRequest, UAvailabilityResponse, FOnGetAvailabilitySuccess, FOnGetAvailabilityError, FOnGetAvailabilityComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
	
	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);
}

void UBeamGroupUsersApi::CPP_GetAvailabilityImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UGetAvailabilityRequest* RequestData, const FOnGetAvailabilityFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UGetAvailabilityRequest, UAvailabilityResponse>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);

	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);
}

		
void UBeamGroupUsersApi::BP_GetRecommendedImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetRecommendedRequest* RequestData,
                                                  const FOnGetRecommendedSuccess& OnSuccess, const FOnGetRecommendedError& OnError, const FOnGetRecommendedComplete& OnComplete,
                                                  int64& OutRequestId, FBeamOperationHandle OpHandle) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UGetRecommendedRequest, UGroupSearchResponse, FOnGetRecommendedSuccess, FOnGetRecommendedError, FOnGetRecommendedComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
	
	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);
}

void UBeamGroupUsersApi::CPP_GetRecommendedImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UGetRecommendedRequest* RequestData, const FOnGetRecommendedFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UGetRecommendedRequest, UGroupSearchResponse>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);

	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);
}

		
void UBeamGroupUsersApi::BP_PostJoinImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostJoinRequest* RequestData,
                                                  const FOnPostJoinSuccess& OnSuccess, const FOnPostJoinError& OnError, const FOnPostJoinComplete& OnComplete,
                                                  int64& OutRequestId, FBeamOperationHandle OpHandle) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UPostJoinRequest, UGroupMembershipResponse, FOnPostJoinSuccess, FOnPostJoinError, FOnPostJoinComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
	
	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);
}

void UBeamGroupUsersApi::CPP_PostJoinImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UPostJoinRequest* RequestData, const FOnPostJoinFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UPostJoinRequest, UGroupMembershipResponse>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);

	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);
}

		
void UBeamGroupUsersApi::BP_DeleteJoinImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UDeleteJoinRequest* RequestData,
                                                  const FOnDeleteJoinSuccess& OnSuccess, const FOnDeleteJoinError& OnError, const FOnDeleteJoinComplete& OnComplete,
                                                  int64& OutRequestId, FBeamOperationHandle OpHandle) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UDeleteJoinRequest, UGroupMembershipResponse, FOnDeleteJoinSuccess, FOnDeleteJoinError, FOnDeleteJoinComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
	
	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);
}

void UBeamGroupUsersApi::CPP_DeleteJoinImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UDeleteJoinRequest* RequestData, const FOnDeleteJoinFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UDeleteJoinRequest, UGroupMembershipResponse>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);

	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);
}

		
void UBeamGroupUsersApi::BP_PostGroupImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostGroupRequest* RequestData,
                                                  const FOnPostGroupSuccess& OnSuccess, const FOnPostGroupError& OnError, const FOnPostGroupComplete& OnComplete,
                                                  int64& OutRequestId, FBeamOperationHandle OpHandle) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UPostGroupRequest, UGroupCreateResponse, FOnPostGroupSuccess, FOnPostGroupError, FOnPostGroupComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
	
	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);
}

void UBeamGroupUsersApi::CPP_PostGroupImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UPostGroupRequest* RequestData, const FOnPostGroupFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UPostGroupRequest, UGroupCreateResponse>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);

	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);
}

		
void UBeamGroupUsersApi::BP_GetSearchImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UObjectGroupUsersGetSearchRequest* RequestData,
                                                  const FOnObjectGroupUsersGetSearchSuccess& OnSuccess, const FOnObjectGroupUsersGetSearchError& OnError, const FOnObjectGroupUsersGetSearchComplete& OnComplete,
                                                  int64& OutRequestId, FBeamOperationHandle OpHandle) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UObjectGroupUsersGetSearchRequest, UGroupSearchResponse, FOnObjectGroupUsersGetSearchSuccess, FOnObjectGroupUsersGetSearchError, FOnObjectGroupUsersGetSearchComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
	
	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);
}

void UBeamGroupUsersApi::CPP_GetSearchImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UObjectGroupUsersGetSearchRequest* RequestData, const FOnObjectGroupUsersGetSearchFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UObjectGroupUsersGetSearchRequest, UGroupSearchResponse>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);

	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);
}

		
void UBeamGroupUsersApi::BP_GetGroupUsersImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetGroupUsersRequest* RequestData,
                                                  const FOnGetGroupUsersSuccess& OnSuccess, const FOnGetGroupUsersError& OnError, const FOnGetGroupUsersComplete& OnComplete,
                                                  int64& OutRequestId, FBeamOperationHandle OpHandle) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UGetGroupUsersRequest, UGroupUser, FOnGetGroupUsersSuccess, FOnGetGroupUsersError, FOnGetGroupUsersComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
	
	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);
}

void UBeamGroupUsersApi::CPP_GetGroupUsersImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UGetGroupUsersRequest* RequestData, const FOnGetGroupUsersFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UGetGroupUsersRequest, UGroupUser>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);

	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);
}






void UBeamGroupUsersApi::CPP_GetAvailability(UGetAvailabilityRequest* Request, const FOnGetAvailabilityFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UGetAvailabilityRequest::StaticClass()->GetName(), RetryConfig);
	
    int64 OutRequestId;
	CPP_GetAvailabilityImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler, OutRequestId, OpHandle);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, FUserSlot(), None};
}

		
void UBeamGroupUsersApi::CPP_GetRecommended(UGetRecommendedRequest* Request, const FOnGetRecommendedFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UGetRecommendedRequest::StaticClass()->GetName(), RetryConfig);
	
    int64 OutRequestId;
	CPP_GetRecommendedImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler, OutRequestId, OpHandle);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, FUserSlot(), None};
}

		
void UBeamGroupUsersApi::CPP_PostJoin(UPostJoinRequest* Request, const FOnPostJoinFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UPostJoinRequest::StaticClass()->GetName(), RetryConfig);
	
    int64 OutRequestId;
	CPP_PostJoinImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler, OutRequestId, OpHandle);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, FUserSlot(), None};
}

		
void UBeamGroupUsersApi::CPP_DeleteJoin(UDeleteJoinRequest* Request, const FOnDeleteJoinFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UDeleteJoinRequest::StaticClass()->GetName(), RetryConfig);
	
    int64 OutRequestId;
	CPP_DeleteJoinImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler, OutRequestId, OpHandle);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, FUserSlot(), None};
}

		
void UBeamGroupUsersApi::CPP_PostGroup(UPostGroupRequest* Request, const FOnPostGroupFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UPostGroupRequest::StaticClass()->GetName(), RetryConfig);
	
    int64 OutRequestId;
	CPP_PostGroupImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler, OutRequestId, OpHandle);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, FUserSlot(), None};
}

		
void UBeamGroupUsersApi::CPP_GetSearch(UObjectGroupUsersGetSearchRequest* Request, const FOnObjectGroupUsersGetSearchFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UObjectGroupUsersGetSearchRequest::StaticClass()->GetName(), RetryConfig);
	
    int64 OutRequestId;
	CPP_GetSearchImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler, OutRequestId, OpHandle);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, FUserSlot(), None};
}

		
void UBeamGroupUsersApi::CPP_GetGroupUsers(UGetGroupUsersRequest* Request, const FOnGetGroupUsersFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UGetGroupUsersRequest::StaticClass()->GetName(), RetryConfig);
	
    int64 OutRequestId;
	CPP_GetGroupUsersImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler, OutRequestId, OpHandle);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, FUserSlot(), None};
}






void UBeamGroupUsersApi::GetAvailability(UGetAvailabilityRequest* Request, const FOnGetAvailabilitySuccess& OnSuccess, const FOnGetAvailabilityError& OnError, const FOnGetAvailabilityComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UGetAvailabilityRequest::StaticClass()->GetName(), RetryConfig);	
	
	int64 OutRequestId = 0;
	BP_GetAvailabilityImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, FUserSlot(), None};
}

		
void UBeamGroupUsersApi::GetRecommended(UGetRecommendedRequest* Request, const FOnGetRecommendedSuccess& OnSuccess, const FOnGetRecommendedError& OnError, const FOnGetRecommendedComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UGetRecommendedRequest::StaticClass()->GetName(), RetryConfig);	
	
	int64 OutRequestId = 0;
	BP_GetRecommendedImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, FUserSlot(), None};
}

		
void UBeamGroupUsersApi::PostJoin(UPostJoinRequest* Request, const FOnPostJoinSuccess& OnSuccess, const FOnPostJoinError& OnError, const FOnPostJoinComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UPostJoinRequest::StaticClass()->GetName(), RetryConfig);	
	
	int64 OutRequestId = 0;
	BP_PostJoinImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, FUserSlot(), None};
}

		
void UBeamGroupUsersApi::DeleteJoin(UDeleteJoinRequest* Request, const FOnDeleteJoinSuccess& OnSuccess, const FOnDeleteJoinError& OnError, const FOnDeleteJoinComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UDeleteJoinRequest::StaticClass()->GetName(), RetryConfig);	
	
	int64 OutRequestId = 0;
	BP_DeleteJoinImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, FUserSlot(), None};
}

		
void UBeamGroupUsersApi::PostGroup(UPostGroupRequest* Request, const FOnPostGroupSuccess& OnSuccess, const FOnPostGroupError& OnError, const FOnPostGroupComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UPostGroupRequest::StaticClass()->GetName(), RetryConfig);	
	
	int64 OutRequestId = 0;
	BP_PostGroupImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, FUserSlot(), None};
}

		
void UBeamGroupUsersApi::GetSearch(UObjectGroupUsersGetSearchRequest* Request, const FOnObjectGroupUsersGetSearchSuccess& OnSuccess, const FOnObjectGroupUsersGetSearchError& OnError, const FOnObjectGroupUsersGetSearchComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UObjectGroupUsersGetSearchRequest::StaticClass()->GetName(), RetryConfig);	
	
	int64 OutRequestId = 0;
	BP_GetSearchImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, FUserSlot(), None};
}

		
void UBeamGroupUsersApi::GetGroupUsers(UGetGroupUsersRequest* Request, const FOnGetGroupUsersSuccess& OnSuccess, const FOnGetGroupUsersError& OnError, const FOnGetGroupUsersComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UGetGroupUsersRequest::StaticClass()->GetName(), RetryConfig);	
	
	int64 OutRequestId = 0;
	BP_GetGroupUsersImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, FUserSlot(), None};
}


	


void UBeamGroupUsersApi::GetAvailabilityWithRetry(const FBeamRetryConfig& RetryConfig, UGetAvailabilityRequest* Request, const FOnGetAvailabilitySuccess& OnSuccess, const FOnGetAvailabilityError& OnError, const FOnGetAvailabilityComplete& OnComplete, FBeamRequestContext& OutRequestContext)
{
	int64 OutRequestId = 0;
	BP_GetAvailabilityImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, FUserSlot(), None}; 
}

		
void UBeamGroupUsersApi::GetRecommendedWithRetry(const FBeamRetryConfig& RetryConfig, UGetRecommendedRequest* Request, const FOnGetRecommendedSuccess& OnSuccess, const FOnGetRecommendedError& OnError, const FOnGetRecommendedComplete& OnComplete, FBeamRequestContext& OutRequestContext)
{
	int64 OutRequestId = 0;
	BP_GetRecommendedImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, FUserSlot(), None}; 
}

		
void UBeamGroupUsersApi::PostJoinWithRetry(const FBeamRetryConfig& RetryConfig, UPostJoinRequest* Request, const FOnPostJoinSuccess& OnSuccess, const FOnPostJoinError& OnError, const FOnPostJoinComplete& OnComplete, FBeamRequestContext& OutRequestContext)
{
	int64 OutRequestId = 0;
	BP_PostJoinImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, FUserSlot(), None}; 
}

		
void UBeamGroupUsersApi::DeleteJoinWithRetry(const FBeamRetryConfig& RetryConfig, UDeleteJoinRequest* Request, const FOnDeleteJoinSuccess& OnSuccess, const FOnDeleteJoinError& OnError, const FOnDeleteJoinComplete& OnComplete, FBeamRequestContext& OutRequestContext)
{
	int64 OutRequestId = 0;
	BP_DeleteJoinImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, FUserSlot(), None}; 
}

		
void UBeamGroupUsersApi::PostGroupWithRetry(const FBeamRetryConfig& RetryConfig, UPostGroupRequest* Request, const FOnPostGroupSuccess& OnSuccess, const FOnPostGroupError& OnError, const FOnPostGroupComplete& OnComplete, FBeamRequestContext& OutRequestContext)
{
	int64 OutRequestId = 0;
	BP_PostGroupImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, FUserSlot(), None}; 
}

		
void UBeamGroupUsersApi::GetSearchWithRetry(const FBeamRetryConfig& RetryConfig, UObjectGroupUsersGetSearchRequest* Request, const FOnObjectGroupUsersGetSearchSuccess& OnSuccess, const FOnObjectGroupUsersGetSearchError& OnError, const FOnObjectGroupUsersGetSearchComplete& OnComplete, FBeamRequestContext& OutRequestContext)
{
	int64 OutRequestId = 0;
	BP_GetSearchImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, FUserSlot(), None}; 
}

		
void UBeamGroupUsersApi::GetGroupUsersWithRetry(const FBeamRetryConfig& RetryConfig, UGetGroupUsersRequest* Request, const FOnGetGroupUsersSuccess& OnSuccess, const FOnGetGroupUsersError& OnError, const FOnGetGroupUsersComplete& OnComplete, FBeamRequestContext& OutRequestContext)
{
	int64 OutRequestId = 0;
	BP_GetGroupUsersImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, FUserSlot(), None}; 
}




