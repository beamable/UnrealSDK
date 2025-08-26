
#include "BeamableCore/Public/AutoGen/SubSystems/BeamBeamoApi.h"
#include "BeamCoreSettings.h"


void UBeamBeamoApi::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Backend = Cast<UBeamBackend>(Collection.InitializeDependency(UBeamBackend::StaticClass()));
	RequestTracker = Cast<UBeamRequestTracker>(Collection.InitializeDependency(UBeamRequestTracker::StaticClass()));
	ResponseCache = Cast<UBeamResponseCache>(Collection.InitializeDependency(UBeamResponseCache::StaticClass()));
	
}

void UBeamBeamoApi::Deinitialize()
{
	Super::Deinitialize();
}




void UBeamBeamoApi::BP_PostManifestsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UPostManifestsRequest* RequestData, const FOnPostManifestsSuccess& OnSuccess, const FOnPostManifestsError& OnError, const FOnPostManifestsComplete& OnComplete, 
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
		Backend->RunAuthenticatedBlueprintRequestProcessor<UPostManifestsRequest, UBeamoV2ManifestChecksum, FOnPostManifestsSuccess, FOnPostManifestsError, FOnPostManifestsComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPostManifestsRequest, UBeamoV2ManifestChecksum, FOnPostManifestsSuccess, FOnPostManifestsError, FOnPostManifestsComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamBeamoApi::CPP_PostManifestsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UPostManifestsRequest* RequestData, const FOnPostManifestsFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
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
		Backend->RunAuthenticatedCodeRequestProcessor<UPostManifestsRequest, UBeamoV2ManifestChecksum>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPostManifestsRequest, UBeamoV2ManifestChecksum>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamBeamoApi::BP_ApiBeamoGetManifestsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UApiBeamoGetManifestsRequest* RequestData, const FOnApiBeamoGetManifestsSuccess& OnSuccess, const FOnApiBeamoGetManifestsError& OnError, const FOnApiBeamoGetManifestsComplete& OnComplete, 
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
		Backend->RunAuthenticatedBlueprintRequestProcessor<UApiBeamoGetManifestsRequest, UBeamoV2GetManifestsResponse, FOnApiBeamoGetManifestsSuccess, FOnApiBeamoGetManifestsError, FOnApiBeamoGetManifestsComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UApiBeamoGetManifestsRequest, UBeamoV2GetManifestsResponse, FOnApiBeamoGetManifestsSuccess, FOnApiBeamoGetManifestsError, FOnApiBeamoGetManifestsComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamBeamoApi::CPP_ApiBeamoGetManifestsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UApiBeamoGetManifestsRequest* RequestData, const FOnApiBeamoGetManifestsFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
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
		Backend->RunAuthenticatedCodeRequestProcessor<UApiBeamoGetManifestsRequest, UBeamoV2GetManifestsResponse>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UApiBeamoGetManifestsRequest, UBeamoV2GetManifestsResponse>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamBeamoApi::BP_ApiBeamoGetManifestsByManifestIdImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UApiBeamoGetManifestsByManifestIdRequest* RequestData, const FOnApiBeamoGetManifestsByManifestIdSuccess& OnSuccess, const FOnApiBeamoGetManifestsByManifestIdError& OnError, const FOnApiBeamoGetManifestsByManifestIdComplete& OnComplete, 
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
		Backend->RunAuthenticatedBlueprintRequestProcessor<UApiBeamoGetManifestsByManifestIdRequest, UBeamoV2Manifest, FOnApiBeamoGetManifestsByManifestIdSuccess, FOnApiBeamoGetManifestsByManifestIdError, FOnApiBeamoGetManifestsByManifestIdComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UApiBeamoGetManifestsByManifestIdRequest, UBeamoV2Manifest, FOnApiBeamoGetManifestsByManifestIdSuccess, FOnApiBeamoGetManifestsByManifestIdError, FOnApiBeamoGetManifestsByManifestIdComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamBeamoApi::CPP_ApiBeamoGetManifestsByManifestIdImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UApiBeamoGetManifestsByManifestIdRequest* RequestData, const FOnApiBeamoGetManifestsByManifestIdFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
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
		Backend->RunAuthenticatedCodeRequestProcessor<UApiBeamoGetManifestsByManifestIdRequest, UBeamoV2Manifest>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UApiBeamoGetManifestsByManifestIdRequest, UBeamoV2Manifest>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamBeamoApi::BP_GetManifestsCurrentImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UGetManifestsCurrentRequest* RequestData, const FOnGetManifestsCurrentSuccess& OnSuccess, const FOnGetManifestsCurrentError& OnError, const FOnGetManifestsCurrentComplete& OnComplete, 
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
		Backend->RunAuthenticatedBlueprintRequestProcessor<UGetManifestsCurrentRequest, UBeamoV2Manifest, FOnGetManifestsCurrentSuccess, FOnGetManifestsCurrentError, FOnGetManifestsCurrentComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UGetManifestsCurrentRequest, UBeamoV2Manifest, FOnGetManifestsCurrentSuccess, FOnGetManifestsCurrentError, FOnGetManifestsCurrentComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamBeamoApi::CPP_GetManifestsCurrentImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UGetManifestsCurrentRequest* RequestData, const FOnGetManifestsCurrentFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
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
		Backend->RunAuthenticatedCodeRequestProcessor<UGetManifestsCurrentRequest, UBeamoV2Manifest>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UGetManifestsCurrentRequest, UBeamoV2Manifest>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamBeamoApi::BP_PostManifestsCurrentImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UPostManifestsCurrentRequest* RequestData, const FOnPostManifestsCurrentSuccess& OnSuccess, const FOnPostManifestsCurrentError& OnError, const FOnPostManifestsCurrentComplete& OnComplete, 
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
		Backend->RunAuthenticatedBlueprintRequestProcessor<UPostManifestsCurrentRequest, UBeamoV2EmptyMessage, FOnPostManifestsCurrentSuccess, FOnPostManifestsCurrentError, FOnPostManifestsCurrentComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPostManifestsCurrentRequest, UBeamoV2EmptyMessage, FOnPostManifestsCurrentSuccess, FOnPostManifestsCurrentError, FOnPostManifestsCurrentComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamBeamoApi::CPP_PostManifestsCurrentImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UPostManifestsCurrentRequest* RequestData, const FOnPostManifestsCurrentFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
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
		Backend->RunAuthenticatedCodeRequestProcessor<UPostManifestsCurrentRequest, UBeamoV2EmptyMessage>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPostManifestsCurrentRequest, UBeamoV2EmptyMessage>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamBeamoApi::BP_PostManifestsPromoteImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UPostManifestsPromoteRequest* RequestData, const FOnPostManifestsPromoteSuccess& OnSuccess, const FOnPostManifestsPromoteError& OnError, const FOnPostManifestsPromoteComplete& OnComplete, 
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
		Backend->RunAuthenticatedBlueprintRequestProcessor<UPostManifestsPromoteRequest, UBeamoV2EmptyMessage, FOnPostManifestsPromoteSuccess, FOnPostManifestsPromoteError, FOnPostManifestsPromoteComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPostManifestsPromoteRequest, UBeamoV2EmptyMessage, FOnPostManifestsPromoteSuccess, FOnPostManifestsPromoteError, FOnPostManifestsPromoteComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamBeamoApi::CPP_PostManifestsPromoteImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UPostManifestsPromoteRequest* RequestData, const FOnPostManifestsPromoteFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
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
		Backend->RunAuthenticatedCodeRequestProcessor<UPostManifestsPromoteRequest, UBeamoV2EmptyMessage>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPostManifestsPromoteRequest, UBeamoV2EmptyMessage>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamBeamoApi::BP_ApiBeamoGetTemplatesImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UApiBeamoGetTemplatesRequest* RequestData, const FOnApiBeamoGetTemplatesSuccess& OnSuccess, const FOnApiBeamoGetTemplatesError& OnError, const FOnApiBeamoGetTemplatesComplete& OnComplete, 
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
		Backend->RunAuthenticatedBlueprintRequestProcessor<UApiBeamoGetTemplatesRequest, UBeamoV2GetTemplatesResponse, FOnApiBeamoGetTemplatesSuccess, FOnApiBeamoGetTemplatesError, FOnApiBeamoGetTemplatesComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UApiBeamoGetTemplatesRequest, UBeamoV2GetTemplatesResponse, FOnApiBeamoGetTemplatesSuccess, FOnApiBeamoGetTemplatesError, FOnApiBeamoGetTemplatesComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamBeamoApi::CPP_ApiBeamoGetTemplatesImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UApiBeamoGetTemplatesRequest* RequestData, const FOnApiBeamoGetTemplatesFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
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
		Backend->RunAuthenticatedCodeRequestProcessor<UApiBeamoGetTemplatesRequest, UBeamoV2GetTemplatesResponse>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UApiBeamoGetTemplatesRequest, UBeamoV2GetTemplatesResponse>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamBeamoApi::BP_ApiBeamoGetStatusImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UApiBeamoGetStatusRequest* RequestData, const FOnApiBeamoGetStatusSuccess& OnSuccess, const FOnApiBeamoGetStatusError& OnError, const FOnApiBeamoGetStatusComplete& OnComplete, 
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
		Backend->RunAuthenticatedBlueprintRequestProcessor<UApiBeamoGetStatusRequest, UBeamoV2GetStatusResponse, FOnApiBeamoGetStatusSuccess, FOnApiBeamoGetStatusError, FOnApiBeamoGetStatusComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UApiBeamoGetStatusRequest, UBeamoV2GetStatusResponse, FOnApiBeamoGetStatusSuccess, FOnApiBeamoGetStatusError, FOnApiBeamoGetStatusComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamBeamoApi::CPP_ApiBeamoGetStatusImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UApiBeamoGetStatusRequest* RequestData, const FOnApiBeamoGetStatusFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
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
		Backend->RunAuthenticatedCodeRequestProcessor<UApiBeamoGetStatusRequest, UBeamoV2GetStatusResponse>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UApiBeamoGetStatusRequest, UBeamoV2GetStatusResponse>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamBeamoApi::BP_GetRegistryUriImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UGetRegistryUriRequest* RequestData, const FOnGetRegistryUriSuccess& OnSuccess, const FOnGetRegistryUriError& OnError, const FOnGetRegistryUriComplete& OnComplete, 
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
		Backend->RunAuthenticatedBlueprintRequestProcessor<UGetRegistryUriRequest, UBeamoV2UriResponse, FOnGetRegistryUriSuccess, FOnGetRegistryUriError, FOnGetRegistryUriComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UGetRegistryUriRequest, UBeamoV2UriResponse, FOnGetRegistryUriSuccess, FOnGetRegistryUriError, FOnGetRegistryUriComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamBeamoApi::CPP_GetRegistryUriImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UGetRegistryUriRequest* RequestData, const FOnGetRegistryUriFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
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
		Backend->RunAuthenticatedCodeRequestProcessor<UGetRegistryUriRequest, UBeamoV2UriResponse>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UGetRegistryUriRequest, UBeamoV2UriResponse>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamBeamoApi::BP_PostServicesRegistrationsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UPostServicesRegistrationsRequest* RequestData, const FOnPostServicesRegistrationsSuccess& OnSuccess, const FOnPostServicesRegistrationsError& OnError, const FOnPostServicesRegistrationsComplete& OnComplete, 
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
		Backend->RunAuthenticatedBlueprintRequestProcessor<UPostServicesRegistrationsRequest, UBeamoV2ServiceRegistrationResponse, FOnPostServicesRegistrationsSuccess, FOnPostServicesRegistrationsError, FOnPostServicesRegistrationsComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPostServicesRegistrationsRequest, UBeamoV2ServiceRegistrationResponse, FOnPostServicesRegistrationsSuccess, FOnPostServicesRegistrationsError, FOnPostServicesRegistrationsComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamBeamoApi::CPP_PostServicesRegistrationsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UPostServicesRegistrationsRequest* RequestData, const FOnPostServicesRegistrationsFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
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
		Backend->RunAuthenticatedCodeRequestProcessor<UPostServicesRegistrationsRequest, UBeamoV2ServiceRegistrationResponse>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPostServicesRegistrationsRequest, UBeamoV2ServiceRegistrationResponse>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamBeamoApi::BP_PostServicesFederationImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UPostServicesFederationRequest* RequestData, const FOnPostServicesFederationSuccess& OnSuccess, const FOnPostServicesFederationError& OnError, const FOnPostServicesFederationComplete& OnComplete, 
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
		Backend->RunAuthenticatedBlueprintRequestProcessor<UPostServicesFederationRequest, UBeamoV2FederationRegistrationResponse, FOnPostServicesFederationSuccess, FOnPostServicesFederationError, FOnPostServicesFederationComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPostServicesFederationRequest, UBeamoV2FederationRegistrationResponse, FOnPostServicesFederationSuccess, FOnPostServicesFederationError, FOnPostServicesFederationComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamBeamoApi::CPP_PostServicesFederationImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UPostServicesFederationRequest* RequestData, const FOnPostServicesFederationFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
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
		Backend->RunAuthenticatedCodeRequestProcessor<UPostServicesFederationRequest, UBeamoV2FederationRegistrationResponse>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPostServicesFederationRequest, UBeamoV2FederationRegistrationResponse>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamBeamoApi::BP_PutServicesFederationTrafficImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UPutServicesFederationTrafficRequest* RequestData, const FOnPutServicesFederationTrafficSuccess& OnSuccess, const FOnPutServicesFederationTrafficError& OnError, const FOnPutServicesFederationTrafficComplete& OnComplete, 
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
		Backend->RunAuthenticatedBlueprintRequestProcessor<UPutServicesFederationTrafficRequest, UBeamoV2EmptyMessage, FOnPutServicesFederationTrafficSuccess, FOnPutServicesFederationTrafficError, FOnPutServicesFederationTrafficComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPutServicesFederationTrafficRequest, UBeamoV2EmptyMessage, FOnPutServicesFederationTrafficSuccess, FOnPutServicesFederationTrafficError, FOnPutServicesFederationTrafficComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamBeamoApi::CPP_PutServicesFederationTrafficImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UPutServicesFederationTrafficRequest* RequestData, const FOnPutServicesFederationTrafficFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
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
		Backend->RunAuthenticatedCodeRequestProcessor<UPutServicesFederationTrafficRequest, UBeamoV2EmptyMessage>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPutServicesFederationTrafficRequest, UBeamoV2EmptyMessage>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamBeamoApi::BP_DeleteServicesFederationTrafficImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UDeleteServicesFederationTrafficRequest* RequestData, const FOnDeleteServicesFederationTrafficSuccess& OnSuccess, const FOnDeleteServicesFederationTrafficError& OnError, const FOnDeleteServicesFederationTrafficComplete& OnComplete, 
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
		Backend->RunAuthenticatedBlueprintRequestProcessor<UDeleteServicesFederationTrafficRequest, UBeamoV2EmptyMessage, FOnDeleteServicesFederationTrafficSuccess, FOnDeleteServicesFederationTrafficError, FOnDeleteServicesFederationTrafficComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UDeleteServicesFederationTrafficRequest, UBeamoV2EmptyMessage, FOnDeleteServicesFederationTrafficSuccess, FOnDeleteServicesFederationTrafficError, FOnDeleteServicesFederationTrafficComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamBeamoApi::CPP_DeleteServicesFederationTrafficImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UDeleteServicesFederationTrafficRequest* RequestData, const FOnDeleteServicesFederationTrafficFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
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
		Backend->RunAuthenticatedCodeRequestProcessor<UDeleteServicesFederationTrafficRequest, UBeamoV2EmptyMessage>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UDeleteServicesFederationTrafficRequest, UBeamoV2EmptyMessage>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamBeamoApi::BP_PostServicesMetricsRequestImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UPostServicesMetricsRequestRequest* RequestData, const FOnPostServicesMetricsRequestSuccess& OnSuccess, const FOnPostServicesMetricsRequestError& OnError, const FOnPostServicesMetricsRequestComplete& OnComplete, 
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
		Backend->RunAuthenticatedBlueprintRequestProcessor<UPostServicesMetricsRequestRequest, UBeamoV2SignedRequestBody, FOnPostServicesMetricsRequestSuccess, FOnPostServicesMetricsRequestError, FOnPostServicesMetricsRequestComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPostServicesMetricsRequestRequest, UBeamoV2SignedRequestBody, FOnPostServicesMetricsRequestSuccess, FOnPostServicesMetricsRequestError, FOnPostServicesMetricsRequestComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamBeamoApi::CPP_PostServicesMetricsRequestImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UPostServicesMetricsRequestRequest* RequestData, const FOnPostServicesMetricsRequestFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
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
		Backend->RunAuthenticatedCodeRequestProcessor<UPostServicesMetricsRequestRequest, UBeamoV2SignedRequestBody>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPostServicesMetricsRequestRequest, UBeamoV2SignedRequestBody>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamBeamoApi::BP_PostServicesLogsQueryImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UPostServicesLogsQueryRequest* RequestData, const FOnPostServicesLogsQuerySuccess& OnSuccess, const FOnPostServicesLogsQueryError& OnError, const FOnPostServicesLogsQueryComplete& OnComplete, 
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
		Backend->RunAuthenticatedBlueprintRequestProcessor<UPostServicesLogsQueryRequest, UBeamoV2QueryResponse, FOnPostServicesLogsQuerySuccess, FOnPostServicesLogsQueryError, FOnPostServicesLogsQueryComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPostServicesLogsQueryRequest, UBeamoV2QueryResponse, FOnPostServicesLogsQuerySuccess, FOnPostServicesLogsQueryError, FOnPostServicesLogsQueryComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamBeamoApi::CPP_PostServicesLogsQueryImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UPostServicesLogsQueryRequest* RequestData, const FOnPostServicesLogsQueryFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
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
		Backend->RunAuthenticatedCodeRequestProcessor<UPostServicesLogsQueryRequest, UBeamoV2QueryResponse>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPostServicesLogsQueryRequest, UBeamoV2QueryResponse>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamBeamoApi::BP_DeleteServicesLogsQueryImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UDeleteServicesLogsQueryRequest* RequestData, const FOnDeleteServicesLogsQuerySuccess& OnSuccess, const FOnDeleteServicesLogsQueryError& OnError, const FOnDeleteServicesLogsQueryComplete& OnComplete, 
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
		Backend->RunAuthenticatedBlueprintRequestProcessor<UDeleteServicesLogsQueryRequest, UBeamoV2ApiBeamoServicesLogsQueryDeleteBeamoResponse, FOnDeleteServicesLogsQuerySuccess, FOnDeleteServicesLogsQueryError, FOnDeleteServicesLogsQueryComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UDeleteServicesLogsQueryRequest, UBeamoV2ApiBeamoServicesLogsQueryDeleteBeamoResponse, FOnDeleteServicesLogsQuerySuccess, FOnDeleteServicesLogsQueryError, FOnDeleteServicesLogsQueryComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamBeamoApi::CPP_DeleteServicesLogsQueryImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UDeleteServicesLogsQueryRequest* RequestData, const FOnDeleteServicesLogsQueryFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
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
		Backend->RunAuthenticatedCodeRequestProcessor<UDeleteServicesLogsQueryRequest, UBeamoV2ApiBeamoServicesLogsQueryDeleteBeamoResponse>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UDeleteServicesLogsQueryRequest, UBeamoV2ApiBeamoServicesLogsQueryDeleteBeamoResponse>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamBeamoApi::BP_GetServicesLogsQueryImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UGetServicesLogsQueryRequest* RequestData, const FOnGetServicesLogsQuerySuccess& OnSuccess, const FOnGetServicesLogsQueryError& OnError, const FOnGetServicesLogsQueryComplete& OnComplete, 
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
		Backend->RunAuthenticatedBlueprintRequestProcessor<UGetServicesLogsQueryRequest, UBeamoV2SignedRequestBody, FOnGetServicesLogsQuerySuccess, FOnGetServicesLogsQueryError, FOnGetServicesLogsQueryComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UGetServicesLogsQueryRequest, UBeamoV2SignedRequestBody, FOnGetServicesLogsQuerySuccess, FOnGetServicesLogsQueryError, FOnGetServicesLogsQueryComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamBeamoApi::CPP_GetServicesLogsQueryImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UGetServicesLogsQueryRequest* RequestData, const FOnGetServicesLogsQueryFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
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
		Backend->RunAuthenticatedCodeRequestProcessor<UGetServicesLogsQueryRequest, UBeamoV2SignedRequestBody>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UGetServicesLogsQueryRequest, UBeamoV2SignedRequestBody>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamBeamoApi::BP_GetServicesSecretImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UGetServicesSecretRequest* RequestData, const FOnGetServicesSecretSuccess& OnSuccess, const FOnGetServicesSecretError& OnError, const FOnGetServicesSecretComplete& OnComplete, 
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
		Backend->RunAuthenticatedBlueprintRequestProcessor<UGetServicesSecretRequest, UBeamoV2GetServiceSecretResponse, FOnGetServicesSecretSuccess, FOnGetServicesSecretError, FOnGetServicesSecretComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UGetServicesSecretRequest, UBeamoV2GetServiceSecretResponse, FOnGetServicesSecretSuccess, FOnGetServicesSecretError, FOnGetServicesSecretComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamBeamoApi::CPP_GetServicesSecretImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UGetServicesSecretRequest* RequestData, const FOnGetServicesSecretFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
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
		Backend->RunAuthenticatedCodeRequestProcessor<UGetServicesSecretRequest, UBeamoV2GetServiceSecretResponse>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UGetServicesSecretRequest, UBeamoV2GetServiceSecretResponse>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamBeamoApi::BP_ApiBeamoGetStorageConnectionImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UApiBeamoGetStorageConnectionRequest* RequestData, const FOnApiBeamoGetStorageConnectionSuccess& OnSuccess, const FOnApiBeamoGetStorageConnectionError& OnError, const FOnApiBeamoGetStorageConnectionComplete& OnComplete, 
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
		Backend->RunAuthenticatedBlueprintRequestProcessor<UApiBeamoGetStorageConnectionRequest, UBeamoV2ConnectionStringResponse, FOnApiBeamoGetStorageConnectionSuccess, FOnApiBeamoGetStorageConnectionError, FOnApiBeamoGetStorageConnectionComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UApiBeamoGetStorageConnectionRequest, UBeamoV2ConnectionStringResponse, FOnApiBeamoGetStorageConnectionSuccess, FOnApiBeamoGetStorageConnectionError, FOnApiBeamoGetStorageConnectionComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamBeamoApi::CPP_ApiBeamoGetStorageConnectionImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UApiBeamoGetStorageConnectionRequest* RequestData, const FOnApiBeamoGetStorageConnectionFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
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
		Backend->RunAuthenticatedCodeRequestProcessor<UApiBeamoGetStorageConnectionRequest, UBeamoV2ConnectionStringResponse>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UApiBeamoGetStorageConnectionRequest, UBeamoV2ConnectionStringResponse>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamBeamoApi::BP_ApiBeamoGetStoragePerformanceByStorageObjectNameImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UApiBeamoGetStoragePerformanceByStorageObjectNameRequest* RequestData, const FOnApiBeamoGetStoragePerformanceByStorageObjectNameSuccess& OnSuccess, const FOnApiBeamoGetStoragePerformanceByStorageObjectNameError& OnError, const FOnApiBeamoGetStoragePerformanceByStorageObjectNameComplete& OnComplete, 
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
		Backend->RunAuthenticatedBlueprintRequestProcessor<UApiBeamoGetStoragePerformanceByStorageObjectNameRequest, UBeamoV2StoragePerformance, FOnApiBeamoGetStoragePerformanceByStorageObjectNameSuccess, FOnApiBeamoGetStoragePerformanceByStorageObjectNameError, FOnApiBeamoGetStoragePerformanceByStorageObjectNameComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UApiBeamoGetStoragePerformanceByStorageObjectNameRequest, UBeamoV2StoragePerformance, FOnApiBeamoGetStoragePerformanceByStorageObjectNameSuccess, FOnApiBeamoGetStoragePerformanceByStorageObjectNameError, FOnApiBeamoGetStoragePerformanceByStorageObjectNameComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamBeamoApi::CPP_ApiBeamoGetStoragePerformanceByStorageObjectNameImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UApiBeamoGetStoragePerformanceByStorageObjectNameRequest* RequestData, const FOnApiBeamoGetStoragePerformanceByStorageObjectNameFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
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
		Backend->RunAuthenticatedCodeRequestProcessor<UApiBeamoGetStoragePerformanceByStorageObjectNameRequest, UBeamoV2StoragePerformance>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UApiBeamoGetStoragePerformanceByStorageObjectNameRequest, UBeamoV2StoragePerformance>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamBeamoApi::BP_PostMicroserviceRegistrationsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UPostMicroserviceRegistrationsRequest* RequestData, const FOnPostMicroserviceRegistrationsSuccess& OnSuccess, const FOnPostMicroserviceRegistrationsError& OnError, const FOnPostMicroserviceRegistrationsComplete& OnComplete, 
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
		Backend->RunAuthenticatedBlueprintRequestProcessor<UPostMicroserviceRegistrationsRequest, UMicroserviceRegistrationsResponse, FOnPostMicroserviceRegistrationsSuccess, FOnPostMicroserviceRegistrationsError, FOnPostMicroserviceRegistrationsComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPostMicroserviceRegistrationsRequest, UMicroserviceRegistrationsResponse, FOnPostMicroserviceRegistrationsSuccess, FOnPostMicroserviceRegistrationsError, FOnPostMicroserviceRegistrationsComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamBeamoApi::CPP_PostMicroserviceRegistrationsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UPostMicroserviceRegistrationsRequest* RequestData, const FOnPostMicroserviceRegistrationsFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
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
		Backend->RunAuthenticatedCodeRequestProcessor<UPostMicroserviceRegistrationsRequest, UMicroserviceRegistrationsResponse>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPostMicroserviceRegistrationsRequest, UMicroserviceRegistrationsResponse>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamBeamoApi::BP_PutMicroserviceFederationTrafficImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UPutMicroserviceFederationTrafficRequest* RequestData, const FOnPutMicroserviceFederationTrafficSuccess& OnSuccess, const FOnPutMicroserviceFederationTrafficError& OnError, const FOnPutMicroserviceFederationTrafficComplete& OnComplete, 
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
		Backend->RunAuthenticatedBlueprintRequestProcessor<UPutMicroserviceFederationTrafficRequest, UCommonResponse, FOnPutMicroserviceFederationTrafficSuccess, FOnPutMicroserviceFederationTrafficError, FOnPutMicroserviceFederationTrafficComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPutMicroserviceFederationTrafficRequest, UCommonResponse, FOnPutMicroserviceFederationTrafficSuccess, FOnPutMicroserviceFederationTrafficError, FOnPutMicroserviceFederationTrafficComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamBeamoApi::CPP_PutMicroserviceFederationTrafficImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UPutMicroserviceFederationTrafficRequest* RequestData, const FOnPutMicroserviceFederationTrafficFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
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
		Backend->RunAuthenticatedCodeRequestProcessor<UPutMicroserviceFederationTrafficRequest, UCommonResponse>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPutMicroserviceFederationTrafficRequest, UCommonResponse>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamBeamoApi::BP_DeleteMicroserviceFederationTrafficImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UDeleteMicroserviceFederationTrafficRequest* RequestData, const FOnDeleteMicroserviceFederationTrafficSuccess& OnSuccess, const FOnDeleteMicroserviceFederationTrafficError& OnError, const FOnDeleteMicroserviceFederationTrafficComplete& OnComplete, 
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
		Backend->RunAuthenticatedBlueprintRequestProcessor<UDeleteMicroserviceFederationTrafficRequest, UCommonResponse, FOnDeleteMicroserviceFederationTrafficSuccess, FOnDeleteMicroserviceFederationTrafficError, FOnDeleteMicroserviceFederationTrafficComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UDeleteMicroserviceFederationTrafficRequest, UCommonResponse, FOnDeleteMicroserviceFederationTrafficSuccess, FOnDeleteMicroserviceFederationTrafficError, FOnDeleteMicroserviceFederationTrafficComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamBeamoApi::CPP_DeleteMicroserviceFederationTrafficImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UDeleteMicroserviceFederationTrafficRequest* RequestData, const FOnDeleteMicroserviceFederationTrafficFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
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
		Backend->RunAuthenticatedCodeRequestProcessor<UDeleteMicroserviceFederationTrafficRequest, UCommonResponse>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UDeleteMicroserviceFederationTrafficRequest, UCommonResponse>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamBeamoApi::BP_PostImageUrlsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UPostImageUrlsRequest* RequestData, const FOnPostImageUrlsSuccess& OnSuccess, const FOnPostImageUrlsError& OnError, const FOnPostImageUrlsComplete& OnComplete, 
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
		Backend->RunAuthenticatedBlueprintRequestProcessor<UPostImageUrlsRequest, UPreSignedUrlsResponse, FOnPostImageUrlsSuccess, FOnPostImageUrlsError, FOnPostImageUrlsComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPostImageUrlsRequest, UPreSignedUrlsResponse, FOnPostImageUrlsSuccess, FOnPostImageUrlsError, FOnPostImageUrlsComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamBeamoApi::CPP_PostImageUrlsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UPostImageUrlsRequest* RequestData, const FOnPostImageUrlsFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
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
		Backend->RunAuthenticatedCodeRequestProcessor<UPostImageUrlsRequest, UPreSignedUrlsResponse>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPostImageUrlsRequest, UPreSignedUrlsResponse>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamBeamoApi::BP_PostMetricsUrlImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UPostMetricsUrlRequest* RequestData, const FOnPostMetricsUrlSuccess& OnSuccess, const FOnPostMetricsUrlError& OnError, const FOnPostMetricsUrlComplete& OnComplete, 
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
		Backend->RunAuthenticatedBlueprintRequestProcessor<UPostMetricsUrlRequest, UGetSignedUrlResponse, FOnPostMetricsUrlSuccess, FOnPostMetricsUrlError, FOnPostMetricsUrlComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPostMetricsUrlRequest, UGetSignedUrlResponse, FOnPostMetricsUrlSuccess, FOnPostMetricsUrlError, FOnPostMetricsUrlComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamBeamoApi::CPP_PostMetricsUrlImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UPostMetricsUrlRequest* RequestData, const FOnPostMetricsUrlFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
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
		Backend->RunAuthenticatedCodeRequestProcessor<UPostMetricsUrlRequest, UGetSignedUrlResponse>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPostMetricsUrlRequest, UGetSignedUrlResponse>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamBeamoApi::BP_GetMicroserviceSecretImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UGetMicroserviceSecretRequest* RequestData, const FOnGetMicroserviceSecretSuccess& OnSuccess, const FOnGetMicroserviceSecretError& OnError, const FOnGetMicroserviceSecretComplete& OnComplete, 
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
		Backend->RunAuthenticatedBlueprintRequestProcessor<UGetMicroserviceSecretRequest, UMicroserviceSecretResponse, FOnGetMicroserviceSecretSuccess, FOnGetMicroserviceSecretError, FOnGetMicroserviceSecretComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UGetMicroserviceSecretRequest, UMicroserviceSecretResponse, FOnGetMicroserviceSecretSuccess, FOnGetMicroserviceSecretError, FOnGetMicroserviceSecretComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamBeamoApi::CPP_GetMicroserviceSecretImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UGetMicroserviceSecretRequest* RequestData, const FOnGetMicroserviceSecretFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
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
		Backend->RunAuthenticatedCodeRequestProcessor<UGetMicroserviceSecretRequest, UMicroserviceSecretResponse>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UGetMicroserviceSecretRequest, UMicroserviceSecretResponse>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamBeamoApi::BP_PostQueryLogsResultImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UPostQueryLogsResultRequest* RequestData, const FOnPostQueryLogsResultSuccess& OnSuccess, const FOnPostQueryLogsResultError& OnError, const FOnPostQueryLogsResultComplete& OnComplete, 
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
		Backend->RunAuthenticatedBlueprintRequestProcessor<UPostQueryLogsResultRequest, UGetSignedUrlResponse, FOnPostQueryLogsResultSuccess, FOnPostQueryLogsResultError, FOnPostQueryLogsResultComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPostQueryLogsResultRequest, UGetSignedUrlResponse, FOnPostQueryLogsResultSuccess, FOnPostQueryLogsResultError, FOnPostQueryLogsResultComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamBeamoApi::CPP_PostQueryLogsResultImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UPostQueryLogsResultRequest* RequestData, const FOnPostQueryLogsResultFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
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
		Backend->RunAuthenticatedCodeRequestProcessor<UPostQueryLogsResultRequest, UGetSignedUrlResponse>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPostQueryLogsResultRequest, UGetSignedUrlResponse>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamBeamoApi::BP_BasicBeamoGetStoragePerformanceImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UBasicBeamoGetStoragePerformanceRequest* RequestData, const FOnBasicBeamoGetStoragePerformanceSuccess& OnSuccess, const FOnBasicBeamoGetStoragePerformanceError& OnError, const FOnBasicBeamoGetStoragePerformanceComplete& OnComplete, 
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
		Backend->RunAuthenticatedBlueprintRequestProcessor<UBasicBeamoGetStoragePerformanceRequest, UPerformanceResponse, FOnBasicBeamoGetStoragePerformanceSuccess, FOnBasicBeamoGetStoragePerformanceError, FOnBasicBeamoGetStoragePerformanceComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UBasicBeamoGetStoragePerformanceRequest, UPerformanceResponse, FOnBasicBeamoGetStoragePerformanceSuccess, FOnBasicBeamoGetStoragePerformanceError, FOnBasicBeamoGetStoragePerformanceComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamBeamoApi::CPP_BasicBeamoGetStoragePerformanceImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UBasicBeamoGetStoragePerformanceRequest* RequestData, const FOnBasicBeamoGetStoragePerformanceFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
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
		Backend->RunAuthenticatedCodeRequestProcessor<UBasicBeamoGetStoragePerformanceRequest, UPerformanceResponse>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UBasicBeamoGetStoragePerformanceRequest, UPerformanceResponse>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamBeamoApi::BP_BasicBeamoGetManifestsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UBasicBeamoGetManifestsRequest* RequestData, const FOnBasicBeamoGetManifestsSuccess& OnSuccess, const FOnBasicBeamoGetManifestsError& OnError, const FOnBasicBeamoGetManifestsComplete& OnComplete, 
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
		Backend->RunAuthenticatedBlueprintRequestProcessor<UBasicBeamoGetManifestsRequest, UGetManifestsResponse, FOnBasicBeamoGetManifestsSuccess, FOnBasicBeamoGetManifestsError, FOnBasicBeamoGetManifestsComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UBasicBeamoGetManifestsRequest, UGetManifestsResponse, FOnBasicBeamoGetManifestsSuccess, FOnBasicBeamoGetManifestsError, FOnBasicBeamoGetManifestsComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamBeamoApi::CPP_BasicBeamoGetManifestsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UBasicBeamoGetManifestsRequest* RequestData, const FOnBasicBeamoGetManifestsFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
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
		Backend->RunAuthenticatedCodeRequestProcessor<UBasicBeamoGetManifestsRequest, UGetManifestsResponse>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UBasicBeamoGetManifestsRequest, UGetManifestsResponse>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamBeamoApi::BP_BasicBeamoGetTemplatesImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UBasicBeamoGetTemplatesRequest* RequestData, const FOnBasicBeamoGetTemplatesSuccess& OnSuccess, const FOnBasicBeamoGetTemplatesError& OnError, const FOnBasicBeamoGetTemplatesComplete& OnComplete, 
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
		Backend->RunAuthenticatedBlueprintRequestProcessor<UBasicBeamoGetTemplatesRequest, UGetTemplatesResponse, FOnBasicBeamoGetTemplatesSuccess, FOnBasicBeamoGetTemplatesError, FOnBasicBeamoGetTemplatesComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UBasicBeamoGetTemplatesRequest, UGetTemplatesResponse, FOnBasicBeamoGetTemplatesSuccess, FOnBasicBeamoGetTemplatesError, FOnBasicBeamoGetTemplatesComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamBeamoApi::CPP_BasicBeamoGetTemplatesImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UBasicBeamoGetTemplatesRequest* RequestData, const FOnBasicBeamoGetTemplatesFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
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
		Backend->RunAuthenticatedCodeRequestProcessor<UBasicBeamoGetTemplatesRequest, UGetTemplatesResponse>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UBasicBeamoGetTemplatesRequest, UGetTemplatesResponse>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamBeamoApi::BP_PostQueryLogsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UPostQueryLogsRequest* RequestData, const FOnPostQueryLogsSuccess& OnSuccess, const FOnPostQueryLogsError& OnError, const FOnPostQueryLogsComplete& OnComplete, 
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
		Backend->RunAuthenticatedBlueprintRequestProcessor<UPostQueryLogsRequest, UQuery, FOnPostQueryLogsSuccess, FOnPostQueryLogsError, FOnPostQueryLogsComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPostQueryLogsRequest, UQuery, FOnPostQueryLogsSuccess, FOnPostQueryLogsError, FOnPostQueryLogsComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamBeamoApi::CPP_PostQueryLogsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UPostQueryLogsRequest* RequestData, const FOnPostQueryLogsFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
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
		Backend->RunAuthenticatedCodeRequestProcessor<UPostQueryLogsRequest, UQuery>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPostQueryLogsRequest, UQuery>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamBeamoApi::BP_DeleteQueryLogsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UDeleteQueryLogsRequest* RequestData, const FOnDeleteQueryLogsSuccess& OnSuccess, const FOnDeleteQueryLogsError& OnError, const FOnDeleteQueryLogsComplete& OnComplete, 
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
		Backend->RunAuthenticatedBlueprintRequestProcessor<UDeleteQueryLogsRequest, UCommonResponse, FOnDeleteQueryLogsSuccess, FOnDeleteQueryLogsError, FOnDeleteQueryLogsComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UDeleteQueryLogsRequest, UCommonResponse, FOnDeleteQueryLogsSuccess, FOnDeleteQueryLogsError, FOnDeleteQueryLogsComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamBeamoApi::CPP_DeleteQueryLogsImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UDeleteQueryLogsRequest* RequestData, const FOnDeleteQueryLogsFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
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
		Backend->RunAuthenticatedCodeRequestProcessor<UDeleteQueryLogsRequest, UCommonResponse>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UDeleteQueryLogsRequest, UCommonResponse>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamBeamoApi::BP_PostLogsUrlImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UPostLogsUrlRequest* RequestData, const FOnPostLogsUrlSuccess& OnSuccess, const FOnPostLogsUrlError& OnError, const FOnPostLogsUrlComplete& OnComplete, 
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
		Backend->RunAuthenticatedBlueprintRequestProcessor<UPostLogsUrlRequest, UGetSignedUrlResponse, FOnPostLogsUrlSuccess, FOnPostLogsUrlError, FOnPostLogsUrlComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPostLogsUrlRequest, UGetSignedUrlResponse, FOnPostLogsUrlSuccess, FOnPostLogsUrlError, FOnPostLogsUrlComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamBeamoApi::CPP_PostLogsUrlImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UPostLogsUrlRequest* RequestData, const FOnPostLogsUrlFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
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
		Backend->RunAuthenticatedCodeRequestProcessor<UPostLogsUrlRequest, UGetSignedUrlResponse>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPostLogsUrlRequest, UGetSignedUrlResponse>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamBeamoApi::BP_PutImageCommitImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UPutImageCommitRequest* RequestData, const FOnPutImageCommitSuccess& OnSuccess, const FOnPutImageCommitError& OnError, const FOnPutImageCommitComplete& OnComplete, 
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
		Backend->RunAuthenticatedBlueprintRequestProcessor<UPutImageCommitRequest, ULambdaResponse, FOnPutImageCommitSuccess, FOnPutImageCommitError, FOnPutImageCommitComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPutImageCommitRequest, ULambdaResponse, FOnPutImageCommitSuccess, FOnPutImageCommitError, FOnPutImageCommitComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamBeamoApi::CPP_PutImageCommitImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UPutImageCommitRequest* RequestData, const FOnPutImageCommitFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
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
		Backend->RunAuthenticatedCodeRequestProcessor<UPutImageCommitRequest, ULambdaResponse>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPutImageCommitRequest, ULambdaResponse>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamBeamoApi::BP_GetUploadAPIImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UGetUploadAPIRequest* RequestData, const FOnGetUploadAPISuccess& OnSuccess, const FOnGetUploadAPIError& OnError, const FOnGetUploadAPIComplete& OnComplete, 
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
		Backend->RunAuthenticatedBlueprintRequestProcessor<UGetUploadAPIRequest, UGetLambdaURI, FOnGetUploadAPISuccess, FOnGetUploadAPIError, FOnGetUploadAPIComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UGetUploadAPIRequest, UGetLambdaURI, FOnGetUploadAPISuccess, FOnGetUploadAPIError, FOnGetUploadAPIComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamBeamoApi::CPP_GetUploadAPIImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UGetUploadAPIRequest* RequestData, const FOnGetUploadAPIFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
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
		Backend->RunAuthenticatedCodeRequestProcessor<UGetUploadAPIRequest, UGetLambdaURI>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UGetUploadAPIRequest, UGetLambdaURI>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamBeamoApi::BP_BasicBeamoGetStatusImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UBasicBeamoGetStatusRequest* RequestData, const FOnBasicBeamoGetStatusSuccess& OnSuccess, const FOnBasicBeamoGetStatusError& OnError, const FOnBasicBeamoGetStatusComplete& OnComplete, 
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
		Backend->RunAuthenticatedBlueprintRequestProcessor<UBasicBeamoGetStatusRequest, UGetStatusResponse, FOnBasicBeamoGetStatusSuccess, FOnBasicBeamoGetStatusError, FOnBasicBeamoGetStatusComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UBasicBeamoGetStatusRequest, UGetStatusResponse, FOnBasicBeamoGetStatusSuccess, FOnBasicBeamoGetStatusError, FOnBasicBeamoGetStatusComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamBeamoApi::CPP_BasicBeamoGetStatusImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UBasicBeamoGetStatusRequest* RequestData, const FOnBasicBeamoGetStatusFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
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
		Backend->RunAuthenticatedCodeRequestProcessor<UBasicBeamoGetStatusRequest, UGetStatusResponse>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UBasicBeamoGetStatusRequest, UGetStatusResponse>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamBeamoApi::BP_GetManifestCurrentImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UGetManifestCurrentRequest* RequestData, const FOnGetManifestCurrentSuccess& OnSuccess, const FOnGetManifestCurrentError& OnError, const FOnGetManifestCurrentComplete& OnComplete, 
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
		Backend->RunAuthenticatedBlueprintRequestProcessor<UGetManifestCurrentRequest, UGetCurrentManifestResponse, FOnGetManifestCurrentSuccess, FOnGetManifestCurrentError, FOnGetManifestCurrentComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UGetManifestCurrentRequest, UGetCurrentManifestResponse, FOnGetManifestCurrentSuccess, FOnGetManifestCurrentError, FOnGetManifestCurrentComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamBeamoApi::CPP_GetManifestCurrentImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UGetManifestCurrentRequest* RequestData, const FOnGetManifestCurrentFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
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
		Backend->RunAuthenticatedCodeRequestProcessor<UGetManifestCurrentRequest, UGetCurrentManifestResponse>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UGetManifestCurrentRequest, UGetCurrentManifestResponse>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamBeamoApi::BP_PostManifestPullImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UBasicBeamoPostManifestPullRequest* RequestData, const FOnBasicBeamoPostManifestPullSuccess& OnSuccess, const FOnBasicBeamoPostManifestPullError& OnError, const FOnBasicBeamoPostManifestPullComplete& OnComplete, 
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
		Backend->RunAuthenticatedBlueprintRequestProcessor<UBasicBeamoPostManifestPullRequest, UManifestChecksums, FOnBasicBeamoPostManifestPullSuccess, FOnBasicBeamoPostManifestPullError, FOnBasicBeamoPostManifestPullComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UBasicBeamoPostManifestPullRequest, UManifestChecksums, FOnBasicBeamoPostManifestPullSuccess, FOnBasicBeamoPostManifestPullError, FOnBasicBeamoPostManifestPullComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamBeamoApi::CPP_PostManifestPullImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UBasicBeamoPostManifestPullRequest* RequestData, const FOnBasicBeamoPostManifestPullFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
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
		Backend->RunAuthenticatedCodeRequestProcessor<UBasicBeamoPostManifestPullRequest, UManifestChecksums>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UBasicBeamoPostManifestPullRequest, UManifestChecksums>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamBeamoApi::BP_GetRegistryImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UGetRegistryRequest* RequestData, const FOnGetRegistrySuccess& OnSuccess, const FOnGetRegistryError& OnError, const FOnGetRegistryComplete& OnComplete, 
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
		Backend->RunAuthenticatedBlueprintRequestProcessor<UGetRegistryRequest, UGetElasticContainerRegistryURI, FOnGetRegistrySuccess, FOnGetRegistryError, FOnGetRegistryComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UGetRegistryRequest, UGetElasticContainerRegistryURI, FOnGetRegistrySuccess, FOnGetRegistryError, FOnGetRegistryComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamBeamoApi::CPP_GetRegistryImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UGetRegistryRequest* RequestData, const FOnGetRegistryFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
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
		Backend->RunAuthenticatedCodeRequestProcessor<UGetRegistryRequest, UGetElasticContainerRegistryURI>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UGetRegistryRequest, UGetElasticContainerRegistryURI>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamBeamoApi::BP_PostManifestDeployImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UPostManifestDeployRequest* RequestData, const FOnPostManifestDeploySuccess& OnSuccess, const FOnPostManifestDeployError& OnError, const FOnPostManifestDeployComplete& OnComplete, 
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
		Backend->RunAuthenticatedBlueprintRequestProcessor<UPostManifestDeployRequest, UEmptyResponse, FOnPostManifestDeploySuccess, FOnPostManifestDeployError, FOnPostManifestDeployComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPostManifestDeployRequest, UEmptyResponse, FOnPostManifestDeploySuccess, FOnPostManifestDeployError, FOnPostManifestDeployComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamBeamoApi::CPP_PostManifestDeployImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UPostManifestDeployRequest* RequestData, const FOnPostManifestDeployFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
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
		Backend->RunAuthenticatedCodeRequestProcessor<UPostManifestDeployRequest, UEmptyResponse>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPostManifestDeployRequest, UEmptyResponse>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamBeamoApi::BP_PostMicroserviceFederationImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UPostMicroserviceFederationRequest* RequestData, const FOnPostMicroserviceFederationSuccess& OnSuccess, const FOnPostMicroserviceFederationError& OnError, const FOnPostMicroserviceFederationComplete& OnComplete, 
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
		Backend->RunAuthenticatedBlueprintRequestProcessor<UPostMicroserviceFederationRequest, USupportedFederationsResponse, FOnPostMicroserviceFederationSuccess, FOnPostMicroserviceFederationError, FOnPostMicroserviceFederationComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UPostMicroserviceFederationRequest, USupportedFederationsResponse, FOnPostMicroserviceFederationSuccess, FOnPostMicroserviceFederationError, FOnPostMicroserviceFederationComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamBeamoApi::CPP_PostMicroserviceFederationImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UPostMicroserviceFederationRequest* RequestData, const FOnPostMicroserviceFederationFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
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
		Backend->RunAuthenticatedCodeRequestProcessor<UPostMicroserviceFederationRequest, USupportedFederationsResponse>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UPostMicroserviceFederationRequest, USupportedFederationsResponse>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamBeamoApi::BP_BasicBeamoGetStorageConnectionImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UBasicBeamoGetStorageConnectionRequest* RequestData, const FOnBasicBeamoGetStorageConnectionSuccess& OnSuccess, const FOnBasicBeamoGetStorageConnectionError& OnError, const FOnBasicBeamoGetStorageConnectionComplete& OnComplete, 
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
		Backend->RunAuthenticatedBlueprintRequestProcessor<UBasicBeamoGetStorageConnectionRequest, UConnectionString, FOnBasicBeamoGetStorageConnectionSuccess, FOnBasicBeamoGetStorageConnectionError, FOnBasicBeamoGetStorageConnectionComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UBasicBeamoGetStorageConnectionRequest, UConnectionString, FOnBasicBeamoGetStorageConnectionSuccess, FOnBasicBeamoGetStorageConnectionError, FOnBasicBeamoGetStorageConnectionComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamBeamoApi::CPP_BasicBeamoGetStorageConnectionImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UBasicBeamoGetStorageConnectionRequest* RequestData, const FOnBasicBeamoGetStorageConnectionFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
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
		Backend->RunAuthenticatedCodeRequestProcessor<UBasicBeamoGetStorageConnectionRequest, UConnectionString>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UBasicBeamoGetStorageConnectionRequest, UConnectionString>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamBeamoApi::BP_GetManifestImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UBasicBeamoGetManifestRequest* RequestData, const FOnBasicBeamoGetManifestSuccess& OnSuccess, const FOnBasicBeamoGetManifestError& OnError, const FOnBasicBeamoGetManifestComplete& OnComplete, 
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
		Backend->RunAuthenticatedBlueprintRequestProcessor<UBasicBeamoGetManifestRequest, UGetManifestResponse, FOnBasicBeamoGetManifestSuccess, FOnBasicBeamoGetManifestError, FOnBasicBeamoGetManifestComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UBasicBeamoGetManifestRequest, UGetManifestResponse, FOnBasicBeamoGetManifestSuccess, FOnBasicBeamoGetManifestError, FOnBasicBeamoGetManifestComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamBeamoApi::CPP_GetManifestImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UBasicBeamoGetManifestRequest* RequestData, const FOnBasicBeamoGetManifestFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
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
		Backend->RunAuthenticatedCodeRequestProcessor<UBasicBeamoGetManifestRequest, UGetManifestResponse>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UBasicBeamoGetManifestRequest, UGetManifestResponse>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

		
void UBeamBeamoApi::BP_PostManifestImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken,
                                UBasicBeamoPostManifestRequest* RequestData, const FOnBasicBeamoPostManifestSuccess& OnSuccess, const FOnBasicBeamoPostManifestError& OnError, const FOnBasicBeamoPostManifestComplete& OnComplete, 
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
		Backend->RunAuthenticatedBlueprintRequestProcessor<UBasicBeamoPostManifestRequest, UPostManifestResponse, FOnBasicBeamoPostManifestSuccess, FOnBasicBeamoPostManifestError, FOnBasicBeamoPostManifestComplete>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)
		const auto BeamRequestProcessor = Backend->MakeAuthenticatedBlueprintRequestProcessor<UBasicBeamoPostManifestRequest, UPostManifestResponse, FOnBasicBeamoPostManifestSuccess, FOnBasicBeamoPostManifestError, FOnBasicBeamoPostManifestComplete>
			(OutRequestId, TargetRealm, AuthToken, RequestData, OnSuccess, OnError, OnComplete);
		Request->OnProcessRequestComplete().BindLambda(BeamRequestProcessor);
	    
		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}

void UBeamBeamoApi::CPP_PostManifestImpl(const FBeamRealmHandle& TargetRealm, const FBeamRetryConfig& RetryConfig, const FBeamAuthToken& AuthToken, 
                              UBasicBeamoPostManifestRequest* RequestData, const FOnBasicBeamoPostManifestFullResponse& Handler, int64& OutRequestId, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
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
		Backend->RunAuthenticatedCodeRequestProcessor<UBasicBeamoPostManifestRequest, UPostManifestResponse>
			(200, CachedResponse, EHttpRequestStatus::Succeeded, OutRequestId, TargetRealm, AuthToken, RequestData, Handler);		
	}
	// If not cached...
	else
	{
		// Binds the handler to the static response handler (pre-generated)	
		auto ResponseProcessor = Backend->MakeAuthenticatedCodeRequestProcessor<UBasicBeamoPostManifestRequest, UPostManifestResponse>
			(OutRequestId, TargetRealm, AuthToken, RequestData, Handler);
		Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

		// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
		Backend->SendPreparedRequest(OutRequestId, CallingContext);	
	}
}






void UBeamBeamoApi::CPP_PostManifests(const FUserSlot& UserSlot, UPostManifestsRequest* Request, const FOnPostManifestsFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostManifestsRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_PostManifestsImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::CPP_ApiBeamoGetManifests(const FUserSlot& UserSlot, UApiBeamoGetManifestsRequest* Request, const FOnApiBeamoGetManifestsFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UApiBeamoGetManifestsRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_ApiBeamoGetManifestsImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::CPP_ApiBeamoGetManifestsByManifestId(const FUserSlot& UserSlot, UApiBeamoGetManifestsByManifestIdRequest* Request, const FOnApiBeamoGetManifestsByManifestIdFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UApiBeamoGetManifestsByManifestIdRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_ApiBeamoGetManifestsByManifestIdImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::CPP_GetManifestsCurrent(const FUserSlot& UserSlot, UGetManifestsCurrentRequest* Request, const FOnGetManifestsCurrentFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UGetManifestsCurrentRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_GetManifestsCurrentImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::CPP_PostManifestsCurrent(const FUserSlot& UserSlot, UPostManifestsCurrentRequest* Request, const FOnPostManifestsCurrentFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostManifestsCurrentRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_PostManifestsCurrentImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::CPP_PostManifestsPromote(const FUserSlot& UserSlot, UPostManifestsPromoteRequest* Request, const FOnPostManifestsPromoteFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostManifestsPromoteRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_PostManifestsPromoteImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::CPP_ApiBeamoGetTemplates(const FUserSlot& UserSlot, UApiBeamoGetTemplatesRequest* Request, const FOnApiBeamoGetTemplatesFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UApiBeamoGetTemplatesRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_ApiBeamoGetTemplatesImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::CPP_ApiBeamoGetStatus(const FUserSlot& UserSlot, UApiBeamoGetStatusRequest* Request, const FOnApiBeamoGetStatusFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UApiBeamoGetStatusRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_ApiBeamoGetStatusImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::CPP_GetRegistryUri(const FUserSlot& UserSlot, UGetRegistryUriRequest* Request, const FOnGetRegistryUriFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UGetRegistryUriRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_GetRegistryUriImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::CPP_PostServicesRegistrations(const FUserSlot& UserSlot, UPostServicesRegistrationsRequest* Request, const FOnPostServicesRegistrationsFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostServicesRegistrationsRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_PostServicesRegistrationsImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::CPP_PostServicesFederation(const FUserSlot& UserSlot, UPostServicesFederationRequest* Request, const FOnPostServicesFederationFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostServicesFederationRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_PostServicesFederationImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::CPP_PutServicesFederationTraffic(const FUserSlot& UserSlot, UPutServicesFederationTrafficRequest* Request, const FOnPutServicesFederationTrafficFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPutServicesFederationTrafficRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_PutServicesFederationTrafficImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::CPP_DeleteServicesFederationTraffic(const FUserSlot& UserSlot, UDeleteServicesFederationTrafficRequest* Request, const FOnDeleteServicesFederationTrafficFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UDeleteServicesFederationTrafficRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_DeleteServicesFederationTrafficImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::CPP_PostServicesMetricsRequest(const FUserSlot& UserSlot, UPostServicesMetricsRequestRequest* Request, const FOnPostServicesMetricsRequestFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostServicesMetricsRequestRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_PostServicesMetricsRequestImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::CPP_PostServicesLogsQuery(const FUserSlot& UserSlot, UPostServicesLogsQueryRequest* Request, const FOnPostServicesLogsQueryFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostServicesLogsQueryRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_PostServicesLogsQueryImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::CPP_DeleteServicesLogsQuery(const FUserSlot& UserSlot, UDeleteServicesLogsQueryRequest* Request, const FOnDeleteServicesLogsQueryFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UDeleteServicesLogsQueryRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_DeleteServicesLogsQueryImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::CPP_GetServicesLogsQuery(const FUserSlot& UserSlot, UGetServicesLogsQueryRequest* Request, const FOnGetServicesLogsQueryFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UGetServicesLogsQueryRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_GetServicesLogsQueryImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::CPP_GetServicesSecret(const FUserSlot& UserSlot, UGetServicesSecretRequest* Request, const FOnGetServicesSecretFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UGetServicesSecretRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_GetServicesSecretImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::CPP_ApiBeamoGetStorageConnection(const FUserSlot& UserSlot, UApiBeamoGetStorageConnectionRequest* Request, const FOnApiBeamoGetStorageConnectionFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UApiBeamoGetStorageConnectionRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_ApiBeamoGetStorageConnectionImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::CPP_ApiBeamoGetStoragePerformanceByStorageObjectName(const FUserSlot& UserSlot, UApiBeamoGetStoragePerformanceByStorageObjectNameRequest* Request, const FOnApiBeamoGetStoragePerformanceByStorageObjectNameFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UApiBeamoGetStoragePerformanceByStorageObjectNameRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_ApiBeamoGetStoragePerformanceByStorageObjectNameImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::CPP_PostMicroserviceRegistrations(const FUserSlot& UserSlot, UPostMicroserviceRegistrationsRequest* Request, const FOnPostMicroserviceRegistrationsFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostMicroserviceRegistrationsRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_PostMicroserviceRegistrationsImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::CPP_PutMicroserviceFederationTraffic(const FUserSlot& UserSlot, UPutMicroserviceFederationTrafficRequest* Request, const FOnPutMicroserviceFederationTrafficFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPutMicroserviceFederationTrafficRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_PutMicroserviceFederationTrafficImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::CPP_DeleteMicroserviceFederationTraffic(const FUserSlot& UserSlot, UDeleteMicroserviceFederationTrafficRequest* Request, const FOnDeleteMicroserviceFederationTrafficFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UDeleteMicroserviceFederationTrafficRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_DeleteMicroserviceFederationTrafficImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::CPP_PostImageUrls(const FUserSlot& UserSlot, UPostImageUrlsRequest* Request, const FOnPostImageUrlsFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostImageUrlsRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_PostImageUrlsImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::CPP_PostMetricsUrl(const FUserSlot& UserSlot, UPostMetricsUrlRequest* Request, const FOnPostMetricsUrlFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostMetricsUrlRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_PostMetricsUrlImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::CPP_GetMicroserviceSecret(const FUserSlot& UserSlot, UGetMicroserviceSecretRequest* Request, const FOnGetMicroserviceSecretFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UGetMicroserviceSecretRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_GetMicroserviceSecretImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::CPP_PostQueryLogsResult(const FUserSlot& UserSlot, UPostQueryLogsResultRequest* Request, const FOnPostQueryLogsResultFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostQueryLogsResultRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_PostQueryLogsResultImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::CPP_BasicBeamoGetStoragePerformance(const FUserSlot& UserSlot, UBasicBeamoGetStoragePerformanceRequest* Request, const FOnBasicBeamoGetStoragePerformanceFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UBasicBeamoGetStoragePerformanceRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_BasicBeamoGetStoragePerformanceImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::CPP_BasicBeamoGetManifests(const FUserSlot& UserSlot, UBasicBeamoGetManifestsRequest* Request, const FOnBasicBeamoGetManifestsFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UBasicBeamoGetManifestsRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_BasicBeamoGetManifestsImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::CPP_BasicBeamoGetTemplates(const FUserSlot& UserSlot, UBasicBeamoGetTemplatesRequest* Request, const FOnBasicBeamoGetTemplatesFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UBasicBeamoGetTemplatesRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_BasicBeamoGetTemplatesImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::CPP_PostQueryLogs(const FUserSlot& UserSlot, UPostQueryLogsRequest* Request, const FOnPostQueryLogsFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostQueryLogsRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_PostQueryLogsImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::CPP_DeleteQueryLogs(const FUserSlot& UserSlot, UDeleteQueryLogsRequest* Request, const FOnDeleteQueryLogsFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UDeleteQueryLogsRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_DeleteQueryLogsImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::CPP_PostLogsUrl(const FUserSlot& UserSlot, UPostLogsUrlRequest* Request, const FOnPostLogsUrlFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostLogsUrlRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_PostLogsUrlImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::CPP_PutImageCommit(const FUserSlot& UserSlot, UPutImageCommitRequest* Request, const FOnPutImageCommitFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPutImageCommitRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_PutImageCommitImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::CPP_GetUploadAPI(const FUserSlot& UserSlot, UGetUploadAPIRequest* Request, const FOnGetUploadAPIFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UGetUploadAPIRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_GetUploadAPIImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::CPP_BasicBeamoGetStatus(const FUserSlot& UserSlot, UBasicBeamoGetStatusRequest* Request, const FOnBasicBeamoGetStatusFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UBasicBeamoGetStatusRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_BasicBeamoGetStatusImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::CPP_GetManifestCurrent(const FUserSlot& UserSlot, UGetManifestCurrentRequest* Request, const FOnGetManifestCurrentFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UGetManifestCurrentRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_GetManifestCurrentImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::CPP_PostManifestPull(const FUserSlot& UserSlot, UBasicBeamoPostManifestPullRequest* Request, const FOnBasicBeamoPostManifestPullFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UBasicBeamoPostManifestPullRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_PostManifestPullImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::CPP_GetRegistry(const FUserSlot& UserSlot, UGetRegistryRequest* Request, const FOnGetRegistryFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UGetRegistryRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_GetRegistryImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::CPP_PostManifestDeploy(const FUserSlot& UserSlot, UPostManifestDeployRequest* Request, const FOnPostManifestDeployFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostManifestDeployRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_PostManifestDeployImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::CPP_PostMicroserviceFederation(const FUserSlot& UserSlot, UPostMicroserviceFederationRequest* Request, const FOnPostMicroserviceFederationFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostMicroserviceFederationRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_PostMicroserviceFederationImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::CPP_BasicBeamoGetStorageConnection(const FUserSlot& UserSlot, UBasicBeamoGetStorageConnectionRequest* Request, const FOnBasicBeamoGetStorageConnectionFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UBasicBeamoGetStorageConnectionRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_BasicBeamoGetStorageConnectionImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::CPP_GetManifest(const FUserSlot& UserSlot, UBasicBeamoGetManifestRequest* Request, const FOnBasicBeamoGetManifestFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UBasicBeamoGetManifestRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_GetManifestImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::CPP_PostManifest(const FUserSlot& UserSlot, UBasicBeamoPostManifestRequest* Request, const FOnBasicBeamoPostManifestFullResponse& Handler, FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext) const
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UBasicBeamoPostManifestRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

    int64 OutRequestId;
	CPP_PostManifestImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, Handler, OutRequestId, OpHandle, CallingContext);
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}






void UBeamBeamoApi::PostManifests(FUserSlot UserSlot, UPostManifestsRequest* Request, const FOnPostManifestsSuccess& OnSuccess, const FOnPostManifestsError& OnError, const FOnPostManifestsComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostManifestsRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_PostManifestsImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::ApiBeamoGetManifests(FUserSlot UserSlot, UApiBeamoGetManifestsRequest* Request, const FOnApiBeamoGetManifestsSuccess& OnSuccess, const FOnApiBeamoGetManifestsError& OnError, const FOnApiBeamoGetManifestsComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UApiBeamoGetManifestsRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_ApiBeamoGetManifestsImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::ApiBeamoGetManifestsByManifestId(FUserSlot UserSlot, UApiBeamoGetManifestsByManifestIdRequest* Request, const FOnApiBeamoGetManifestsByManifestIdSuccess& OnSuccess, const FOnApiBeamoGetManifestsByManifestIdError& OnError, const FOnApiBeamoGetManifestsByManifestIdComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UApiBeamoGetManifestsByManifestIdRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_ApiBeamoGetManifestsByManifestIdImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::GetManifestsCurrent(FUserSlot UserSlot, UGetManifestsCurrentRequest* Request, const FOnGetManifestsCurrentSuccess& OnSuccess, const FOnGetManifestsCurrentError& OnError, const FOnGetManifestsCurrentComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UGetManifestsCurrentRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_GetManifestsCurrentImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::PostManifestsCurrent(FUserSlot UserSlot, UPostManifestsCurrentRequest* Request, const FOnPostManifestsCurrentSuccess& OnSuccess, const FOnPostManifestsCurrentError& OnError, const FOnPostManifestsCurrentComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostManifestsCurrentRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_PostManifestsCurrentImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::PostManifestsPromote(FUserSlot UserSlot, UPostManifestsPromoteRequest* Request, const FOnPostManifestsPromoteSuccess& OnSuccess, const FOnPostManifestsPromoteError& OnError, const FOnPostManifestsPromoteComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostManifestsPromoteRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_PostManifestsPromoteImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::ApiBeamoGetTemplates(FUserSlot UserSlot, UApiBeamoGetTemplatesRequest* Request, const FOnApiBeamoGetTemplatesSuccess& OnSuccess, const FOnApiBeamoGetTemplatesError& OnError, const FOnApiBeamoGetTemplatesComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UApiBeamoGetTemplatesRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_ApiBeamoGetTemplatesImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::ApiBeamoGetStatus(FUserSlot UserSlot, UApiBeamoGetStatusRequest* Request, const FOnApiBeamoGetStatusSuccess& OnSuccess, const FOnApiBeamoGetStatusError& OnError, const FOnApiBeamoGetStatusComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UApiBeamoGetStatusRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_ApiBeamoGetStatusImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::GetRegistryUri(FUserSlot UserSlot, UGetRegistryUriRequest* Request, const FOnGetRegistryUriSuccess& OnSuccess, const FOnGetRegistryUriError& OnError, const FOnGetRegistryUriComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UGetRegistryUriRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_GetRegistryUriImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::PostServicesRegistrations(FUserSlot UserSlot, UPostServicesRegistrationsRequest* Request, const FOnPostServicesRegistrationsSuccess& OnSuccess, const FOnPostServicesRegistrationsError& OnError, const FOnPostServicesRegistrationsComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostServicesRegistrationsRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_PostServicesRegistrationsImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::PostServicesFederation(FUserSlot UserSlot, UPostServicesFederationRequest* Request, const FOnPostServicesFederationSuccess& OnSuccess, const FOnPostServicesFederationError& OnError, const FOnPostServicesFederationComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostServicesFederationRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_PostServicesFederationImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::PutServicesFederationTraffic(FUserSlot UserSlot, UPutServicesFederationTrafficRequest* Request, const FOnPutServicesFederationTrafficSuccess& OnSuccess, const FOnPutServicesFederationTrafficError& OnError, const FOnPutServicesFederationTrafficComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPutServicesFederationTrafficRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_PutServicesFederationTrafficImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::DeleteServicesFederationTraffic(FUserSlot UserSlot, UDeleteServicesFederationTrafficRequest* Request, const FOnDeleteServicesFederationTrafficSuccess& OnSuccess, const FOnDeleteServicesFederationTrafficError& OnError, const FOnDeleteServicesFederationTrafficComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UDeleteServicesFederationTrafficRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_DeleteServicesFederationTrafficImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::PostServicesMetricsRequest(FUserSlot UserSlot, UPostServicesMetricsRequestRequest* Request, const FOnPostServicesMetricsRequestSuccess& OnSuccess, const FOnPostServicesMetricsRequestError& OnError, const FOnPostServicesMetricsRequestComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostServicesMetricsRequestRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_PostServicesMetricsRequestImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::PostServicesLogsQuery(FUserSlot UserSlot, UPostServicesLogsQueryRequest* Request, const FOnPostServicesLogsQuerySuccess& OnSuccess, const FOnPostServicesLogsQueryError& OnError, const FOnPostServicesLogsQueryComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostServicesLogsQueryRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_PostServicesLogsQueryImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::DeleteServicesLogsQuery(FUserSlot UserSlot, UDeleteServicesLogsQueryRequest* Request, const FOnDeleteServicesLogsQuerySuccess& OnSuccess, const FOnDeleteServicesLogsQueryError& OnError, const FOnDeleteServicesLogsQueryComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UDeleteServicesLogsQueryRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_DeleteServicesLogsQueryImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::GetServicesLogsQuery(FUserSlot UserSlot, UGetServicesLogsQueryRequest* Request, const FOnGetServicesLogsQuerySuccess& OnSuccess, const FOnGetServicesLogsQueryError& OnError, const FOnGetServicesLogsQueryComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UGetServicesLogsQueryRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_GetServicesLogsQueryImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::GetServicesSecret(FUserSlot UserSlot, UGetServicesSecretRequest* Request, const FOnGetServicesSecretSuccess& OnSuccess, const FOnGetServicesSecretError& OnError, const FOnGetServicesSecretComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UGetServicesSecretRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_GetServicesSecretImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::ApiBeamoGetStorageConnection(FUserSlot UserSlot, UApiBeamoGetStorageConnectionRequest* Request, const FOnApiBeamoGetStorageConnectionSuccess& OnSuccess, const FOnApiBeamoGetStorageConnectionError& OnError, const FOnApiBeamoGetStorageConnectionComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UApiBeamoGetStorageConnectionRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_ApiBeamoGetStorageConnectionImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::ApiBeamoGetStoragePerformanceByStorageObjectName(FUserSlot UserSlot, UApiBeamoGetStoragePerformanceByStorageObjectNameRequest* Request, const FOnApiBeamoGetStoragePerformanceByStorageObjectNameSuccess& OnSuccess, const FOnApiBeamoGetStoragePerformanceByStorageObjectNameError& OnError, const FOnApiBeamoGetStoragePerformanceByStorageObjectNameComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UApiBeamoGetStoragePerformanceByStorageObjectNameRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_ApiBeamoGetStoragePerformanceByStorageObjectNameImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::PostMicroserviceRegistrations(FUserSlot UserSlot, UPostMicroserviceRegistrationsRequest* Request, const FOnPostMicroserviceRegistrationsSuccess& OnSuccess, const FOnPostMicroserviceRegistrationsError& OnError, const FOnPostMicroserviceRegistrationsComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostMicroserviceRegistrationsRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_PostMicroserviceRegistrationsImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::PutMicroserviceFederationTraffic(FUserSlot UserSlot, UPutMicroserviceFederationTrafficRequest* Request, const FOnPutMicroserviceFederationTrafficSuccess& OnSuccess, const FOnPutMicroserviceFederationTrafficError& OnError, const FOnPutMicroserviceFederationTrafficComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPutMicroserviceFederationTrafficRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_PutMicroserviceFederationTrafficImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::DeleteMicroserviceFederationTraffic(FUserSlot UserSlot, UDeleteMicroserviceFederationTrafficRequest* Request, const FOnDeleteMicroserviceFederationTrafficSuccess& OnSuccess, const FOnDeleteMicroserviceFederationTrafficError& OnError, const FOnDeleteMicroserviceFederationTrafficComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UDeleteMicroserviceFederationTrafficRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_DeleteMicroserviceFederationTrafficImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::PostImageUrls(FUserSlot UserSlot, UPostImageUrlsRequest* Request, const FOnPostImageUrlsSuccess& OnSuccess, const FOnPostImageUrlsError& OnError, const FOnPostImageUrlsComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostImageUrlsRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_PostImageUrlsImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::PostMetricsUrl(FUserSlot UserSlot, UPostMetricsUrlRequest* Request, const FOnPostMetricsUrlSuccess& OnSuccess, const FOnPostMetricsUrlError& OnError, const FOnPostMetricsUrlComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostMetricsUrlRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_PostMetricsUrlImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::GetMicroserviceSecret(FUserSlot UserSlot, UGetMicroserviceSecretRequest* Request, const FOnGetMicroserviceSecretSuccess& OnSuccess, const FOnGetMicroserviceSecretError& OnError, const FOnGetMicroserviceSecretComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UGetMicroserviceSecretRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_GetMicroserviceSecretImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::PostQueryLogsResult(FUserSlot UserSlot, UPostQueryLogsResultRequest* Request, const FOnPostQueryLogsResultSuccess& OnSuccess, const FOnPostQueryLogsResultError& OnError, const FOnPostQueryLogsResultComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostQueryLogsResultRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_PostQueryLogsResultImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::BasicBeamoGetStoragePerformance(FUserSlot UserSlot, UBasicBeamoGetStoragePerformanceRequest* Request, const FOnBasicBeamoGetStoragePerformanceSuccess& OnSuccess, const FOnBasicBeamoGetStoragePerformanceError& OnError, const FOnBasicBeamoGetStoragePerformanceComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UBasicBeamoGetStoragePerformanceRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_BasicBeamoGetStoragePerformanceImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::BasicBeamoGetManifests(FUserSlot UserSlot, UBasicBeamoGetManifestsRequest* Request, const FOnBasicBeamoGetManifestsSuccess& OnSuccess, const FOnBasicBeamoGetManifestsError& OnError, const FOnBasicBeamoGetManifestsComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UBasicBeamoGetManifestsRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_BasicBeamoGetManifestsImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::BasicBeamoGetTemplates(FUserSlot UserSlot, UBasicBeamoGetTemplatesRequest* Request, const FOnBasicBeamoGetTemplatesSuccess& OnSuccess, const FOnBasicBeamoGetTemplatesError& OnError, const FOnBasicBeamoGetTemplatesComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UBasicBeamoGetTemplatesRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_BasicBeamoGetTemplatesImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::PostQueryLogs(FUserSlot UserSlot, UPostQueryLogsRequest* Request, const FOnPostQueryLogsSuccess& OnSuccess, const FOnPostQueryLogsError& OnError, const FOnPostQueryLogsComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostQueryLogsRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_PostQueryLogsImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::DeleteQueryLogs(FUserSlot UserSlot, UDeleteQueryLogsRequest* Request, const FOnDeleteQueryLogsSuccess& OnSuccess, const FOnDeleteQueryLogsError& OnError, const FOnDeleteQueryLogsComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UDeleteQueryLogsRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_DeleteQueryLogsImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::PostLogsUrl(FUserSlot UserSlot, UPostLogsUrlRequest* Request, const FOnPostLogsUrlSuccess& OnSuccess, const FOnPostLogsUrlError& OnError, const FOnPostLogsUrlComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostLogsUrlRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_PostLogsUrlImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::PutImageCommit(FUserSlot UserSlot, UPutImageCommitRequest* Request, const FOnPutImageCommitSuccess& OnSuccess, const FOnPutImageCommitError& OnError, const FOnPutImageCommitComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPutImageCommitRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_PutImageCommitImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::GetUploadAPI(FUserSlot UserSlot, UGetUploadAPIRequest* Request, const FOnGetUploadAPISuccess& OnSuccess, const FOnGetUploadAPIError& OnError, const FOnGetUploadAPIComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UGetUploadAPIRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_GetUploadAPIImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::BasicBeamoGetStatus(FUserSlot UserSlot, UBasicBeamoGetStatusRequest* Request, const FOnBasicBeamoGetStatusSuccess& OnSuccess, const FOnBasicBeamoGetStatusError& OnError, const FOnBasicBeamoGetStatusComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UBasicBeamoGetStatusRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_BasicBeamoGetStatusImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::GetManifestCurrent(FUserSlot UserSlot, UGetManifestCurrentRequest* Request, const FOnGetManifestCurrentSuccess& OnSuccess, const FOnGetManifestCurrentError& OnError, const FOnGetManifestCurrentComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UGetManifestCurrentRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_GetManifestCurrentImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::PostManifestPull(FUserSlot UserSlot, UBasicBeamoPostManifestPullRequest* Request, const FOnBasicBeamoPostManifestPullSuccess& OnSuccess, const FOnBasicBeamoPostManifestPullError& OnError, const FOnBasicBeamoPostManifestPullComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UBasicBeamoPostManifestPullRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_PostManifestPullImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::GetRegistry(FUserSlot UserSlot, UGetRegistryRequest* Request, const FOnGetRegistrySuccess& OnSuccess, const FOnGetRegistryError& OnError, const FOnGetRegistryComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UGetRegistryRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_GetRegistryImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::PostManifestDeploy(FUserSlot UserSlot, UPostManifestDeployRequest* Request, const FOnPostManifestDeploySuccess& OnSuccess, const FOnPostManifestDeployError& OnError, const FOnPostManifestDeployComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostManifestDeployRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_PostManifestDeployImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::PostMicroserviceFederation(FUserSlot UserSlot, UPostMicroserviceFederationRequest* Request, const FOnPostMicroserviceFederationSuccess& OnSuccess, const FOnPostMicroserviceFederationError& OnError, const FOnPostMicroserviceFederationComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UPostMicroserviceFederationRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_PostMicroserviceFederationImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::BasicBeamoGetStorageConnection(FUserSlot UserSlot, UBasicBeamoGetStorageConnectionRequest* Request, const FOnBasicBeamoGetStorageConnectionSuccess& OnSuccess, const FOnBasicBeamoGetStorageConnectionError& OnError, const FOnBasicBeamoGetStorageConnectionComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UBasicBeamoGetStorageConnectionRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_BasicBeamoGetStorageConnectionImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::GetManifest(FUserSlot UserSlot, UBasicBeamoGetManifestRequest* Request, const FOnBasicBeamoGetManifestSuccess& OnSuccess, const FOnBasicBeamoGetManifestError& OnError, const FOnBasicBeamoGetManifestComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UBasicBeamoGetManifestRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_GetManifestImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

		
void UBeamBeamoApi::PostManifest(FUserSlot UserSlot, UBasicBeamoPostManifestRequest* Request, const FOnBasicBeamoPostManifestSuccess& OnSuccess, const FOnBasicBeamoPostManifestError& OnError, const FOnBasicBeamoPostManifestComplete& OnComplete,  FBeamRequestContext& OutRequestContext, FBeamOperationHandle OpHandle, const UObject* CallingContext)
{
	// AUTO-GENERATED...
	FBeamRealmUser AuthenticatedUser;
	Backend->BeamUserSlots->GetUserDataAtSlot(UserSlot, AuthenticatedUser, CallingContext);

	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForUserSlotAndRequestType(UBasicBeamoPostManifestRequest::StaticClass()->GetName(), UserSlot, RetryConfig);

	int64 OutRequestId;
	BP_PostManifestImpl(GetDefault<UBeamCoreSettings>()->TargetRealm, RetryConfig, AuthenticatedUser.AuthToken, Request, OnSuccess, OnError, OnComplete, OutRequestId, OpHandle, CallingContext);	
	OutRequestContext = FBeamRequestContext{OutRequestId, RetryConfig, GetDefault<UBeamCoreSettings>()->TargetRealm, -1, UserSlot, AS_None};
}

