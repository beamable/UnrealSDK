
#include "AutoGen/SubSystems/BeamInventoryApi.h"
#include "BeamCoreSettings.h"


void UBeamInventoryApi::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Backend = Cast<UBeamBackend>(Collection.InitializeDependency(UBeamBackend::StaticClass()));
	RequestTracker = Cast<UBeamRequestTracker>(Collection.InitializeDependency(UBeamRequestTracker::StaticClass()));
}

void UBeamInventoryApi::Deinitialize()
{
	Super::Deinitialize();
}


void UBeamInventoryApi::BP_GetItemsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetItemsRequest* RequestData,
                                                  const FOnGetItemsSuccess& OnSuccess, const FOnGetItemsError& OnError, const FOnGetItemsComplete& OnComplete,
                                                  int64& OutRequestId, FBeamOperationHandle OpHandle) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UGetItemsRequest, UItemContentResponse, FOnGetItemsSuccess, FOnGetItemsError, FOnGetItemsComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
	
	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);
}

void UBeamInventoryApi::CPP_GetItemsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UGetItemsRequest* RequestData, const FOnGetItemsFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UGetItemsRequest, UItemContentResponse>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);

	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);
}

		
void UBeamInventoryApi::BP_GetCurrencyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetCurrencyRequest* RequestData,
                                                  const FOnGetCurrencySuccess& OnSuccess, const FOnGetCurrencyError& OnError, const FOnGetCurrencyComplete& OnComplete,
                                                  int64& OutRequestId, FBeamOperationHandle OpHandle) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UGetCurrencyRequest, UCurrencyContentResponse, FOnGetCurrencySuccess, FOnGetCurrencyError, FOnGetCurrencyComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
	
	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);
}

void UBeamInventoryApi::CPP_GetCurrencyImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UGetCurrencyRequest* RequestData, const FOnGetCurrencyFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UGetCurrencyRequest, UCurrencyContentResponse>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);

	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);
}

		
void UBeamInventoryApi::BP_PutPreviewImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPutPreviewRequest* RequestData,
                                                  const FOnPutPreviewSuccess& OnSuccess, const FOnPutPreviewError& OnError, const FOnPutPreviewComplete& OnComplete,
                                                  int64& OutRequestId, FBeamOperationHandle OpHandle) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UPutPreviewRequest, UPreviewVipBonusResponse, FOnPutPreviewSuccess, FOnPutPreviewError, FOnPutPreviewComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
	
	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);
}

void UBeamInventoryApi::CPP_PutPreviewImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UPutPreviewRequest* RequestData, const FOnPutPreviewFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UPutPreviewRequest, UPreviewVipBonusResponse>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);

	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);
}

		
void UBeamInventoryApi::BP_GetMultipliersImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetMultipliersRequest* RequestData,
                                                  const FOnGetMultipliersSuccess& OnSuccess, const FOnGetMultipliersError& OnError, const FOnGetMultipliersComplete& OnComplete,
                                                  int64& OutRequestId, FBeamOperationHandle OpHandle) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UGetMultipliersRequest, UMultipliersGetResponse, FOnGetMultipliersSuccess, FOnGetMultipliersError, FOnGetMultipliersComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
	
	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);
}

void UBeamInventoryApi::CPP_GetMultipliersImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UGetMultipliersRequest* RequestData, const FOnGetMultipliersFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UGetMultipliersRequest, UMultipliersGetResponse>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);

	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);
}

		
void UBeamInventoryApi::BP_GetInventoryImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UGetInventoryRequest* RequestData,
                                                  const FOnGetInventorySuccess& OnSuccess, const FOnGetInventoryError& OnError, const FOnGetInventoryComplete& OnComplete,
                                                  int64& OutRequestId, FBeamOperationHandle OpHandle) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UGetInventoryRequest, UInventoryView, FOnGetInventorySuccess, FOnGetInventoryError, FOnGetInventoryComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
	
	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);
}

void UBeamInventoryApi::CPP_GetInventoryImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UGetInventoryRequest* RequestData, const FOnGetInventoryFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UGetInventoryRequest, UInventoryView>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);

	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);
}

		
void UBeamInventoryApi::BP_PostInventoryImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPostInventoryRequest* RequestData,
                                                  const FOnPostInventorySuccess& OnSuccess, const FOnPostInventoryError& OnError, const FOnPostInventoryComplete& OnComplete,
                                                  int64& OutRequestId, FBeamOperationHandle OpHandle) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UPostInventoryRequest, UInventoryView, FOnPostInventorySuccess, FOnPostInventoryError, FOnPostInventoryComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
	
	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);
}

void UBeamInventoryApi::CPP_PostInventoryImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UPostInventoryRequest* RequestData, const FOnPostInventoryFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UPostInventoryRequest, UInventoryView>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);

	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);
}

		
void UBeamInventoryApi::BP_PutInventoryImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus, UPutInventoryRequest* RequestData,
                                                  const FOnPutInventorySuccess& OnSuccess, const FOnPutInventoryError& OnError, const FOnPutInventoryComplete& OnComplete,
                                                  int64& OutRequestId, FBeamOperationHandle OpHandle) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UPutInventoryRequest, UCommonResponse, FOnPutInventorySuccess, FOnPutInventoryError, FOnPutInventoryComplete>
		(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);
	
	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);
}

void UBeamInventoryApi::CPP_PutInventoryImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, FBeamConnectivity& ConnectivityStatus,
                                               UPutInventoryRequest* RequestData, const FOnPutInventoryFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UPutInventoryRequest, UCommonResponse>(OutRequestId, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);

	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);
}



void UBeamInventoryApi::BP_DeleteTransactionImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UDeleteTransactionRequest* RequestData, const FOnDeleteTransactionSuccess& OnSuccess, const FOnDeleteTransactionError& OnError, const FOnDeleteTransactionComplete& OnComplete, 
								int64& OutRequestId, FBeamOperationHandle OpHandle) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UDeleteTransactionRequest, UCommonResponse, FOnDeleteTransactionSuccess, FOnDeleteTransactionError, FOnDeleteTransactionComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);

	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);
}

void UBeamInventoryApi::CPP_DeleteTransactionImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UDeleteTransactionRequest* RequestData, const FOnDeleteTransactionFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle) const
{
	// AUTO-GENERATED...
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UDeleteTransactionRequest, UCommonResponse>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);

	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);
}

		
void UBeamInventoryApi::BP_PutTransferImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                                UPutTransferRequest* RequestData, const FOnPutTransferSuccess& OnSuccess, const FOnPutTransferError& OnError, const FOnPutTransferComplete& OnComplete, 
								int64& OutRequestId, FBeamOperationHandle OpHandle) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)
	const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPutTransferRequest, UCommonResponse, FOnPutTransferSuccess, FOnPutTransferError, FOnPutTransferComplete>
		(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
	Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);

	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);
}

void UBeamInventoryApi::CPP_PutTransferImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, FBeamConnectivity& ConnectivityStatus,
                              UPutTransferRequest* RequestData, const FOnPutTransferFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle) const
{
	// AUTO-GENERATED...
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPutTransferRequest, UCommonResponse>(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
	Backend->ExecuteRequestDelegate.ExecuteIfBound(OutRequestId, ConnectivityStatus);

	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);
}




void UBeamInventoryApi::CPP_GetItems(UGetItemsRequest* Request, const FOnGetItemsFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UGetItemsRequest::StaticClass()->GetName(), RetryConfig);
	
    int64 OutRequestId;
	CPP_GetItemsImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler, OutRequestId, OpHandle);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, FUserSlot(), None};
}

		
void UBeamInventoryApi::CPP_GetCurrency(UGetCurrencyRequest* Request, const FOnGetCurrencyFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UGetCurrencyRequest::StaticClass()->GetName(), RetryConfig);
	
    int64 OutRequestId;
	CPP_GetCurrencyImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler, OutRequestId, OpHandle);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, FUserSlot(), None};
}

		
void UBeamInventoryApi::CPP_PutPreview(UPutPreviewRequest* Request, const FOnPutPreviewFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UPutPreviewRequest::StaticClass()->GetName(), RetryConfig);
	
    int64 OutRequestId;
	CPP_PutPreviewImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler, OutRequestId, OpHandle);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, FUserSlot(), None};
}

		
void UBeamInventoryApi::CPP_GetMultipliers(UGetMultipliersRequest* Request, const FOnGetMultipliersFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UGetMultipliersRequest::StaticClass()->GetName(), RetryConfig);
	
    int64 OutRequestId;
	CPP_GetMultipliersImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler, OutRequestId, OpHandle);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, FUserSlot(), None};
}

		
void UBeamInventoryApi::CPP_GetInventory(UGetInventoryRequest* Request, const FOnGetInventoryFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UGetInventoryRequest::StaticClass()->GetName(), RetryConfig);
	
    int64 OutRequestId;
	CPP_GetInventoryImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler, OutRequestId, OpHandle);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, FUserSlot(), None};
}

		
void UBeamInventoryApi::CPP_PostInventory(UPostInventoryRequest* Request, const FOnPostInventoryFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UPostInventoryRequest::StaticClass()->GetName(), RetryConfig);
	
    int64 OutRequestId;
	CPP_PostInventoryImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler, OutRequestId, OpHandle);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, FUserSlot(), None};
}

		
void UBeamInventoryApi::CPP_PutInventory(UPutInventoryRequest* Request, const FOnPutInventoryFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UPutInventoryRequest::StaticClass()->GetName(), RetryConfig);
	
    int64 OutRequestId;
	CPP_PutInventoryImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, Handler, OutRequestId, OpHandle);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, FUserSlot(), None};
}



void UBeamInventoryApi::CPP_DeleteTransaction(const FUserSlot& UserSlot, UDeleteTransactionRequest* Request, const FOnDeleteTransactionFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UDeleteTransactionRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_DeleteTransactionImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler, OutRequestId, OpHandle);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, AuthenticatedUser.RealmHandle, -1, UserSlot, None};
}

		
void UBeamInventoryApi::CPP_PutTransfer(const FUserSlot& UserSlot, UPutTransferRequest* Request, const FOnPutTransferFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPutTransferRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_PutTransferImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, Handler, OutRequestId, OpHandle);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, AuthenticatedUser.RealmHandle, -1, UserSlot, None};
}




void UBeamInventoryApi::GetItems(UGetItemsRequest* Request, const FOnGetItemsSuccess& OnSuccess, const FOnGetItemsError& OnError, const FOnGetItemsComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UGetItemsRequest::StaticClass()->GetName(), RetryConfig);	
	
	int64 OutRequestId = 0;
	BP_GetItemsImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, FUserSlot(), None};
}

		
void UBeamInventoryApi::GetCurrency(UGetCurrencyRequest* Request, const FOnGetCurrencySuccess& OnSuccess, const FOnGetCurrencyError& OnError, const FOnGetCurrencyComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UGetCurrencyRequest::StaticClass()->GetName(), RetryConfig);	
	
	int64 OutRequestId = 0;
	BP_GetCurrencyImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, FUserSlot(), None};
}

		
void UBeamInventoryApi::PutPreview(UPutPreviewRequest* Request, const FOnPutPreviewSuccess& OnSuccess, const FOnPutPreviewError& OnError, const FOnPutPreviewComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UPutPreviewRequest::StaticClass()->GetName(), RetryConfig);	
	
	int64 OutRequestId = 0;
	BP_PutPreviewImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, FUserSlot(), None};
}

		
void UBeamInventoryApi::GetMultipliers(UGetMultipliersRequest* Request, const FOnGetMultipliersSuccess& OnSuccess, const FOnGetMultipliersError& OnError, const FOnGetMultipliersComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UGetMultipliersRequest::StaticClass()->GetName(), RetryConfig);	
	
	int64 OutRequestId = 0;
	BP_GetMultipliersImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, FUserSlot(), None};
}

		
void UBeamInventoryApi::GetInventory(UGetInventoryRequest* Request, const FOnGetInventorySuccess& OnSuccess, const FOnGetInventoryError& OnError, const FOnGetInventoryComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UGetInventoryRequest::StaticClass()->GetName(), RetryConfig);	
	
	int64 OutRequestId = 0;
	BP_GetInventoryImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, FUserSlot(), None};
}

		
void UBeamInventoryApi::PostInventory(UPostInventoryRequest* Request, const FOnPostInventorySuccess& OnSuccess, const FOnPostInventoryError& OnError, const FOnPostInventoryComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UPostInventoryRequest::StaticClass()->GetName(), RetryConfig);	
	
	int64 OutRequestId = 0;
	BP_PostInventoryImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, FUserSlot(), None};
}

		
void UBeamInventoryApi::PutInventory(UPutInventoryRequest* Request, const FOnPutInventorySuccess& OnSuccess, const FOnPutInventoryError& OnError, const FOnPutInventoryComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UPutInventoryRequest::StaticClass()->GetName(), RetryConfig);	
	
	int64 OutRequestId = 0;
	BP_PutInventoryImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, FUserSlot(), None};
}



void UBeamInventoryApi::DeleteTransaction(FUserSlot UserSlot, UDeleteTransactionRequest* Request, const FOnDeleteTransactionSuccess& OnSuccess, const FOnDeleteTransactionError& OnError, const FOnDeleteTransactionComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UDeleteTransactionRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_DeleteTransactionImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, AuthenticatedUser.RealmHandle, -1, UserSlot, None};
}

		
void UBeamInventoryApi::PutTransfer(FUserSlot UserSlot, UPutTransferRequest* Request, const FOnPutTransferSuccess& OnSuccess, const FOnPutTransferError& OnError, const FOnPutTransferComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPutTransferRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_PutTransferImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, AuthenticatedUser.RealmHandle, -1, UserSlot, None};
}
	


void UBeamInventoryApi::GetItemsWithRetry(const FBeamRetryConfig& RetryConfig, UGetItemsRequest* Request, const FOnGetItemsSuccess& OnSuccess, const FOnGetItemsError& OnError, const FOnGetItemsComplete& OnComplete, FBeamRequestContext& OutRequestContext)
{
	int64 OutRequestId = 0;
	BP_GetItemsImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, FUserSlot(), None}; 
}

		
void UBeamInventoryApi::GetCurrencyWithRetry(const FBeamRetryConfig& RetryConfig, UGetCurrencyRequest* Request, const FOnGetCurrencySuccess& OnSuccess, const FOnGetCurrencyError& OnError, const FOnGetCurrencyComplete& OnComplete, FBeamRequestContext& OutRequestContext)
{
	int64 OutRequestId = 0;
	BP_GetCurrencyImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, FUserSlot(), None}; 
}

		
void UBeamInventoryApi::PutPreviewWithRetry(const FBeamRetryConfig& RetryConfig, UPutPreviewRequest* Request, const FOnPutPreviewSuccess& OnSuccess, const FOnPutPreviewError& OnError, const FOnPutPreviewComplete& OnComplete, FBeamRequestContext& OutRequestContext)
{
	int64 OutRequestId = 0;
	BP_PutPreviewImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, FUserSlot(), None}; 
}

		
void UBeamInventoryApi::GetMultipliersWithRetry(const FBeamRetryConfig& RetryConfig, UGetMultipliersRequest* Request, const FOnGetMultipliersSuccess& OnSuccess, const FOnGetMultipliersError& OnError, const FOnGetMultipliersComplete& OnComplete, FBeamRequestContext& OutRequestContext)
{
	int64 OutRequestId = 0;
	BP_GetMultipliersImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, FUserSlot(), None}; 
}

		
void UBeamInventoryApi::GetInventoryWithRetry(const FBeamRetryConfig& RetryConfig, UGetInventoryRequest* Request, const FOnGetInventorySuccess& OnSuccess, const FOnGetInventoryError& OnError, const FOnGetInventoryComplete& OnComplete, FBeamRequestContext& OutRequestContext)
{
	int64 OutRequestId = 0;
	BP_GetInventoryImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, FUserSlot(), None}; 
}

		
void UBeamInventoryApi::PostInventoryWithRetry(const FBeamRetryConfig& RetryConfig, UPostInventoryRequest* Request, const FOnPostInventorySuccess& OnSuccess, const FOnPostInventoryError& OnError, const FOnPostInventoryComplete& OnComplete, FBeamRequestContext& OutRequestContext)
{
	int64 OutRequestId = 0;
	BP_PostInventoryImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, FUserSlot(), None}; 
}

		
void UBeamInventoryApi::PutInventoryWithRetry(const FBeamRetryConfig& RetryConfig, UPutInventoryRequest* Request, const FOnPutInventorySuccess& OnSuccess, const FOnPutInventoryError& OnError, const FOnPutInventoryComplete& OnComplete, FBeamRequestContext& OutRequestContext)
{
	int64 OutRequestId = 0;
	BP_PutInventoryImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, FUserSlot(), None}; 
}



void UBeamInventoryApi::DeleteTransactionWithRetry(FUserSlot UserSlot, const FBeamRetryConfig& RetryConfig, UDeleteTransactionRequest* Request, const FOnDeleteTransactionSuccess& OnSuccess, const FOnDeleteTransactionError& OnError, const FOnDeleteTransactionComplete& OnComplete, FBeamRequestContext& OutRequestContext, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);	

	int64 OutRequestId;
	BP_DeleteTransactionImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, AuthenticatedUser.RealmHandle, -1, UserSlot, None}; 
}

		
void UBeamInventoryApi::PutTransferWithRetry(FUserSlot UserSlot, const FBeamRetryConfig& RetryConfig, UPutTransferRequest* Request, const FOnPutTransferSuccess& OnSuccess, const FOnPutTransferError& OnError, const FOnPutTransferComplete& OnComplete, FBeamRequestContext& OutRequestContext, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);	

	int64 OutRequestId;
	BP_PutTransferImpl(AuthenticatedUser.RealmHandle, RetryConfig, AuthenticatedUser.AuthToken, Backend->CurrentConnectivityStatus, Request, OnSuccess, OnError, OnComplete, OutRequestId);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, AuthenticatedUser.RealmHandle, -1, UserSlot, None}; 
}


