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
	FName ExpectedEventId;
	int64 ExpectedEventRequestId;
	FString ExpectedEventSystem;
	FString ExpectedEventCode;
	TScriptInterface<IBeamOperationEventData> ExpectedEventData;


	// Done callback so that we can run latent tests correctly
	FDoneDelegate DoneDelegateForLatentTests;


	UFUNCTION()
	void MockOperationEvent_Expected(FBeamOperationEvent OperationEvent) const;
	UFUNCTION()
	void MockOperationEvent_Fail(FBeamOperationEvent OperationEvent) const;
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

	UPROPERTY()
	TArray<FBeamRequestContext> ExpectedContexts;
	UPROPERTY()
	TArray<TScriptInterface<IBeamBaseRequestInterface>> ExpectedRequests;
	UPROPERTY()
	TArray<UObject*> ExpectedResponses;
	UPROPERTY()
	TArray<FBeamErrorResponse> ExpectedErrors;

	// Done callback so that we can run latent tests correctly
	FDoneDelegate DoneDelegateForLatentTests;

	UFUNCTION()
	void MockWaitCompleteEvent_Expected(const FBeamWaitCompleteEvent& Evt) const;
	UFUNCTION()
	void MockWaitCompleteEvent_Fail(const FBeamWaitCompleteEvent& Evt) const;
};
