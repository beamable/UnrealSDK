#include "BeamRequestTrackerTestCallbacks.h"

#include "BeamRequestTracker.spec.h"

void UBeamRequestTrackerOperationTestCallbacks::MockOperationEvent_Expected(FBeamOperationEvent OperationEvent) const
{
	Spec->TestEqual("Event Request Id was correctly passed along", OperationEvent.RequestId, ExpectedEventRequestId);
	Spec->TestEqual("Event Type was correctly passed along", OperationEvent.EventType, ExpectedEventType);
	Spec->TestEqual("Event Id was correctly passed along", OperationEvent.EventId, ExpectedEventId);
	Spec->TestEqual("Event System was correctly passed along", OperationEvent.System, ExpectedEventSystem);
	Spec->TestEqual("Event Code was correctly passed along", OperationEvent.EventCode, ExpectedEventCode);
	Spec->TestEqual("Event Data was correctly passed along", OperationEvent.EventData, ExpectedEventData);
	Spec->TestEqual("Operation Participants was correctly passed along", BeamRequestTracker->ActiveOperationState.FindChecked(OperationEvent.OwnerHandle)->DependentUserSlots, ExpectedParticipants);
	Spec->TestEqual("Operation Requests was correctly passed along", BeamRequestTracker->ActiveOperationState.FindRef(OperationEvent.OwnerHandle)->DependentRequests, ExpectedRequestsInOperations);
}

void UBeamRequestTrackerOperationTestCallbacks::MockOperationEvent_Fail(FBeamOperationEvent OperationEvent) const
{
	Spec->TestTrue("Callback should not be invoked!", false);
}

void UBeamRequestTrackerWaitAllTestCallbacks::MockWaitCompleteEvent_Expected(const FBeamWaitCompleteEvent& Evt) const
{
	UE_LOG(LogTemp, Display, TEXT("Callback was called"));
	
	Spec->TestEqual("Contexts are the same", Evt.Contexts, ExpectedContexts);
	Spec->TestEqual("Requests are the same", Evt.Requests, ExpectedRequests);
	// Spec->TestEqual("Responses are the same", Responses, ExpectedResponses);
	// Spec->TestEqual("Responses are the same", Errors, ExpectedErrors);
}

void UBeamRequestTrackerWaitAllTestCallbacks::MockWaitCompleteEvent_Fail(const FBeamWaitCompleteEvent&) const
{
	Spec->TestTrue("Callback should not be invoked!", false);
}
