
#include "AutoGen/SubSystems/BeamCommerceApi.h"

void UBeamCommerceApi::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Backend = Cast<UBeamBackend>(Collection.InitializeDependency(UBeamBackend::StaticClass()));
}

void UBeamCommerceApi::Deinitialize()
{
	Super::Deinitialize();
}


void UBeamCommerceApi::BP_GetSkusImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetSkusRequest* RequestData,
                                                  const FOnGetSkusSuccess& OnSuccess, const FOnGetSkusError& OnError, const FOnGetSkusComplete& OnComplete,
                                                  int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UGetSkusRequest, UGetSKUsResponse, FOnGetSkusSuccess, FOnGetSkusError, FOnGetSkusComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig,TargetRealm, -1, FUserSlot(""), None};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamCommerceApi::CPP_GetSkusImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UGetSkusRequest* RequestData, const FOnGetSkusFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UGetSkusRequest, UGetSKUsResponse>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamCommerceApi::BP_GetCouponsCountImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetCouponsCountRequest* RequestData,
                                                  const FOnGetCouponsCountSuccess& OnSuccess, const FOnGetCouponsCountError& OnError, const FOnGetCouponsCountComplete& OnComplete,
                                                  int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UGetCouponsCountRequest, UGetTotalCouponResponse, FOnGetCouponsCountSuccess, FOnGetCouponsCountError, FOnGetCouponsCountComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	auto RequestContext = FBeamRequestContext{OutRequestId, RetryConfig,TargetRealm, -1, FUserSlot(""), None};
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamCommerceApi::CPP_GetCouponsCountImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UGetCouponsCountRequest* RequestData, const FOnGetCouponsCountFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UGetCouponsCountRequest, UGetTotalCouponResponse>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}



void UBeamCommerceApi::BP_PostCatalogLegacyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UPostCatalogLegacyRequest* RequestData, const FOnPostCatalogLegacySuccess& OnSuccess, const FOnPostCatalogLegacyError& OnError, const FOnPostCatalogLegacyComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPostCatalogLegacyRequest, UResultResponse, FOnPostCatalogLegacySuccess, FOnPostCatalogLegacyError, FOnPostCatalogLegacyComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamCommerceApi::CPP_PostCatalogLegacyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UPostCatalogLegacyRequest* RequestData, const FOnPostCatalogLegacyFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPostCatalogLegacyRequest, UResultResponse>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamCommerceApi::BP_GetCatalogImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UGetCatalogRequest* RequestData, const FOnGetCatalogSuccess& OnSuccess, const FOnGetCatalogError& OnError, const FOnGetCatalogComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UGetCatalogRequest, UGetCatalogResponse, FOnGetCatalogSuccess, FOnGetCatalogError, FOnGetCatalogComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamCommerceApi::CPP_GetCatalogImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UGetCatalogRequest* RequestData, const FOnGetCatalogFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UGetCatalogRequest, UGetCatalogResponse>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamCommerceApi::BP_PostSkusImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UPostSkusRequest* RequestData, const FOnPostSkusSuccess& OnSuccess, const FOnPostSkusError& OnError, const FOnPostSkusComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPostSkusRequest, UResultResponse, FOnPostSkusSuccess, FOnPostSkusError, FOnPostSkusComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamCommerceApi::CPP_PostSkusImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UPostSkusRequest* RequestData, const FOnPostSkusFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPostSkusRequest, UResultResponse>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamCommerceApi::BP_GetCommerceImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UGetCommerceRequest* RequestData, const FOnGetCommerceSuccess& OnSuccess, const FOnGetCommerceError& OnError, const FOnGetCommerceComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UGetCommerceRequest, UGetActiveOffersResponse, FOnGetCommerceSuccess, FOnGetCommerceError, FOnGetCommerceComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamCommerceApi::CPP_GetCommerceImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UGetCommerceRequest* RequestData, const FOnGetCommerceFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UGetCommerceRequest, UGetActiveOffersResponse>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamCommerceApi::BP_PutListingsCooldownImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UPutListingsCooldownRequest* RequestData, const FOnPutListingsCooldownSuccess& OnSuccess, const FOnPutListingsCooldownError& OnError, const FOnPutListingsCooldownComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPutListingsCooldownRequest, UCommonResponse, FOnPutListingsCooldownSuccess, FOnPutListingsCooldownError, FOnPutListingsCooldownComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamCommerceApi::CPP_PutListingsCooldownImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UPutListingsCooldownRequest* RequestData, const FOnPutListingsCooldownFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPutListingsCooldownRequest, UCommonResponse>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamCommerceApi::BP_GetOffersAdminImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UGetOffersAdminRequest* RequestData, const FOnGetOffersAdminSuccess& OnSuccess, const FOnGetOffersAdminError& OnError, const FOnGetOffersAdminComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UGetOffersAdminRequest, UGetActiveOffersResponse, FOnGetOffersAdminSuccess, FOnGetOffersAdminError, FOnGetOffersAdminComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamCommerceApi::CPP_GetOffersAdminImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UGetOffersAdminRequest* RequestData, const FOnGetOffersAdminFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UGetOffersAdminRequest, UGetActiveOffersResponse>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamCommerceApi::BP_PostPurchaseImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UPostPurchaseRequest* RequestData, const FOnPostPurchaseSuccess& OnSuccess, const FOnPostPurchaseError& OnError, const FOnPostPurchaseComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPostPurchaseRequest, UCommonResponse, FOnPostPurchaseSuccess, FOnPostPurchaseError, FOnPostPurchaseComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamCommerceApi::CPP_PostPurchaseImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UPostPurchaseRequest* RequestData, const FOnPostPurchaseFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPostPurchaseRequest, UCommonResponse>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamCommerceApi::BP_PutPurchaseImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UPutPurchaseRequest* RequestData, const FOnPutPurchaseSuccess& OnSuccess, const FOnPutPurchaseError& OnError, const FOnPutPurchaseComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPutPurchaseRequest, UResultResponse, FOnPutPurchaseSuccess, FOnPutPurchaseError, FOnPutPurchaseComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamCommerceApi::CPP_PutPurchaseImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UPutPurchaseRequest* RequestData, const FOnPutPurchaseFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPutPurchaseRequest, UResultResponse>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamCommerceApi::BP_GetListingsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UGetListingsRequest* RequestData, const FOnGetListingsSuccess& OnSuccess, const FOnGetListingsError& OnError, const FOnGetListingsComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UGetListingsRequest, UActiveListingResponse, FOnGetListingsSuccess, FOnGetListingsError, FOnGetListingsComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamCommerceApi::CPP_GetListingsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UGetListingsRequest* RequestData, const FOnGetListingsFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UGetListingsRequest, UActiveListingResponse>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamCommerceApi::BP_DeleteStatusImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UDeleteStatusRequest* RequestData, const FOnDeleteStatusSuccess& OnSuccess, const FOnDeleteStatusError& OnError, const FOnDeleteStatusComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UDeleteStatusRequest, UCommonResponse, FOnDeleteStatusSuccess, FOnDeleteStatusError, FOnDeleteStatusComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamCommerceApi::CPP_DeleteStatusImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UDeleteStatusRequest* RequestData, const FOnDeleteStatusFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UDeleteStatusRequest, UCommonResponse>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamCommerceApi::BP_PostCouponsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UPostCouponsRequest* RequestData, const FOnPostCouponsSuccess& OnSuccess, const FOnPostCouponsError& OnError, const FOnPostCouponsComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPostCouponsRequest, UCommonResponse, FOnPostCouponsSuccess, FOnPostCouponsError, FOnPostCouponsComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamCommerceApi::CPP_PostCouponsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UPostCouponsRequest* RequestData, const FOnPostCouponsFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPostCouponsRequest, UCommonResponse>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamCommerceApi::BP_PostStatsUpdateImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UPostStatsUpdateRequest* RequestData, const FOnPostStatsUpdateSuccess& OnSuccess, const FOnPostStatsUpdateError& OnError, const FOnPostStatsUpdateComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPostStatsUpdateRequest, UCommonResponse, FOnPostStatsUpdateSuccess, FOnPostStatsUpdateError, FOnPostStatsUpdateComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamCommerceApi::CPP_PostStatsUpdateImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UPostStatsUpdateRequest* RequestData, const FOnPostStatsUpdateFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPostStatsUpdateRequest, UCommonResponse>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

		
void UBeamCommerceApi::BP_GetOffersImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UGetOffersRequest* RequestData, const FOnGetOffersSuccess& OnSuccess, const FOnGetOffersError& OnError, const FOnGetOffersComplete& OnComplete, int64& OutRequestId) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UGetOffersRequest, UGetActiveOffersResponse, FOnGetOffersSuccess, FOnGetOffersError, FOnGetOffersComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}

void UBeamCommerceApi::CPP_GetOffersImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UGetOffersRequest* RequestData, const FOnGetOffersFullResponse& Handler) const
{
	// AUTO-GENERATED...
	int64 OutRequestId;
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UGetOffersRequest, UGetActiveOffersResponse>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
}




void UBeamCommerceApi::CPP_GetSkus(UGetSkusRequest* Request, const FOnGetSkusFullResponse& Handler) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UGetSkusRequest::StaticClass()->GetName(), RetryConfig);
	CPP_GetSkusImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamCommerceApi::CPP_GetCouponsCount(UGetCouponsCountRequest* Request, const FOnGetCouponsCountFullResponse& Handler) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UGetCouponsCountRequest::StaticClass()->GetName(), RetryConfig);
	CPP_GetCouponsCountImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler);
}



void UBeamCommerceApi::CPP_PostCatalogLegacy(const FUserSlot& UserSlotId, UPostCatalogLegacyRequest* Request, const FOnPostCatalogLegacyFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostCatalogLegacyRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_PostCatalogLegacyImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamCommerceApi::CPP_GetCatalog(const FUserSlot& UserSlotId, UGetCatalogRequest* Request, const FOnGetCatalogFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UGetCatalogRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_GetCatalogImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamCommerceApi::CPP_PostSkus(const FUserSlot& UserSlotId, UPostSkusRequest* Request, const FOnPostSkusFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostSkusRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_PostSkusImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamCommerceApi::CPP_GetCommerce(const FUserSlot& UserSlotId, UGetCommerceRequest* Request, const FOnGetCommerceFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UGetCommerceRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_GetCommerceImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamCommerceApi::CPP_PutListingsCooldown(const FUserSlot& UserSlotId, UPutListingsCooldownRequest* Request, const FOnPutListingsCooldownFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPutListingsCooldownRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_PutListingsCooldownImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamCommerceApi::CPP_GetOffersAdmin(const FUserSlot& UserSlotId, UGetOffersAdminRequest* Request, const FOnGetOffersAdminFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UGetOffersAdminRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_GetOffersAdminImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamCommerceApi::CPP_PostPurchase(const FUserSlot& UserSlotId, UPostPurchaseRequest* Request, const FOnPostPurchaseFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostPurchaseRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_PostPurchaseImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamCommerceApi::CPP_PutPurchase(const FUserSlot& UserSlotId, UPutPurchaseRequest* Request, const FOnPutPurchaseFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPutPurchaseRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_PutPurchaseImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamCommerceApi::CPP_GetListings(const FUserSlot& UserSlotId, UGetListingsRequest* Request, const FOnGetListingsFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UGetListingsRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_GetListingsImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamCommerceApi::CPP_DeleteStatus(const FUserSlot& UserSlotId, UDeleteStatusRequest* Request, const FOnDeleteStatusFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UDeleteStatusRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_DeleteStatusImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamCommerceApi::CPP_PostCoupons(const FUserSlot& UserSlotId, UPostCouponsRequest* Request, const FOnPostCouponsFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostCouponsRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_PostCouponsImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamCommerceApi::CPP_PostStatsUpdate(const FUserSlot& UserSlotId, UPostStatsUpdateRequest* Request, const FOnPostStatsUpdateFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostStatsUpdateRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_PostStatsUpdateImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}

		
void UBeamCommerceApi::CPP_GetOffers(const FUserSlot& UserSlotId, UGetOffersRequest* Request, const FOnGetOffersFullResponse& Handler) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UGetOffersRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	CPP_GetOffersImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler);
}




void UBeamCommerceApi::GetSkus(UGetSkusRequest* Request, const FOnGetSkusSuccess& OnSuccess, const FOnGetSkusError& OnError,
                                           const FOnGetSkusComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UGetSkusRequest::StaticClass()->GetName(), RetryConfig);
	BP_GetSkusImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamCommerceApi::GetCouponsCount(UGetCouponsCountRequest* Request, const FOnGetCouponsCountSuccess& OnSuccess, const FOnGetCouponsCountError& OnError,
                                           const FOnGetCouponsCountComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UGetCouponsCountRequest::StaticClass()->GetName(), RetryConfig);
	BP_GetCouponsCountImpl(Backend->UnauthenticatedRequestsTargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}



void UBeamCommerceApi::PostCatalogLegacy(const FUserSlot& UserSlotId, UPostCatalogLegacyRequest* Request, const FOnPostCatalogLegacySuccess& OnSuccess, const FOnPostCatalogLegacyError& OnError,
                             const FOnPostCatalogLegacyComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostCatalogLegacyRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	BP_PostCatalogLegacyImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamCommerceApi::GetCatalog(const FUserSlot& UserSlotId, UGetCatalogRequest* Request, const FOnGetCatalogSuccess& OnSuccess, const FOnGetCatalogError& OnError,
                             const FOnGetCatalogComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UGetCatalogRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	BP_GetCatalogImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamCommerceApi::PostSkus(const FUserSlot& UserSlotId, UPostSkusRequest* Request, const FOnPostSkusSuccess& OnSuccess, const FOnPostSkusError& OnError,
                             const FOnPostSkusComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostSkusRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	BP_PostSkusImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamCommerceApi::GetCommerce(const FUserSlot& UserSlotId, UGetCommerceRequest* Request, const FOnGetCommerceSuccess& OnSuccess, const FOnGetCommerceError& OnError,
                             const FOnGetCommerceComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UGetCommerceRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	BP_GetCommerceImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamCommerceApi::PutListingsCooldown(const FUserSlot& UserSlotId, UPutListingsCooldownRequest* Request, const FOnPutListingsCooldownSuccess& OnSuccess, const FOnPutListingsCooldownError& OnError,
                             const FOnPutListingsCooldownComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPutListingsCooldownRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	BP_PutListingsCooldownImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamCommerceApi::GetOffersAdmin(const FUserSlot& UserSlotId, UGetOffersAdminRequest* Request, const FOnGetOffersAdminSuccess& OnSuccess, const FOnGetOffersAdminError& OnError,
                             const FOnGetOffersAdminComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UGetOffersAdminRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	BP_GetOffersAdminImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamCommerceApi::PostPurchase(const FUserSlot& UserSlotId, UPostPurchaseRequest* Request, const FOnPostPurchaseSuccess& OnSuccess, const FOnPostPurchaseError& OnError,
                             const FOnPostPurchaseComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostPurchaseRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	BP_PostPurchaseImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamCommerceApi::PutPurchase(const FUserSlot& UserSlotId, UPutPurchaseRequest* Request, const FOnPutPurchaseSuccess& OnSuccess, const FOnPutPurchaseError& OnError,
                             const FOnPutPurchaseComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPutPurchaseRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	BP_PutPurchaseImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamCommerceApi::GetListings(const FUserSlot& UserSlotId, UGetListingsRequest* Request, const FOnGetListingsSuccess& OnSuccess, const FOnGetListingsError& OnError,
                             const FOnGetListingsComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UGetListingsRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	BP_GetListingsImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamCommerceApi::DeleteStatus(const FUserSlot& UserSlotId, UDeleteStatusRequest* Request, const FOnDeleteStatusSuccess& OnSuccess, const FOnDeleteStatusError& OnError,
                             const FOnDeleteStatusComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UDeleteStatusRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	BP_DeleteStatusImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamCommerceApi::PostCoupons(const FUserSlot& UserSlotId, UPostCouponsRequest* Request, const FOnPostCouponsSuccess& OnSuccess, const FOnPostCouponsError& OnError,
                             const FOnPostCouponsComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostCouponsRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	BP_PostCouponsImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamCommerceApi::PostStatsUpdate(const FUserSlot& UserSlotId, UPostStatsUpdateRequest* Request, const FOnPostStatsUpdateSuccess& OnSuccess, const FOnPostStatsUpdateError& OnError,
                             const FOnPostStatsUpdateComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostStatsUpdateRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	BP_PostStatsUpdateImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}

		
void UBeamCommerceApi::GetOffers(const FUserSlot& UserSlotId, UGetOffersRequest* Request, const FOnGetOffersSuccess& OnSuccess, const FOnGetOffersError& OnError,
                             const FOnGetOffersComplete& OnComplete, int64& OutRequestId)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlotId, AuthenticatedUser);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UGetOffersRequest::StaticClass()->GetName(), UserSlotId, RetryConfig);

	BP_GetOffersImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
}
	

