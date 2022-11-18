// Fill out your copyright notice in the Description page of Project Settings.


#include "RequestTracker/BeamRequestTracker.h"
#include "BeamLogging.h"


void UBeamRequestTracker::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	WaitHandleId = new long();
	*WaitHandleId = -1;

	OperationHandleId = new long();
	*OperationHandleId = -1;

	Backend = Cast<UBeamBackend>(Collection.InitializeDependency(UBeamBackend::StaticClass()));

	// Set up the RequestId-related cleanup
	TickOnRequestIdCompletedDelegate.BindUFunction(this, GET_FUNCTION_NAME_CHECKED(UBeamRequestTracker, TickOnRequestIdCompleted));
	Backend->TickOnRequestIdCompletedDelegates.Add(TickOnRequestIdCompletedDelegate);

	// Set up the RequestId-related cleanup
	TickOnBackendCleanUpDelegate.BindUFunction(this, GET_FUNCTION_NAME_CHECKED(UBeamRequestTracker, TickOnBackendCleanUp));
	Backend->TickOnBackendCleanUpDelegates.Add(TickOnBackendCleanUpDelegate);
}

void UBeamRequestTracker::Deinitialize()
{
	Super::Deinitialize();

	// Clean up backend delegates
	Backend->TickOnRequestIdCompletedDelegates.Remove(TickOnRequestIdCompletedDelegate);
	Backend->TickOnBackendCleanUpDelegates.Remove(TickOnBackendCleanUpDelegate);
	TickOnBackendCleanUpDelegate.Clear();
	TickOnRequestIdCompletedDelegate.Clear();

	delete WaitHandleId;
	delete OperationHandleId;
}

void UBeamRequestTracker::GatherRequestIdsFromWaitHandle(const FBeamWaitHandle Handle, TArray<FBeamRequestId>& DependedOnRequests) const
{
	// We get all the Request Ids that were awaited on directly		
	ActiveRequestsForWaitHandles.MultiFind(Handle, DependedOnRequests);

	// Then, we get all the operations that we are waiting on
	TArray<FBeamOperationId> DependedOnOperations;
	ActiveOperationsForWaitHandles.MultiFind(Handle, DependedOnOperations);
	for (const auto& Op : DependedOnOperations)
	{
		check(ActiveOperations.Contains(Op))
		const auto State = ActiveOperationState.FindChecked(Op);

		for (const auto& Req : State.DependentRequests)
		{
			DependedOnRequests.AddUnique(Req);
		}
	}

	// Finally, we recursively get all request ids from any wait handles this wait handle depends on.
	TArray<FBeamWaitHandleId> DependedOnWaitHandles;
	ActiveWaitHandlesForWaitHandles.MultiFind(Handle, DependedOnWaitHandles);
	for (const auto& DependentWaitHandleId : DependedOnWaitHandles)
	{
		const auto DependedHandle = ActiveWaitHandles.FindByPredicate([DependentWaitHandleId](const FBeamWaitHandle& wh) { return wh.WaitHandleId == DependentWaitHandleId; });
		ensureAlwaysMsgf(DependedHandle, TEXT("Somehow you are depending on a wait handle that doesn't exist... This should be impossible"));
		GatherRequestIdsFromWaitHandle(*DependedHandle, DependedOnRequests);
	}
}

void UBeamRequestTracker::TickOnRequestIdCompleted(int64)
{
	// Go through all active wait handles and figure out which of them have been completed.
	// If they have, we run their register FOnWaitCompleted callback.
	for (auto& ActiveWaitHandle : ActiveWaitHandles)
	{
		if (ActiveWaitHandle.Status == Completed)
		{
			UE_LOG(LogBeamRequestTracker, Verbose, TEXT("Beamable WaitHandle | WaitHandle is already completed and awaiting clean up. WAIT_HANDLE=%llu"), ActiveWaitHandle.WaitHandleId);
			continue;
		}

		// We get all the Request Ids that were awaited on directly
		TArray<FBeamRequestId> DependedOnRequests;
		GatherRequestIdsFromWaitHandle(ActiveWaitHandle, DependedOnRequests);

		// We sort the dependencies so that they are returned in the order they were made.
		DependedOnRequests.Sort();


		// Handle the All case: Basically, all the dependency nodes need to be completed in order for us to fire off the wait event.
		if (ActiveWaitHandle.Mode == All)
		{
			auto bAreAllDepsDone = true;
			for (const auto& DependedOnId : DependedOnRequests)
			{
				const auto& DependedOnCtx = Backend->InFlightRequestContexts.FindRef(DependedOnId);
				bAreAllDepsDone &= DependedOnCtx.BeamStatus == Completed;
			}

			// If all dependencies are done, let's call the WaitCompleted callback with all the dependencies correctly set up!
			if (bAreAllDepsDone)
			{
				TArray<FBeamRequestContext> Contexts;
				TArray<TScriptInterface<IBeamBaseRequestInterface>> RequestData;
				TArray<UObject*> ResponseBodies;
				TArray<FBeamErrorResponse> ResponseErrors;

				// String builder so we can log all the ids
				FString IdList;
				IdList.Reserve(DependedOnRequests.Num() * 2);

				// Go through ids
				for (const auto& DependedOnId : DependedOnRequests)
				{
					const auto DependedOnContext = Backend->InFlightRequestContexts.FindRef(DependedOnId);

					Contexts.Add(DependedOnContext);
					RequestData.Add(Backend->InFlightRequestData.FindRef(DependedOnContext));
					ResponseBodies.Add(Backend->InFlightResponseBodyData.FindRef(DependedOnContext));
					ResponseErrors.Add(Backend->InFlightResponseErrorData.FindRef(DependedOnContext));
					IdList += FString::Printf(TEXT("%llu, "), DependedOnId);
				}

				UE_LOG(LogBeamRequestTracker, Verbose, TEXT("Beamable WaitHandles | Completed WAIT_HANDLE=%llu, REQUEST_IDS=[%s]"), ActiveWaitHandle.WaitHandleId, *IdList);

				const auto& OnComplete = ActiveWaitHandleCallbacks.FindRef(ActiveWaitHandle);
				auto _ = OnComplete.ExecuteIfBound(Contexts, RequestData, ResponseBodies, ResponseErrors);
				ActiveWaitHandle.Status = Completed;
			}
		}
	}
}

void UBeamRequestTracker::TickOnBackendCleanUp(TArray<int64>& OutUsingRequestIds)
{
	// We start by finding all handles that are completed. 
	TArray<FBeamWaitHandle> WaitHandlesToCleanUp;
	TArray<FBeamOperationHandle> WaitedOnOperationHandles;
	for (const auto& ActiveWaitHandle : ActiveWaitHandles)
	{
		if (ActiveWaitHandle.Status == Completed)
			WaitHandlesToCleanUp.Add(ActiveWaitHandle);
	}

	// Then we go through them and clean our internal state up.
	for (const auto& HandleToCleanUp : WaitHandlesToCleanUp)
	{
		UE_LOG(LogBeamRequestTracker, Verbose, TEXT("Beamable CleanUp | Cleaning Up Data associated with WaitHandle. WAIT_HANDLE_ID=%llu"), HandleToCleanUp.WaitHandleId);

		// Clear the handle from active ones
		ActiveWaitHandles.Remove(HandleToCleanUp);		
		
		// Clear the handle from the map of dependencies for them.
		ActiveRequestsForWaitHandles.Remove(HandleToCleanUp);
		ActiveOperationsForWaitHandles.Remove(HandleToCleanUp);
		ActiveWaitHandlesForWaitHandles.Remove(HandleToCleanUp);

		// Clear the callback associated with the handle
		ActiveWaitHandleCallbacks.Remove(HandleToCleanUp);
	}

	// Then, we go through all the ActiveOperations and find all operations that are no longer ongoing...
	TArray<FBeamOperationHandle> OperationsToCleanUp;
	for (const auto& ActiveOperationId : ActiveOperations)
	{
		const auto State = ActiveOperationState.FindChecked(ActiveOperationId);
		if (State.Status != FBeamOperationState::ONGOING)
			OperationsToCleanUp.Add(ActiveOperationId);
	}

	// ... and we clean them up.
	for (const auto& CompletedOperationId : OperationsToCleanUp)
	{
		ActiveOperations.Remove(CompletedOperationId);
		ActiveOperationState.Remove(CompletedOperationId);
		ActiveOperationEventHandlers.Remove(CompletedOperationId);
	}

	// Finally, we go through the current wait handles and operations to find the all request ids that  
	TArray<FBeamRequestId> RequestIdsHelper;
	RequestIdsHelper.Reserve(16);

	// For every active wait handle add their Request Ids so that BeamBackend knows not to clean them up yet.
	for (const auto& ActiveWaitHandle : ActiveWaitHandles)
	{
		ActiveRequestsForWaitHandles.MultiFind(ActiveWaitHandle, RequestIdsHelper);
		for (const auto& ReqId : RequestIdsHelper) OutUsingRequestIds.AddUnique(ReqId);
		RequestIdsHelper.Reset();
	}

	// For every active operation add their Request Ids so that BeamBackend knows not to clean them up yet.
	for (const auto& ActiveOperationId : ActiveOperations)
	{
		const auto State = ActiveOperationState.FindChecked(ActiveOperationId);
		for (const auto& Req : State.DependentRequests)
			OutUsingRequestIds.AddUnique(Req);
	}
}

FBeamWaitHandle UBeamRequestTracker::WaitAll(const TArray<FBeamRequestContext>& RequestContexts, const TArray<FBeamOperationHandle>& Operations, const TArray<FBeamWaitHandle>& Waits,
                                             FOnWaitComplete OnComplete)
{
	// Ensures we get a valid Next Id even if requests get made from multiple threads.
	const auto NextId = _InterlockedIncrement(WaitHandleId);
	const auto WaitHandle = FBeamWaitHandle{NextId, Backend, All};

	ActiveWaitHandles.Add(WaitHandle);

	auto bDepExists = true;
	for (const auto& Context : RequestContexts)
	{
		bDepExists &= Backend->InFlightRequests.Contains(Context.RequestId);
		ensureAlwaysMsgf(bDepExists, TEXT("Added Request Dependency to WaitHandle does not exist. OWNER_WAIT_HANDLE=%lld, REQUEST_ID=%lld"),
		                 WaitHandle.WaitHandleId, Context.RequestId);
		UE_LOG(LogBeamRequestTracker, Verbose, TEXT("Adding Request Dependency to WaitHandle. OWNER_WAIT_HANDLE=%lld, REQUEST_ID=%lld"), WaitHandle.WaitHandleId, Context.RequestId);
		ActiveRequestsForWaitHandles.AddUnique(WaitHandle, Context.RequestId);
	}

	for (const auto& Operation : Operations)
	{
		bDepExists &=ActiveOperations.Contains(Operation);
		ensureAlwaysMsgf(bDepExists, TEXT("Added Operation Dependency to WaitHandle does not exist. OWNER_WAIT_HANDLE=%lld, OPERATION_ID=%lld"),
		                 WaitHandle.WaitHandleId, Operation.OperationId);

		UE_LOG(LogBeamRequestTracker, Verbose, TEXT("Adding Operation Dependency to WaitHandle. OWNER_WAIT_HANDLE=%lld, OPERATION_ID=%lld"), WaitHandle.WaitHandleId, Operation.OperationId);
		ActiveOperationsForWaitHandles.AddUnique(WaitHandle, Operation.OperationId);
	}

	for (const auto& WaitDep : Waits)
	{
		bDepExists &= ActiveWaitHandles.Contains(WaitDep);
		ensureAlwaysMsgf(bDepExists, TEXT("Added WaitHandle Dependency to WaitHandle does not exist. OWNER_WAIT_HANDLE=%lld, WAIT_HANDLE_ID=%lld"),
		                 WaitHandle.WaitHandleId, WaitDep.WaitHandleId);

		UE_LOG(LogBeamRequestTracker, Verbose, TEXT("Adding WaitHandle Dependency to WaitHandle. OWNER_WAIT_HANDLE=%lld, WAIT_HANDLE_ID=%lld"), WaitHandle.WaitHandleId, WaitDep.WaitHandleId);
		ActiveWaitHandlesForWaitHandles.AddUnique(WaitHandle, WaitDep.WaitHandleId);
	}
	// TODO: Handle case of DEPENDENCIES BEING COMPLETE WHEN WE CALL WAIT.

	ActiveWaitHandleCallbacks.Add(WaitHandle, OnComplete);

	// Handle extremely unlikely edge-case of all dependencies of a wait being completed by the time you call the wait.
	// Just going through this case typically means you're making some dangerous architecture decisions and you should probably re-think them.
	// We only run this section if all the dependencies exist. This should only fail during our Automated Tests. 
	if(bDepExists)
	{
		TArray<int64> DependedOnRequests;
		GatherRequestIdsFromWaitHandle(WaitHandle, DependedOnRequests);

		bool bAreAllComplete = true;
		for (const auto ReqId : DependedOnRequests)
		{
			bAreAllComplete &= Backend->InFlightRequestContexts.FindRef(ReqId).BeamStatus == Completed;
		}
		// If all dependencies are already completed, we tick this to run the callback immediately.
		// Couple of things to note:
		//   - The ID here is irrelevant so we pass in -1. Its irrelevant because we always update all WaitHandles when we run this tick.
		//   - This is OK to run as the request timeout is significantly smaller than the amount of time we wait between BeamBackend clean up ticks so we are guaranteed to still have the
		//     data for Requests/Operations/Wait Handles every time this runs.
		if(bAreAllComplete)
		{
			TickOnRequestIdCompleted(-1);
			UE_LOG(LogBeamRequestTracker, Warning, TEXT("All Wait Dependencies were completed by the time you called this. Consider revisiting your code that caused this to happen. OWNER_WAIT_HANDLE=%lld"), WaitHandle.WaitHandleId);
		}
	}

	return WaitHandle;
}

FBeamOperationHandle UBeamRequestTracker::BeginOperation(const TArray<FUserSlot>& Participants, const FString& CallingSystem, FBeamOperationEventHandler OnEvent, int MaxRequestsInOperation)
{
	// Ensures we get a valid Next Id even if requests get made from multiple threads.
	const auto NextId = _InterlockedIncrement(OperationHandleId);
	const auto OperationHandle = FBeamOperationHandle{NextId};
	ActiveOperations.Add(OperationHandle);

	// Initialize it's state.
	auto State = FBeamOperationState{false, CallingSystem, {}, Participants, MaxRequestsInOperation};
	ActiveOperationState.Add(OperationHandle, State);
	ActiveOperationEventHandlers.Add(OperationHandle, OnEvent);

	return OperationHandle;
}

void UBeamRequestTracker::AddRequestToOperation(const FBeamOperationHandle& Op, int64 RequestId)
{
	auto& OperationState = ActiveOperationState.FindChecked(Op);
	ensureAlwaysMsgf(OperationState.MaximumRequestCount == -1 || OperationState.DependentRequests.Num() - 1 < OperationState.MaximumRequestCount, TEXT("Unexpected Request added to Operation"));
	ensureAlwaysMsgf(!OperationState.Status, TEXT("Can't add a request to a Cancelled or Done Operation"));

	const auto InFlightRequest = Backend->InFlightRequests.FindChecked(RequestId);
	const auto InFlightRequestStatus = InFlightRequest->GetStatus();
	ensureAlwaysMsgf(InFlightRequestStatus == EHttpRequestStatus::NotStarted ||
	                 InFlightRequestStatus == EHttpRequestStatus::Processing,
	                 TEXT("Cannot depend on a request that is already done!"));

	OperationState.DependentRequests.Add(RequestId);
}

void UBeamRequestTracker::AddRequestToOperation(const FBeamOperationHandle& Op, FBeamRequestContext RequestContext)
{
	AddRequestToOperation(Op, RequestContext.RequestId);
}

void UBeamRequestTracker::TriggerOperationEvent(const FBeamOperationHandle& Op, const EBeamOperationEventType Type, uint8 SubEvent, const FString& EventData, const int64& RequestId)
{
	const auto& OperationState = ActiveOperationState.FindChecked(Op);

	// If we have the default one, let's pass along '-1' only if there were no dependent requests. If there, were assume it's a sequential chain and we are being called in the latest request's handler.
	// As such, we pass in the last dependent request id added.
	const auto ReqId = RequestId == DEFAULT_REQUEST_ID ? (OperationState.DependentRequests.Num() > 0 ? OperationState.DependentRequests.Last() : -1) : RequestId;
	TriggerOperationEventFull(Op, Type, SubEvent, OperationState.DependentUserSlots, EventData, OperationState.CallingSystem, ReqId);
}

void UBeamRequestTracker::TriggerOperationEventFull(const FBeamOperationHandle& Op, const EBeamOperationEventType Type, uint8 SubEvent, const TArray<FUserSlot>& UserSlots, const FString& EventData,
                                                    const FString& CallingSystem, const int64 RequestId)
{
	checkf(!ActiveOperationState.FindRef(Op).Status, TEXT("Cannot trigger an operation event after it's being completed!"));

	const auto& OperationEventHandler = ActiveOperationEventHandlers.FindChecked(Op);
	const FBeamOperationEvent Result{Type, RequestId, SubEvent, CallingSystem, EventData, Op};
	if (OperationEventHandler.ExecuteIfBound(UserSlots, Result))
	{
		TArray<FString> SlotsStr;
		for (const auto& UserSlot : UserSlots)
			SlotsStr.Add(UserSlot.Name);

		const auto SlotsJoinedStr = FString::Join(SlotsStr, TEXT(","));
		UE_LOG(LogBeamRequestTracker, Verbose, TEXT("Handling Operation Event: OPERATION_ID=%lld SLOTS=[%s], EVENT_TYPE=%s, SUB_EVENT=%c, CALLING_SYSTEM=%s, DATA=%s"),
		       Op.OperationId,
		       *SlotsJoinedStr,
		       *StaticEnum<EBeamOperationEventType>()->GetNameStringByValue(Type),
		       SubEvent,
		       *CallingSystem,
		       *EventData);
	}
}

void UBeamRequestTracker::TriggerOperationSuccess(const FBeamOperationHandle& Op, const FString& EventData, const int64& RequestId)
{
	TriggerOperationEvent(Op, SUCCESS, Final, EventData, RequestId);
	auto& OperationState = ActiveOperationState.FindChecked(Op);
	OperationState.Status = FBeamOperationState::COMPLETE;
}

void UBeamRequestTracker::TriggerOperationError(const FBeamOperationHandle& Op, const FString& EventData, const int64& RequestId)
{
	TriggerOperationEvent(Op, ERROR, Final, EventData, RequestId);
	auto& OperationState = ActiveOperationState.FindChecked(Op);
	OperationState.Status = FBeamOperationState::COMPLETE;
}

void UBeamRequestTracker::TriggerOperationCancelled(const FBeamOperationHandle& Op, const FString& EventData, const int64& RequestId)
{
	auto& OperationState = ActiveOperationState.FindChecked(Op);
	TriggerOperationEvent(Op, CANCELLED, Final, EventData, RequestId);
	OperationState.Status = FBeamOperationState::CANCELED;
}
