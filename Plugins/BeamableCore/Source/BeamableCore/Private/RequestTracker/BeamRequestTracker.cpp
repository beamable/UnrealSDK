// Fill out your copyright notice in the Description page of Project Settings.


#include "RequestTracker/BeamRequestTracker.h"
#include "BeamLogging.h"
#include <atomic>

void UBeamRequestTracker::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	WaitHandleId = -1;
	OperationHandleId = -1;

	Backend = Cast<UBeamBackend>(Collection.InitializeDependency(UBeamBackend::StaticClass()));

	// Set up the RequestId-related cleanup
	TickOnRequestIdCompletedDelegate.BindUFunction(this, GET_FUNCTION_NAME_CHECKED(UBeamRequestTracker, CheckAndCompleteWaitHandles));
	Backend->TickOnRequestIdCompletedDelegates.Add(TickOnRequestIdCompletedDelegate);

	// Set up the RequestId-related cleanup
	TickOnBackendCleanUpDelegate.BindUFunction(this, GET_FUNCTION_NAME_CHECKED(UBeamRequestTracker, HandleBackendCleanUp));
	Backend->TickOnBackendCleanUpDelegates.Add(TickOnBackendCleanUpDelegate);

	TickCleanUpRequestTracker = FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateLambda([this](const float)
	{
		// Clean up Completed wait handles
		CleanUpWaitHandles();

		// Clean up Completed Operations
		CleanUpOperations();

		return true;
	}), GetDefault<UBeamCoreSettings>()->RequestTrackerCleanUpInterval);
}

void UBeamRequestTracker::Deinitialize()
{
	Super::Deinitialize();

	// Clean up backend delegates
	Backend->TickOnRequestIdCompletedDelegates.Remove(TickOnRequestIdCompletedDelegate);
	Backend->TickOnBackendCleanUpDelegates.Remove(TickOnBackendCleanUpDelegate);
	TickOnBackendCleanUpDelegate.Clear();
	TickOnRequestIdCompletedDelegate.Clear();

	FTSTicker::GetCoreTicker().RemoveTicker(TickCleanUpRequestTracker);
}

void UBeamRequestTracker::GatherRequestIdsFromWaitHandle(const FBeamWaitHandle Handle, TArray<FBeamRequestId>& DependedOnRequests, TArray<FBeamOperationHandle>& DependedOnOperations) const
{
	// We get all the Request Ids that were awaited on directly
	const auto WaitState = ActiveWaitStates.FindChecked(Handle);
	DependedOnRequests.Append(WaitState->RequestDependencies);

	// Then, we get all the operations that we are waiting on
	TArray<FBeamOperationHandle> OperationDependencies;
	OperationDependencies.Append(WaitState->OperationDependencies);
	for (const auto& Op : OperationDependencies)
	{
		check(ActiveOperations.Contains(Op))
		DependedOnOperations.Add(Op);

		const auto State = ActiveOperationState.FindChecked(Op);
		for (const auto& Req : State->DependentRequests)
		{
			DependedOnRequests.AddUnique(Req);
		}
	}

	// Finally, we recursively get all request ids from any wait handles this wait handle depends on.
	TArray<FBeamWaitHandle> WaitDependencies;
	WaitDependencies.Append(WaitState->WaitDependencies);
	for (const auto& DependentWaitHandle : WaitDependencies)
	{
		const auto DependedHandle = ActiveWaitHandles.FindByPredicate([DependentWaitHandle](const FBeamWaitHandle& wh) { return wh.WaitHandleId == DependentWaitHandle.WaitHandleId; });
		ensureAlwaysMsgf(DependedHandle, TEXT("Somehow you are depending on a wait handle that doesn't exist... This should be impossible"));
		GatherRequestIdsFromWaitHandle(*DependedHandle, DependedOnRequests, DependedOnOperations);
	}
}

void UBeamRequestTracker::CheckAndCompleteWaitHandles(int64)
{
	// Go through all active wait handles and figure out which of them have been completed.
	// If they have, we run their register FOnWaitCompleted callback.
	// Also, gets list of completed wait handles that are just awaiting clean up
	TArray<FString> AwaitingCleanupHandles;
	bool bDidCompleteAtLeastOneWait = false;
	for (int i = ActiveWaitHandles.Num() - 1; i >= 0; --i)
	{
		// Get the handle
		const auto ActiveWaitHandle = ActiveWaitHandles[i];

		// Get the state for this wait handle
		auto ActiveWaitState = ActiveWaitStates.FindChecked(ActiveWaitHandle);

		// Skip if it is already completed and just awaiting
		if (ActiveWaitState->Status == AS_Completed)
		{
			AwaitingCleanupHandles.Add(FString::Printf(TEXT("%llu"), ActiveWaitHandle.WaitHandleId));
			continue;
		}

		// We get all the Request Ids that were awaited on directly
		TArray<FBeamRequestId> DependedOnRequests;
		TArray<FBeamOperationHandle> DependedOnOperations;
		GatherRequestIdsFromWaitHandle(ActiveWaitHandle, DependedOnRequests, DependedOnOperations);

		// We also sort the dependencies so that they are returned in the order they were made.
		DependedOnRequests.Sort();

		// Basically, all the dependency nodes need to be completed in order for us to fire off the wait event.
		auto bAreAllDepsDone = true;

		// If operations we depend on are still running, we are not done.
		for (const auto& Op : DependedOnOperations)
		{
			check(ActiveOperations.Contains(Op))
			const auto& State = ActiveOperationState.FindChecked(Op);
			bAreAllDepsDone &= State->Status != UBeamOperationState::ONGOING;
		}

		// If requests (from within each operation or individually made) are still running, we are not done.
		for (const auto& DependedOnId : DependedOnRequests)
		{
			const auto& DependedOnCtx = Backend->InFlightRequestContexts.FindChecked(DependedOnId);
			bAreAllDepsDone &= DependedOnCtx.BeamStatus == AS_Completed;
		}

		// Track if we completed at least one wait dependency.
		bDidCompleteAtLeastOneWait |= bAreAllDepsDone;

		// If all dependencies are done, let's call the WaitCompleted callback with all the dependencies correctly set up!
		if (bAreAllDepsDone)
		{
			UE_LOG(LogBeamRequestTracker, Verbose, TEXT("Beamable WaitHandles | Wait Completed WAIT_HANDLE=%llu"), ActiveWaitHandle.WaitHandleId);
			ActiveWaitState->Status = AS_Completed;

			const bool bHasCodeHandler = ActiveWaitState->CodeHandler.IsBound();
			const bool bHasBlueprintHandler = ActiveWaitState->BlueprintHandler.IsBound();

			if (bHasCodeHandler || bHasBlueprintHandler)
			{
				TArray<FBeamRequestContext> Contexts;
				TArray<TScriptInterface<IBeamBaseRequestInterface>> RequestData;
				TArray<TScriptInterface<IBeamBaseResponseBodyInterface>> ResponseBodies;
				TArray<FBeamErrorResponse> ResponseErrors;

				// String builder so we can log all the ids
				FString IdList;
				IdList.Reserve(DependedOnRequests.Num() * 2);

				// Go through ids
				for (const auto& DependedOnId : DependedOnRequests)
				{
					const auto& DependedOnContext = Backend->InFlightRequestContexts.FindChecked(DependedOnId);
					Contexts.Add(DependedOnContext);
					RequestData.Add(Backend->InFlightRequestData.FindChecked(DependedOnContext));
					ResponseBodies.Add(Backend->InFlightResponseBodyData.FindChecked(DependedOnContext));
					ResponseErrors.Add(Backend->InFlightResponseErrorData.FindChecked(DependedOnContext));
					IdList += FString::Printf(TEXT("%llu, "), DependedOnId);
				}

				UE_LOG(LogBeamRequestTracker, Verbose, TEXT("Beamable WaitHandles | Invoking Wait Handlers WAIT_HANDLE=%llu, REQUEST_IDS=[%s]"), ActiveWaitHandle.WaitHandleId, *IdList);

				FBeamWaitCompleteEvent Evt{};
				Evt.WaitHandle = ActiveWaitHandle;
				Evt.Contexts = Contexts;
				Evt.Requests = RequestData;
				Evt.Responses = ResponseBodies;
				Evt.Errors = ResponseErrors;
				Evt.Operations = DependedOnOperations;

				if (bHasCodeHandler) ActiveWaitState->CodeHandler.Execute(Evt);
				if (bHasBlueprintHandler) ActiveWaitState->BlueprintHandler.Execute(Evt);

				ActiveWaitState->CodeHandler.Unbind();
				ActiveWaitState->BlueprintHandler.Unbind();
			}
		}
	}

	// Log out handles that are waiting clean up.
	if (AwaitingCleanupHandles.Num())
		UE_LOG(LogBeamRequestTracker, Verbose, TEXT("Beamable WaitHandle | WaitHandles awaiting clean up. WAIT_HANDLE=%s"), *FString::Join(AwaitingCleanupHandles, TEXT(",")));

	// We re-run the check if at least one wait handle was completed.
	if (bDidCompleteAtLeastOneWait) CheckAndCompleteWaitHandles(-1);
}


void UBeamRequestTracker::CleanUpWaitHandles()
{
	TArray<FString> CleanedUpHandles;
	// Go through all active wait handles and figure out which of them have been completed.
	// If they have, we run their register FOnWaitCompleted callback.
	for (int i = ActiveWaitHandles.Num() - 1; i >= 0; --i)
	{
		auto ActiveWaitHandle = ActiveWaitHandles[i];
		const auto& ActiveWaitState = ActiveWaitStates.FindChecked(ActiveWaitHandle);

		if (ActiveWaitState->Status != AS_InFlight)
		{
			// Notify the Operations that this wait handle was completed so that any Operation that was dependent on it can clean itself up correctly in CleanUpOperations().
			TArray<FBeamRequestId> DependedOnRequests;
			TArray<FBeamOperationHandle> DependedOnOperations;
			GatherRequestIdsFromWaitHandle(ActiveWaitHandle, DependedOnRequests, DependedOnOperations);
			// First, we make sure remove this completed wait handle from the map of Operation->WaitHandles that depend on it.
			for (const auto& DependedOnOperation : DependedOnOperations)
			{
				ActiveOperationState.FindChecked(DependedOnOperation)->WaitedBy.Remove(ActiveWaitHandle);
			}

			// Clear the handle from active ones
			CleanedUpHandles.Add(FString::Printf(TEXT("%llu"), ActiveWaitHandle.WaitHandleId));
			ActiveWaitHandles.RemoveAt(i);
			ActiveWaitStates.Remove(ActiveWaitHandle);
		}
	}

	if (CleanedUpHandles.Num())
		UE_LOG(LogBeamRequestTracker, Verbose, TEXT("Beamable WaitHandle | Cleaned Up Data associated with WaitHandle. WAIT_HANDLE=%s"), *FString::Join(CleanedUpHandles, TEXT(",")));
}


void UBeamRequestTracker::CleanUpOperations()
{
	TArray<FString> OngoingOperations;
	TArray<FString> CleanedUpOperations;
	// Go through all active wait handles and figure out which of them have been completed.
	// If they have, we run their register FOnWaitCompleted callback.
	for (int i = ActiveOperations.Num() - 1; i >= 0; --i)
	{
		const auto OpId = ActiveOperations[i];

		// We skip all non-completed operations
		if (const auto& Op = ActiveOperationState[OpId]; Op->Status == UBeamOperationState::ONGOING)
		{
			OngoingOperations.Add(FString::Printf(TEXT("%llu"), OpId.OperationId));
			continue;
		}

		// If they are completed, we need to figure out if anyone depends on it.
		const auto OpState = ActiveOperationState.FindChecked(OpId);
		const auto bIsDependedOn = OpState->WaitedBy.Num() > 0;;
		auto bDependenciesAreFinished = !bIsDependedOn;
		if (bIsDependedOn)
		{
			// Check if any wait handle still depends on this operation
			for (const auto WaitHandle : OpState->WaitedBy)
			{
				auto WaitState = ActiveWaitStates[WaitHandle];
				bDependenciesAreFinished &= WaitState->Status != AS_Completed;
			}
		}

		// If the operation is done and no wait handle depends on it, just clean it up.
		if (bDependenciesAreFinished)
		{
			CleanedUpOperations.Add(FString::Printf(TEXT("%llu"), OpId.OperationId));
			ActiveOperations.RemoveAt(i);
			ActiveOperationState.Remove(OpId);
		}
	}

	if (OngoingOperations.Num())
		UE_LOG(LogBeamRequestTracker, Verbose, TEXT("Beamable CleanUp | Operation is ongoing so we won't clean it up. OP_IDS=%s"), *FString::Join(OngoingOperations, TEXT(", ")));

	if (CleanedUpOperations.Num())
		UE_LOG(LogBeamRequestTracker, Verbose, TEXT("Beamable CleanUp | Cleaning Up Operation. OP_IDS=%s"), *FString::Join(CleanedUpOperations, TEXT(", ")));
}

void UBeamRequestTracker::HandleBackendCleanUp(TArray<int64>& OutUsingRequestIds)
{
	// Finally, we go through the current wait handles and operations to find the all request ids that
	TArray<FBeamOperationHandle> DependencyOperationIds;
	DependencyOperationIds.Reserve(16);

	// For every active wait handle add their Request Ids so that BeamBackend knows not to clean them up yet.
	for (const auto& ActiveWaitHandle : ActiveWaitHandles)
	{
		const auto State = ActiveWaitStates[ActiveWaitHandle];
		if (State->Status == AS_InFlight)
		{
			for (const auto& ReqId : State->RequestDependencies)
				OutUsingRequestIds.AddUnique(ReqId);

			DependencyOperationIds.Append(State->OperationDependencies);
		}
	}

	// For every active operation add their Request Ids so that BeamBackend knows not to clean them up yet.
	for (const auto& ActiveOperationId : ActiveOperations)
	{
		const auto State = ActiveOperationState[ActiveOperationId];
		if (State->Status == UBeamOperationState::ONGOING || DependencyOperationIds.Contains(ActiveOperationId.OperationId))
		{
			for (const auto& Req : State->DependentRequests)
				OutUsingRequestIds.AddUnique(Req);
		}
	}
}

FBeamWaitHandle UBeamRequestTracker::WaitAll(const TArray<FBeamRequestContext>& RequestContexts, const TArray<FBeamOperationHandle>& Operations, const TArray<FBeamWaitHandle>& Waits,
                                             FOnWaitComplete OnComplete)
{
	// Ensures we get a valid Next Id even if requests get made from multiple threads.

	const auto NextId = ++WaitHandleId;
	const auto WaitHandle = FBeamWaitHandle{NextId,};

	ActiveWaitHandles.Add(WaitHandle);
	ActiveWaitStates.Add(WaitHandle, NewObject<UBeamWaitState>());
	auto WaitState = ActiveWaitStates[WaitHandle];
	WaitState->Status = AS_InFlight;

	auto bDepExists = true;
	for (const auto& Context : RequestContexts)
	{
		bDepExists &= Backend->InFlightRequests.Contains(Context.RequestId);
		ensureAlwaysMsgf(bDepExists, TEXT("Added Request Dependency to WaitHandle does not exist. OWNER_WAIT_HANDLE=%lld, REQUEST_ID=%lld"), WaitHandle.WaitHandleId, Context.RequestId);

		UE_LOG(LogBeamRequestTracker, Verbose, TEXT("Adding Request Dependency to WaitHandle. OWNER_WAIT_HANDLE=%lld, REQUEST_ID=%lld"), WaitHandle.WaitHandleId, Context.RequestId);
		WaitState->RequestDependencies.AddUnique(Context.RequestId);
	}

	for (const auto& Operation : Operations)
	{
		bDepExists &= ActiveOperations.Contains(Operation);
		ensureAlwaysMsgf(bDepExists, TEXT("Added Operation Dependency to WaitHandle does not exist. OWNER_WAIT_HANDLE=%lld, OPERATION_ID=%lld"), WaitHandle.WaitHandleId, Operation.OperationId);

		UE_LOG(LogBeamRequestTracker, Verbose, TEXT("Adding Operation Dependency to WaitHandle. OWNER_WAIT_HANDLE=%lld, OPERATION_ID=%lld"), WaitHandle.WaitHandleId, Operation.OperationId);
		WaitState->OperationDependencies.AddUnique(Operation);

		// If let the operation know that its being waited on by this wait handle.
		if (bDepExists)
			ActiveOperationState.FindChecked(Operation)->WaitedBy.Add(WaitHandle);
	}

	for (const auto& WaitDep : Waits)
	{
		bDepExists &= ActiveWaitHandles.Contains(WaitDep);
		ensureAlwaysMsgf(bDepExists, TEXT("Added WaitHandle Dependency to WaitHandle does not exist. OWNER_WAIT_HANDLE=%lld, WAIT_HANDLE_ID=%lld"), WaitHandle.WaitHandleId, WaitDep.WaitHandleId);

		UE_LOG(LogBeamRequestTracker, Verbose, TEXT("Adding WaitHandle Dependency to WaitHandle. OWNER_WAIT_HANDLE=%lld, WAIT_HANDLE_ID=%lld"), WaitHandle.WaitHandleId, WaitDep.WaitHandleId);
		WaitState->WaitDependencies.AddUnique(WaitDep);
	}
	WaitState->BlueprintHandler = OnComplete;

	// Handle extremely unlikely edge-case of all dependencies of a wait being completed by the time you call the wait.
	// Just going through this case typically means you're making some dangerous architecture decisions and you should probably re-think them.
	// We only run this section if all the dependencies exist. 
	if (bDepExists)
	{
		CheckAndCompleteWaitHandles(-1);
	}

	return WaitHandle;
}

FBeamWaitHandle UBeamRequestTracker::CPP_WaitAll(const TArray<FBeamRequestContext>& RequestContexts, const TArray<FBeamOperationHandle>& Operations, const TArray<FBeamWaitHandle>& Waits,
                                                 FOnWaitCompleteCode OnCompleteCode)
{
	// Ensures we get a valid Next Id even if requests get made from multiple threads.
	const auto NextId = ++WaitHandleId;
	const auto WaitHandle = FBeamWaitHandle{NextId,};

	// Add the state
	ActiveWaitStates.Add(WaitHandle, NewObject<UBeamWaitState>());
	auto WaitState = ActiveWaitStates.FindChecked(WaitHandle);
	WaitState->Status = AS_InFlight;

	ActiveWaitHandles.Add(WaitHandle);

	auto bDepExists = true;
	for (const auto& Context : RequestContexts)
	{
		bDepExists &= Backend->InFlightRequests.Contains(Context.RequestId);
		ensureAlwaysMsgf(bDepExists, TEXT("Added Request Dependency to WaitHandle does not exist. OWNER_WAIT_HANDLE=%lld, REQUEST_ID=%lld"), WaitHandle.WaitHandleId, Context.RequestId);
		UE_LOG(LogBeamRequestTracker, Verbose, TEXT("Adding Request Dependency to WaitHandle. OWNER_WAIT_HANDLE=%lld, REQUEST_ID=%lld"), WaitHandle.WaitHandleId, Context.RequestId);
		WaitState->RequestDependencies.AddUnique(Context.RequestId);
	}

	for (const auto& Operation : Operations)
	{
		bDepExists &= ActiveOperations.Contains(Operation);
		ensureAlwaysMsgf(bDepExists, TEXT("Added Operation Dependency to WaitHandle does not exist. OWNER_WAIT_HANDLE=%lld, OPERATION_ID=%lld"), WaitHandle.WaitHandleId, Operation.OperationId);

		UE_LOG(LogBeamRequestTracker, Verbose, TEXT("Adding Operation Dependency to WaitHandle. OWNER_WAIT_HANDLE=%lld, OPERATION_ID=%lld"), WaitHandle.WaitHandleId, Operation.OperationId);
		WaitState->OperationDependencies.AddUnique(Operation);

		if (bDepExists)
		{
			ActiveOperationState.FindChecked(Operation)->WaitedBy.AddUnique(WaitHandle);
		}
	}

	for (const auto& WaitDep : Waits)
	{
		bDepExists &= ActiveWaitHandles.Contains(WaitDep);
		ensureAlwaysMsgf(bDepExists, TEXT("Added WaitHandle Dependency to WaitHandle does not exist. OWNER_WAIT_HANDLE=%lld, WAIT_HANDLE_ID=%lld"), WaitHandle.WaitHandleId, WaitDep.WaitHandleId);

		UE_LOG(LogBeamRequestTracker, Verbose, TEXT("Adding WaitHandle Dependency to WaitHandle. OWNER_WAIT_HANDLE=%lld, WAIT_HANDLE_ID=%lld"), WaitHandle.WaitHandleId, WaitDep.WaitHandleId);
		WaitState->WaitDependencies.AddUnique(WaitDep);
	}
	WaitState->CodeHandler = MoveTemp(OnCompleteCode);

	// Handle extremely unlikely edge-case of all dependencies of a wait being completed by the time you call the wait.
	// Just going through this case typically means you're making some dangerous architecture decisions and you should probably re-think them.
	// We only run this section if all the dependencies exist. 
	if (bDepExists)
	{
		CheckAndCompleteWaitHandles(-1);
	}

	return WaitHandle;
}

bool UBeamRequestTracker::IsWaitSuccessful(const FBeamWaitCompleteEvent& Evt) const
{
	auto State = ActiveWaitStates.FindChecked(Evt.WaitHandle);
	if (State->Status != AS_Completed) return false;

	bool bDidSucceed = true;
	for (const FBeamRequestId& RequestId : State->RequestDependencies)
	{
		const auto Context = Backend->InFlightRequestContexts.FindChecked(RequestId);
		bDidSucceed &= Backend->IsSuccessfulResponse(Context.ResponseCode);
	}

	for (const FBeamOperationHandle& Operation : Evt.Operations)
	{
		const UBeamOperationState* OpState = ActiveOperationState.FindChecked(Operation);
		bDidSucceed &= OpState->Status == UBeamOperationState::COMPLETE_SUCCESS;
	}

	for (const FBeamWaitHandle& WaitDependency : State->WaitDependencies)
	{
		bDidSucceed &= IsWaitSuccessful(FBeamWaitCompleteEvent{WaitDependency});
	}

	return bDidSucceed;
}

bool UBeamRequestTracker::IsWaitFailed(const FBeamWaitCompleteEvent& Evt, TArray<FString>& Errors) const
{
	auto State = ActiveWaitStates.FindChecked(Evt.WaitHandle);
	if (State->Status != AS_Completed) return false;

	bool bDidFail = false;
	for (const FBeamRequestId& RequestId : State->RequestDependencies)
	{
		const auto Context = Backend->InFlightRequestContexts.FindChecked(RequestId);
		const auto bDidError = !Backend->IsSuccessfulResponse(Context.ResponseCode);
		bDidFail |= bDidError;
		if (bDidError) Errors.Add(Backend->InFlightResponseErrorData[Context].message);
	}

	for (const FBeamOperationHandle& Operation : Evt.Operations)
	{
		const UBeamOperationState* OpState = ActiveOperationState.FindChecked(Operation);
		const auto bDidError = OpState->Status == UBeamOperationState::COMPLETE_FAILURE;
		bDidFail |= bDidError;
		if (bDidError)
		{
			for (FBeamOperationEvent TriggeredEvent : OpState->TriggeredEvents)
			{
				if (TriggeredEvent.EventType == OET_ERROR)
					Errors.Add(TriggeredEvent.EventCode);
			}
		}
	}

	for (const FBeamWaitHandle& WaitDependency : State->WaitDependencies)
	{
		bDidFail |= IsWaitFailed(FBeamWaitCompleteEvent{WaitDependency}, Errors);
	}

	return bDidFail;
}

bool UBeamRequestTracker::IsAnyWaitCancelled(const FBeamWaitCompleteEvent& Evt) const
{
	auto State = ActiveWaitStates.FindChecked(Evt.WaitHandle);
	if (State->Status != AS_Completed) return false;

	bool bWasCancelled = false;
	for (const FBeamRequestId& RequestId : State->RequestDependencies)
	{
		bWasCancelled |= Backend->IsRequestCancelled(RequestId);
	}

	for (const FBeamOperationHandle& Operation : Evt.Operations)
	{
		const UBeamOperationState* OpState = ActiveOperationState.FindChecked(Operation);
		bWasCancelled |= OpState->Status == UBeamOperationState::CANCELLED;
	}

	for (const FBeamWaitHandle& WaitDependency : State->WaitDependencies)
	{
		bWasCancelled |= IsAnyWaitCancelled(FBeamWaitCompleteEvent{WaitDependency});
	}

	return bWasCancelled;
}


FBeamOperationHandle UBeamRequestTracker::BeginOperation(const TArray<FUserSlot>& Participants, const FString& CallingSystem, FBeamOperationEventHandler OnEvent)
{
	// Ensures we get a valid Next Id even if requests get made from multiple threads.	
	const auto NextId = ++OperationHandleId;
	const auto OperationHandle = FBeamOperationHandle{NextId};
	ActiveOperations.Add(OperationHandle);

	// Initialize it's state.
	auto State = NewObject<UBeamOperationState>();
	State->Status = EBeamOperationEventType::OET_NONE;
	State->CallingSystem = CallingSystem;
	State->DependentRequests = {};
	State->TriggeredEvents = {};
	State->DependentUserSlots = Participants;
	State->WaitedBy = {};
	State->CodeHandler = {};
	State->BlueprintHandler = OnEvent;
	ActiveOperationState.Add(OperationHandle, State);

	return OperationHandle;
}

FBeamOperationHandle UBeamRequestTracker::CPP_BeginOperation(const TArray<FUserSlot>& Participants, const FString& CallingSystem, FBeamOperationEventHandlerCode OnEvent)
{
	// Ensures we get a valid Next Id even if requests get made from multiple threads.
	const auto NextId = ++OperationHandleId;
	const auto OperationHandle = FBeamOperationHandle{NextId};
	ActiveOperations.Add(OperationHandle);

	// Initialize it's state.
	auto State = NewObject<UBeamOperationState>();
	State->Status = EBeamOperationEventType::OET_NONE;
	State->CallingSystem = CallingSystem;
	State->DependentRequests = {};
	State->TriggeredEvents = {};
	State->DependentUserSlots = Participants;
	State->WaitedBy = {};
	State->CodeHandler = OnEvent;
	State->BlueprintHandler = {};
	ActiveOperationState.Add(OperationHandle, State);

	return OperationHandle;
}

void UBeamRequestTracker::AddRequestToOperation(const FBeamOperationHandle& Op, int64 RequestId)
{
	auto& OperationState = ActiveOperationState.FindChecked(Op);
	ensureAlwaysMsgf(!OperationState->Status, TEXT("Can't add a request to a Cancelled or Done Operation"));

	const auto InFlightRequest = Backend->InFlightRequests.FindChecked(RequestId);
	const auto InFlightRequestStatus = InFlightRequest->GetStatus();
	ensureAlwaysMsgf(InFlightRequestStatus == EHttpRequestStatus::NotStarted ||
	                 InFlightRequestStatus == EHttpRequestStatus::Processing,
	                 TEXT("Cannot depend on a request that is already done!"));

	OperationState->DependentRequests.Add(RequestId);
	for (FBeamWaitHandle WaitedBy : OperationState->WaitedBy)
	{
		auto WaitedByState = ActiveWaitStates.FindChecked(WaitedBy);
		WaitedByState->RequestDependencies.AddUnique(RequestId);
	}
}

void UBeamRequestTracker::AddRequestToOperation(const FBeamOperationHandle& Op, FBeamRequestContext RequestContext)
{
	AddRequestToOperation(Op, RequestContext.RequestId);
}

void UBeamRequestTracker::TriggerOperationEvent(const FBeamOperationHandle& Op, const EBeamOperationEventType Type, FName EventId, const FString& EventCode, const int64& RequestId)
{
	TriggerOperationEventWithData(Op, Type, EventId, EventCode, {}, RequestId);
}

void UBeamRequestTracker::TriggerOperationEventWithData(const FBeamOperationHandle& Op, const EBeamOperationEventType Type, FName EventId, const FString& EventCode,
                                                        const TScriptInterface<IBeamOperationEventData> EventData, const int64& RequestId)
{
	const auto& OperationState = ActiveOperationState.FindChecked(Op);

	// If we have the default one, let's pass along '-1000' only if there were no dependent requests. If there, were assume it's a sequential chain and we are being called in the latest request's handler.
	// As such, we pass in the last dependent request id added.
	const auto ReqId = RequestId == DEFAULT_REQUEST_ID ? (OperationState->DependentRequests.Num() > 0 ? OperationState->DependentRequests.Last() : -1) : RequestId;
	TriggerOperationEventFull(Op, Type, EventId, OperationState->DependentUserSlots, EventCode, EventData, OperationState->CallingSystem, ReqId);
}

void UBeamRequestTracker::TriggerOperationEventFull(const FBeamOperationHandle& Op, const EBeamOperationEventType Type, FName EventId, const TArray<FUserSlot>& UserSlots, const FString& EventCode,
                                                    const TScriptInterface<IBeamOperationEventData>& EventData, const FString& CallingSystem, const int64 RequestId)
{
	UBeamOperationState* State = ActiveOperationState.FindChecked(Op);
	checkf(State->Status <= 0, TEXT("Cannot trigger an operation event after it's being completed! %s, %d"), *State->CallingSystem, State->Status);

	const FBeamOperationEvent Result{Op, Type, RequestId, EventId, CallingSystem, EventCode, EventData};

	TArray<FString> SlotsStr;
	for (const auto& UserSlot : UserSlots)
		SlotsStr.Add(UserSlot.Name);
	const auto SlotsJoinedStr = FString::Join(SlotsStr, TEXT(","));

	State->TriggeredEvents.Add(Result);
	if (State->CodeHandler.ExecuteIfBound(Result))
	{
		UE_LOG(LogBeamRequestTracker, Verbose, TEXT("Called CPP Handler for Operation Event: OPERATION_ID=%lld SLOTS=[%s], EVENT_TYPE=%s, SUB_EVENT=%s, CALLING_SYSTEM=%s, DATA=%s"),
		       Op.OperationId,
		       *SlotsJoinedStr,
		       *StaticEnum<EBeamOperationEventType>()->GetNameStringByValue(static_cast<uint8>(Type)),
		       *EventId.ToString(),
		       *CallingSystem,
		       *EventCode);
	}

	if (State->BlueprintHandler.ExecuteIfBound(Result))
	{
		UE_LOG(LogBeamRequestTracker, Verbose, TEXT("Called Dynamic Handler for Operation Event: OPERATION_ID=%lld SLOTS=[%s], EVENT_TYPE=%s, SUB_EVENT=%s, CALLING_SYSTEM=%s, DATA=%s"),
		       Op.OperationId,
		       *SlotsJoinedStr,
		       *StaticEnum<EBeamOperationEventType>()->GetNameStringByValue(static_cast<uint8>(Type)),
		       *EventId.ToString(),
		       *CallingSystem,
		       *EventCode);
	}

	if (EventId == NAME_None)
	{
		if (Type == OET_SUCCESS)
			State->Status = UBeamOperationState::COMPLETE_SUCCESS;

		if (Type == OET_ERROR)
			State->Status = UBeamOperationState::COMPLETE_FAILURE;

		if (Type == OET_CANCELLED)
			State->Status = UBeamOperationState::CANCELLED;

		CheckAndCompleteWaitHandles(-1);
	}
}

bool UBeamRequestTracker::TryGetOperationEvents(const FBeamOperationHandle& Op, const EBeamOperationEventType& FilterType, const FName& FilterId, TArray<FBeamOperationEvent>& Events)
{
	if (const auto StatePtr = ActiveOperationState.Find(Op))
	{
		const auto State = *StatePtr;

		const auto MaxEventCount = State->TriggeredEvents.Num();
		Events.Reserve(MaxEventCount);

		for (const auto& TriggeredEvent : State->TriggeredEvents)
		{
			auto bShouldInclude = true;
			bShouldInclude &= FilterType == OET_NONE || TriggeredEvent.EventType == FilterType;
			bShouldInclude &= FilterId == NAME_All || TriggeredEvent.EventId == FilterId;

			if (bShouldInclude)
			{
				Events.Add(TriggeredEvent);
			}
		}

		return Events.Num() > 0;
	}

	return false;
}

bool UBeamRequestTracker::TryGetOperationSuccesses(const FBeamOperationHandle& Op, TArray<FBeamOperationEvent>& Events)
{
	return TryGetOperationEvents(Op, OET_SUCCESS, NAME_All, Events);
}

bool UBeamRequestTracker::TryGetOperationErrors(const FBeamOperationHandle& Op, TArray<FBeamOperationEvent>& Events)
{
	return TryGetOperationEvents(Op, OET_ERROR, NAME_All, Events);
}

bool UBeamRequestTracker::TryGetOperationCancelations(const FBeamOperationHandle& Op, TArray<FBeamOperationEvent>& Events)
{
	return TryGetOperationEvents(Op, OET_CANCELLED, NAME_All, Events);
}

bool UBeamRequestTracker::TryGetOperationSuccessesWithId(const FBeamOperationHandle& Op, FName FilterId, TArray<FBeamOperationEvent>& Events)
{
	return TryGetOperationEvents(Op, OET_SUCCESS, FilterId, Events);
}

bool UBeamRequestTracker::TryGetOperationErrorsWithId(const FBeamOperationHandle& Op, FName FilterId, TArray<FBeamOperationEvent>& Events)
{
	return TryGetOperationEvents(Op, OET_ERROR, FilterId, Events);
}

bool UBeamRequestTracker::TryGetOperationCancelationsWithId(const FBeamOperationHandle& Op, FName FilterId, TArray<FBeamOperationEvent>& Events)
{
	return TryGetOperationEvents(Op, OET_CANCELLED, FilterId, Events);
}

bool UBeamRequestTracker::TryGetOperationResult(const FBeamOperationHandle& Op, FString& EventCode, TScriptInterface<IBeamOperationEventData>& EventData, TEnumAsByte<EBeamOperationEventType>& OperationEventType)
{
	if (TArray<FBeamOperationEvent> Events; TryGetOperationEvents(Op, OET_NONE, NAME_None, Events))
	{
		ensureAlwaysMsgf(Events.Num() == 1,
		                 TEXT("Found more than one completing event. This should be impossible. Please turn on verbose logging for the relevant systems and get in touch with Beamable."));

		EventCode = Events[0].EventCode;
		EventData = Events[0].EventData;
		OperationEventType = Events[0].EventType;
		return true;
	}

	return false;
}

bool UBeamRequestTracker::IsOperationActive(const FBeamOperationHandle& Op)
{
	if (const auto StatePtr = ActiveOperationState.Find(Op))
	{
		const auto State = *StatePtr;

		return State->Status == 0;
	}

	return false;
}


FBeamOperationHandle UBeamRequestTracker::CPP_BeginSuccessfulOperation(const TArray<FUserSlot>& Participants, const FString& CallingSystem, FString Success, FBeamOperationEventHandlerCode OnEvent)
{
	const auto OpHandle = CPP_BeginOperation(Participants, CallingSystem, OnEvent);
	TriggerOperationSuccess(OpHandle, Success);
	return OpHandle;
}

FBeamOperationHandle UBeamRequestTracker::CPP_BeginErrorOperation(const TArray<FUserSlot>& Participants, const FString& CallingSystem, FString Error, FBeamOperationEventHandlerCode OnEvent)
{
	const auto OpHandle = CPP_BeginOperation(Participants, CallingSystem, OnEvent);
	TriggerOperationError(OpHandle, Error);
	return OpHandle;
}

void UBeamRequestTracker::TriggerOperationSuccess(const FBeamOperationHandle& Op, const FString& EventCode, const int64& RequestId)
{
	TriggerOperationEvent(Op, EBeamOperationEventType::OET_SUCCESS, NAME_None, EventCode, RequestId);
}

void UBeamRequestTracker::TriggerOperationError(const FBeamOperationHandle& Op, const FString& EventCode, const int64& RequestId)
{
	TriggerOperationEvent(Op, EBeamOperationEventType::OET_ERROR, NAME_None, EventCode, RequestId);
}

void UBeamRequestTracker::TriggerOperationCancelled(const FBeamOperationHandle& Op, const FString& EventCode, const int64& RequestId)
{
	TriggerOperationEvent(Op, EBeamOperationEventType::OET_CANCELLED, NAME_None, EventCode, RequestId);
}

void UBeamRequestTracker::TriggerOperationSuccessWithData(const FBeamOperationHandle& Op, const FString& EventCode, const TScriptInterface<IBeamOperationEventData>& EventData, const int64& RequestId)
{
	TriggerOperationEventWithData(Op, EBeamOperationEventType::OET_SUCCESS, NAME_None, EventCode, EventData, RequestId);
}

void UBeamRequestTracker::TriggerOperationErrorWithData(const FBeamOperationHandle& Op, const FString& EventCode, const TScriptInterface<IBeamOperationEventData>& EventData, const int64& RequestId)
{
	TriggerOperationEventWithData(Op, EBeamOperationEventType::OET_ERROR, NAME_None, EventCode, EventData, RequestId);
}

void UBeamRequestTracker::TriggerOperationCancelledWithData(const FBeamOperationHandle& Op, const FString& EventCode, const TScriptInterface<IBeamOperationEventData>& EventData,
                                                            const int64& RequestId)
{
	TriggerOperationEventWithData(Op, EBeamOperationEventType::OET_CANCELLED, NAME_None, EventCode, EventData, RequestId);
}
