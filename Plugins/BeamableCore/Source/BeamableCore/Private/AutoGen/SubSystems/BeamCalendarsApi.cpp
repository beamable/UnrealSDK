
#include "AutoGen/SubSystems/BeamCalendarsApi.h"

void UBeamCalendarsApi::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Backend = Cast<UBeamBackend>(Collection.InitializeDependency(UBeamBackend::StaticClass()));
}

void UBeamCalendarsApi::Deinitialize()
{
	Super::Deinitialize();
}


void UBeamCalendarsApi::BP_PostClaimImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UObjectCalendarsPostClaimRequest* RequestData,
                                                  const FOnObjectCalendarsPostClaimSuccess& OnSuccess, const FOnObjectCalendarsPostClaimError& OnError, const FOnObjectCalendarsPostClaimComplete& OnComplete,
                                                  int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UObjectCalendarsPostClaimRequest, UCommonResponse, FOnObjectCalendarsPostClaimSuccess, FOnObjectCalendarsPostClaimError, FOnObjectCalendarsPostClaimComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamCalendarsApi::CPP_PostClaimImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UObjectCalendarsPostClaimRequest* RequestData, const FOnObjectCalendarsPostClaimFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UObjectCalendarsPostClaimRequest, UCommonResponse>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamCalendarsApi::BP_GetCalendarsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetCalendarsRequest* RequestData,
                                                  const FOnGetCalendarsSuccess& OnSuccess, const FOnGetCalendarsError& OnError, const FOnGetCalendarsComplete& OnComplete,
                                                  int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UGetCalendarsRequest, UCalendarQueryResponse, FOnGetCalendarsSuccess, FOnGetCalendarsError, FOnGetCalendarsComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamCalendarsApi::CPP_GetCalendarsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UGetCalendarsRequest* RequestData, const FOnGetCalendarsFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UGetCalendarsRequest, UCalendarQueryResponse>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}






void UBeamCalendarsApi::CPP_PostClaim(UObjectCalendarsPostClaimRequest* Request, const FOnObjectCalendarsPostClaimFullResponse& Handler) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UObjectCalendarsPostClaimRequest::StaticClass()->GetName(), RetryConfig);
	CPP_PostClaimImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamCalendarsApi::CPP_GetCalendars(UGetCalendarsRequest* Request, const FOnGetCalendarsFullResponse& Handler) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UGetCalendarsRequest::StaticClass()->GetName(), RetryConfig);
	CPP_GetCalendarsImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler);
}






void UBeamCalendarsApi::PostClaim(UObjectCalendarsPostClaimRequest* Request, const FOnObjectCalendarsPostClaimSuccess& OnSuccess, const FOnObjectCalendarsPostClaimError& OnError, const FOnObjectCalendarsPostClaimComplete& OnComplete, FBeamRequestContext& OutRequestContext)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UObjectCalendarsPostClaimRequest::StaticClass()->GetName(), RetryConfig);	
	
	int64 OutRequestId = 0;
	BP_PostClaimImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, Backend->UnauthenticatedRequestsTargetRealm, -1, FUserSlot(), None};
}

		
void UBeamCalendarsApi::GetCalendars(UGetCalendarsRequest* Request, const FOnGetCalendarsSuccess& OnSuccess, const FOnGetCalendarsError& OnError, const FOnGetCalendarsComplete& OnComplete, FBeamRequestContext& OutRequestContext)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UGetCalendarsRequest::StaticClass()->GetName(), RetryConfig);	
	
	int64 OutRequestId = 0;
	BP_GetCalendarsImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, Backend->UnauthenticatedRequestsTargetRealm, -1, FUserSlot(), None};
}


	


void UBeamCalendarsApi::PostClaimWithRetry(const FBeamRetryConfig& RetryConfig, UObjectCalendarsPostClaimRequest* Request, const FOnObjectCalendarsPostClaimSuccess& OnSuccess, const FOnObjectCalendarsPostClaimError& OnError, const FOnObjectCalendarsPostClaimComplete& OnComplete, FBeamRequestContext& OutRequestContext)
{
	int64 OutRequestId = 0;
	BP_PostClaimImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, Backend->UnauthenticatedRequestsTargetRealm, -1, FUserSlot(), None}; 
}

		
void UBeamCalendarsApi::GetCalendarsWithRetry(const FBeamRetryConfig& RetryConfig, UGetCalendarsRequest* Request, const FOnGetCalendarsSuccess& OnSuccess, const FOnGetCalendarsError& OnError, const FOnGetCalendarsComplete& OnComplete, FBeamRequestContext& OutRequestContext)
{
	int64 OutRequestId = 0;
	BP_GetCalendarsImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, Backend->UnauthenticatedRequestsTargetRealm, -1, FUserSlot(), None}; 
}




