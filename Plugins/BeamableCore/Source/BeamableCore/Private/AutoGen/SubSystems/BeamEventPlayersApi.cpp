
#include "AutoGen/SubSystems/BeamEventPlayersApi.h"
#include "BeamCoreSettings.h"


void UBeamEventPlayersApi::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Backend = Cast<UBeamBackend>(Collection.InitializeDependency(UBeamBackend::StaticClass()));
	RequestTracker = Cast<UBeamRequestTracker>(Collection.InitializeDependency(UBeamRequestTracker::StaticClass()));
}

void UBeamEventPlayersApi::Deinitialize()
{
	Super::Deinitialize();
}


void UBeamEventPlayersApi::BP_GetEventPlayersImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetEventPlayersRequest* RequestData,
                                                  const FOnGetEventPlayersSuccess& OnSuccess, const FOnGetEventPlayersError& OnError, const FOnGetEventPlayersComplete& OnComplete,
                                                  int64& OutRequestId, FBeamOperationHandle OpHandle) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UGetEventPlayersRequest, UEventPlayerView, FOnGetEventPlayersSuccess, FOnGetEventPlayersError, FOnGetEventPlayersComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
	
	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);
}

void UBeamEventPlayersApi::CPP_GetEventPlayersImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UGetEventPlayersRequest* RequestData, const FOnGetEventPlayersFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UGetEventPlayersRequest, UEventPlayerView>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);

	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);
}

		
void UBeamEventPlayersApi::BP_PostClaimImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UObjectEventPlayersPostClaimRequest* RequestData,
                                                  const FOnObjectEventPlayersPostClaimSuccess& OnSuccess, const FOnObjectEventPlayersPostClaimError& OnError, const FOnObjectEventPlayersPostClaimComplete& OnComplete,
                                                  int64& OutRequestId, FBeamOperationHandle OpHandle) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UObjectEventPlayersPostClaimRequest, UEventClaimResponse, FOnObjectEventPlayersPostClaimSuccess, FOnObjectEventPlayersPostClaimError, FOnObjectEventPlayersPostClaimComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
	
	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);
}

void UBeamEventPlayersApi::CPP_PostClaimImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UObjectEventPlayersPostClaimRequest* RequestData, const FOnObjectEventPlayersPostClaimFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UObjectEventPlayersPostClaimRequest, UEventClaimResponse>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);

	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);
}

		
void UBeamEventPlayersApi::BP_PutScoreImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPutScoreRequest* RequestData,
                                                  const FOnPutScoreSuccess& OnSuccess, const FOnPutScoreError& OnError, const FOnPutScoreComplete& OnComplete,
                                                  int64& OutRequestId, FBeamOperationHandle OpHandle) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UPutScoreRequest, UCommonResponse, FOnPutScoreSuccess, FOnPutScoreError, FOnPutScoreComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
	
	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);
}

void UBeamEventPlayersApi::CPP_PutScoreImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UPutScoreRequest* RequestData, const FOnPutScoreFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UPutScoreRequest, UCommonResponse>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);

	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);
}






void UBeamEventPlayersApi::CPP_GetEventPlayers(UGetEventPlayersRequest* Request, const FOnGetEventPlayersFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UGetEventPlayersRequest::StaticClass()->GetName(), RetryConfig);
	
    int64 OutRequestId;
	CPP_GetEventPlayersImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler, OutRequestId, OpHandle);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, FUserSlot(), None};
}

		
void UBeamEventPlayersApi::CPP_PostClaim(UObjectEventPlayersPostClaimRequest* Request, const FOnObjectEventPlayersPostClaimFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UObjectEventPlayersPostClaimRequest::StaticClass()->GetName(), RetryConfig);
	
    int64 OutRequestId;
	CPP_PostClaimImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler, OutRequestId, OpHandle);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, FUserSlot(), None};
}

		
void UBeamEventPlayersApi::CPP_PutScore(UPutScoreRequest* Request, const FOnPutScoreFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UPutScoreRequest::StaticClass()->GetName(), RetryConfig);
	
    int64 OutRequestId;
	CPP_PutScoreImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler, OutRequestId, OpHandle);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, FUserSlot(), None};
}






void UBeamEventPlayersApi::GetEventPlayers(UGetEventPlayersRequest* Request, const FOnGetEventPlayersSuccess& OnSuccess, const FOnGetEventPlayersError& OnError, const FOnGetEventPlayersComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UGetEventPlayersRequest::StaticClass()->GetName(), RetryConfig);	
	
	int64 OutRequestId = 0;
	BP_GetEventPlayersImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, FUserSlot(), None};
}

		
void UBeamEventPlayersApi::PostClaim(UObjectEventPlayersPostClaimRequest* Request, const FOnObjectEventPlayersPostClaimSuccess& OnSuccess, const FOnObjectEventPlayersPostClaimError& OnError, const FOnObjectEventPlayersPostClaimComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UObjectEventPlayersPostClaimRequest::StaticClass()->GetName(), RetryConfig);	
	
	int64 OutRequestId = 0;
	BP_PostClaimImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, FUserSlot(), None};
}

		
void UBeamEventPlayersApi::PutScore(UPutScoreRequest* Request, const FOnPutScoreSuccess& OnSuccess, const FOnPutScoreError& OnError, const FOnPutScoreComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UPutScoreRequest::StaticClass()->GetName(), RetryConfig);	
	
	int64 OutRequestId = 0;
	BP_PutScoreImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, FUserSlot(), None};
}


	


void UBeamEventPlayersApi::GetEventPlayersWithRetry(const FBeamRetryConfig& RetryConfig, UGetEventPlayersRequest* Request, const FOnGetEventPlayersSuccess& OnSuccess, const FOnGetEventPlayersError& OnError, const FOnGetEventPlayersComplete& OnComplete, FBeamRequestContext& OutRequestContext)
{
	int64 OutRequestId = 0;
	BP_GetEventPlayersImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, FUserSlot(), None}; 
}

		
void UBeamEventPlayersApi::PostClaimWithRetry(const FBeamRetryConfig& RetryConfig, UObjectEventPlayersPostClaimRequest* Request, const FOnObjectEventPlayersPostClaimSuccess& OnSuccess, const FOnObjectEventPlayersPostClaimError& OnError, const FOnObjectEventPlayersPostClaimComplete& OnComplete, FBeamRequestContext& OutRequestContext)
{
	int64 OutRequestId = 0;
	BP_PostClaimImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, FUserSlot(), None}; 
}

		
void UBeamEventPlayersApi::PutScoreWithRetry(const FBeamRetryConfig& RetryConfig, UPutScoreRequest* Request, const FOnPutScoreSuccess& OnSuccess, const FOnPutScoreError& OnError, const FOnPutScoreComplete& OnComplete, FBeamRequestContext& OutRequestContext)
{
	int64 OutRequestId = 0;
	BP_PutScoreImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, FUserSlot(), None}; 
}




