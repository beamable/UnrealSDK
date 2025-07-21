#include "BeamableCore/Public/BeamBackend/BeamGenericApi.h"
#include "BeamCoreSettings.h"


void UBeamGenericApi::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	Backend = Cast<UBeamBackend>(Collection.InitializeDependency(UBeamBackend::StaticClass()));
	RequestTracker = Cast<UBeamRequestTracker>(Collection.InitializeDependency(UBeamRequestTracker::StaticClass()));
	ResponseCache = Cast<UBeamResponseCache>(Collection.InitializeDependency(UBeamResponseCache::StaticClass()));
}

void UBeamGenericApi::Deinitialize()
{
	Super::Deinitialize();
}

FBeamRequestContext UBeamGenericApi::CPP_ExecuteNonBeamRequest(UGenericBeamRequest* RequestData, const FOnGenericBeamRequestFullResponse& Handler, const FBeamOperationHandle OpHandle,
                                                               const UObject* CallingContext) const
{
	FBeamRequestContext OutRequestId = {};

	// Get the retry config for this class of generic requests
	FBeamRetryConfig RetryConfig;
	Backend->GetRetryConfigForRequestType(RequestData->RequestTypeName, RetryConfig);

	// Create it
	const auto Request = Backend->CreateGenericBeamRequest(OutRequestId.RequestId, RetryConfig, RequestData);

	// If we are making this request as part of an operation, we add it to it.
	if (OpHandle.OperationId >= 0)
		RequestTracker->AddRequestToOperation(OpHandle, OutRequestId.RequestId);

	// Binds the handler to the static response handler (pre-generated)	
	auto ResponseProcessor = Backend->MakeCodeRequestProcessor<UGenericBeamRequest, UGenericBeamResponse>(OutRequestId.RequestId, RequestData, Handler, CallingContext);
	Request->OnProcessRequestComplete().BindLambda(ResponseProcessor);

	// Logic that actually talks to the backend --- if you pass in some other delegate, that means you can avoid making the actual back-end call.	
	Backend->SendPreparedRequest(OutRequestId.RequestId, CallingContext);

	return OutRequestId;
}
