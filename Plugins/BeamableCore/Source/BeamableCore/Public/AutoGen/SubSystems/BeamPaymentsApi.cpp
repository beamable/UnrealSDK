
#include "AutoGen/SubSystems/BeamPaymentsApi.h"

void UBeamPaymentsApi::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Backend = Cast<UBeamBackend>(Collection.InitializeDependency(UBeamBackend::StaticClass()));
}

void UBeamPaymentsApi::Deinitialize()
{
	Super::Deinitialize();
}


void UBeamPaymentsApi::BP_PostWindowsPurchaseTrackImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostWindowsPurchaseTrackRequest* RequestData,
                                                  const FOnPostWindowsPurchaseTrackSuccess& OnSuccess, const FOnPostWindowsPurchaseTrackError& OnError, const FOnPostWindowsPurchaseTrackComplete& OnComplete,
                                                  int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UPostWindowsPurchaseTrackRequest, UPaymentResultResponse, FOnPostWindowsPurchaseTrackSuccess, FOnPostWindowsPurchaseTrackError, FOnPostWindowsPurchaseTrackComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig,TargetRealm, -1, FUserSlot(""), None};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamPaymentsApi::CPP_PostWindowsPurchaseTrackImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UPostWindowsPurchaseTrackRequest* RequestData, const FOnPostWindowsPurchaseTrackFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UPostWindowsPurchaseTrackRequest, UPaymentResultResponse>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamPaymentsApi::BP_GetAuditsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetAuditsRequest* RequestData,
                                                  const FOnGetAuditsSuccess& OnSuccess, const FOnGetAuditsError& OnError, const FOnGetAuditsComplete& OnComplete,
                                                  int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UGetAuditsRequest, UListAuditResponse, FOnGetAuditsSuccess, FOnGetAuditsError, FOnGetAuditsComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig,TargetRealm, -1, FUserSlot(""), None};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamPaymentsApi::CPP_GetAuditsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UGetAuditsRequest* RequestData, const FOnGetAuditsFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UGetAuditsRequest, UListAuditResponse>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamPaymentsApi::BP_PostWindowsPurchaseCompleteImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostWindowsPurchaseCompleteRequest* RequestData,
                                                  const FOnPostWindowsPurchaseCompleteSuccess& OnSuccess, const FOnPostWindowsPurchaseCompleteError& OnError, const FOnPostWindowsPurchaseCompleteComplete& OnComplete,
                                                  int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UPostWindowsPurchaseCompleteRequest, UPaymentResultResponse, FOnPostWindowsPurchaseCompleteSuccess, FOnPostWindowsPurchaseCompleteError, FOnPostWindowsPurchaseCompleteComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig,TargetRealm, -1, FUserSlot(""), None};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamPaymentsApi::CPP_PostWindowsPurchaseCompleteImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UPostWindowsPurchaseCompleteRequest* RequestData, const FOnPostWindowsPurchaseCompleteFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UPostWindowsPurchaseCompleteRequest, UPaymentResultResponse>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamPaymentsApi::BP_GetFacebookUpdateImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetFacebookUpdateRequest* RequestData,
                                                  const FOnGetFacebookUpdateSuccess& OnSuccess, const FOnGetFacebookUpdateError& OnError, const FOnGetFacebookUpdateComplete& OnComplete,
                                                  int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UGetFacebookUpdateRequest, USubscriptionVerificationResponse, FOnGetFacebookUpdateSuccess, FOnGetFacebookUpdateError, FOnGetFacebookUpdateComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig,TargetRealm, -1, FUserSlot(""), None};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamPaymentsApi::CPP_GetFacebookUpdateImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UGetFacebookUpdateRequest* RequestData, const FOnGetFacebookUpdateFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UGetFacebookUpdateRequest, USubscriptionVerificationResponse>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamPaymentsApi::BP_PostFacebookUpdateImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostFacebookUpdateRequest* RequestData,
                                                  const FOnPostFacebookUpdateSuccess& OnSuccess, const FOnPostFacebookUpdateError& OnError, const FOnPostFacebookUpdateComplete& OnComplete,
                                                  int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UPostFacebookUpdateRequest, UFacebookPaymentUpdateResponse, FOnPostFacebookUpdateSuccess, FOnPostFacebookUpdateError, FOnPostFacebookUpdateComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig,TargetRealm, -1, FUserSlot(""), None};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamPaymentsApi::CPP_PostFacebookUpdateImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UPostFacebookUpdateRequest* RequestData, const FOnPostFacebookUpdateFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UPostFacebookUpdateRequest, UFacebookPaymentUpdateResponse>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamPaymentsApi::BP_PostFacebookPurchaseCompleteImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostFacebookPurchaseCompleteRequest* RequestData,
                                                  const FOnPostFacebookPurchaseCompleteSuccess& OnSuccess, const FOnPostFacebookPurchaseCompleteError& OnError, const FOnPostFacebookPurchaseCompleteComplete& OnComplete,
                                                  int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UPostFacebookPurchaseCompleteRequest, UPaymentResultResponse, FOnPostFacebookPurchaseCompleteSuccess, FOnPostFacebookPurchaseCompleteError, FOnPostFacebookPurchaseCompleteComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig,TargetRealm, -1, FUserSlot(""), None};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamPaymentsApi::CPP_PostFacebookPurchaseCompleteImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UPostFacebookPurchaseCompleteRequest* RequestData, const FOnPostFacebookPurchaseCompleteFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UPostFacebookPurchaseCompleteRequest, UPaymentResultResponse>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamPaymentsApi::BP_PostTestPurchaseCompleteImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostTestPurchaseCompleteRequest* RequestData,
                                                  const FOnPostTestPurchaseCompleteSuccess& OnSuccess, const FOnPostTestPurchaseCompleteError& OnError, const FOnPostTestPurchaseCompleteComplete& OnComplete,
                                                  int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UPostTestPurchaseCompleteRequest, UPaymentResultResponse, FOnPostTestPurchaseCompleteSuccess, FOnPostTestPurchaseCompleteError, FOnPostTestPurchaseCompleteComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig,TargetRealm, -1, FUserSlot(""), None};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamPaymentsApi::CPP_PostTestPurchaseCompleteImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UPostTestPurchaseCompleteRequest* RequestData, const FOnPostTestPurchaseCompleteFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UPostTestPurchaseCompleteRequest, UPaymentResultResponse>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamPaymentsApi::BP_GetItunesProductImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetItunesProductRequest* RequestData,
                                                  const FOnGetItunesProductSuccess& OnSuccess, const FOnGetItunesProductError& OnError, const FOnGetItunesProductComplete& OnComplete,
                                                  int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UGetItunesProductRequest, UGetProductResponse, FOnGetItunesProductSuccess, FOnGetItunesProductError, FOnGetItunesProductComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig,TargetRealm, -1, FUserSlot(""), None};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamPaymentsApi::CPP_GetItunesProductImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UGetItunesProductRequest* RequestData, const FOnGetItunesProductFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UGetItunesProductRequest, UGetProductResponse>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamPaymentsApi::BP_PostGoogleplayPurchaseCompleteImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostGoogleplayPurchaseCompleteRequest* RequestData,
                                                  const FOnPostGoogleplayPurchaseCompleteSuccess& OnSuccess, const FOnPostGoogleplayPurchaseCompleteError& OnError, const FOnPostGoogleplayPurchaseCompleteComplete& OnComplete,
                                                  int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UPostGoogleplayPurchaseCompleteRequest, UPaymentResultResponse, FOnPostGoogleplayPurchaseCompleteSuccess, FOnPostGoogleplayPurchaseCompleteError, FOnPostGoogleplayPurchaseCompleteComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig,TargetRealm, -1, FUserSlot(""), None};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamPaymentsApi::CPP_PostGoogleplayPurchaseCompleteImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UPostGoogleplayPurchaseCompleteRequest* RequestData, const FOnPostGoogleplayPurchaseCompleteFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UPostGoogleplayPurchaseCompleteRequest, UPaymentResultResponse>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamPaymentsApi::BP_PostTestPurchaseTrackImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostTestPurchaseTrackRequest* RequestData,
                                                  const FOnPostTestPurchaseTrackSuccess& OnSuccess, const FOnPostTestPurchaseTrackError& OnError, const FOnPostTestPurchaseTrackComplete& OnComplete,
                                                  int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UPostTestPurchaseTrackRequest, UPaymentResultResponse, FOnPostTestPurchaseTrackSuccess, FOnPostTestPurchaseTrackError, FOnPostTestPurchaseTrackComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig,TargetRealm, -1, FUserSlot(""), None};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamPaymentsApi::CPP_PostTestPurchaseTrackImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UPostTestPurchaseTrackRequest* RequestData, const FOnPostTestPurchaseTrackFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UPostTestPurchaseTrackRequest, UPaymentResultResponse>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamPaymentsApi::BP_PostGoogleplayPurchaseVerifyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostGoogleplayPurchaseVerifyRequest* RequestData,
                                                  const FOnPostGoogleplayPurchaseVerifySuccess& OnSuccess, const FOnPostGoogleplayPurchaseVerifyError& OnError, const FOnPostGoogleplayPurchaseVerifyComplete& OnComplete,
                                                  int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UPostGoogleplayPurchaseVerifyRequest, UPaymentResultResponse, FOnPostGoogleplayPurchaseVerifySuccess, FOnPostGoogleplayPurchaseVerifyError, FOnPostGoogleplayPurchaseVerifyComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig,TargetRealm, -1, FUserSlot(""), None};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamPaymentsApi::CPP_PostGoogleplayPurchaseVerifyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UPostGoogleplayPurchaseVerifyRequest* RequestData, const FOnPostGoogleplayPurchaseVerifyFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UPostGoogleplayPurchaseVerifyRequest, UPaymentResultResponse>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamPaymentsApi::BP_PostCouponPurchaseTrackImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostCouponPurchaseTrackRequest* RequestData,
                                                  const FOnPostCouponPurchaseTrackSuccess& OnSuccess, const FOnPostCouponPurchaseTrackError& OnError, const FOnPostCouponPurchaseTrackComplete& OnComplete,
                                                  int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UPostCouponPurchaseTrackRequest, UPaymentResultResponse, FOnPostCouponPurchaseTrackSuccess, FOnPostCouponPurchaseTrackError, FOnPostCouponPurchaseTrackComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig,TargetRealm, -1, FUserSlot(""), None};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamPaymentsApi::CPP_PostCouponPurchaseTrackImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UPostCouponPurchaseTrackRequest* RequestData, const FOnPostCouponPurchaseTrackFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UPostCouponPurchaseTrackRequest, UPaymentResultResponse>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamPaymentsApi::BP_PostSteamPurchaseCompleteImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostSteamPurchaseCompleteRequest* RequestData,
                                                  const FOnPostSteamPurchaseCompleteSuccess& OnSuccess, const FOnPostSteamPurchaseCompleteError& OnError, const FOnPostSteamPurchaseCompleteComplete& OnComplete,
                                                  int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UPostSteamPurchaseCompleteRequest, UPaymentResultResponse, FOnPostSteamPurchaseCompleteSuccess, FOnPostSteamPurchaseCompleteError, FOnPostSteamPurchaseCompleteComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig,TargetRealm, -1, FUserSlot(""), None};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamPaymentsApi::CPP_PostSteamPurchaseCompleteImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UPostSteamPurchaseCompleteRequest* RequestData, const FOnPostSteamPurchaseCompleteFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UPostSteamPurchaseCompleteRequest, UPaymentResultResponse>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamPaymentsApi::BP_PostFacebookPurchaseTrackImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostFacebookPurchaseTrackRequest* RequestData,
                                                  const FOnPostFacebookPurchaseTrackSuccess& OnSuccess, const FOnPostFacebookPurchaseTrackError& OnError, const FOnPostFacebookPurchaseTrackComplete& OnComplete,
                                                  int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UPostFacebookPurchaseTrackRequest, UPaymentResultResponse, FOnPostFacebookPurchaseTrackSuccess, FOnPostFacebookPurchaseTrackError, FOnPostFacebookPurchaseTrackComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig,TargetRealm, -1, FUserSlot(""), None};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamPaymentsApi::CPP_PostFacebookPurchaseTrackImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UPostFacebookPurchaseTrackRequest* RequestData, const FOnPostFacebookPurchaseTrackFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UPostFacebookPurchaseTrackRequest, UPaymentResultResponse>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamPaymentsApi::BP_PostTestPurchaseVerifyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostTestPurchaseVerifyRequest* RequestData,
                                                  const FOnPostTestPurchaseVerifySuccess& OnSuccess, const FOnPostTestPurchaseVerifyError& OnError, const FOnPostTestPurchaseVerifyComplete& OnComplete,
                                                  int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UPostTestPurchaseVerifyRequest, UPaymentResultResponse, FOnPostTestPurchaseVerifySuccess, FOnPostTestPurchaseVerifyError, FOnPostTestPurchaseVerifyComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig,TargetRealm, -1, FUserSlot(""), None};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamPaymentsApi::CPP_PostTestPurchaseVerifyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UPostTestPurchaseVerifyRequest* RequestData, const FOnPostTestPurchaseVerifyFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UPostTestPurchaseVerifyRequest, UPaymentResultResponse>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamPaymentsApi::BP_PostGoogleplayPurchaseTrackImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostGoogleplayPurchaseTrackRequest* RequestData,
                                                  const FOnPostGoogleplayPurchaseTrackSuccess& OnSuccess, const FOnPostGoogleplayPurchaseTrackError& OnError, const FOnPostGoogleplayPurchaseTrackComplete& OnComplete,
                                                  int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UPostGoogleplayPurchaseTrackRequest, UPaymentResultResponse, FOnPostGoogleplayPurchaseTrackSuccess, FOnPostGoogleplayPurchaseTrackError, FOnPostGoogleplayPurchaseTrackComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig,TargetRealm, -1, FUserSlot(""), None};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamPaymentsApi::CPP_PostGoogleplayPurchaseTrackImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UPostGoogleplayPurchaseTrackRequest* RequestData, const FOnPostGoogleplayPurchaseTrackFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UPostGoogleplayPurchaseTrackRequest, UPaymentResultResponse>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamPaymentsApi::BP_GetSteamPricesImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetSteamPricesRequest* RequestData,
                                                  const FOnGetSteamPricesSuccess& OnSuccess, const FOnGetSteamPricesError& OnError, const FOnGetSteamPricesComplete& OnComplete,
                                                  int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UGetSteamPricesRequest, ULocalizedPriceMap, FOnGetSteamPricesSuccess, FOnGetSteamPricesError, FOnGetSteamPricesComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig,TargetRealm, -1, FUserSlot(""), None};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamPaymentsApi::CPP_GetSteamPricesImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UGetSteamPricesRequest* RequestData, const FOnGetSteamPricesFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UGetSteamPricesRequest, ULocalizedPriceMap>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamPaymentsApi::BP_PostWindowsPurchaseVerifyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostWindowsPurchaseVerifyRequest* RequestData,
                                                  const FOnPostWindowsPurchaseVerifySuccess& OnSuccess, const FOnPostWindowsPurchaseVerifyError& OnError, const FOnPostWindowsPurchaseVerifyComplete& OnComplete,
                                                  int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UPostWindowsPurchaseVerifyRequest, UPaymentResultResponse, FOnPostWindowsPurchaseVerifySuccess, FOnPostWindowsPurchaseVerifyError, FOnPostWindowsPurchaseVerifyComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig,TargetRealm, -1, FUserSlot(""), None};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamPaymentsApi::CPP_PostWindowsPurchaseVerifyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UPostWindowsPurchaseVerifyRequest* RequestData, const FOnPostWindowsPurchaseVerifyFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UPostWindowsPurchaseVerifyRequest, UPaymentResultResponse>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamPaymentsApi::BP_PostItunesPurchaseVerifyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostItunesPurchaseVerifyRequest* RequestData,
                                                  const FOnPostItunesPurchaseVerifySuccess& OnSuccess, const FOnPostItunesPurchaseVerifyError& OnError, const FOnPostItunesPurchaseVerifyComplete& OnComplete,
                                                  int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UPostItunesPurchaseVerifyRequest, UPaymentResultResponse, FOnPostItunesPurchaseVerifySuccess, FOnPostItunesPurchaseVerifyError, FOnPostItunesPurchaseVerifyComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig,TargetRealm, -1, FUserSlot(""), None};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamPaymentsApi::CPP_PostItunesPurchaseVerifyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UPostItunesPurchaseVerifyRequest* RequestData, const FOnPostItunesPurchaseVerifyFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UPostItunesPurchaseVerifyRequest, UPaymentResultResponse>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamPaymentsApi::BP_PostItunesPurchaseCompleteImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostItunesPurchaseCompleteRequest* RequestData,
                                                  const FOnPostItunesPurchaseCompleteSuccess& OnSuccess, const FOnPostItunesPurchaseCompleteError& OnError, const FOnPostItunesPurchaseCompleteComplete& OnComplete,
                                                  int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UPostItunesPurchaseCompleteRequest, UPaymentResultResponse, FOnPostItunesPurchaseCompleteSuccess, FOnPostItunesPurchaseCompleteError, FOnPostItunesPurchaseCompleteComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig,TargetRealm, -1, FUserSlot(""), None};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamPaymentsApi::CPP_PostItunesPurchaseCompleteImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UPostItunesPurchaseCompleteRequest* RequestData, const FOnPostItunesPurchaseCompleteFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UPostItunesPurchaseCompleteRequest, UPaymentResultResponse>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamPaymentsApi::BP_PostFacebookPurchaseVerifyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostFacebookPurchaseVerifyRequest* RequestData,
                                                  const FOnPostFacebookPurchaseVerifySuccess& OnSuccess, const FOnPostFacebookPurchaseVerifyError& OnError, const FOnPostFacebookPurchaseVerifyComplete& OnComplete,
                                                  int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UPostFacebookPurchaseVerifyRequest, UPaymentResultResponse, FOnPostFacebookPurchaseVerifySuccess, FOnPostFacebookPurchaseVerifyError, FOnPostFacebookPurchaseVerifyComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig,TargetRealm, -1, FUserSlot(""), None};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamPaymentsApi::CPP_PostFacebookPurchaseVerifyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UPostFacebookPurchaseVerifyRequest* RequestData, const FOnPostFacebookPurchaseVerifyFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UPostFacebookPurchaseVerifyRequest, UPaymentResultResponse>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamPaymentsApi::BP_PostSteamPurchaseTrackImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostSteamPurchaseTrackRequest* RequestData,
                                                  const FOnPostSteamPurchaseTrackSuccess& OnSuccess, const FOnPostSteamPurchaseTrackError& OnError, const FOnPostSteamPurchaseTrackComplete& OnComplete,
                                                  int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UPostSteamPurchaseTrackRequest, UPaymentResultResponse, FOnPostSteamPurchaseTrackSuccess, FOnPostSteamPurchaseTrackError, FOnPostSteamPurchaseTrackComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig,TargetRealm, -1, FUserSlot(""), None};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamPaymentsApi::CPP_PostSteamPurchaseTrackImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UPostSteamPurchaseTrackRequest* RequestData, const FOnPostSteamPurchaseTrackFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UPostSteamPurchaseTrackRequest, UPaymentResultResponse>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamPaymentsApi::BP_PostCouponPurchaseVerifyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostCouponPurchaseVerifyRequest* RequestData,
                                                  const FOnPostCouponPurchaseVerifySuccess& OnSuccess, const FOnPostCouponPurchaseVerifyError& OnError, const FOnPostCouponPurchaseVerifyComplete& OnComplete,
                                                  int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UPostCouponPurchaseVerifyRequest, UPaymentResultResponse, FOnPostCouponPurchaseVerifySuccess, FOnPostCouponPurchaseVerifyError, FOnPostCouponPurchaseVerifyComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig,TargetRealm, -1, FUserSlot(""), None};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamPaymentsApi::CPP_PostCouponPurchaseVerifyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UPostCouponPurchaseVerifyRequest* RequestData, const FOnPostCouponPurchaseVerifyFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UPostCouponPurchaseVerifyRequest, UPaymentResultResponse>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamPaymentsApi::BP_GetWindowsProductImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetWindowsProductRequest* RequestData,
                                                  const FOnGetWindowsProductSuccess& OnSuccess, const FOnGetWindowsProductError& OnError, const FOnGetWindowsProductComplete& OnComplete,
                                                  int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UGetWindowsProductRequest, UGetProductResponse, FOnGetWindowsProductSuccess, FOnGetWindowsProductError, FOnGetWindowsProductComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig,TargetRealm, -1, FUserSlot(""), None};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamPaymentsApi::CPP_GetWindowsProductImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UGetWindowsProductRequest* RequestData, const FOnGetWindowsProductFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UGetWindowsProductRequest, UGetProductResponse>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamPaymentsApi::BP_GetFacebookProductImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetFacebookProductRequest* RequestData,
                                                  const FOnGetFacebookProductSuccess& OnSuccess, const FOnGetFacebookProductError& OnError, const FOnGetFacebookProductComplete& OnComplete,
                                                  int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UGetFacebookProductRequest, UGetProductResponse, FOnGetFacebookProductSuccess, FOnGetFacebookProductError, FOnGetFacebookProductComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig,TargetRealm, -1, FUserSlot(""), None};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamPaymentsApi::CPP_GetFacebookProductImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UGetFacebookProductRequest* RequestData, const FOnGetFacebookProductFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UGetFacebookProductRequest, UGetProductResponse>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamPaymentsApi::BP_GetCouponProductImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetCouponProductRequest* RequestData,
                                                  const FOnGetCouponProductSuccess& OnSuccess, const FOnGetCouponProductError& OnError, const FOnGetCouponProductComplete& OnComplete,
                                                  int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UGetCouponProductRequest, UGetProductResponse, FOnGetCouponProductSuccess, FOnGetCouponProductError, FOnGetCouponProductComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig,TargetRealm, -1, FUserSlot(""), None};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamPaymentsApi::CPP_GetCouponProductImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UGetCouponProductRequest* RequestData, const FOnGetCouponProductFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UGetCouponProductRequest, UGetProductResponse>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamPaymentsApi::BP_GetSteamProductsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetSteamProductsRequest* RequestData,
                                                  const FOnGetSteamProductsSuccess& OnSuccess, const FOnGetSteamProductsError& OnError, const FOnGetSteamProductsComplete& OnComplete,
                                                  int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UGetSteamProductsRequest, UGetProductsResponse, FOnGetSteamProductsSuccess, FOnGetSteamProductsError, FOnGetSteamProductsComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig,TargetRealm, -1, FUserSlot(""), None};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamPaymentsApi::CPP_GetSteamProductsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UGetSteamProductsRequest* RequestData, const FOnGetSteamProductsFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UGetSteamProductsRequest, UGetProductsResponse>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamPaymentsApi::BP_PostSteamAuthImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostSteamAuthRequest* RequestData,
                                                  const FOnPostSteamAuthSuccess& OnSuccess, const FOnPostSteamAuthError& OnError, const FOnPostSteamAuthComplete& OnComplete,
                                                  int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UPostSteamAuthRequest, UEmptyResponse, FOnPostSteamAuthSuccess, FOnPostSteamAuthError, FOnPostSteamAuthComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig,TargetRealm, -1, FUserSlot(""), None};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamPaymentsApi::CPP_PostSteamAuthImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UPostSteamAuthRequest* RequestData, const FOnPostSteamAuthFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UPostSteamAuthRequest, UEmptyResponse>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamPaymentsApi::BP_GetSteamProductImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetSteamProductRequest* RequestData,
                                                  const FOnGetSteamProductSuccess& OnSuccess, const FOnGetSteamProductError& OnError, const FOnGetSteamProductComplete& OnComplete,
                                                  int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UGetSteamProductRequest, UGetProductResponse, FOnGetSteamProductSuccess, FOnGetSteamProductError, FOnGetSteamProductComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig,TargetRealm, -1, FUserSlot(""), None};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamPaymentsApi::CPP_GetSteamProductImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UGetSteamProductRequest* RequestData, const FOnGetSteamProductFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UGetSteamProductRequest, UGetProductResponse>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamPaymentsApi::BP_PostCouponPurchaseCompleteImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostCouponPurchaseCompleteRequest* RequestData,
                                                  const FOnPostCouponPurchaseCompleteSuccess& OnSuccess, const FOnPostCouponPurchaseCompleteError& OnError, const FOnPostCouponPurchaseCompleteComplete& OnComplete,
                                                  int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UPostCouponPurchaseCompleteRequest, UPaymentResultResponse, FOnPostCouponPurchaseCompleteSuccess, FOnPostCouponPurchaseCompleteError, FOnPostCouponPurchaseCompleteComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig,TargetRealm, -1, FUserSlot(""), None};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamPaymentsApi::CPP_PostCouponPurchaseCompleteImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UPostCouponPurchaseCompleteRequest* RequestData, const FOnPostCouponPurchaseCompleteFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UPostCouponPurchaseCompleteRequest, UPaymentResultResponse>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamPaymentsApi::BP_GetGoogleplayProductImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetGoogleplayProductRequest* RequestData,
                                                  const FOnGetGoogleplayProductSuccess& OnSuccess, const FOnGetGoogleplayProductError& OnError, const FOnGetGoogleplayProductComplete& OnComplete,
                                                  int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UGetGoogleplayProductRequest, UGetProductResponse, FOnGetGoogleplayProductSuccess, FOnGetGoogleplayProductError, FOnGetGoogleplayProductComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig,TargetRealm, -1, FUserSlot(""), None};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamPaymentsApi::CPP_GetGoogleplayProductImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UGetGoogleplayProductRequest* RequestData, const FOnGetGoogleplayProductFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UGetGoogleplayProductRequest, UGetProductResponse>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamPaymentsApi::BP_GetTestProductImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetTestProductRequest* RequestData,
                                                  const FOnGetTestProductSuccess& OnSuccess, const FOnGetTestProductError& OnError, const FOnGetTestProductComplete& OnComplete,
                                                  int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UGetTestProductRequest, UGetProductResponse, FOnGetTestProductSuccess, FOnGetTestProductError, FOnGetTestProductComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig,TargetRealm, -1, FUserSlot(""), None};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamPaymentsApi::CPP_GetTestProductImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UGetTestProductRequest* RequestData, const FOnGetTestProductFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UGetTestProductRequest, UGetProductResponse>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamPaymentsApi::BP_PostSteamPurchaseVerifyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostSteamPurchaseVerifyRequest* RequestData,
                                                  const FOnPostSteamPurchaseVerifySuccess& OnSuccess, const FOnPostSteamPurchaseVerifyError& OnError, const FOnPostSteamPurchaseVerifyComplete& OnComplete,
                                                  int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UPostSteamPurchaseVerifyRequest, UPaymentResultResponse, FOnPostSteamPurchaseVerifySuccess, FOnPostSteamPurchaseVerifyError, FOnPostSteamPurchaseVerifyComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig,TargetRealm, -1, FUserSlot(""), None};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamPaymentsApi::CPP_PostSteamPurchaseVerifyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UPostSteamPurchaseVerifyRequest* RequestData, const FOnPostSteamPurchaseVerifyFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UPostSteamPurchaseVerifyRequest, UPaymentResultResponse>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamPaymentsApi::BP_PostItunesPurchaseTrackImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostItunesPurchaseTrackRequest* RequestData,
                                                  const FOnPostItunesPurchaseTrackSuccess& OnSuccess, const FOnPostItunesPurchaseTrackError& OnError, const FOnPostItunesPurchaseTrackComplete& OnComplete,
                                                  int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UPostItunesPurchaseTrackRequest, UPaymentResultResponse, FOnPostItunesPurchaseTrackSuccess, FOnPostItunesPurchaseTrackError, FOnPostItunesPurchaseTrackComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig,TargetRealm, -1, FUserSlot(""), None};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamPaymentsApi::CPP_PostItunesPurchaseTrackImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UPostItunesPurchaseTrackRequest* RequestData, const FOnPostItunesPurchaseTrackFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UPostItunesPurchaseTrackRequest, UPaymentResultResponse>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamPaymentsApi::BP_GetPaymentsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetPaymentsRequest* RequestData,
                                                  const FOnGetPaymentsSuccess& OnSuccess, const FOnGetPaymentsError& OnError, const FOnGetPaymentsComplete& OnComplete,
                                                  int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UGetPaymentsRequest, UCommonResponse, FOnGetPaymentsSuccess, FOnGetPaymentsError, FOnGetPaymentsComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig,TargetRealm, -1, FUserSlot(""), None};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamPaymentsApi::CPP_GetPaymentsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UGetPaymentsRequest* RequestData, const FOnGetPaymentsFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UGetPaymentsRequest, UCommonResponse>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}



void UBeamPaymentsApi::BP_PostTestPurchaseBeginImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UPostTestPurchaseBeginRequest* RequestData, const FOnPostTestPurchaseBeginSuccess& OnSuccess, const FOnPostTestPurchaseBeginError& OnError, const FOnPostTestPurchaseBeginComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPostTestPurchaseBeginRequest, UBeginPurchaseResponse, FOnPostTestPurchaseBeginSuccess, FOnPostTestPurchaseBeginError, FOnPostTestPurchaseBeginComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamPaymentsApi::CPP_PostTestPurchaseBeginImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UPostTestPurchaseBeginRequest* RequestData, const FOnPostTestPurchaseBeginFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPostTestPurchaseBeginRequest, UBeginPurchaseResponse>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamPaymentsApi::BP_PostSteamPurchaseFailImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UPostSteamPurchaseFailRequest* RequestData, const FOnPostSteamPurchaseFailSuccess& OnSuccess, const FOnPostSteamPurchaseFailError& OnError, const FOnPostSteamPurchaseFailComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPostSteamPurchaseFailRequest, UPaymentResultResponse, FOnPostSteamPurchaseFailSuccess, FOnPostSteamPurchaseFailError, FOnPostSteamPurchaseFailComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamPaymentsApi::CPP_PostSteamPurchaseFailImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UPostSteamPurchaseFailRequest* RequestData, const FOnPostSteamPurchaseFailFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPostSteamPurchaseFailRequest, UPaymentResultResponse>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamPaymentsApi::BP_PostFacebookPurchaseFailImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UPostFacebookPurchaseFailRequest* RequestData, const FOnPostFacebookPurchaseFailSuccess& OnSuccess, const FOnPostFacebookPurchaseFailError& OnError, const FOnPostFacebookPurchaseFailComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPostFacebookPurchaseFailRequest, UPaymentResultResponse, FOnPostFacebookPurchaseFailSuccess, FOnPostFacebookPurchaseFailError, FOnPostFacebookPurchaseFailComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamPaymentsApi::CPP_PostFacebookPurchaseFailImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UPostFacebookPurchaseFailRequest* RequestData, const FOnPostFacebookPurchaseFailFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPostFacebookPurchaseFailRequest, UPaymentResultResponse>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamPaymentsApi::BP_PostGoogleplayPurchaseBeginImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UPostGoogleplayPurchaseBeginRequest* RequestData, const FOnPostGoogleplayPurchaseBeginSuccess& OnSuccess, const FOnPostGoogleplayPurchaseBeginError& OnError, const FOnPostGoogleplayPurchaseBeginComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPostGoogleplayPurchaseBeginRequest, UBeginPurchaseResponse, FOnPostGoogleplayPurchaseBeginSuccess, FOnPostGoogleplayPurchaseBeginError, FOnPostGoogleplayPurchaseBeginComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamPaymentsApi::CPP_PostGoogleplayPurchaseBeginImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UPostGoogleplayPurchaseBeginRequest* RequestData, const FOnPostGoogleplayPurchaseBeginFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPostGoogleplayPurchaseBeginRequest, UBeginPurchaseResponse>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamPaymentsApi::BP_PostItunesPurchaseBeginImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UPostItunesPurchaseBeginRequest* RequestData, const FOnPostItunesPurchaseBeginSuccess& OnSuccess, const FOnPostItunesPurchaseBeginError& OnError, const FOnPostItunesPurchaseBeginComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPostItunesPurchaseBeginRequest, UBeginPurchaseResponse, FOnPostItunesPurchaseBeginSuccess, FOnPostItunesPurchaseBeginError, FOnPostItunesPurchaseBeginComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamPaymentsApi::CPP_PostItunesPurchaseBeginImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UPostItunesPurchaseBeginRequest* RequestData, const FOnPostItunesPurchaseBeginFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPostItunesPurchaseBeginRequest, UBeginPurchaseResponse>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamPaymentsApi::BP_PostFacebookPurchaseCancelImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UPostFacebookPurchaseCancelRequest* RequestData, const FOnPostFacebookPurchaseCancelSuccess& OnSuccess, const FOnPostFacebookPurchaseCancelError& OnError, const FOnPostFacebookPurchaseCancelComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPostFacebookPurchaseCancelRequest, UPaymentResultResponse, FOnPostFacebookPurchaseCancelSuccess, FOnPostFacebookPurchaseCancelError, FOnPostFacebookPurchaseCancelComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamPaymentsApi::CPP_PostFacebookPurchaseCancelImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UPostFacebookPurchaseCancelRequest* RequestData, const FOnPostFacebookPurchaseCancelFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPostFacebookPurchaseCancelRequest, UPaymentResultResponse>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamPaymentsApi::BP_PostItunesPurchaseFailImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UPostItunesPurchaseFailRequest* RequestData, const FOnPostItunesPurchaseFailSuccess& OnSuccess, const FOnPostItunesPurchaseFailError& OnError, const FOnPostItunesPurchaseFailComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPostItunesPurchaseFailRequest, UPaymentResultResponse, FOnPostItunesPurchaseFailSuccess, FOnPostItunesPurchaseFailError, FOnPostItunesPurchaseFailComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamPaymentsApi::CPP_PostItunesPurchaseFailImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UPostItunesPurchaseFailRequest* RequestData, const FOnPostItunesPurchaseFailFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPostItunesPurchaseFailRequest, UPaymentResultResponse>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamPaymentsApi::BP_PostTestPurchaseCancelImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UPostTestPurchaseCancelRequest* RequestData, const FOnPostTestPurchaseCancelSuccess& OnSuccess, const FOnPostTestPurchaseCancelError& OnError, const FOnPostTestPurchaseCancelComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPostTestPurchaseCancelRequest, UPaymentResultResponse, FOnPostTestPurchaseCancelSuccess, FOnPostTestPurchaseCancelError, FOnPostTestPurchaseCancelComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamPaymentsApi::CPP_PostTestPurchaseCancelImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UPostTestPurchaseCancelRequest* RequestData, const FOnPostTestPurchaseCancelFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPostTestPurchaseCancelRequest, UPaymentResultResponse>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamPaymentsApi::BP_PostTestPurchaseFailImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UPostTestPurchaseFailRequest* RequestData, const FOnPostTestPurchaseFailSuccess& OnSuccess, const FOnPostTestPurchaseFailError& OnError, const FOnPostTestPurchaseFailComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPostTestPurchaseFailRequest, UPaymentResultResponse, FOnPostTestPurchaseFailSuccess, FOnPostTestPurchaseFailError, FOnPostTestPurchaseFailComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamPaymentsApi::CPP_PostTestPurchaseFailImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UPostTestPurchaseFailRequest* RequestData, const FOnPostTestPurchaseFailFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPostTestPurchaseFailRequest, UPaymentResultResponse>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamPaymentsApi::BP_PostCouponPurchaseCancelImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UPostCouponPurchaseCancelRequest* RequestData, const FOnPostCouponPurchaseCancelSuccess& OnSuccess, const FOnPostCouponPurchaseCancelError& OnError, const FOnPostCouponPurchaseCancelComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPostCouponPurchaseCancelRequest, UPaymentResultResponse, FOnPostCouponPurchaseCancelSuccess, FOnPostCouponPurchaseCancelError, FOnPostCouponPurchaseCancelComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamPaymentsApi::CPP_PostCouponPurchaseCancelImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UPostCouponPurchaseCancelRequest* RequestData, const FOnPostCouponPurchaseCancelFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPostCouponPurchaseCancelRequest, UPaymentResultResponse>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamPaymentsApi::BP_PostCouponPurchaseBeginImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UPostCouponPurchaseBeginRequest* RequestData, const FOnPostCouponPurchaseBeginSuccess& OnSuccess, const FOnPostCouponPurchaseBeginError& OnError, const FOnPostCouponPurchaseBeginComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPostCouponPurchaseBeginRequest, UBeginPurchaseResponse, FOnPostCouponPurchaseBeginSuccess, FOnPostCouponPurchaseBeginError, FOnPostCouponPurchaseBeginComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamPaymentsApi::CPP_PostCouponPurchaseBeginImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UPostCouponPurchaseBeginRequest* RequestData, const FOnPostCouponPurchaseBeginFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPostCouponPurchaseBeginRequest, UBeginPurchaseResponse>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamPaymentsApi::BP_PostFacebookPurchaseBeginImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UPostFacebookPurchaseBeginRequest* RequestData, const FOnPostFacebookPurchaseBeginSuccess& OnSuccess, const FOnPostFacebookPurchaseBeginError& OnError, const FOnPostFacebookPurchaseBeginComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPostFacebookPurchaseBeginRequest, UBeginPurchaseResponse, FOnPostFacebookPurchaseBeginSuccess, FOnPostFacebookPurchaseBeginError, FOnPostFacebookPurchaseBeginComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamPaymentsApi::CPP_PostFacebookPurchaseBeginImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UPostFacebookPurchaseBeginRequest* RequestData, const FOnPostFacebookPurchaseBeginFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPostFacebookPurchaseBeginRequest, UBeginPurchaseResponse>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamPaymentsApi::BP_GetSteamOrderImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UGetSteamOrderRequest* RequestData, const FOnGetSteamOrderSuccess& OnSuccess, const FOnGetSteamOrderError& OnError, const FOnGetSteamOrderComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UGetSteamOrderRequest, USteamOrderInfoResponse, FOnGetSteamOrderSuccess, FOnGetSteamOrderError, FOnGetSteamOrderComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamPaymentsApi::CPP_GetSteamOrderImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UGetSteamOrderRequest* RequestData, const FOnGetSteamOrderFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UGetSteamOrderRequest, USteamOrderInfoResponse>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamPaymentsApi::BP_PostWindowsPurchaseBeginImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UPostWindowsPurchaseBeginRequest* RequestData, const FOnPostWindowsPurchaseBeginSuccess& OnSuccess, const FOnPostWindowsPurchaseBeginError& OnError, const FOnPostWindowsPurchaseBeginComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPostWindowsPurchaseBeginRequest, UBeginPurchaseResponse, FOnPostWindowsPurchaseBeginSuccess, FOnPostWindowsPurchaseBeginError, FOnPostWindowsPurchaseBeginComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamPaymentsApi::CPP_PostWindowsPurchaseBeginImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UPostWindowsPurchaseBeginRequest* RequestData, const FOnPostWindowsPurchaseBeginFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPostWindowsPurchaseBeginRequest, UBeginPurchaseResponse>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamPaymentsApi::BP_PostGoogleplayPurchaseFailImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UPostGoogleplayPurchaseFailRequest* RequestData, const FOnPostGoogleplayPurchaseFailSuccess& OnSuccess, const FOnPostGoogleplayPurchaseFailError& OnError, const FOnPostGoogleplayPurchaseFailComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPostGoogleplayPurchaseFailRequest, UPaymentResultResponse, FOnPostGoogleplayPurchaseFailSuccess, FOnPostGoogleplayPurchaseFailError, FOnPostGoogleplayPurchaseFailComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamPaymentsApi::CPP_PostGoogleplayPurchaseFailImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UPostGoogleplayPurchaseFailRequest* RequestData, const FOnPostGoogleplayPurchaseFailFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPostGoogleplayPurchaseFailRequest, UPaymentResultResponse>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamPaymentsApi::BP_PostGoogleplayPurchaseCancelImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UPostGoogleplayPurchaseCancelRequest* RequestData, const FOnPostGoogleplayPurchaseCancelSuccess& OnSuccess, const FOnPostGoogleplayPurchaseCancelError& OnError, const FOnPostGoogleplayPurchaseCancelComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPostGoogleplayPurchaseCancelRequest, UPaymentResultResponse, FOnPostGoogleplayPurchaseCancelSuccess, FOnPostGoogleplayPurchaseCancelError, FOnPostGoogleplayPurchaseCancelComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamPaymentsApi::CPP_PostGoogleplayPurchaseCancelImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UPostGoogleplayPurchaseCancelRequest* RequestData, const FOnPostGoogleplayPurchaseCancelFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPostGoogleplayPurchaseCancelRequest, UPaymentResultResponse>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamPaymentsApi::BP_PostCouponPurchaseFailImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UPostCouponPurchaseFailRequest* RequestData, const FOnPostCouponPurchaseFailSuccess& OnSuccess, const FOnPostCouponPurchaseFailError& OnError, const FOnPostCouponPurchaseFailComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPostCouponPurchaseFailRequest, UPaymentResultResponse, FOnPostCouponPurchaseFailSuccess, FOnPostCouponPurchaseFailError, FOnPostCouponPurchaseFailComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamPaymentsApi::CPP_PostCouponPurchaseFailImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UPostCouponPurchaseFailRequest* RequestData, const FOnPostCouponPurchaseFailFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPostCouponPurchaseFailRequest, UPaymentResultResponse>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamPaymentsApi::BP_PostSteamPurchaseBeginImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UPostSteamPurchaseBeginRequest* RequestData, const FOnPostSteamPurchaseBeginSuccess& OnSuccess, const FOnPostSteamPurchaseBeginError& OnError, const FOnPostSteamPurchaseBeginComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPostSteamPurchaseBeginRequest, UBeginPurchaseResponse, FOnPostSteamPurchaseBeginSuccess, FOnPostSteamPurchaseBeginError, FOnPostSteamPurchaseBeginComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamPaymentsApi::CPP_PostSteamPurchaseBeginImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UPostSteamPurchaseBeginRequest* RequestData, const FOnPostSteamPurchaseBeginFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPostSteamPurchaseBeginRequest, UBeginPurchaseResponse>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamPaymentsApi::BP_PostSteamPurchaseCancelImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UPostSteamPurchaseCancelRequest* RequestData, const FOnPostSteamPurchaseCancelSuccess& OnSuccess, const FOnPostSteamPurchaseCancelError& OnError, const FOnPostSteamPurchaseCancelComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPostSteamPurchaseCancelRequest, UPaymentResultResponse, FOnPostSteamPurchaseCancelSuccess, FOnPostSteamPurchaseCancelError, FOnPostSteamPurchaseCancelComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamPaymentsApi::CPP_PostSteamPurchaseCancelImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UPostSteamPurchaseCancelRequest* RequestData, const FOnPostSteamPurchaseCancelFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPostSteamPurchaseCancelRequest, UPaymentResultResponse>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamPaymentsApi::BP_PostWindowsPurchaseCancelImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UPostWindowsPurchaseCancelRequest* RequestData, const FOnPostWindowsPurchaseCancelSuccess& OnSuccess, const FOnPostWindowsPurchaseCancelError& OnError, const FOnPostWindowsPurchaseCancelComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPostWindowsPurchaseCancelRequest, UPaymentResultResponse, FOnPostWindowsPurchaseCancelSuccess, FOnPostWindowsPurchaseCancelError, FOnPostWindowsPurchaseCancelComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamPaymentsApi::CPP_PostWindowsPurchaseCancelImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UPostWindowsPurchaseCancelRequest* RequestData, const FOnPostWindowsPurchaseCancelFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPostWindowsPurchaseCancelRequest, UPaymentResultResponse>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamPaymentsApi::BP_PostWindowsPurchaseFailImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UPostWindowsPurchaseFailRequest* RequestData, const FOnPostWindowsPurchaseFailSuccess& OnSuccess, const FOnPostWindowsPurchaseFailError& OnError, const FOnPostWindowsPurchaseFailComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPostWindowsPurchaseFailRequest, UPaymentResultResponse, FOnPostWindowsPurchaseFailSuccess, FOnPostWindowsPurchaseFailError, FOnPostWindowsPurchaseFailComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamPaymentsApi::CPP_PostWindowsPurchaseFailImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UPostWindowsPurchaseFailRequest* RequestData, const FOnPostWindowsPurchaseFailFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPostWindowsPurchaseFailRequest, UPaymentResultResponse>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamPaymentsApi::BP_PostItunesPurchaseCancelImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UPostItunesPurchaseCancelRequest* RequestData, const FOnPostItunesPurchaseCancelSuccess& OnSuccess, const FOnPostItunesPurchaseCancelError& OnError, const FOnPostItunesPurchaseCancelComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPostItunesPurchaseCancelRequest, UPaymentResultResponse, FOnPostItunesPurchaseCancelSuccess, FOnPostItunesPurchaseCancelError, FOnPostItunesPurchaseCancelComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamPaymentsApi::CPP_PostItunesPurchaseCancelImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UPostItunesPurchaseCancelRequest* RequestData, const FOnPostItunesPurchaseCancelFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPostItunesPurchaseCancelRequest, UPaymentResultResponse>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}




void UBeamPaymentsApi::CPP_PostWindowsPurchaseTrack(UPostWindowsPurchaseTrackRequest* Request, const FOnPostWindowsPurchaseTrackFullResponse& Handler) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UPostWindowsPurchaseTrackRequest::StaticClass()->GetName(), RetryConfig);
	CPP_PostWindowsPurchaseTrackImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamPaymentsApi::CPP_GetAudits(UGetAuditsRequest* Request, const FOnGetAuditsFullResponse& Handler) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UGetAuditsRequest::StaticClass()->GetName(), RetryConfig);
	CPP_GetAuditsImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamPaymentsApi::CPP_PostWindowsPurchaseComplete(UPostWindowsPurchaseCompleteRequest* Request, const FOnPostWindowsPurchaseCompleteFullResponse& Handler) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UPostWindowsPurchaseCompleteRequest::StaticClass()->GetName(), RetryConfig);
	CPP_PostWindowsPurchaseCompleteImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamPaymentsApi::CPP_GetFacebookUpdate(UGetFacebookUpdateRequest* Request, const FOnGetFacebookUpdateFullResponse& Handler) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UGetFacebookUpdateRequest::StaticClass()->GetName(), RetryConfig);
	CPP_GetFacebookUpdateImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamPaymentsApi::CPP_PostFacebookUpdate(UPostFacebookUpdateRequest* Request, const FOnPostFacebookUpdateFullResponse& Handler) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UPostFacebookUpdateRequest::StaticClass()->GetName(), RetryConfig);
	CPP_PostFacebookUpdateImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamPaymentsApi::CPP_PostFacebookPurchaseComplete(UPostFacebookPurchaseCompleteRequest* Request, const FOnPostFacebookPurchaseCompleteFullResponse& Handler) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UPostFacebookPurchaseCompleteRequest::StaticClass()->GetName(), RetryConfig);
	CPP_PostFacebookPurchaseCompleteImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamPaymentsApi::CPP_PostTestPurchaseComplete(UPostTestPurchaseCompleteRequest* Request, const FOnPostTestPurchaseCompleteFullResponse& Handler) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UPostTestPurchaseCompleteRequest::StaticClass()->GetName(), RetryConfig);
	CPP_PostTestPurchaseCompleteImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamPaymentsApi::CPP_GetItunesProduct(UGetItunesProductRequest* Request, const FOnGetItunesProductFullResponse& Handler) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UGetItunesProductRequest::StaticClass()->GetName(), RetryConfig);
	CPP_GetItunesProductImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamPaymentsApi::CPP_PostGoogleplayPurchaseComplete(UPostGoogleplayPurchaseCompleteRequest* Request, const FOnPostGoogleplayPurchaseCompleteFullResponse& Handler) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UPostGoogleplayPurchaseCompleteRequest::StaticClass()->GetName(), RetryConfig);
	CPP_PostGoogleplayPurchaseCompleteImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamPaymentsApi::CPP_PostTestPurchaseTrack(UPostTestPurchaseTrackRequest* Request, const FOnPostTestPurchaseTrackFullResponse& Handler) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UPostTestPurchaseTrackRequest::StaticClass()->GetName(), RetryConfig);
	CPP_PostTestPurchaseTrackImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamPaymentsApi::CPP_PostGoogleplayPurchaseVerify(UPostGoogleplayPurchaseVerifyRequest* Request, const FOnPostGoogleplayPurchaseVerifyFullResponse& Handler) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UPostGoogleplayPurchaseVerifyRequest::StaticClass()->GetName(), RetryConfig);
	CPP_PostGoogleplayPurchaseVerifyImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamPaymentsApi::CPP_PostCouponPurchaseTrack(UPostCouponPurchaseTrackRequest* Request, const FOnPostCouponPurchaseTrackFullResponse& Handler) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UPostCouponPurchaseTrackRequest::StaticClass()->GetName(), RetryConfig);
	CPP_PostCouponPurchaseTrackImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamPaymentsApi::CPP_PostSteamPurchaseComplete(UPostSteamPurchaseCompleteRequest* Request, const FOnPostSteamPurchaseCompleteFullResponse& Handler) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UPostSteamPurchaseCompleteRequest::StaticClass()->GetName(), RetryConfig);
	CPP_PostSteamPurchaseCompleteImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamPaymentsApi::CPP_PostFacebookPurchaseTrack(UPostFacebookPurchaseTrackRequest* Request, const FOnPostFacebookPurchaseTrackFullResponse& Handler) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UPostFacebookPurchaseTrackRequest::StaticClass()->GetName(), RetryConfig);
	CPP_PostFacebookPurchaseTrackImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamPaymentsApi::CPP_PostTestPurchaseVerify(UPostTestPurchaseVerifyRequest* Request, const FOnPostTestPurchaseVerifyFullResponse& Handler) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UPostTestPurchaseVerifyRequest::StaticClass()->GetName(), RetryConfig);
	CPP_PostTestPurchaseVerifyImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamPaymentsApi::CPP_PostGoogleplayPurchaseTrack(UPostGoogleplayPurchaseTrackRequest* Request, const FOnPostGoogleplayPurchaseTrackFullResponse& Handler) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UPostGoogleplayPurchaseTrackRequest::StaticClass()->GetName(), RetryConfig);
	CPP_PostGoogleplayPurchaseTrackImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamPaymentsApi::CPP_GetSteamPrices(UGetSteamPricesRequest* Request, const FOnGetSteamPricesFullResponse& Handler) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UGetSteamPricesRequest::StaticClass()->GetName(), RetryConfig);
	CPP_GetSteamPricesImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamPaymentsApi::CPP_PostWindowsPurchaseVerify(UPostWindowsPurchaseVerifyRequest* Request, const FOnPostWindowsPurchaseVerifyFullResponse& Handler) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UPostWindowsPurchaseVerifyRequest::StaticClass()->GetName(), RetryConfig);
	CPP_PostWindowsPurchaseVerifyImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamPaymentsApi::CPP_PostItunesPurchaseVerify(UPostItunesPurchaseVerifyRequest* Request, const FOnPostItunesPurchaseVerifyFullResponse& Handler) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UPostItunesPurchaseVerifyRequest::StaticClass()->GetName(), RetryConfig);
	CPP_PostItunesPurchaseVerifyImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamPaymentsApi::CPP_PostItunesPurchaseComplete(UPostItunesPurchaseCompleteRequest* Request, const FOnPostItunesPurchaseCompleteFullResponse& Handler) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UPostItunesPurchaseCompleteRequest::StaticClass()->GetName(), RetryConfig);
	CPP_PostItunesPurchaseCompleteImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamPaymentsApi::CPP_PostFacebookPurchaseVerify(UPostFacebookPurchaseVerifyRequest* Request, const FOnPostFacebookPurchaseVerifyFullResponse& Handler) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UPostFacebookPurchaseVerifyRequest::StaticClass()->GetName(), RetryConfig);
	CPP_PostFacebookPurchaseVerifyImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamPaymentsApi::CPP_PostSteamPurchaseTrack(UPostSteamPurchaseTrackRequest* Request, const FOnPostSteamPurchaseTrackFullResponse& Handler) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UPostSteamPurchaseTrackRequest::StaticClass()->GetName(), RetryConfig);
	CPP_PostSteamPurchaseTrackImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamPaymentsApi::CPP_PostCouponPurchaseVerify(UPostCouponPurchaseVerifyRequest* Request, const FOnPostCouponPurchaseVerifyFullResponse& Handler) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UPostCouponPurchaseVerifyRequest::StaticClass()->GetName(), RetryConfig);
	CPP_PostCouponPurchaseVerifyImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamPaymentsApi::CPP_GetWindowsProduct(UGetWindowsProductRequest* Request, const FOnGetWindowsProductFullResponse& Handler) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UGetWindowsProductRequest::StaticClass()->GetName(), RetryConfig);
	CPP_GetWindowsProductImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamPaymentsApi::CPP_GetFacebookProduct(UGetFacebookProductRequest* Request, const FOnGetFacebookProductFullResponse& Handler) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UGetFacebookProductRequest::StaticClass()->GetName(), RetryConfig);
	CPP_GetFacebookProductImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamPaymentsApi::CPP_GetCouponProduct(UGetCouponProductRequest* Request, const FOnGetCouponProductFullResponse& Handler) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UGetCouponProductRequest::StaticClass()->GetName(), RetryConfig);
	CPP_GetCouponProductImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamPaymentsApi::CPP_GetSteamProducts(UGetSteamProductsRequest* Request, const FOnGetSteamProductsFullResponse& Handler) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UGetSteamProductsRequest::StaticClass()->GetName(), RetryConfig);
	CPP_GetSteamProductsImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamPaymentsApi::CPP_PostSteamAuth(UPostSteamAuthRequest* Request, const FOnPostSteamAuthFullResponse& Handler) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UPostSteamAuthRequest::StaticClass()->GetName(), RetryConfig);
	CPP_PostSteamAuthImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamPaymentsApi::CPP_GetSteamProduct(UGetSteamProductRequest* Request, const FOnGetSteamProductFullResponse& Handler) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UGetSteamProductRequest::StaticClass()->GetName(), RetryConfig);
	CPP_GetSteamProductImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamPaymentsApi::CPP_PostCouponPurchaseComplete(UPostCouponPurchaseCompleteRequest* Request, const FOnPostCouponPurchaseCompleteFullResponse& Handler) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UPostCouponPurchaseCompleteRequest::StaticClass()->GetName(), RetryConfig);
	CPP_PostCouponPurchaseCompleteImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamPaymentsApi::CPP_GetGoogleplayProduct(UGetGoogleplayProductRequest* Request, const FOnGetGoogleplayProductFullResponse& Handler) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UGetGoogleplayProductRequest::StaticClass()->GetName(), RetryConfig);
	CPP_GetGoogleplayProductImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamPaymentsApi::CPP_GetTestProduct(UGetTestProductRequest* Request, const FOnGetTestProductFullResponse& Handler) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UGetTestProductRequest::StaticClass()->GetName(), RetryConfig);
	CPP_GetTestProductImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamPaymentsApi::CPP_PostSteamPurchaseVerify(UPostSteamPurchaseVerifyRequest* Request, const FOnPostSteamPurchaseVerifyFullResponse& Handler) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UPostSteamPurchaseVerifyRequest::StaticClass()->GetName(), RetryConfig);
	CPP_PostSteamPurchaseVerifyImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamPaymentsApi::CPP_PostItunesPurchaseTrack(UPostItunesPurchaseTrackRequest* Request, const FOnPostItunesPurchaseTrackFullResponse& Handler) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UPostItunesPurchaseTrackRequest::StaticClass()->GetName(), RetryConfig);
	CPP_PostItunesPurchaseTrackImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamPaymentsApi::CPP_GetPayments(UGetPaymentsRequest* Request, const FOnGetPaymentsFullResponse& Handler) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UGetPaymentsRequest::StaticClass()->GetName(), RetryConfig);
	CPP_GetPaymentsImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler);
}



void UBeamPaymentsApi::CPP_PostTestPurchaseBegin(const FUserSlot& UserSlotId, UPostTestPurchaseBeginRequest* Request, const FOnPostTestPurchaseBeginFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostTestPurchaseBeginRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_PostTestPurchaseBeginImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamPaymentsApi::CPP_PostSteamPurchaseFail(const FUserSlot& UserSlotId, UPostSteamPurchaseFailRequest* Request, const FOnPostSteamPurchaseFailFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostSteamPurchaseFailRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_PostSteamPurchaseFailImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamPaymentsApi::CPP_PostFacebookPurchaseFail(const FUserSlot& UserSlotId, UPostFacebookPurchaseFailRequest* Request, const FOnPostFacebookPurchaseFailFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostFacebookPurchaseFailRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_PostFacebookPurchaseFailImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamPaymentsApi::CPP_PostGoogleplayPurchaseBegin(const FUserSlot& UserSlotId, UPostGoogleplayPurchaseBeginRequest* Request, const FOnPostGoogleplayPurchaseBeginFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostGoogleplayPurchaseBeginRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_PostGoogleplayPurchaseBeginImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamPaymentsApi::CPP_PostItunesPurchaseBegin(const FUserSlot& UserSlotId, UPostItunesPurchaseBeginRequest* Request, const FOnPostItunesPurchaseBeginFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostItunesPurchaseBeginRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_PostItunesPurchaseBeginImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamPaymentsApi::CPP_PostFacebookPurchaseCancel(const FUserSlot& UserSlotId, UPostFacebookPurchaseCancelRequest* Request, const FOnPostFacebookPurchaseCancelFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostFacebookPurchaseCancelRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_PostFacebookPurchaseCancelImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamPaymentsApi::CPP_PostItunesPurchaseFail(const FUserSlot& UserSlotId, UPostItunesPurchaseFailRequest* Request, const FOnPostItunesPurchaseFailFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostItunesPurchaseFailRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_PostItunesPurchaseFailImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamPaymentsApi::CPP_PostTestPurchaseCancel(const FUserSlot& UserSlotId, UPostTestPurchaseCancelRequest* Request, const FOnPostTestPurchaseCancelFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostTestPurchaseCancelRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_PostTestPurchaseCancelImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamPaymentsApi::CPP_PostTestPurchaseFail(const FUserSlot& UserSlotId, UPostTestPurchaseFailRequest* Request, const FOnPostTestPurchaseFailFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostTestPurchaseFailRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_PostTestPurchaseFailImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamPaymentsApi::CPP_PostCouponPurchaseCancel(const FUserSlot& UserSlotId, UPostCouponPurchaseCancelRequest* Request, const FOnPostCouponPurchaseCancelFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostCouponPurchaseCancelRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_PostCouponPurchaseCancelImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamPaymentsApi::CPP_PostCouponPurchaseBegin(const FUserSlot& UserSlotId, UPostCouponPurchaseBeginRequest* Request, const FOnPostCouponPurchaseBeginFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostCouponPurchaseBeginRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_PostCouponPurchaseBeginImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamPaymentsApi::CPP_PostFacebookPurchaseBegin(const FUserSlot& UserSlotId, UPostFacebookPurchaseBeginRequest* Request, const FOnPostFacebookPurchaseBeginFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostFacebookPurchaseBeginRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_PostFacebookPurchaseBeginImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamPaymentsApi::CPP_GetSteamOrder(const FUserSlot& UserSlotId, UGetSteamOrderRequest* Request, const FOnGetSteamOrderFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UGetSteamOrderRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_GetSteamOrderImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamPaymentsApi::CPP_PostWindowsPurchaseBegin(const FUserSlot& UserSlotId, UPostWindowsPurchaseBeginRequest* Request, const FOnPostWindowsPurchaseBeginFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostWindowsPurchaseBeginRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_PostWindowsPurchaseBeginImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamPaymentsApi::CPP_PostGoogleplayPurchaseFail(const FUserSlot& UserSlotId, UPostGoogleplayPurchaseFailRequest* Request, const FOnPostGoogleplayPurchaseFailFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostGoogleplayPurchaseFailRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_PostGoogleplayPurchaseFailImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamPaymentsApi::CPP_PostGoogleplayPurchaseCancel(const FUserSlot& UserSlotId, UPostGoogleplayPurchaseCancelRequest* Request, const FOnPostGoogleplayPurchaseCancelFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostGoogleplayPurchaseCancelRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_PostGoogleplayPurchaseCancelImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamPaymentsApi::CPP_PostCouponPurchaseFail(const FUserSlot& UserSlotId, UPostCouponPurchaseFailRequest* Request, const FOnPostCouponPurchaseFailFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostCouponPurchaseFailRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_PostCouponPurchaseFailImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamPaymentsApi::CPP_PostSteamPurchaseBegin(const FUserSlot& UserSlotId, UPostSteamPurchaseBeginRequest* Request, const FOnPostSteamPurchaseBeginFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostSteamPurchaseBeginRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_PostSteamPurchaseBeginImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamPaymentsApi::CPP_PostSteamPurchaseCancel(const FUserSlot& UserSlotId, UPostSteamPurchaseCancelRequest* Request, const FOnPostSteamPurchaseCancelFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostSteamPurchaseCancelRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_PostSteamPurchaseCancelImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamPaymentsApi::CPP_PostWindowsPurchaseCancel(const FUserSlot& UserSlotId, UPostWindowsPurchaseCancelRequest* Request, const FOnPostWindowsPurchaseCancelFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostWindowsPurchaseCancelRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_PostWindowsPurchaseCancelImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamPaymentsApi::CPP_PostWindowsPurchaseFail(const FUserSlot& UserSlotId, UPostWindowsPurchaseFailRequest* Request, const FOnPostWindowsPurchaseFailFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostWindowsPurchaseFailRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_PostWindowsPurchaseFailImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamPaymentsApi::CPP_PostItunesPurchaseCancel(const FUserSlot& UserSlotId, UPostItunesPurchaseCancelRequest* Request, const FOnPostItunesPurchaseCancelFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostItunesPurchaseCancelRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_PostItunesPurchaseCancelImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}




void UBeamPaymentsApi::PostWindowsPurchaseTrack(UPostWindowsPurchaseTrackRequest* Request, const FOnPostWindowsPurchaseTrackSuccess& OnSuccess, const FOnPostWindowsPurchaseTrackError& OnError,
                                           const FOnPostWindowsPurchaseTrackComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UPostWindowsPurchaseTrackRequest::StaticClass()->GetName(), RetryConfig);
	BP_PostWindowsPurchaseTrackImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamPaymentsApi::GetAudits(UGetAuditsRequest* Request, const FOnGetAuditsSuccess& OnSuccess, const FOnGetAuditsError& OnError,
                                           const FOnGetAuditsComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UGetAuditsRequest::StaticClass()->GetName(), RetryConfig);
	BP_GetAuditsImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamPaymentsApi::PostWindowsPurchaseComplete(UPostWindowsPurchaseCompleteRequest* Request, const FOnPostWindowsPurchaseCompleteSuccess& OnSuccess, const FOnPostWindowsPurchaseCompleteError& OnError,
                                           const FOnPostWindowsPurchaseCompleteComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UPostWindowsPurchaseCompleteRequest::StaticClass()->GetName(), RetryConfig);
	BP_PostWindowsPurchaseCompleteImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamPaymentsApi::GetFacebookUpdate(UGetFacebookUpdateRequest* Request, const FOnGetFacebookUpdateSuccess& OnSuccess, const FOnGetFacebookUpdateError& OnError,
                                           const FOnGetFacebookUpdateComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UGetFacebookUpdateRequest::StaticClass()->GetName(), RetryConfig);
	BP_GetFacebookUpdateImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamPaymentsApi::PostFacebookUpdate(UPostFacebookUpdateRequest* Request, const FOnPostFacebookUpdateSuccess& OnSuccess, const FOnPostFacebookUpdateError& OnError,
                                           const FOnPostFacebookUpdateComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UPostFacebookUpdateRequest::StaticClass()->GetName(), RetryConfig);
	BP_PostFacebookUpdateImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamPaymentsApi::PostFacebookPurchaseComplete(UPostFacebookPurchaseCompleteRequest* Request, const FOnPostFacebookPurchaseCompleteSuccess& OnSuccess, const FOnPostFacebookPurchaseCompleteError& OnError,
                                           const FOnPostFacebookPurchaseCompleteComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UPostFacebookPurchaseCompleteRequest::StaticClass()->GetName(), RetryConfig);
	BP_PostFacebookPurchaseCompleteImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamPaymentsApi::PostTestPurchaseComplete(UPostTestPurchaseCompleteRequest* Request, const FOnPostTestPurchaseCompleteSuccess& OnSuccess, const FOnPostTestPurchaseCompleteError& OnError,
                                           const FOnPostTestPurchaseCompleteComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UPostTestPurchaseCompleteRequest::StaticClass()->GetName(), RetryConfig);
	BP_PostTestPurchaseCompleteImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamPaymentsApi::GetItunesProduct(UGetItunesProductRequest* Request, const FOnGetItunesProductSuccess& OnSuccess, const FOnGetItunesProductError& OnError,
                                           const FOnGetItunesProductComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UGetItunesProductRequest::StaticClass()->GetName(), RetryConfig);
	BP_GetItunesProductImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamPaymentsApi::PostGoogleplayPurchaseComplete(UPostGoogleplayPurchaseCompleteRequest* Request, const FOnPostGoogleplayPurchaseCompleteSuccess& OnSuccess, const FOnPostGoogleplayPurchaseCompleteError& OnError,
                                           const FOnPostGoogleplayPurchaseCompleteComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UPostGoogleplayPurchaseCompleteRequest::StaticClass()->GetName(), RetryConfig);
	BP_PostGoogleplayPurchaseCompleteImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamPaymentsApi::PostTestPurchaseTrack(UPostTestPurchaseTrackRequest* Request, const FOnPostTestPurchaseTrackSuccess& OnSuccess, const FOnPostTestPurchaseTrackError& OnError,
                                           const FOnPostTestPurchaseTrackComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UPostTestPurchaseTrackRequest::StaticClass()->GetName(), RetryConfig);
	BP_PostTestPurchaseTrackImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamPaymentsApi::PostGoogleplayPurchaseVerify(UPostGoogleplayPurchaseVerifyRequest* Request, const FOnPostGoogleplayPurchaseVerifySuccess& OnSuccess, const FOnPostGoogleplayPurchaseVerifyError& OnError,
                                           const FOnPostGoogleplayPurchaseVerifyComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UPostGoogleplayPurchaseVerifyRequest::StaticClass()->GetName(), RetryConfig);
	BP_PostGoogleplayPurchaseVerifyImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamPaymentsApi::PostCouponPurchaseTrack(UPostCouponPurchaseTrackRequest* Request, const FOnPostCouponPurchaseTrackSuccess& OnSuccess, const FOnPostCouponPurchaseTrackError& OnError,
                                           const FOnPostCouponPurchaseTrackComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UPostCouponPurchaseTrackRequest::StaticClass()->GetName(), RetryConfig);
	BP_PostCouponPurchaseTrackImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamPaymentsApi::PostSteamPurchaseComplete(UPostSteamPurchaseCompleteRequest* Request, const FOnPostSteamPurchaseCompleteSuccess& OnSuccess, const FOnPostSteamPurchaseCompleteError& OnError,
                                           const FOnPostSteamPurchaseCompleteComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UPostSteamPurchaseCompleteRequest::StaticClass()->GetName(), RetryConfig);
	BP_PostSteamPurchaseCompleteImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamPaymentsApi::PostFacebookPurchaseTrack(UPostFacebookPurchaseTrackRequest* Request, const FOnPostFacebookPurchaseTrackSuccess& OnSuccess, const FOnPostFacebookPurchaseTrackError& OnError,
                                           const FOnPostFacebookPurchaseTrackComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UPostFacebookPurchaseTrackRequest::StaticClass()->GetName(), RetryConfig);
	BP_PostFacebookPurchaseTrackImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamPaymentsApi::PostTestPurchaseVerify(UPostTestPurchaseVerifyRequest* Request, const FOnPostTestPurchaseVerifySuccess& OnSuccess, const FOnPostTestPurchaseVerifyError& OnError,
                                           const FOnPostTestPurchaseVerifyComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UPostTestPurchaseVerifyRequest::StaticClass()->GetName(), RetryConfig);
	BP_PostTestPurchaseVerifyImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamPaymentsApi::PostGoogleplayPurchaseTrack(UPostGoogleplayPurchaseTrackRequest* Request, const FOnPostGoogleplayPurchaseTrackSuccess& OnSuccess, const FOnPostGoogleplayPurchaseTrackError& OnError,
                                           const FOnPostGoogleplayPurchaseTrackComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UPostGoogleplayPurchaseTrackRequest::StaticClass()->GetName(), RetryConfig);
	BP_PostGoogleplayPurchaseTrackImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamPaymentsApi::GetSteamPrices(UGetSteamPricesRequest* Request, const FOnGetSteamPricesSuccess& OnSuccess, const FOnGetSteamPricesError& OnError,
                                           const FOnGetSteamPricesComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UGetSteamPricesRequest::StaticClass()->GetName(), RetryConfig);
	BP_GetSteamPricesImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamPaymentsApi::PostWindowsPurchaseVerify(UPostWindowsPurchaseVerifyRequest* Request, const FOnPostWindowsPurchaseVerifySuccess& OnSuccess, const FOnPostWindowsPurchaseVerifyError& OnError,
                                           const FOnPostWindowsPurchaseVerifyComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UPostWindowsPurchaseVerifyRequest::StaticClass()->GetName(), RetryConfig);
	BP_PostWindowsPurchaseVerifyImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamPaymentsApi::PostItunesPurchaseVerify(UPostItunesPurchaseVerifyRequest* Request, const FOnPostItunesPurchaseVerifySuccess& OnSuccess, const FOnPostItunesPurchaseVerifyError& OnError,
                                           const FOnPostItunesPurchaseVerifyComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UPostItunesPurchaseVerifyRequest::StaticClass()->GetName(), RetryConfig);
	BP_PostItunesPurchaseVerifyImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamPaymentsApi::PostItunesPurchaseComplete(UPostItunesPurchaseCompleteRequest* Request, const FOnPostItunesPurchaseCompleteSuccess& OnSuccess, const FOnPostItunesPurchaseCompleteError& OnError,
                                           const FOnPostItunesPurchaseCompleteComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UPostItunesPurchaseCompleteRequest::StaticClass()->GetName(), RetryConfig);
	BP_PostItunesPurchaseCompleteImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamPaymentsApi::PostFacebookPurchaseVerify(UPostFacebookPurchaseVerifyRequest* Request, const FOnPostFacebookPurchaseVerifySuccess& OnSuccess, const FOnPostFacebookPurchaseVerifyError& OnError,
                                           const FOnPostFacebookPurchaseVerifyComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UPostFacebookPurchaseVerifyRequest::StaticClass()->GetName(), RetryConfig);
	BP_PostFacebookPurchaseVerifyImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamPaymentsApi::PostSteamPurchaseTrack(UPostSteamPurchaseTrackRequest* Request, const FOnPostSteamPurchaseTrackSuccess& OnSuccess, const FOnPostSteamPurchaseTrackError& OnError,
                                           const FOnPostSteamPurchaseTrackComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UPostSteamPurchaseTrackRequest::StaticClass()->GetName(), RetryConfig);
	BP_PostSteamPurchaseTrackImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamPaymentsApi::PostCouponPurchaseVerify(UPostCouponPurchaseVerifyRequest* Request, const FOnPostCouponPurchaseVerifySuccess& OnSuccess, const FOnPostCouponPurchaseVerifyError& OnError,
                                           const FOnPostCouponPurchaseVerifyComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UPostCouponPurchaseVerifyRequest::StaticClass()->GetName(), RetryConfig);
	BP_PostCouponPurchaseVerifyImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamPaymentsApi::GetWindowsProduct(UGetWindowsProductRequest* Request, const FOnGetWindowsProductSuccess& OnSuccess, const FOnGetWindowsProductError& OnError,
                                           const FOnGetWindowsProductComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UGetWindowsProductRequest::StaticClass()->GetName(), RetryConfig);
	BP_GetWindowsProductImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamPaymentsApi::GetFacebookProduct(UGetFacebookProductRequest* Request, const FOnGetFacebookProductSuccess& OnSuccess, const FOnGetFacebookProductError& OnError,
                                           const FOnGetFacebookProductComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UGetFacebookProductRequest::StaticClass()->GetName(), RetryConfig);
	BP_GetFacebookProductImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamPaymentsApi::GetCouponProduct(UGetCouponProductRequest* Request, const FOnGetCouponProductSuccess& OnSuccess, const FOnGetCouponProductError& OnError,
                                           const FOnGetCouponProductComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UGetCouponProductRequest::StaticClass()->GetName(), RetryConfig);
	BP_GetCouponProductImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamPaymentsApi::GetSteamProducts(UGetSteamProductsRequest* Request, const FOnGetSteamProductsSuccess& OnSuccess, const FOnGetSteamProductsError& OnError,
                                           const FOnGetSteamProductsComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UGetSteamProductsRequest::StaticClass()->GetName(), RetryConfig);
	BP_GetSteamProductsImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamPaymentsApi::PostSteamAuth(UPostSteamAuthRequest* Request, const FOnPostSteamAuthSuccess& OnSuccess, const FOnPostSteamAuthError& OnError,
                                           const FOnPostSteamAuthComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UPostSteamAuthRequest::StaticClass()->GetName(), RetryConfig);
	BP_PostSteamAuthImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamPaymentsApi::GetSteamProduct(UGetSteamProductRequest* Request, const FOnGetSteamProductSuccess& OnSuccess, const FOnGetSteamProductError& OnError,
                                           const FOnGetSteamProductComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UGetSteamProductRequest::StaticClass()->GetName(), RetryConfig);
	BP_GetSteamProductImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamPaymentsApi::PostCouponPurchaseComplete(UPostCouponPurchaseCompleteRequest* Request, const FOnPostCouponPurchaseCompleteSuccess& OnSuccess, const FOnPostCouponPurchaseCompleteError& OnError,
                                           const FOnPostCouponPurchaseCompleteComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UPostCouponPurchaseCompleteRequest::StaticClass()->GetName(), RetryConfig);
	BP_PostCouponPurchaseCompleteImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamPaymentsApi::GetGoogleplayProduct(UGetGoogleplayProductRequest* Request, const FOnGetGoogleplayProductSuccess& OnSuccess, const FOnGetGoogleplayProductError& OnError,
                                           const FOnGetGoogleplayProductComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UGetGoogleplayProductRequest::StaticClass()->GetName(), RetryConfig);
	BP_GetGoogleplayProductImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamPaymentsApi::GetTestProduct(UGetTestProductRequest* Request, const FOnGetTestProductSuccess& OnSuccess, const FOnGetTestProductError& OnError,
                                           const FOnGetTestProductComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UGetTestProductRequest::StaticClass()->GetName(), RetryConfig);
	BP_GetTestProductImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamPaymentsApi::PostSteamPurchaseVerify(UPostSteamPurchaseVerifyRequest* Request, const FOnPostSteamPurchaseVerifySuccess& OnSuccess, const FOnPostSteamPurchaseVerifyError& OnError,
                                           const FOnPostSteamPurchaseVerifyComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UPostSteamPurchaseVerifyRequest::StaticClass()->GetName(), RetryConfig);
	BP_PostSteamPurchaseVerifyImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamPaymentsApi::PostItunesPurchaseTrack(UPostItunesPurchaseTrackRequest* Request, const FOnPostItunesPurchaseTrackSuccess& OnSuccess, const FOnPostItunesPurchaseTrackError& OnError,
                                           const FOnPostItunesPurchaseTrackComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UPostItunesPurchaseTrackRequest::StaticClass()->GetName(), RetryConfig);
	BP_PostItunesPurchaseTrackImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamPaymentsApi::GetPayments(UGetPaymentsRequest* Request, const FOnGetPaymentsSuccess& OnSuccess, const FOnGetPaymentsError& OnError,
                                           const FOnGetPaymentsComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UGetPaymentsRequest::StaticClass()->GetName(), RetryConfig);
	BP_GetPaymentsImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}



void UBeamPaymentsApi::PostTestPurchaseBegin(const FUserSlot& UserSlotId, UPostTestPurchaseBeginRequest* Request, const FOnPostTestPurchaseBeginSuccess& OnSuccess, const FOnPostTestPurchaseBeginError& OnError,
                             const FOnPostTestPurchaseBeginComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostTestPurchaseBeginRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	BP_PostTestPurchaseBeginImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamPaymentsApi::PostSteamPurchaseFail(const FUserSlot& UserSlotId, UPostSteamPurchaseFailRequest* Request, const FOnPostSteamPurchaseFailSuccess& OnSuccess, const FOnPostSteamPurchaseFailError& OnError,
                             const FOnPostSteamPurchaseFailComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostSteamPurchaseFailRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	BP_PostSteamPurchaseFailImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamPaymentsApi::PostFacebookPurchaseFail(const FUserSlot& UserSlotId, UPostFacebookPurchaseFailRequest* Request, const FOnPostFacebookPurchaseFailSuccess& OnSuccess, const FOnPostFacebookPurchaseFailError& OnError,
                             const FOnPostFacebookPurchaseFailComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostFacebookPurchaseFailRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	BP_PostFacebookPurchaseFailImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamPaymentsApi::PostGoogleplayPurchaseBegin(const FUserSlot& UserSlotId, UPostGoogleplayPurchaseBeginRequest* Request, const FOnPostGoogleplayPurchaseBeginSuccess& OnSuccess, const FOnPostGoogleplayPurchaseBeginError& OnError,
                             const FOnPostGoogleplayPurchaseBeginComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostGoogleplayPurchaseBeginRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	BP_PostGoogleplayPurchaseBeginImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamPaymentsApi::PostItunesPurchaseBegin(const FUserSlot& UserSlotId, UPostItunesPurchaseBeginRequest* Request, const FOnPostItunesPurchaseBeginSuccess& OnSuccess, const FOnPostItunesPurchaseBeginError& OnError,
                             const FOnPostItunesPurchaseBeginComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostItunesPurchaseBeginRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	BP_PostItunesPurchaseBeginImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamPaymentsApi::PostFacebookPurchaseCancel(const FUserSlot& UserSlotId, UPostFacebookPurchaseCancelRequest* Request, const FOnPostFacebookPurchaseCancelSuccess& OnSuccess, const FOnPostFacebookPurchaseCancelError& OnError,
                             const FOnPostFacebookPurchaseCancelComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostFacebookPurchaseCancelRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	BP_PostFacebookPurchaseCancelImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamPaymentsApi::PostItunesPurchaseFail(const FUserSlot& UserSlotId, UPostItunesPurchaseFailRequest* Request, const FOnPostItunesPurchaseFailSuccess& OnSuccess, const FOnPostItunesPurchaseFailError& OnError,
                             const FOnPostItunesPurchaseFailComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostItunesPurchaseFailRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	BP_PostItunesPurchaseFailImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamPaymentsApi::PostTestPurchaseCancel(const FUserSlot& UserSlotId, UPostTestPurchaseCancelRequest* Request, const FOnPostTestPurchaseCancelSuccess& OnSuccess, const FOnPostTestPurchaseCancelError& OnError,
                             const FOnPostTestPurchaseCancelComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostTestPurchaseCancelRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	BP_PostTestPurchaseCancelImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamPaymentsApi::PostTestPurchaseFail(const FUserSlot& UserSlotId, UPostTestPurchaseFailRequest* Request, const FOnPostTestPurchaseFailSuccess& OnSuccess, const FOnPostTestPurchaseFailError& OnError,
                             const FOnPostTestPurchaseFailComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostTestPurchaseFailRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	BP_PostTestPurchaseFailImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamPaymentsApi::PostCouponPurchaseCancel(const FUserSlot& UserSlotId, UPostCouponPurchaseCancelRequest* Request, const FOnPostCouponPurchaseCancelSuccess& OnSuccess, const FOnPostCouponPurchaseCancelError& OnError,
                             const FOnPostCouponPurchaseCancelComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostCouponPurchaseCancelRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	BP_PostCouponPurchaseCancelImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamPaymentsApi::PostCouponPurchaseBegin(const FUserSlot& UserSlotId, UPostCouponPurchaseBeginRequest* Request, const FOnPostCouponPurchaseBeginSuccess& OnSuccess, const FOnPostCouponPurchaseBeginError& OnError,
                             const FOnPostCouponPurchaseBeginComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostCouponPurchaseBeginRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	BP_PostCouponPurchaseBeginImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamPaymentsApi::PostFacebookPurchaseBegin(const FUserSlot& UserSlotId, UPostFacebookPurchaseBeginRequest* Request, const FOnPostFacebookPurchaseBeginSuccess& OnSuccess, const FOnPostFacebookPurchaseBeginError& OnError,
                             const FOnPostFacebookPurchaseBeginComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostFacebookPurchaseBeginRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	BP_PostFacebookPurchaseBeginImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamPaymentsApi::GetSteamOrder(const FUserSlot& UserSlotId, UGetSteamOrderRequest* Request, const FOnGetSteamOrderSuccess& OnSuccess, const FOnGetSteamOrderError& OnError,
                             const FOnGetSteamOrderComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UGetSteamOrderRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	BP_GetSteamOrderImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamPaymentsApi::PostWindowsPurchaseBegin(const FUserSlot& UserSlotId, UPostWindowsPurchaseBeginRequest* Request, const FOnPostWindowsPurchaseBeginSuccess& OnSuccess, const FOnPostWindowsPurchaseBeginError& OnError,
                             const FOnPostWindowsPurchaseBeginComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostWindowsPurchaseBeginRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	BP_PostWindowsPurchaseBeginImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamPaymentsApi::PostGoogleplayPurchaseFail(const FUserSlot& UserSlotId, UPostGoogleplayPurchaseFailRequest* Request, const FOnPostGoogleplayPurchaseFailSuccess& OnSuccess, const FOnPostGoogleplayPurchaseFailError& OnError,
                             const FOnPostGoogleplayPurchaseFailComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostGoogleplayPurchaseFailRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	BP_PostGoogleplayPurchaseFailImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamPaymentsApi::PostGoogleplayPurchaseCancel(const FUserSlot& UserSlotId, UPostGoogleplayPurchaseCancelRequest* Request, const FOnPostGoogleplayPurchaseCancelSuccess& OnSuccess, const FOnPostGoogleplayPurchaseCancelError& OnError,
                             const FOnPostGoogleplayPurchaseCancelComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostGoogleplayPurchaseCancelRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	BP_PostGoogleplayPurchaseCancelImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamPaymentsApi::PostCouponPurchaseFail(const FUserSlot& UserSlotId, UPostCouponPurchaseFailRequest* Request, const FOnPostCouponPurchaseFailSuccess& OnSuccess, const FOnPostCouponPurchaseFailError& OnError,
                             const FOnPostCouponPurchaseFailComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostCouponPurchaseFailRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	BP_PostCouponPurchaseFailImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamPaymentsApi::PostSteamPurchaseBegin(const FUserSlot& UserSlotId, UPostSteamPurchaseBeginRequest* Request, const FOnPostSteamPurchaseBeginSuccess& OnSuccess, const FOnPostSteamPurchaseBeginError& OnError,
                             const FOnPostSteamPurchaseBeginComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostSteamPurchaseBeginRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	BP_PostSteamPurchaseBeginImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamPaymentsApi::PostSteamPurchaseCancel(const FUserSlot& UserSlotId, UPostSteamPurchaseCancelRequest* Request, const FOnPostSteamPurchaseCancelSuccess& OnSuccess, const FOnPostSteamPurchaseCancelError& OnError,
                             const FOnPostSteamPurchaseCancelComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostSteamPurchaseCancelRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	BP_PostSteamPurchaseCancelImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamPaymentsApi::PostWindowsPurchaseCancel(const FUserSlot& UserSlotId, UPostWindowsPurchaseCancelRequest* Request, const FOnPostWindowsPurchaseCancelSuccess& OnSuccess, const FOnPostWindowsPurchaseCancelError& OnError,
                             const FOnPostWindowsPurchaseCancelComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostWindowsPurchaseCancelRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	BP_PostWindowsPurchaseCancelImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamPaymentsApi::PostWindowsPurchaseFail(const FUserSlot& UserSlotId, UPostWindowsPurchaseFailRequest* Request, const FOnPostWindowsPurchaseFailSuccess& OnSuccess, const FOnPostWindowsPurchaseFailError& OnError,
                             const FOnPostWindowsPurchaseFailComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostWindowsPurchaseFailRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	BP_PostWindowsPurchaseFailImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamPaymentsApi::PostItunesPurchaseCancel(const FUserSlot& UserSlotId, UPostItunesPurchaseCancelRequest* Request, const FOnPostItunesPurchaseCancelSuccess& OnSuccess, const FOnPostItunesPurchaseCancelError& OnError,
                             const FOnPostItunesPurchaseCancelComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostItunesPurchaseCancelRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	BP_PostItunesPurchaseCancelImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}
	

