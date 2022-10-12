
#include "AutoGen/SubSystems/BeamAnnouncementsApi.h"

void UBeamAnnouncementsApi::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Backend = Cast<UBeamBackend>(Collection.InitializeDependency(UBeamBackend::StaticClass()));
}

void UBeamAnnouncementsApi::Deinitialize()
{
	Super::Deinitialize();
}




void UBeamAnnouncementsApi::BP_GetListTagsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UGetListTagsRequest* RequestData, const FOnGetListTagsSuccess& OnSuccess, const FOnGetListTagsError& OnError, const FOnGetListTagsComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UGetListTagsRequest, UListTagsResponse, FOnGetListTagsSuccess, FOnGetListTagsError, FOnGetListTagsComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	const auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig, TargetRealm};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(RequestContext, ConnectivityStatus, OutRequestId);
}

void UBeamAnnouncementsApi::CPP_GetListTagsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UGetListTagsRequest* RequestData, const FOnGetListTagsFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UGetListTagsRequest, UListTagsResponse>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	const auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig, TargetRealm};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(RequestContext, ConnectivityStatus, OutRequestId);
}

		
void UBeamAnnouncementsApi::BP_GetListImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UBasicAnnouncementsGetListRequest* RequestData, const FOnBasicAnnouncementsGetListSuccess& OnSuccess, const FOnBasicAnnouncementsGetListError& OnError, const FOnBasicAnnouncementsGetListComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UBasicAnnouncementsGetListRequest, UAnnouncementContentResponse, FOnBasicAnnouncementsGetListSuccess, FOnBasicAnnouncementsGetListError, FOnBasicAnnouncementsGetListComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	const auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig, TargetRealm};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(RequestContext, ConnectivityStatus, OutRequestId);
}

void UBeamAnnouncementsApi::CPP_GetListImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UBasicAnnouncementsGetListRequest* RequestData, const FOnBasicAnnouncementsGetListFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UBasicAnnouncementsGetListRequest, UAnnouncementContentResponse>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	const auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig, TargetRealm};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(RequestContext, ConnectivityStatus, OutRequestId);
}

		
void UBeamAnnouncementsApi::BP_GetSearchImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UBasicAnnouncementsGetSearchRequest* RequestData, const FOnBasicAnnouncementsGetSearchSuccess& OnSuccess, const FOnBasicAnnouncementsGetSearchError& OnError, const FOnBasicAnnouncementsGetSearchComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UBasicAnnouncementsGetSearchRequest, UAnnouncementContentResponse, FOnBasicAnnouncementsGetSearchSuccess, FOnBasicAnnouncementsGetSearchError, FOnBasicAnnouncementsGetSearchComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	const auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig, TargetRealm};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(RequestContext, ConnectivityStatus, OutRequestId);
}

void UBeamAnnouncementsApi::CPP_GetSearchImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UBasicAnnouncementsGetSearchRequest* RequestData, const FOnBasicAnnouncementsGetSearchFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UBasicAnnouncementsGetSearchRequest, UAnnouncementContentResponse>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	const auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig, TargetRealm};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(RequestContext, ConnectivityStatus, OutRequestId);
}

		
void UBeamAnnouncementsApi::BP_GetListDefinitionsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UGetListDefinitionsRequest* RequestData, const FOnGetListDefinitionsSuccess& OnSuccess, const FOnGetListDefinitionsError& OnError, const FOnGetListDefinitionsComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UGetListDefinitionsRequest, UListDefinitionsResponse, FOnGetListDefinitionsSuccess, FOnGetListDefinitionsError, FOnGetListDefinitionsComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	const auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig, TargetRealm};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(RequestContext, ConnectivityStatus, OutRequestId);
}

void UBeamAnnouncementsApi::CPP_GetListDefinitionsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UGetListDefinitionsRequest* RequestData, const FOnGetListDefinitionsFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UGetListDefinitionsRequest, UListDefinitionsResponse>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	const auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig, TargetRealm};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(RequestContext, ConnectivityStatus, OutRequestId);
}

		
void UBeamAnnouncementsApi::BP_PostAnnouncementsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UPostAnnouncementsRequest* RequestData, const FOnPostAnnouncementsSuccess& OnSuccess, const FOnPostAnnouncementsError& OnError, const FOnPostAnnouncementsComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPostAnnouncementsRequest, UEmptyResponse, FOnPostAnnouncementsSuccess, FOnPostAnnouncementsError, FOnPostAnnouncementsComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	const auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig, TargetRealm};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(RequestContext, ConnectivityStatus, OutRequestId);
}

void UBeamAnnouncementsApi::CPP_PostAnnouncementsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UPostAnnouncementsRequest* RequestData, const FOnPostAnnouncementsFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPostAnnouncementsRequest, UEmptyResponse>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	const auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig, TargetRealm};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(RequestContext, ConnectivityStatus, OutRequestId);
}

		
void UBeamAnnouncementsApi::BP_BasicAnnouncementsDeleteAnnouncementsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UBasicAnnouncementsDeleteAnnouncementsRequest* RequestData, const FOnBasicAnnouncementsDeleteAnnouncementsSuccess& OnSuccess, const FOnBasicAnnouncementsDeleteAnnouncementsError& OnError, const FOnBasicAnnouncementsDeleteAnnouncementsComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UBasicAnnouncementsDeleteAnnouncementsRequest, UEmptyResponse, FOnBasicAnnouncementsDeleteAnnouncementsSuccess, FOnBasicAnnouncementsDeleteAnnouncementsError, FOnBasicAnnouncementsDeleteAnnouncementsComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	const auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig, TargetRealm};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(RequestContext, ConnectivityStatus, OutRequestId);
}

void UBeamAnnouncementsApi::CPP_BasicAnnouncementsDeleteAnnouncementsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UBasicAnnouncementsDeleteAnnouncementsRequest* RequestData, const FOnBasicAnnouncementsDeleteAnnouncementsFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UBasicAnnouncementsDeleteAnnouncementsRequest, UEmptyResponse>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	const auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig, TargetRealm};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(RequestContext, ConnectivityStatus, OutRequestId);
}

		
void UBeamAnnouncementsApi::BP_GetContentImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UBasicAnnouncementsGetContentRequest* RequestData, const FOnBasicAnnouncementsGetContentSuccess& OnSuccess, const FOnBasicAnnouncementsGetContentError& OnError, const FOnBasicAnnouncementsGetContentComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UBasicAnnouncementsGetContentRequest, UAnnouncementContentResponse, FOnBasicAnnouncementsGetContentSuccess, FOnBasicAnnouncementsGetContentError, FOnBasicAnnouncementsGetContentComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	const auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig, TargetRealm};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(RequestContext, ConnectivityStatus, OutRequestId);
}

void UBeamAnnouncementsApi::CPP_GetContentImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UBasicAnnouncementsGetContentRequest* RequestData, const FOnBasicAnnouncementsGetContentFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UBasicAnnouncementsGetContentRequest, UAnnouncementContentResponse>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	const auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig, TargetRealm};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(RequestContext, ConnectivityStatus, OutRequestId);
}

		
void UBeamAnnouncementsApi::BP_PutReadImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UPutReadRequest* RequestData, const FOnPutReadSuccess& OnSuccess, const FOnPutReadError& OnError, const FOnPutReadComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPutReadRequest, UCommonResponse, FOnPutReadSuccess, FOnPutReadError, FOnPutReadComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	const auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig, TargetRealm};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(RequestContext, ConnectivityStatus, OutRequestId);
}

void UBeamAnnouncementsApi::CPP_PutReadImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UPutReadRequest* RequestData, const FOnPutReadFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPutReadRequest, UCommonResponse>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	const auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig, TargetRealm};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(RequestContext, ConnectivityStatus, OutRequestId);
}

		
void UBeamAnnouncementsApi::BP_PostClaimImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UObjectAnnouncementsPostClaimRequest* RequestData, const FOnObjectAnnouncementsPostClaimSuccess& OnSuccess, const FOnObjectAnnouncementsPostClaimError& OnError, const FOnObjectAnnouncementsPostClaimComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UObjectAnnouncementsPostClaimRequest, UCommonResponse, FOnObjectAnnouncementsPostClaimSuccess, FOnObjectAnnouncementsPostClaimError, FOnObjectAnnouncementsPostClaimComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	const auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig, TargetRealm};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(RequestContext, ConnectivityStatus, OutRequestId);
}

void UBeamAnnouncementsApi::CPP_PostClaimImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UObjectAnnouncementsPostClaimRequest* RequestData, const FOnObjectAnnouncementsPostClaimFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UObjectAnnouncementsPostClaimRequest, UCommonResponse>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	const auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig, TargetRealm};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(RequestContext, ConnectivityStatus, OutRequestId);
}

		
void UBeamAnnouncementsApi::BP_GetRawImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UGetRawRequest* RequestData, const FOnGetRawSuccess& OnSuccess, const FOnGetRawError& OnError, const FOnGetRawComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UGetRawRequest, UAnnouncementRawResponse, FOnGetRawSuccess, FOnGetRawError, FOnGetRawComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	const auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig, TargetRealm};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(RequestContext, ConnectivityStatus, OutRequestId);
}

void UBeamAnnouncementsApi::CPP_GetRawImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UGetRawRequest* RequestData, const FOnGetRawFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UGetRawRequest, UAnnouncementRawResponse>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	const auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig, TargetRealm};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(RequestContext, ConnectivityStatus, OutRequestId);
}

		
void UBeamAnnouncementsApi::BP_GetAnnouncementsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UGetAnnouncementsRequest* RequestData, const FOnGetAnnouncementsSuccess& OnSuccess, const FOnGetAnnouncementsError& OnError, const FOnGetAnnouncementsComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UGetAnnouncementsRequest, UAnnouncementQueryResponse, FOnGetAnnouncementsSuccess, FOnGetAnnouncementsError, FOnGetAnnouncementsComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	const auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig, TargetRealm};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(RequestContext, ConnectivityStatus, OutRequestId);
}

void UBeamAnnouncementsApi::CPP_GetAnnouncementsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UGetAnnouncementsRequest* RequestData, const FOnGetAnnouncementsFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UGetAnnouncementsRequest, UAnnouncementQueryResponse>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	const auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig, TargetRealm};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(RequestContext, ConnectivityStatus, OutRequestId);
}

		
void UBeamAnnouncementsApi::BP_ObjectAnnouncementsDeleteAnnouncementsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UObjectAnnouncementsDeleteAnnouncementsRequest* RequestData, const FOnObjectAnnouncementsDeleteAnnouncementsSuccess& OnSuccess, const FOnObjectAnnouncementsDeleteAnnouncementsError& OnError, const FOnObjectAnnouncementsDeleteAnnouncementsComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UObjectAnnouncementsDeleteAnnouncementsRequest, UCommonResponse, FOnObjectAnnouncementsDeleteAnnouncementsSuccess, FOnObjectAnnouncementsDeleteAnnouncementsError, FOnObjectAnnouncementsDeleteAnnouncementsComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	const auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig, TargetRealm};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(RequestContext, ConnectivityStatus, OutRequestId);
}

void UBeamAnnouncementsApi::CPP_ObjectAnnouncementsDeleteAnnouncementsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UObjectAnnouncementsDeleteAnnouncementsRequest* RequestData, const FOnObjectAnnouncementsDeleteAnnouncementsFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UObjectAnnouncementsDeleteAnnouncementsRequest, UCommonResponse>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	const auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig, TargetRealm};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(RequestContext, ConnectivityStatus, OutRequestId);
}






void UBeamAnnouncementsApi::CPP_GetListTags(const FUserSlot& UserSlotId, UGetListTagsRequest* Request, const FOnGetListTagsFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UGetListTagsRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_GetListTagsImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamAnnouncementsApi::CPP_GetList(const FUserSlot& UserSlotId, UBasicAnnouncementsGetListRequest* Request, const FOnBasicAnnouncementsGetListFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UBasicAnnouncementsGetListRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_GetListImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamAnnouncementsApi::CPP_GetSearch(const FUserSlot& UserSlotId, UBasicAnnouncementsGetSearchRequest* Request, const FOnBasicAnnouncementsGetSearchFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UBasicAnnouncementsGetSearchRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_GetSearchImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamAnnouncementsApi::CPP_GetListDefinitions(const FUserSlot& UserSlotId, UGetListDefinitionsRequest* Request, const FOnGetListDefinitionsFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UGetListDefinitionsRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_GetListDefinitionsImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamAnnouncementsApi::CPP_PostAnnouncements(const FUserSlot& UserSlotId, UPostAnnouncementsRequest* Request, const FOnPostAnnouncementsFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostAnnouncementsRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_PostAnnouncementsImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamAnnouncementsApi::CPP_BasicAnnouncementsDeleteAnnouncements(const FUserSlot& UserSlotId, UBasicAnnouncementsDeleteAnnouncementsRequest* Request, const FOnBasicAnnouncementsDeleteAnnouncementsFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UBasicAnnouncementsDeleteAnnouncementsRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_BasicAnnouncementsDeleteAnnouncementsImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamAnnouncementsApi::CPP_GetContent(const FUserSlot& UserSlotId, UBasicAnnouncementsGetContentRequest* Request, const FOnBasicAnnouncementsGetContentFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UBasicAnnouncementsGetContentRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_GetContentImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamAnnouncementsApi::CPP_PutRead(const FUserSlot& UserSlotId, UPutReadRequest* Request, const FOnPutReadFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPutReadRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_PutReadImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamAnnouncementsApi::CPP_PostClaim(const FUserSlot& UserSlotId, UObjectAnnouncementsPostClaimRequest* Request, const FOnObjectAnnouncementsPostClaimFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UObjectAnnouncementsPostClaimRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_PostClaimImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamAnnouncementsApi::CPP_GetRaw(const FUserSlot& UserSlotId, UGetRawRequest* Request, const FOnGetRawFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UGetRawRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_GetRawImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamAnnouncementsApi::CPP_GetAnnouncements(const FUserSlot& UserSlotId, UGetAnnouncementsRequest* Request, const FOnGetAnnouncementsFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UGetAnnouncementsRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_GetAnnouncementsImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamAnnouncementsApi::CPP_ObjectAnnouncementsDeleteAnnouncements(const FUserSlot& UserSlotId, UObjectAnnouncementsDeleteAnnouncementsRequest* Request, const FOnObjectAnnouncementsDeleteAnnouncementsFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UObjectAnnouncementsDeleteAnnouncementsRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_ObjectAnnouncementsDeleteAnnouncementsImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}






void UBeamAnnouncementsApi::GetListTags(const FUserSlot& UserSlotId, UGetListTagsRequest* Request, const FOnGetListTagsSuccess& OnSuccess, const FOnGetListTagsError& OnError,
                             const FOnGetListTagsComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UGetListTagsRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	BP_GetListTagsImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamAnnouncementsApi::GetList(const FUserSlot& UserSlotId, UBasicAnnouncementsGetListRequest* Request, const FOnBasicAnnouncementsGetListSuccess& OnSuccess, const FOnBasicAnnouncementsGetListError& OnError,
                             const FOnBasicAnnouncementsGetListComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UBasicAnnouncementsGetListRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	BP_GetListImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamAnnouncementsApi::GetSearch(const FUserSlot& UserSlotId, UBasicAnnouncementsGetSearchRequest* Request, const FOnBasicAnnouncementsGetSearchSuccess& OnSuccess, const FOnBasicAnnouncementsGetSearchError& OnError,
                             const FOnBasicAnnouncementsGetSearchComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UBasicAnnouncementsGetSearchRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	BP_GetSearchImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamAnnouncementsApi::GetListDefinitions(const FUserSlot& UserSlotId, UGetListDefinitionsRequest* Request, const FOnGetListDefinitionsSuccess& OnSuccess, const FOnGetListDefinitionsError& OnError,
                             const FOnGetListDefinitionsComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UGetListDefinitionsRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	BP_GetListDefinitionsImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamAnnouncementsApi::PostAnnouncements(const FUserSlot& UserSlotId, UPostAnnouncementsRequest* Request, const FOnPostAnnouncementsSuccess& OnSuccess, const FOnPostAnnouncementsError& OnError,
                             const FOnPostAnnouncementsComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostAnnouncementsRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	BP_PostAnnouncementsImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamAnnouncementsApi::BasicAnnouncementsDeleteAnnouncements(const FUserSlot& UserSlotId, UBasicAnnouncementsDeleteAnnouncementsRequest* Request, const FOnBasicAnnouncementsDeleteAnnouncementsSuccess& OnSuccess, const FOnBasicAnnouncementsDeleteAnnouncementsError& OnError,
                             const FOnBasicAnnouncementsDeleteAnnouncementsComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UBasicAnnouncementsDeleteAnnouncementsRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	BP_BasicAnnouncementsDeleteAnnouncementsImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamAnnouncementsApi::GetContent(const FUserSlot& UserSlotId, UBasicAnnouncementsGetContentRequest* Request, const FOnBasicAnnouncementsGetContentSuccess& OnSuccess, const FOnBasicAnnouncementsGetContentError& OnError,
                             const FOnBasicAnnouncementsGetContentComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UBasicAnnouncementsGetContentRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	BP_GetContentImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamAnnouncementsApi::PutRead(const FUserSlot& UserSlotId, UPutReadRequest* Request, const FOnPutReadSuccess& OnSuccess, const FOnPutReadError& OnError,
                             const FOnPutReadComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPutReadRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	BP_PutReadImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamAnnouncementsApi::PostClaim(const FUserSlot& UserSlotId, UObjectAnnouncementsPostClaimRequest* Request, const FOnObjectAnnouncementsPostClaimSuccess& OnSuccess, const FOnObjectAnnouncementsPostClaimError& OnError,
                             const FOnObjectAnnouncementsPostClaimComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UObjectAnnouncementsPostClaimRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	BP_PostClaimImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamAnnouncementsApi::GetRaw(const FUserSlot& UserSlotId, UGetRawRequest* Request, const FOnGetRawSuccess& OnSuccess, const FOnGetRawError& OnError,
                             const FOnGetRawComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UGetRawRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	BP_GetRawImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamAnnouncementsApi::GetAnnouncements(const FUserSlot& UserSlotId, UGetAnnouncementsRequest* Request, const FOnGetAnnouncementsSuccess& OnSuccess, const FOnGetAnnouncementsError& OnError,
                             const FOnGetAnnouncementsComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UGetAnnouncementsRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	BP_GetAnnouncementsImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamAnnouncementsApi::ObjectAnnouncementsDeleteAnnouncements(const FUserSlot& UserSlotId, UObjectAnnouncementsDeleteAnnouncementsRequest* Request, const FOnObjectAnnouncementsDeleteAnnouncementsSuccess& OnSuccess, const FOnObjectAnnouncementsDeleteAnnouncementsError& OnError,
                             const FOnObjectAnnouncementsDeleteAnnouncementsComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UObjectAnnouncementsDeleteAnnouncementsRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	BP_ObjectAnnouncementsDeleteAnnouncementsImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}
	
