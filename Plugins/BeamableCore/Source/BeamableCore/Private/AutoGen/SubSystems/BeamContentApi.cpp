
#include "BeamableCore/Public/AutoGen/SubSystems/BeamContentApi.h"
#include "BeamCoreSettings.h"


void UBeamContentApi::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Backend = Cast<UBeamBackend>(Collection.InitializeDependency(UBeamBackend::StaticClass()));
	RequestTracker = Cast<UBeamRequestTracker>(Collection.InitializeDependency(UBeamRequestTracker::StaticClass()));
	ResponseCache = Cast<UBeamResponseCache>(Collection.InitializeDependency(UBeamResponseCache::StaticClass()));
	
}

void UBeamContentApi::Deinitialize()
{
	Super::Deinitialize();
}


void UBeamContentApi::BP_GetManifestPublicJsonImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, UGetManifestPublicJsonRequest* RequestData,
                                                  const FOnGetManifestPublicJsonSuccess& OnSuccess, const FOnGetManifestPublicJsonError& OnError, const FOnGetManifestPublicJsonComplete& OnComplete,
                                                  int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);

	// If cached...
	if(FString CachedResponse; ResponseCache->TryHitResponseCache(RequestData, Request, CallingContext,  CachedResponse))
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Found data in cache.REQUEST_TYPE=%s\\n%s"), *RequestData->GetRequestType().Name, *CachedResponse);
		Backend->RunBlueprintRequestProcessor<UGetManifestPublicJsonRequest, UClientManifestJsonResponse, FOnGetManifestPublicJsonSuccess, FOnGetManifestPublicJsonError, FOnGetManifestPublicJsonComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{			
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UGetManifestPublicJsonRequest, UClientManifestJsonResponse, FOnGetManifestPublicJsonSuccess, FOnGetManifestPublicJsonError, FOnGetManifestPublicJsonComplete>
			(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
		Backend->SendPreparedRequest(OutRequestId, CallingContext);		
	}	
}

void UBeamContentApi::CPP_GetManifestPublicJsonImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, 
                                               UGetManifestPublicJsonRequest* RequestData, const FOnGetManifestPublicJsonFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);

	// If cached...
	if(FString CachedResponse; ResponseCache->TryHitResponseCache(RequestData, Request, CallingContext,  CachedResponse))
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Found data in cache.REQUEST_TYPE=%s\\n%s"), *RequestData->GetRequestType().Name, *CachedResponse);
		Backend->RunCodeRequestProcessor<UGetManifestPublicJsonRequest, UClientManifestJsonResponse>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, RequestData, Handler);			
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UGetManifestPublicJsonRequest, UClientManifestJsonResponse>
			(OutRequestId, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamContentApi::BP_GetManifestChecksumImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, UGetManifestChecksumRequest* RequestData,
                                                  const FOnGetManifestChecksumSuccess& OnSuccess, const FOnGetManifestChecksumError& OnError, const FOnGetManifestChecksumComplete& OnComplete,
                                                  int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);

	// If cached...
	if(FString CachedResponse; ResponseCache->TryHitResponseCache(RequestData, Request, CallingContext,  CachedResponse))
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Found data in cache.REQUEST_TYPE=%s\\n%s"), *RequestData->GetRequestType().Name, *CachedResponse);
		Backend->RunBlueprintRequestProcessor<UGetManifestChecksumRequest, UContentBasicManifestChecksum, FOnGetManifestChecksumSuccess, FOnGetManifestChecksumError, FOnGetManifestChecksumComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{			
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeBlueprintRequestProcessor<UGetManifestChecksumRequest, UContentBasicManifestChecksum, FOnGetManifestChecksumSuccess, FOnGetManifestChecksumError, FOnGetManifestChecksumComplete>
			(OutRequestId, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
		Backend->SendPreparedRequest(OutRequestId, CallingContext);		
	}	
}

void UBeamContentApi::CPP_GetManifestChecksumImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, 
                                               UGetManifestChecksumRequest* RequestData, const FOnGetManifestChecksumFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateRequest(OutRequestId, TargetRealm, RetryConfig, RequestData);

	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);

	// If cached...
	if(FString CachedResponse; ResponseCache->TryHitResponseCache(RequestData, Request, CallingContext,  CachedResponse))
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Found data in cache.REQUEST_TYPE=%s\\n%s"), *RequestData->GetRequestType().Name, *CachedResponse);
		Backend->RunCodeRequestProcessor<UGetManifestChecksumRequest, UContentBasicManifestChecksum>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, RequestData, Handler);			
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UGetManifestChecksumRequest, UContentBasicManifestChecksum>
			(OutRequestId, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}



void UBeamContentApi::BP_PostManifestsUnarchiveImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UPostManifestsUnarchiveRequest* RequestData, const FOnPostManifestsUnarchiveSuccess& OnSuccess, const FOnPostManifestsUnarchiveError& OnError, const FOnPostManifestsUnarchiveComplete& OnComplete, 
								int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);

	// If cached...
	if(FString CachedResponse; ResponseCache->TryHitResponseCache(RequestData, Request, CallingContext,  CachedResponse))
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Found data in cache.REQUEST_TYPE=%s\\n%s"), *RequestData->GetRequestType().Name, *CachedResponse);
		Backend->RunAuthenticatedBlueprintRequestProcessor<UPostManifestsUnarchiveRequest, UEmptyResponse, FOnPostManifestsUnarchiveSuccess, FOnPostManifestsUnarchiveError, FOnPostManifestsUnarchiveComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPostManifestsUnarchiveRequest, UEmptyResponse, FOnPostManifestsUnarchiveSuccess, FOnPostManifestsUnarchiveError, FOnPostManifestsUnarchiveComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamContentApi::CPP_PostManifestsUnarchiveImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UPostManifestsUnarchiveRequest* RequestData, const FOnPostManifestsUnarchiveFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);
	
	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);

	// If cached...
	if(FString CachedResponse; ResponseCache->TryHitResponseCache(RequestData, Request, CallingContext,  CachedResponse))
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Found data in cache.REQUEST_TYPE=%s\\n%s"), *RequestData->GetRequestType().Name, *CachedResponse);
		Backend->RunAuthenticatedCodeRequestProcessor<UPostManifestsUnarchiveRequest, UEmptyResponse>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPostManifestsUnarchiveRequest, UEmptyResponse>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamContentApi::BP_PostManifestPullImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UBasicContentPostManifestPullRequest* RequestData, const FOnBasicContentPostManifestPullSuccess& OnSuccess, const FOnBasicContentPostManifestPullError& OnError, const FOnBasicContentPostManifestPullComplete& OnComplete, 
								int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);

	// If cached...
	if(FString CachedResponse; ResponseCache->TryHitResponseCache(RequestData, Request, CallingContext,  CachedResponse))
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Found data in cache.REQUEST_TYPE=%s\\n%s"), *RequestData->GetRequestType().Name, *CachedResponse);
		Backend->RunAuthenticatedBlueprintRequestProcessor<UBasicContentPostManifestPullRequest, UContentBasicManifest, FOnBasicContentPostManifestPullSuccess, FOnBasicContentPostManifestPullError, FOnBasicContentPostManifestPullComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UBasicContentPostManifestPullRequest, UContentBasicManifest, FOnBasicContentPostManifestPullSuccess, FOnBasicContentPostManifestPullError, FOnBasicContentPostManifestPullComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamContentApi::CPP_PostManifestPullImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UBasicContentPostManifestPullRequest* RequestData, const FOnBasicContentPostManifestPullFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);
	
	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);

	// If cached...
	if(FString CachedResponse; ResponseCache->TryHitResponseCache(RequestData, Request, CallingContext,  CachedResponse))
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Found data in cache.REQUEST_TYPE=%s\\n%s"), *RequestData->GetRequestType().Name, *CachedResponse);
		Backend->RunAuthenticatedCodeRequestProcessor<UBasicContentPostManifestPullRequest, UContentBasicManifest>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UBasicContentPostManifestPullRequest, UContentBasicManifest>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamContentApi::BP_GetManifestHistoryImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UGetManifestHistoryRequest* RequestData, const FOnGetManifestHistorySuccess& OnSuccess, const FOnGetManifestHistoryError& OnError, const FOnGetManifestHistoryComplete& OnComplete, 
								int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);

	// If cached...
	if(FString CachedResponse; ResponseCache->TryHitResponseCache(RequestData, Request, CallingContext,  CachedResponse))
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Found data in cache.REQUEST_TYPE=%s\\n%s"), *RequestData->GetRequestType().Name, *CachedResponse);
		Backend->RunAuthenticatedBlueprintRequestProcessor<UGetManifestHistoryRequest, UGetManifestHistoryResponse, FOnGetManifestHistorySuccess, FOnGetManifestHistoryError, FOnGetManifestHistoryComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UGetManifestHistoryRequest, UGetManifestHistoryResponse, FOnGetManifestHistorySuccess, FOnGetManifestHistoryError, FOnGetManifestHistoryComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamContentApi::CPP_GetManifestHistoryImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UGetManifestHistoryRequest* RequestData, const FOnGetManifestHistoryFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);
	
	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);

	// If cached...
	if(FString CachedResponse; ResponseCache->TryHitResponseCache(RequestData, Request, CallingContext,  CachedResponse))
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Found data in cache.REQUEST_TYPE=%s\\n%s"), *RequestData->GetRequestType().Name, *CachedResponse);
		Backend->RunAuthenticatedCodeRequestProcessor<UGetManifestHistoryRequest, UGetManifestHistoryResponse>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UGetManifestHistoryRequest, UGetManifestHistoryResponse>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamContentApi::BP_PostBinaryImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UPostBinaryRequest* RequestData, const FOnPostBinarySuccess& OnSuccess, const FOnPostBinaryError& OnError, const FOnPostBinaryComplete& OnComplete, 
								int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);

	// If cached...
	if(FString CachedResponse; ResponseCache->TryHitResponseCache(RequestData, Request, CallingContext,  CachedResponse))
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Found data in cache.REQUEST_TYPE=%s\\n%s"), *RequestData->GetRequestType().Name, *CachedResponse);
		Backend->RunAuthenticatedBlueprintRequestProcessor<UPostBinaryRequest, USaveBinaryResponse, FOnPostBinarySuccess, FOnPostBinaryError, FOnPostBinaryComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPostBinaryRequest, USaveBinaryResponse, FOnPostBinarySuccess, FOnPostBinaryError, FOnPostBinaryComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamContentApi::CPP_PostBinaryImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UPostBinaryRequest* RequestData, const FOnPostBinaryFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);
	
	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);

	// If cached...
	if(FString CachedResponse; ResponseCache->TryHitResponseCache(RequestData, Request, CallingContext,  CachedResponse))
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Found data in cache.REQUEST_TYPE=%s\\n%s"), *RequestData->GetRequestType().Name, *CachedResponse);
		Backend->RunAuthenticatedCodeRequestProcessor<UPostBinaryRequest, USaveBinaryResponse>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPostBinaryRequest, USaveBinaryResponse>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamContentApi::BP_PostManifestsPullImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UPostManifestsPullRequest* RequestData, const FOnPostManifestsPullSuccess& OnSuccess, const FOnPostManifestsPullError& OnError, const FOnPostManifestsPullComplete& OnComplete, 
								int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);

	// If cached...
	if(FString CachedResponse; ResponseCache->TryHitResponseCache(RequestData, Request, CallingContext,  CachedResponse))
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Found data in cache.REQUEST_TYPE=%s\\n%s"), *RequestData->GetRequestType().Name, *CachedResponse);
		Backend->RunAuthenticatedBlueprintRequestProcessor<UPostManifestsPullRequest, UManifestChecksums, FOnPostManifestsPullSuccess, FOnPostManifestsPullError, FOnPostManifestsPullComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPostManifestsPullRequest, UManifestChecksums, FOnPostManifestsPullSuccess, FOnPostManifestsPullError, FOnPostManifestsPullComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamContentApi::CPP_PostManifestsPullImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UPostManifestsPullRequest* RequestData, const FOnPostManifestsPullFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);
	
	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);

	// If cached...
	if(FString CachedResponse; ResponseCache->TryHitResponseCache(RequestData, Request, CallingContext,  CachedResponse))
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Found data in cache.REQUEST_TYPE=%s\\n%s"), *RequestData->GetRequestType().Name, *CachedResponse);
		Backend->RunAuthenticatedCodeRequestProcessor<UPostManifestsPullRequest, UManifestChecksums>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPostManifestsPullRequest, UManifestChecksums>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamContentApi::BP_GetContentImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UBasicContentGetContentRequest* RequestData, const FOnBasicContentGetContentSuccess& OnSuccess, const FOnBasicContentGetContentError& OnError, const FOnBasicContentGetContentComplete& OnComplete, 
								int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);

	// If cached...
	if(FString CachedResponse; ResponseCache->TryHitResponseCache(RequestData, Request, CallingContext,  CachedResponse))
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Found data in cache.REQUEST_TYPE=%s\\n%s"), *RequestData->GetRequestType().Name, *CachedResponse);
		Backend->RunAuthenticatedBlueprintRequestProcessor<UBasicContentGetContentRequest, UContentOrText, FOnBasicContentGetContentSuccess, FOnBasicContentGetContentError, FOnBasicContentGetContentComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UBasicContentGetContentRequest, UContentOrText, FOnBasicContentGetContentSuccess, FOnBasicContentGetContentError, FOnBasicContentGetContentComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamContentApi::CPP_GetContentImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UBasicContentGetContentRequest* RequestData, const FOnBasicContentGetContentFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);
	
	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);

	// If cached...
	if(FString CachedResponse; ResponseCache->TryHitResponseCache(RequestData, Request, CallingContext,  CachedResponse))
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Found data in cache.REQUEST_TYPE=%s\\n%s"), *RequestData->GetRequestType().Name, *CachedResponse);
		Backend->RunAuthenticatedCodeRequestProcessor<UBasicContentGetContentRequest, UContentOrText>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UBasicContentGetContentRequest, UContentOrText>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamContentApi::BP_GetLocalizationsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UGetLocalizationsRequest* RequestData, const FOnGetLocalizationsSuccess& OnSuccess, const FOnGetLocalizationsError& OnError, const FOnGetLocalizationsComplete& OnComplete, 
								int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);

	// If cached...
	if(FString CachedResponse; ResponseCache->TryHitResponseCache(RequestData, Request, CallingContext,  CachedResponse))
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Found data in cache.REQUEST_TYPE=%s\\n%s"), *RequestData->GetRequestType().Name, *CachedResponse);
		Backend->RunAuthenticatedBlueprintRequestProcessor<UGetLocalizationsRequest, UGetLocalizationsResponse, FOnGetLocalizationsSuccess, FOnGetLocalizationsError, FOnGetLocalizationsComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UGetLocalizationsRequest, UGetLocalizationsResponse, FOnGetLocalizationsSuccess, FOnGetLocalizationsError, FOnGetLocalizationsComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamContentApi::CPP_GetLocalizationsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UGetLocalizationsRequest* RequestData, const FOnGetLocalizationsFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);
	
	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);

	// If cached...
	if(FString CachedResponse; ResponseCache->TryHitResponseCache(RequestData, Request, CallingContext,  CachedResponse))
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Found data in cache.REQUEST_TYPE=%s\\n%s"), *RequestData->GetRequestType().Name, *CachedResponse);
		Backend->RunAuthenticatedCodeRequestProcessor<UGetLocalizationsRequest, UGetLocalizationsResponse>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UGetLocalizationsRequest, UGetLocalizationsResponse>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamContentApi::BP_PutLocalizationsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UPutLocalizationsRequest* RequestData, const FOnPutLocalizationsSuccess& OnSuccess, const FOnPutLocalizationsError& OnError, const FOnPutLocalizationsComplete& OnComplete, 
								int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);

	// If cached...
	if(FString CachedResponse; ResponseCache->TryHitResponseCache(RequestData, Request, CallingContext,  CachedResponse))
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Found data in cache.REQUEST_TYPE=%s\\n%s"), *RequestData->GetRequestType().Name, *CachedResponse);
		Backend->RunAuthenticatedBlueprintRequestProcessor<UPutLocalizationsRequest, UCommonResponse, FOnPutLocalizationsSuccess, FOnPutLocalizationsError, FOnPutLocalizationsComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPutLocalizationsRequest, UCommonResponse, FOnPutLocalizationsSuccess, FOnPutLocalizationsError, FOnPutLocalizationsComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamContentApi::CPP_PutLocalizationsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UPutLocalizationsRequest* RequestData, const FOnPutLocalizationsFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);
	
	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);

	// If cached...
	if(FString CachedResponse; ResponseCache->TryHitResponseCache(RequestData, Request, CallingContext,  CachedResponse))
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Found data in cache.REQUEST_TYPE=%s\\n%s"), *RequestData->GetRequestType().Name, *CachedResponse);
		Backend->RunAuthenticatedCodeRequestProcessor<UPutLocalizationsRequest, UCommonResponse>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPutLocalizationsRequest, UCommonResponse>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamContentApi::BP_DeleteLocalizationsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UDeleteLocalizationsRequest* RequestData, const FOnDeleteLocalizationsSuccess& OnSuccess, const FOnDeleteLocalizationsError& OnError, const FOnDeleteLocalizationsComplete& OnComplete, 
								int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);

	// If cached...
	if(FString CachedResponse; ResponseCache->TryHitResponseCache(RequestData, Request, CallingContext,  CachedResponse))
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Found data in cache.REQUEST_TYPE=%s\\n%s"), *RequestData->GetRequestType().Name, *CachedResponse);
		Backend->RunAuthenticatedBlueprintRequestProcessor<UDeleteLocalizationsRequest, UCommonResponse, FOnDeleteLocalizationsSuccess, FOnDeleteLocalizationsError, FOnDeleteLocalizationsComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UDeleteLocalizationsRequest, UCommonResponse, FOnDeleteLocalizationsSuccess, FOnDeleteLocalizationsError, FOnDeleteLocalizationsComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamContentApi::CPP_DeleteLocalizationsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UDeleteLocalizationsRequest* RequestData, const FOnDeleteLocalizationsFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);
	
	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);

	// If cached...
	if(FString CachedResponse; ResponseCache->TryHitResponseCache(RequestData, Request, CallingContext,  CachedResponse))
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Found data in cache.REQUEST_TYPE=%s\\n%s"), *RequestData->GetRequestType().Name, *CachedResponse);
		Backend->RunAuthenticatedCodeRequestProcessor<UDeleteLocalizationsRequest, UCommonResponse>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UDeleteLocalizationsRequest, UCommonResponse>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamContentApi::BP_PostTextImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UPostTextRequest* RequestData, const FOnPostTextSuccess& OnSuccess, const FOnPostTextError& OnError, const FOnPostTextComplete& OnComplete, 
								int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);

	// If cached...
	if(FString CachedResponse; ResponseCache->TryHitResponseCache(RequestData, Request, CallingContext,  CachedResponse))
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Found data in cache.REQUEST_TYPE=%s\\n%s"), *RequestData->GetRequestType().Name, *CachedResponse);
		Backend->RunAuthenticatedBlueprintRequestProcessor<UPostTextRequest, USaveTextResponse, FOnPostTextSuccess, FOnPostTextError, FOnPostTextComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPostTextRequest, USaveTextResponse, FOnPostTextSuccess, FOnPostTextError, FOnPostTextComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamContentApi::CPP_PostTextImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UPostTextRequest* RequestData, const FOnPostTextFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);
	
	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);

	// If cached...
	if(FString CachedResponse; ResponseCache->TryHitResponseCache(RequestData, Request, CallingContext,  CachedResponse))
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Found data in cache.REQUEST_TYPE=%s\\n%s"), *RequestData->GetRequestType().Name, *CachedResponse);
		Backend->RunAuthenticatedCodeRequestProcessor<UPostTextRequest, USaveTextResponse>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPostTextRequest, USaveTextResponse>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamContentApi::BP_GetManifestExactImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UGetManifestExactRequest* RequestData, const FOnGetManifestExactSuccess& OnSuccess, const FOnGetManifestExactError& OnError, const FOnGetManifestExactComplete& OnComplete, 
								int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);

	// If cached...
	if(FString CachedResponse; ResponseCache->TryHitResponseCache(RequestData, Request, CallingContext,  CachedResponse))
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Found data in cache.REQUEST_TYPE=%s\\n%s"), *RequestData->GetRequestType().Name, *CachedResponse);
		Backend->RunAuthenticatedBlueprintRequestProcessor<UGetManifestExactRequest, UContentBasicManifest, FOnGetManifestExactSuccess, FOnGetManifestExactError, FOnGetManifestExactComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UGetManifestExactRequest, UContentBasicManifest, FOnGetManifestExactSuccess, FOnGetManifestExactError, FOnGetManifestExactComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamContentApi::CPP_GetManifestExactImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UGetManifestExactRequest* RequestData, const FOnGetManifestExactFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);
	
	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);

	// If cached...
	if(FString CachedResponse; ResponseCache->TryHitResponseCache(RequestData, Request, CallingContext,  CachedResponse))
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Found data in cache.REQUEST_TYPE=%s\\n%s"), *RequestData->GetRequestType().Name, *CachedResponse);
		Backend->RunAuthenticatedCodeRequestProcessor<UGetManifestExactRequest, UContentBasicManifest>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UGetManifestExactRequest, UContentBasicManifest>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamContentApi::BP_GetManifestImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UBasicContentGetManifestRequest* RequestData, const FOnBasicContentGetManifestSuccess& OnSuccess, const FOnBasicContentGetManifestError& OnError, const FOnBasicContentGetManifestComplete& OnComplete, 
								int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);

	// If cached...
	if(FString CachedResponse; ResponseCache->TryHitResponseCache(RequestData, Request, CallingContext,  CachedResponse))
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Found data in cache.REQUEST_TYPE=%s\\n%s"), *RequestData->GetRequestType().Name, *CachedResponse);
		Backend->RunAuthenticatedBlueprintRequestProcessor<UBasicContentGetManifestRequest, UContentBasicManifest, FOnBasicContentGetManifestSuccess, FOnBasicContentGetManifestError, FOnBasicContentGetManifestComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UBasicContentGetManifestRequest, UContentBasicManifest, FOnBasicContentGetManifestSuccess, FOnBasicContentGetManifestError, FOnBasicContentGetManifestComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamContentApi::CPP_GetManifestImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UBasicContentGetManifestRequest* RequestData, const FOnBasicContentGetManifestFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);
	
	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);

	// If cached...
	if(FString CachedResponse; ResponseCache->TryHitResponseCache(RequestData, Request, CallingContext,  CachedResponse))
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Found data in cache.REQUEST_TYPE=%s\\n%s"), *RequestData->GetRequestType().Name, *CachedResponse);
		Backend->RunAuthenticatedCodeRequestProcessor<UBasicContentGetManifestRequest, UContentBasicManifest>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UBasicContentGetManifestRequest, UContentBasicManifest>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamContentApi::BP_PostManifestImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UBasicContentPostManifestRequest* RequestData, const FOnBasicContentPostManifestSuccess& OnSuccess, const FOnBasicContentPostManifestError& OnError, const FOnBasicContentPostManifestComplete& OnComplete, 
								int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);

	// If cached...
	if(FString CachedResponse; ResponseCache->TryHitResponseCache(RequestData, Request, CallingContext,  CachedResponse))
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Found data in cache.REQUEST_TYPE=%s\\n%s"), *RequestData->GetRequestType().Name, *CachedResponse);
		Backend->RunAuthenticatedBlueprintRequestProcessor<UBasicContentPostManifestRequest, UContentBasicManifest, FOnBasicContentPostManifestSuccess, FOnBasicContentPostManifestError, FOnBasicContentPostManifestComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UBasicContentPostManifestRequest, UContentBasicManifest, FOnBasicContentPostManifestSuccess, FOnBasicContentPostManifestError, FOnBasicContentPostManifestComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamContentApi::CPP_PostManifestImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UBasicContentPostManifestRequest* RequestData, const FOnBasicContentPostManifestFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);
	
	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);

	// If cached...
	if(FString CachedResponse; ResponseCache->TryHitResponseCache(RequestData, Request, CallingContext,  CachedResponse))
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Found data in cache.REQUEST_TYPE=%s\\n%s"), *RequestData->GetRequestType().Name, *CachedResponse);
		Backend->RunAuthenticatedCodeRequestProcessor<UBasicContentPostManifestRequest, UContentBasicManifest>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UBasicContentPostManifestRequest, UContentBasicManifest>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamContentApi::BP_PostManifestsArchiveImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UPostManifestsArchiveRequest* RequestData, const FOnPostManifestsArchiveSuccess& OnSuccess, const FOnPostManifestsArchiveError& OnError, const FOnPostManifestsArchiveComplete& OnComplete, 
								int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);

	// If cached...
	if(FString CachedResponse; ResponseCache->TryHitResponseCache(RequestData, Request, CallingContext,  CachedResponse))
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Found data in cache.REQUEST_TYPE=%s\\n%s"), *RequestData->GetRequestType().Name, *CachedResponse);
		Backend->RunAuthenticatedBlueprintRequestProcessor<UPostManifestsArchiveRequest, UEmptyResponse, FOnPostManifestsArchiveSuccess, FOnPostManifestsArchiveError, FOnPostManifestsArchiveComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPostManifestsArchiveRequest, UEmptyResponse, FOnPostManifestsArchiveSuccess, FOnPostManifestsArchiveError, FOnPostManifestsArchiveComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamContentApi::CPP_PostManifestsArchiveImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UPostManifestsArchiveRequest* RequestData, const FOnPostManifestsArchiveFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);
	
	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);

	// If cached...
	if(FString CachedResponse; ResponseCache->TryHitResponseCache(RequestData, Request, CallingContext,  CachedResponse))
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Found data in cache.REQUEST_TYPE=%s\\n%s"), *RequestData->GetRequestType().Name, *CachedResponse);
		Backend->RunAuthenticatedCodeRequestProcessor<UPostManifestsArchiveRequest, UEmptyResponse>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPostManifestsArchiveRequest, UEmptyResponse>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamContentApi::BP_PostContentImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UPostContentRequest* RequestData, const FOnPostContentSuccess& OnSuccess, const FOnPostContentError& OnError, const FOnPostContentComplete& OnComplete, 
								int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);

	// If cached...
	if(FString CachedResponse; ResponseCache->TryHitResponseCache(RequestData, Request, CallingContext,  CachedResponse))
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Found data in cache.REQUEST_TYPE=%s\\n%s"), *RequestData->GetRequestType().Name, *CachedResponse);
		Backend->RunAuthenticatedBlueprintRequestProcessor<UPostContentRequest, USaveContentResponse, FOnPostContentSuccess, FOnPostContentError, FOnPostContentComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPostContentRequest, USaveContentResponse, FOnPostContentSuccess, FOnPostContentError, FOnPostContentComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamContentApi::CPP_PostContentImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UPostContentRequest* RequestData, const FOnPostContentFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);
	
	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);

	// If cached...
	if(FString CachedResponse; ResponseCache->TryHitResponseCache(RequestData, Request, CallingContext,  CachedResponse))
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Found data in cache.REQUEST_TYPE=%s\\n%s"), *RequestData->GetRequestType().Name, *CachedResponse);
		Backend->RunAuthenticatedCodeRequestProcessor<UPostContentRequest, USaveContentResponse>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPostContentRequest, USaveContentResponse>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamContentApi::BP_PutManifestRepeatImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UPutManifestRepeatRequest* RequestData, const FOnPutManifestRepeatSuccess& OnSuccess, const FOnPutManifestRepeatError& OnError, const FOnPutManifestRepeatComplete& OnComplete, 
								int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);

	// If cached...
	if(FString CachedResponse; ResponseCache->TryHitResponseCache(RequestData, Request, CallingContext,  CachedResponse))
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Found data in cache.REQUEST_TYPE=%s\\n%s"), *RequestData->GetRequestType().Name, *CachedResponse);
		Backend->RunAuthenticatedBlueprintRequestProcessor<UPutManifestRepeatRequest, UCommonResponse, FOnPutManifestRepeatSuccess, FOnPutManifestRepeatError, FOnPutManifestRepeatComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPutManifestRepeatRequest, UCommonResponse, FOnPutManifestRepeatSuccess, FOnPutManifestRepeatError, FOnPutManifestRepeatComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamContentApi::CPP_PutManifestRepeatImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UPutManifestRepeatRequest* RequestData, const FOnPutManifestRepeatFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);
	
	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);

	// If cached...
	if(FString CachedResponse; ResponseCache->TryHitResponseCache(RequestData, Request, CallingContext,  CachedResponse))
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Found data in cache.REQUEST_TYPE=%s\\n%s"), *RequestData->GetRequestType().Name, *CachedResponse);
		Backend->RunAuthenticatedCodeRequestProcessor<UPutManifestRepeatRequest, UCommonResponse>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPutManifestRepeatRequest, UCommonResponse>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamContentApi::BP_GetManifestPrivateJsonImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UGetManifestPrivateJsonRequest* RequestData, const FOnGetManifestPrivateJsonSuccess& OnSuccess, const FOnGetManifestPrivateJsonError& OnError, const FOnGetManifestPrivateJsonComplete& OnComplete, 
								int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);

	// If cached...
	if(FString CachedResponse; ResponseCache->TryHitResponseCache(RequestData, Request, CallingContext,  CachedResponse))
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Found data in cache.REQUEST_TYPE=%s\\n%s"), *RequestData->GetRequestType().Name, *CachedResponse);
		Backend->RunAuthenticatedBlueprintRequestProcessor<UGetManifestPrivateJsonRequest, UClientManifestJsonResponse, FOnGetManifestPrivateJsonSuccess, FOnGetManifestPrivateJsonError, FOnGetManifestPrivateJsonComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UGetManifestPrivateJsonRequest, UClientManifestJsonResponse, FOnGetManifestPrivateJsonSuccess, FOnGetManifestPrivateJsonError, FOnGetManifestPrivateJsonComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamContentApi::CPP_GetManifestPrivateJsonImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UGetManifestPrivateJsonRequest* RequestData, const FOnGetManifestPrivateJsonFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);
	
	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);

	// If cached...
	if(FString CachedResponse; ResponseCache->TryHitResponseCache(RequestData, Request, CallingContext,  CachedResponse))
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Found data in cache.REQUEST_TYPE=%s\\n%s"), *RequestData->GetRequestType().Name, *CachedResponse);
		Backend->RunAuthenticatedCodeRequestProcessor<UGetManifestPrivateJsonRequest, UClientManifestJsonResponse>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UGetManifestPrivateJsonRequest, UClientManifestJsonResponse>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamContentApi::BP_GetManifestChecksumsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UGetManifestChecksumsRequest* RequestData, const FOnGetManifestChecksumsSuccess& OnSuccess, const FOnGetManifestChecksumsError& OnError, const FOnGetManifestChecksumsComplete& OnComplete, 
								int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);

	// If cached...
	if(FString CachedResponse; ResponseCache->TryHitResponseCache(RequestData, Request, CallingContext,  CachedResponse))
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Found data in cache.REQUEST_TYPE=%s\\n%s"), *RequestData->GetRequestType().Name, *CachedResponse);
		Backend->RunAuthenticatedBlueprintRequestProcessor<UGetManifestChecksumsRequest, UManifestChecksums, FOnGetManifestChecksumsSuccess, FOnGetManifestChecksumsError, FOnGetManifestChecksumsComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UGetManifestChecksumsRequest, UManifestChecksums, FOnGetManifestChecksumsSuccess, FOnGetManifestChecksumsError, FOnGetManifestChecksumsComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamContentApi::CPP_GetManifestChecksumsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UGetManifestChecksumsRequest* RequestData, const FOnGetManifestChecksumsFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);
	
	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);

	// If cached...
	if(FString CachedResponse; ResponseCache->TryHitResponseCache(RequestData, Request, CallingContext,  CachedResponse))
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Found data in cache.REQUEST_TYPE=%s\\n%s"), *RequestData->GetRequestType().Name, *CachedResponse);
		Backend->RunAuthenticatedCodeRequestProcessor<UGetManifestChecksumsRequest, UManifestChecksums>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UGetManifestChecksumsRequest, UManifestChecksums>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamContentApi::BP_GetManifestsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UBasicContentGetManifestsRequest* RequestData, const FOnBasicContentGetManifestsSuccess& OnSuccess, const FOnBasicContentGetManifestsError& OnError, const FOnBasicContentGetManifestsComplete& OnComplete, 
								int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...	
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);

	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);

	// If cached...
	if(FString CachedResponse; ResponseCache->TryHitResponseCache(RequestData, Request, CallingContext,  CachedResponse))
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Found data in cache.REQUEST_TYPE=%s\\n%s"), *RequestData->GetRequestType().Name, *CachedResponse);
		Backend->RunAuthenticatedBlueprintRequestProcessor<UBasicContentGetManifestsRequest, UGetManifestsResponse, FOnBasicContentGetManifestsSuccess, FOnBasicContentGetManifestsError, FOnBasicContentGetManifestsComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UBasicContentGetManifestsRequest, UGetManifestsResponse, FOnBasicContentGetManifestsSuccess, FOnBasicContentGetManifestsError, FOnBasicContentGetManifestsComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamContentApi::CPP_GetManifestsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UBasicContentGetManifestsRequest* RequestData, const FOnBasicContentGetManifestsFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	const auto Request = Backend->CreateAuthenticatedRequest(OutRequestId, TargetRealm, RetryConfig, AuthToken, RequestData);
	
	// If we are making this request as part of an operation, we add it to it.
	if(OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId);

	// If cached...
	if(FString CachedResponse; ResponseCache->TryHitResponseCache(RequestData, Request, CallingContext,  CachedResponse))
	{
		UE_LOG(LogBeamBackend, Verbose, TEXT("Found data in cache.REQUEST_TYPE=%s\\n%s"), *RequestData->GetRequestType().Name, *CachedResponse);
		Backend->RunAuthenticatedCodeRequestProcessor<UBasicContentGetManifestsRequest, UGetManifestsResponse>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UBasicContentGetManifestsRequest, UGetManifestsResponse>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}




void UBeamContentApi::CPP_GetManifestPublicJson(UGetManifestPublicJsonRequest* Request, const FOnGetManifestPublicJsonFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UGetManifestPublicJsonRequest::StaticClass()->GetName(), RetryConfig);
	
    int64 OutRequestId;
	CPP_GetManifestPublicJsonImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, FUserSlot(), AS_None};
}

		
void UBeamContentApi::CPP_GetManifestChecksum(UGetManifestChecksumRequest* Request, const FOnGetManifestChecksumFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UGetManifestChecksumRequest::StaticClass()->GetName(), RetryConfig);
	
    int64 OutRequestId;
	CPP_GetManifestChecksumImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, FUserSlot(), AS_None};
}



void UBeamContentApi::CPP_PostManifestsUnarchive(const FUserSlot& UserSlot, UPostManifestsUnarchiveRequest* Request, const FOnPostManifestsUnarchiveFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostManifestsUnarchiveRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_PostManifestsUnarchiveImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamContentApi::CPP_PostManifestPull(const FUserSlot& UserSlot, UBasicContentPostManifestPullRequest* Request, const FOnBasicContentPostManifestPullFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UBasicContentPostManifestPullRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_PostManifestPullImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamContentApi::CPP_GetManifestHistory(const FUserSlot& UserSlot, UGetManifestHistoryRequest* Request, const FOnGetManifestHistoryFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UGetManifestHistoryRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_GetManifestHistoryImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamContentApi::CPP_PostBinary(const FUserSlot& UserSlot, UPostBinaryRequest* Request, const FOnPostBinaryFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostBinaryRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_PostBinaryImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamContentApi::CPP_PostManifestsPull(const FUserSlot& UserSlot, UPostManifestsPullRequest* Request, const FOnPostManifestsPullFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostManifestsPullRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_PostManifestsPullImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamContentApi::CPP_GetContent(const FUserSlot& UserSlot, UBasicContentGetContentRequest* Request, const FOnBasicContentGetContentFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UBasicContentGetContentRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_GetContentImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamContentApi::CPP_GetLocalizations(const FUserSlot& UserSlot, UGetLocalizationsRequest* Request, const FOnGetLocalizationsFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UGetLocalizationsRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_GetLocalizationsImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamContentApi::CPP_PutLocalizations(const FUserSlot& UserSlot, UPutLocalizationsRequest* Request, const FOnPutLocalizationsFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPutLocalizationsRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_PutLocalizationsImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamContentApi::CPP_DeleteLocalizations(const FUserSlot& UserSlot, UDeleteLocalizationsRequest* Request, const FOnDeleteLocalizationsFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UDeleteLocalizationsRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_DeleteLocalizationsImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamContentApi::CPP_PostText(const FUserSlot& UserSlot, UPostTextRequest* Request, const FOnPostTextFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostTextRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_PostTextImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamContentApi::CPP_GetManifestExact(const FUserSlot& UserSlot, UGetManifestExactRequest* Request, const FOnGetManifestExactFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UGetManifestExactRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_GetManifestExactImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamContentApi::CPP_GetManifest(const FUserSlot& UserSlot, UBasicContentGetManifestRequest* Request, const FOnBasicContentGetManifestFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UBasicContentGetManifestRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_GetManifestImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamContentApi::CPP_PostManifest(const FUserSlot& UserSlot, UBasicContentPostManifestRequest* Request, const FOnBasicContentPostManifestFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UBasicContentPostManifestRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_PostManifestImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamContentApi::CPP_PostManifestsArchive(const FUserSlot& UserSlot, UPostManifestsArchiveRequest* Request, const FOnPostManifestsArchiveFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostManifestsArchiveRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_PostManifestsArchiveImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamContentApi::CPP_PostContent(const FUserSlot& UserSlot, UPostContentRequest* Request, const FOnPostContentFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostContentRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_PostContentImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamContentApi::CPP_PutManifestRepeat(const FUserSlot& UserSlot, UPutManifestRepeatRequest* Request, const FOnPutManifestRepeatFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPutManifestRepeatRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_PutManifestRepeatImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamContentApi::CPP_GetManifestPrivateJson(const FUserSlot& UserSlot, UGetManifestPrivateJsonRequest* Request, const FOnGetManifestPrivateJsonFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UGetManifestPrivateJsonRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_GetManifestPrivateJsonImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamContentApi::CPP_GetManifestChecksums(const FUserSlot& UserSlot, UGetManifestChecksumsRequest* Request, const FOnGetManifestChecksumsFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UGetManifestChecksumsRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_GetManifestChecksumsImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamContentApi::CPP_GetManifests(const FUserSlot& UserSlot, UBasicContentGetManifestsRequest* Request, const FOnBasicContentGetManifestsFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UBasicContentGetManifestsRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_GetManifestsImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}




void UBeamContentApi::GetManifestPublicJson(UGetManifestPublicJsonRequest* Request, const FOnGetManifestPublicJsonSuccess& OnSuccess, const FOnGetManifestPublicJsonError& OnError, const FOnGetManifestPublicJsonComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UGetManifestPublicJsonRequest::StaticClass()->GetName(), RetryConfig);	
	
	int64 OutRequestId = 0;
	BP_GetManifestPublicJsonImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, FUserSlot(), AS_None};
}

		
void UBeamContentApi::GetManifestChecksum(UGetManifestChecksumRequest* Request, const FOnGetManifestChecksumSuccess& OnSuccess, const FOnGetManifestChecksumError& OnError, const FOnGetManifestChecksumComplete& OnComplete, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...	
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(UGetManifestChecksumRequest::StaticClass()->GetName(), RetryConfig);	
	
	int64 OutRequestId = 0;
	BP_GetManifestChecksumImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, FUserSlot(), AS_None};
}



void UBeamContentApi::PostManifestsUnarchive(FUserSlot UserSlot, UPostManifestsUnarchiveRequest* Request, const FOnPostManifestsUnarchiveSuccess& OnSuccess, const FOnPostManifestsUnarchiveError& OnError, const FOnPostManifestsUnarchiveComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostManifestsUnarchiveRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_PostManifestsUnarchiveImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamContentApi::PostManifestPull(FUserSlot UserSlot, UBasicContentPostManifestPullRequest* Request, const FOnBasicContentPostManifestPullSuccess& OnSuccess, const FOnBasicContentPostManifestPullError& OnError, const FOnBasicContentPostManifestPullComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UBasicContentPostManifestPullRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_PostManifestPullImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamContentApi::GetManifestHistory(FUserSlot UserSlot, UGetManifestHistoryRequest* Request, const FOnGetManifestHistorySuccess& OnSuccess, const FOnGetManifestHistoryError& OnError, const FOnGetManifestHistoryComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UGetManifestHistoryRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_GetManifestHistoryImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamContentApi::PostBinary(FUserSlot UserSlot, UPostBinaryRequest* Request, const FOnPostBinarySuccess& OnSuccess, const FOnPostBinaryError& OnError, const FOnPostBinaryComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostBinaryRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_PostBinaryImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamContentApi::PostManifestsPull(FUserSlot UserSlot, UPostManifestsPullRequest* Request, const FOnPostManifestsPullSuccess& OnSuccess, const FOnPostManifestsPullError& OnError, const FOnPostManifestsPullComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostManifestsPullRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_PostManifestsPullImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamContentApi::GetContent(FUserSlot UserSlot, UBasicContentGetContentRequest* Request, const FOnBasicContentGetContentSuccess& OnSuccess, const FOnBasicContentGetContentError& OnError, const FOnBasicContentGetContentComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UBasicContentGetContentRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_GetContentImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamContentApi::GetLocalizations(FUserSlot UserSlot, UGetLocalizationsRequest* Request, const FOnGetLocalizationsSuccess& OnSuccess, const FOnGetLocalizationsError& OnError, const FOnGetLocalizationsComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UGetLocalizationsRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_GetLocalizationsImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamContentApi::PutLocalizations(FUserSlot UserSlot, UPutLocalizationsRequest* Request, const FOnPutLocalizationsSuccess& OnSuccess, const FOnPutLocalizationsError& OnError, const FOnPutLocalizationsComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPutLocalizationsRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_PutLocalizationsImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamContentApi::DeleteLocalizations(FUserSlot UserSlot, UDeleteLocalizationsRequest* Request, const FOnDeleteLocalizationsSuccess& OnSuccess, const FOnDeleteLocalizationsError& OnError, const FOnDeleteLocalizationsComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UDeleteLocalizationsRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_DeleteLocalizationsImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamContentApi::PostText(FUserSlot UserSlot, UPostTextRequest* Request, const FOnPostTextSuccess& OnSuccess, const FOnPostTextError& OnError, const FOnPostTextComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostTextRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_PostTextImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamContentApi::GetManifestExact(FUserSlot UserSlot, UGetManifestExactRequest* Request, const FOnGetManifestExactSuccess& OnSuccess, const FOnGetManifestExactError& OnError, const FOnGetManifestExactComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UGetManifestExactRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_GetManifestExactImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamContentApi::GetManifest(FUserSlot UserSlot, UBasicContentGetManifestRequest* Request, const FOnBasicContentGetManifestSuccess& OnSuccess, const FOnBasicContentGetManifestError& OnError, const FOnBasicContentGetManifestComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UBasicContentGetManifestRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_GetManifestImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamContentApi::PostManifest(FUserSlot UserSlot, UBasicContentPostManifestRequest* Request, const FOnBasicContentPostManifestSuccess& OnSuccess, const FOnBasicContentPostManifestError& OnError, const FOnBasicContentPostManifestComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UBasicContentPostManifestRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_PostManifestImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamContentApi::PostManifestsArchive(FUserSlot UserSlot, UPostManifestsArchiveRequest* Request, const FOnPostManifestsArchiveSuccess& OnSuccess, const FOnPostManifestsArchiveError& OnError, const FOnPostManifestsArchiveComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostManifestsArchiveRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_PostManifestsArchiveImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamContentApi::PostContent(FUserSlot UserSlot, UPostContentRequest* Request, const FOnPostContentSuccess& OnSuccess, const FOnPostContentError& OnError, const FOnPostContentComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostContentRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_PostContentImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamContentApi::PutManifestRepeat(FUserSlot UserSlot, UPutManifestRepeatRequest* Request, const FOnPutManifestRepeatSuccess& OnSuccess, const FOnPutManifestRepeatError& OnError, const FOnPutManifestRepeatComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPutManifestRepeatRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_PutManifestRepeatImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamContentApi::GetManifestPrivateJson(FUserSlot UserSlot, UGetManifestPrivateJsonRequest* Request, const FOnGetManifestPrivateJsonSuccess& OnSuccess, const FOnGetManifestPrivateJsonError& OnError, const FOnGetManifestPrivateJsonComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UGetManifestPrivateJsonRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_GetManifestPrivateJsonImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamContentApi::GetManifestChecksums(FUserSlot UserSlot, UGetManifestChecksumsRequest* Request, const FOnGetManifestChecksumsSuccess& OnSuccess, const FOnGetManifestChecksumsError& OnError, const FOnGetManifestChecksumsComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UGetManifestChecksumsRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_GetManifestChecksumsImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamContentApi::GetManifests(FUserSlot UserSlot, UBasicContentGetManifestsRequest* Request, const FOnBasicContentGetManifestsSuccess& OnSuccess, const FOnBasicContentGetManifestsError& OnError, const FOnBasicContentGetManifestsComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UBasicContentGetManifestsRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_GetManifestsImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

