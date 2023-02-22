#pragma once
#include "BeamBackend/BeamBackend.h"
#include "RequestTracker/BeamRequestTracker.h"
#include "RequestTracker/BeamOperation.h"

#include "BeamRequestTrackerTestCallbacks.generated.h"

class FBeamRequestTrackerSpec;

UCLASS()
class UBeamRequestTrackerOperationTestCallbacks final : public UObject
{
	GENERATED_BODY()

public:
	FBeamRequestTrackerSpec* Spec;

	UPROPERTY()
	UBeamBackend* BeamBackend;

	UPROPERTY()
	UBeamRequestTracker* BeamRequestTracker;

	TArray<int64> ExpectedRequestsInOperations;
	TArray<FUserSlot> ExpectedParticipants;

	EBeamOperationEventType ExpectedEventType;
	uint8 ExpectedEventSubTypeCode;
	int64 ExpectedEventRequestId;	
	FString ExpectedEventSystem;
	FString ExpectedEventData;
	
	
	
	// Done callback so that we can run latent tests correctly
	FDoneDelegate DoneDelegateForLatentTests;
	

	UFUNCTION()
	void MockOperationEvent_Expected(const TArray<FUserSlot>& UserSlots, FBeamOperationEvent OperationEvent) const;
	UFUNCTION()
	void MockOperationEvent_Fail(const TArray<FUserSlot>& UserSlots, FBeamOperationEvent OperationEvent) const;
};


UCLASS()
class UBeamRequestTrackerWaitAllTestCallbacks final : public UObject
{
	GENERATED_BODY()

public:
	FBeamRequestTrackerSpec* Spec;

	UPROPERTY()
	UBeamBackend* BeamBackend;

	UPROPERTY()
	UBeamRequestTracker* BeamRequestTracker;

	TArray<FBeamRequestContext> ExpectedContexts;
	TArray<TScriptInterface<IBeamBaseRequestInterface>> ExpectedRequests;
	TArray<UObject*> ExpectedResponses;
	TArray<FBeamErrorResponse> ExpectedErrors;	

	// Done callback so that we can run latent tests correctly
	FDoneDelegate DoneDelegateForLatentTests;	

	UFUNCTION()
	void MockWaitCompleteEvent_Expected(const TArray<FBeamRequestContext>& Contexts, const TArray<TScriptInterface<IBeamBaseRequestInterface>>& Requests,
									const TArray<UObject*>& Responses, const TArray<FBeamErrorResponse>& Errors) const;
	UFUNCTION()
	void MockWaitCompleteEvent_Fail(const TArray<FBeamRequestContext>& Contexts, const TArray<TScriptInterface<IBeamBaseRequestInterface>>& Requests,
									const TArray<UObject*>& Responses, const TArray<FBeamErrorResponse>& Errors) const;
};

