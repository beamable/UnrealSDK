#include "BeamRequestTrackerTestCallbacks.h"

#include "BeamRequestTracker.spec.h"

void UBeamRequestTrackerOperationTestCallbacks::MockOperationEvent_Expected(const TArray<FUserSlot>& UserSlots, FBeamOperationEvent OperationEvent) const
{
	Spec->TestEqual("Event Request Id was correctly passed along", OperationEvent.RequestId, ExpectedEventRequestId);
	Spec->TestEqual("Event Type was correctly passed along", OperationEvent.EventType, ExpectedEventType);
	Spec->TestEqual("Event SubType was correctly passed along", OperationEvent.EventSubTypeCode, ExpectedEventSubTypeCode);
	Spec->TestEqual("Event System was correctly passed along", OperationEvent.System, ExpectedEventSystem);
	Spec->TestEqual("Event Data was correctly passed along", OperationEvent.EventData, ExpectedEventData);
	Spec->TestEqual("Operation Participants was correctly passed along", UserSlots, ExpectedParticipants);

	Spec->TestEqual("Operation Participants was correctly passed along", BeamRequestTracker->ActiveOperationState.FindRef(OperationEvent.OwnerHandle).DependentRequests,
	                ExpectedRequestsInOperations);
}

void UBeamRequestTrackerOperationTestCallbacks::MockOperationEvent_Fail(const TArray<FUserSlot>& UserSlots, FBeamOperationEvent OperationEvent) const
{
	Spec->TestTrue("Callback should not be invoked!", false);
}

void UBeamRequestTrackerWaitAllTestCallbacks::MockWaitCompleteEvent_Expected(const TArray<FBeamRequestContext>& Contexts, const TArray<TScriptInterface<IBeamBaseRequestInterface>>& Requests,
	const TArray<UObject*>& Responses, const TArray<FBeamErrorResponse>& Errors) const
{
	UE_LOG(LogTemp, Display, TEXT("Callback was called"));
	
	Spec->TestEqual("Contexts are the same", Contexts, ExpectedContexts);
	Spec->TestEqual("Requests are the same", Requests, ExpectedRequests);
	// Spec->TestEqual("Responses are the same", Responses, ExpectedResponses);
	// Spec->TestEqual("Responses are the same", Errors, ExpectedErrors);
}

void UBeamRequestTrackerWaitAllTestCallbacks::MockWaitCompleteEvent_Fail(const TArray<FBeamRequestContext>& Contexts, const TArray<TScriptInterface<IBeamBaseRequestInterface>>& Requests,
                                                                         const TArray<UObject*>& Responses, const TArray<FBeamErrorResponse>& Errors) const
{
	Spec->TestTrue("Callback should not be invoked!", false);
}
