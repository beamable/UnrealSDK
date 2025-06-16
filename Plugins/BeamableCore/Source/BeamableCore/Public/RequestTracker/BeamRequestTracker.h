// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BeamOperation.h"
#include "BeamBackend/BeamBackend.h"
#include "RequestTracker/BeamWaitHandle.h"
#include "RequestTracker/BeamOperationHandle.h"

#include "BeamRequestTracker.generated.h"


// If we have the default one, let's pass along '-1' only if there were no dependent requests. If there, were assume it's a sequential chain and we are being called in the latest request's handler.
// As such, we pass in the last dependent request id added.
#define DEFAULT_REQUEST_ID -1000

// Used by our systems when we want to allow for one operation from a known set of operations to be executed in the middle of a predefined operation.
// Ie.: UBeamRuntime's Authentication flows have varying things they want to do based on the type of operation before they notify UBeamRuntimeSubsystems and/or Project-Level code that the user has signed in.
#define EXPAND(x) x
DECLARE_DELEGATE_RetVal(FBeamOperationHandle, FDelayedOperation)
#define DEFINE_BEAM_OPERATION_HOOK_OneParam(HookName, ...) EXPAND(DECLARE_DELEGATE_RetVal_OneParam(FBeamOperationHandle, HookName, __VA_ARGS__))
#define DEFINE_BEAM_OPERATION_HOOK_TwoParams(HookName, ...) EXPAND(DECLARE_DELEGATE_RetVal_TwoParams(FBeamOperationHandle, HookName, __VA_ARGS__))
#define DEFINE_BEAM_OPERATION_HOOK_ThreeParams(HookName, ...) EXPAND(DECLARE_DELEGATE_RetVal_ThreeParams(FBeamOperationHandle, HookName, __VA_ARGS__))
#define DEFINE_BEAM_OPERATION_HOOK_FourParams(HookName, ...) EXPAND(DECLARE_DELEGATE_RetVal_FourParams(FBeamOperationHandle, HookName, __VA_ARGS__))
#define DEFINE_BEAM_OPERATION_HOOK_FiveParams(HookName, ...) EXPAND(DECLARE_DELEGATE_RetVal_FiveParams(FBeamOperationHandle, HookName, __VA_ARGS__))
#define DEFINE_BEAM_OPERATION_HOOK_SixParams(HookName, ...) EXPAND(DECLARE_DELEGATE_RetVal_SixParams(FBeamOperationHandle, HookName, __VA_ARGS__))
#define DEFINE_BEAM_OPERATION_HOOK_SevenParams(HookName, ...) EXPAND(DECLARE_DELEGATE_RetVal_SevenParams(FBeamOperationHandle, HookName, __VA_ARGS__))
#define DEFINE_BEAM_OPERATION_HOOK_EightParams(HookName, ...) EXPAND(DECLARE_DELEGATE_RetVal_EightParams(FBeamOperationHandle, HookName, __VA_ARGS__))


UCLASS(BlueprintType, NotBlueprintable)
class BEAMABLECORE_API UBeamRequestTracker : public UEngineSubsystem
{
	GENERATED_BODY()

	friend class FBeamRequestTrackerSpec;

private:
	/**
	 * @brief  Just an Auto-Increment ID of each running request.
	 */
	std::atomic<long> WaitHandleId;

	/**
	 * @brief  Just an Auto-Increment ID of each running request.
	 */
	std::atomic<long> OperationHandleId;

	UPROPERTY()
	UBeamBackend* Backend;

	/**
	 * @brief Delegate instance that we bind to and then register with BeamBackend. 
	 */
	FTickOnRequestIdCompleted TickOnRequestIdCompletedDelegate;

	/**
	 * @brief Delegate instance that we bind to and then register with BeamBackend. 
	 */
	FTickOnBackendCleanUp TickOnBackendCleanUpDelegate;

	/**
	 * @brief Delegate instance that we bind to a ticking function (every X minutes) that'll run the CleanUp functions for WaitHandles and Operations.  
	 */
	FTSTicker::FDelegateHandle TickCleanUpRequestTracker;

	/** @brief Initializes the subsystem.  */
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	/** Cleans up the system.  */
	virtual void Deinitialize() override;

	/**
	 * @brief Utility function that gathers all request ids that a given wait handle is waiting on.
	 * @param Handle The wait handle whose request dependencies you wish to get.
	 * @param DependedOnRequests The dependent RequestIds for the given wait handle.
	 */
	void GatherRequestIdsFromWaitHandle(const FBeamWaitHandle Handle, TArray<FBeamRequestId>& DependedOnRequests,
	                                    TArray<FBeamOperationHandle>& DependedOnOperations) const;

	/**
	 * @brief This is bound to UBeamBackend's request complete delegate.
	 * It's basically a heads up from BeamBackend that a request has finished ALL it's processing and that we can react to it's change in state.
	 * @param RequestId The request that completed.
	 */
	UFUNCTION()
	void CheckAndCompleteWaitHandles(int64 RequestId);

	/**
	 * @brief Iterates through all existing wait handles and clean up the ones that are completed and/or cancelled.
	 */
	UFUNCTION()
	void CleanUpWaitHandles();

	/**
	 * @brief Iterates through all Operations and clean up all complete operations THAT ARE NOT BEING WAITED ON BY ANY WAIT_HANDLES. 
	 */
	UFUNCTION()
	void CleanUpOperations();

	/**
	 * @brief This is bound to UBeamBackend's CleanUp delegate.
	 * Beam Backend keeps references to all request/response UObjects in internal maps. Other systems, instead of keeping references themselves keep only the RequestId as a handle.
	 * Every time a request is completed, BeamBackend will trigger a clean up where it figures out which requests are done and removes them from these internal maps.
	 * In order to guarantee other systems don't lose data they depend on, they must register a callback like this and fill out this list informing beam backend of all RequestIds they
	 * depend on.
	 * @param OutUsingRequestIds A list of all Request Ids this system currently depends on.
	 */
	UFUNCTION()
	void HandleBackendCleanUp(TArray<int64>& OutUsingRequestIds);

public:
	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly)
	static UBeamRequestTracker* GetSelf() { return GEngine->GetEngineSubsystem<UBeamRequestTracker>(); }


	/***
	 *     _       __      _ __      
	 *    | |     / /___ _(_) /______
	 *    | | /| / / __ `/ / __/ ___/
	 *    | |/ |/ / /_/ / / /_(__  ) 
	 *    |__/|__/\__,_/_/\__/____/  
	 *                               
	 */

	/**
	 * @brief List of wait handles that are currently being waited on.
	 */
	TArray<FBeamWaitHandle> ActiveWaitHandles;

	/**
	 * @brief List of the data for each wait handles that are currently being waited on.
	 */
	UPROPERTY()
	TMap<FBeamWaitHandle, UBeamWaitState*> ActiveWaitStates;

	/**
	 * @brief Given a set of contexts, waits until the frame they are all done and then calls OnComplete. 
	 * @param RequestContexts The set of Request Contexts to wait for.
	 * @param Operations The set of Operations to wait for.
	 * @param Waits The set of Wait Handles to wait for
	 * @param OnComplete What to do when all those requests/operations are 100% done.
	 * @return A Wait Handle identifying this wait all command.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Waits",
		meta=(AutoCreateRefTerm="RequestContexts,Operations,Waits", BeamFlowFunction))
	FBeamWaitHandle WaitAll(const TArray<FBeamRequestContext>& RequestContexts,
	                        const TArray<FBeamOperationHandle>& Operations, const TArray<FBeamWaitHandle>& Waits,
	                        FOnWaitComplete OnComplete);

	/**
	 * @copybrief WaitAll
	 */
	FBeamWaitHandle CPP_WaitAll(const TArray<FBeamRequestContext>& RequestContexts,
	                            const TArray<FBeamOperationHandle>& Operations, const TArray<FBeamWaitHandle>& Waits,
	                            FOnWaitCompleteCode OnCompleteCode);

	/**
	 * Returns TRUE if ALL of the Requests, Operations or Waits it depends on Succeeded.
	 * Cancelled operations do not make this return true.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Waits")
	bool IsWaitSuccessful(const FBeamWaitCompleteEvent& Evt) const;

	/**
	 * Returns TRUE if any of the Requests, Operations or Waits it depends on Failed.
	 * Cancelled operations do not make this return true.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Waits")
	bool IsWaitFailed(const FBeamWaitCompleteEvent& Evt, TArray<FString>& Errors) const;

	/**
	 * Returns TRUE if any of the Requests, Operations or Waits it depends on were cancelled.	 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Waits")
	bool IsAnyWaitCancelled(const FBeamWaitCompleteEvent& Evt) const;


	/**
	 * This will invoke a single hook --- returns false if the hook was not bound.
	 */
	template <typename FHook, typename... Args>
	bool InvokeAndWaitForHooks(FBeamWaitHandle& OutWaitHandle, FHook Hooks, FOnWaitCompleteCode Handler, Args&&... args)
	{
		if (Hooks.IsBound()) return InvokeAndWaitForHooks(OutWaitHandle, TArray<FHook>{Hooks}, Handler, std::forward<Args>(args)...);
		return InvokeAndWaitForHooks(OutWaitHandle, TArray<FHook>{}, Handler, std::forward<Args>(args)...);
	}

	/**
	 * Returns false if a hook was not bound or if no hooks were present. True if all present hooks were correctly bound.   
	 */
	template <typename FHook, typename... Args>
	bool InvokeAndWaitForHooks(FBeamWaitHandle& OutWaitHandle, TArray<FHook> Hooks, FOnWaitCompleteCode Handler, Args&&... args)
	{
		static_assert(std::is_same_v<typename FHook::RetValType, FBeamOperationHandle>, TEXT("This FHook does not return an FBeamOperationHandle. You can't wait on it."));

		// Since hooks are optional by default, if there are none we just do nothing.
		if (!Hooks.Num())
		{
			OutWaitHandle = GetSelf()->CPP_WaitAll({}, {}, {}, Handler);
			return true;
		}

		bool bShouldRun = true;
		FString Error = FString(TEXT("Unbound hook detected! All hooks in the array must be bound to something. "));
		for (int i = 0; i < Hooks.Num(); ++i)
		{
			const FHook& Hook = Hooks[i];
			const bool bIsBound = Hook.IsBound();
			bShouldRun &= bIsBound;
			Error.Append(bIsBound ? "" : "Hook at idx=%d is not bound, ");
		}

		if (bShouldRun)
		{
			TArray<FBeamOperationHandle> Handles;
			Handles.AddUninitialized(Hooks.Num());
			for (int i = 0; i < Hooks.Num(); ++i)
			{
				const FHook& Hook = Hooks[i];
				Handles[i] = Hook.Execute(std::forward<Args>(args)...);
			}
			OutWaitHandle = GetSelf()->CPP_WaitAll({}, Handles, {}, Handler);
			return true;
		}

		UE_LOG(LogBeamRequestTracker, Error, TEXT("%s"), *Error);
		return false;
	}


	/***
	 *       ____                        __  _                 
	 *      / __ \____  ___  _________ _/ /_(_)___  ____  _____
	 *     / / / / __ \/ _ \/ ___/ __ `/ __/ / __ \/ __ \/ ___/
	 *    / /_/ / /_/ /  __/ /  / /_/ / /_/ / /_/ / / / (__  ) 
	 *    \____/ .___/\___/_/   \__,_/\__/_/\____/_/ /_/____/  
	 *        /_/                                              
	 */

	/**
	 * @brief List of all active operations. See BeginOperation and MarkOperation____ functions.
	 */
	TArray<FBeamOperationHandle> ActiveOperations;

	/**
	 * @brief Current state of each operation --- keeps track of the maximum number of requests we can expect, current list of requests we depend on and the Status of the operation.
	 */
	UPROPERTY()
	TMap<FBeamOperationHandle, UBeamOperationState*> ActiveOperationState;

	/**
	 * @brief This begins an Operation.
	 * The returning OperationWaitHandle can be used to Wait on an entire chain of requests.
	 * @param Participants The list of all potential user slots that are participating in this operation.
	 * @param OnEvent An event handler to handle all potential events of this operation. 
	 * @return An Operation Handle you can use to enable callers to wait on the operation. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operations", meta=(AutoCreateRefTerm="CallingSystem"))
	FBeamOperationHandle BeginOperation(const TArray<FUserSlot>& Participants, const FString& CallingSystem,
	                                    FBeamOperationEventHandler OnEvent);

	/**
	 * @brief This begins an Operation.
	 * The returning OperationWaitHandle can be used to Wait on an entire chain of requests.
	 * @param Participants The list of all potential user slots that are participating in this operation.
	 * @param OnEvent An event handler to handle all potential events of this operation. 
	 * @return An Operation Handle you can use to enable callers to wait on the operation. 
	 */
	FBeamOperationHandle CPP_BeginOperation(const TArray<FUserSlot>& Participants, const FString& CallingSystem,
	                                        FBeamOperationEventHandlerCode OnEvent);

	/**
	 * @brief Adds a request to this transaction. This means that every WaitHandle that is waiting on this Operation will now be waiting on this request still.
	 */
	void AddRequestToOperation(const FBeamOperationHandle& Op, int64 RequestId);

	/**
	 * @brief Adds a request to this transaction. This means that every WaitHandle that is waiting on this Operation will now be waiting on this request still.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operations")
	void AddRequestToOperation(const FBeamOperationHandle& Op, FBeamRequestContext RequestContext);

	/**
	 * @brief Call only within OnSuccess/OnError/OnComplete or FullResponse handlers when the operation is completed and ended with success. 	 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operations", meta=(AdvancedDisplay="RequestId", AutoCreateRefTerm="RequestId"))
	void TriggerOperationSuccess(const FBeamOperationHandle& Op, const FString& EventCode, const int64& RequestId = -1000);

	/**
	 * @brief Call only within OnSuccess/OnError/OnComplete or FullResponse handlers when the operation is completed and ended with an error. 	 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operations", meta=(AdvancedDisplay="RequestId", AutoCreateRefTerm="RequestId"))
	void TriggerOperationError(const FBeamOperationHandle& Op, const FString& EventCode, const int64& RequestId = -1000);

	/**
	 * @brief Call only within OnSuccess/OnError/OnComplete or FullResponse handlers when the operation is completed and was cancelled by the user.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operations", meta=(AdvancedDisplay="RequestId", AutoCreateRefTerm="RequestId"))
	void TriggerOperationCancelled(const FBeamOperationHandle& Op, const FString& EventCode, const int64& RequestId = -1000);

	/**
	 * @brief Call only within OnSuccess/OnError/OnComplete or FullResponse handlers when the operation is completed and ended with success. 	 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operations", meta=(AdvancedDisplay="RequestId", AutoCreateRefTerm="RequestId"))
	void TriggerOperationSuccessWithData(const FBeamOperationHandle& Op, const FString& EventCode, const TScriptInterface<IBeamOperationEventData>& EventData, const int64& RequestId = -1000);

	/**
	 * @brief Call only within OnSuccess/OnError/OnComplete or FullResponse handlers when the operation is completed and ended with an error. 	 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operations", meta=(AdvancedDisplay="RequestId", AutoCreateRefTerm="RequestId"))
	void TriggerOperationErrorWithData(const FBeamOperationHandle& Op, const FString& EventCode, const TScriptInterface<IBeamOperationEventData>& EventData, const int64& RequestId = -1000);

	/**
	 * @brief Call only within OnSuccess/OnError/OnComplete or FullResponse handlers when the operation is completed and was cancelled by the user.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operations", meta=(AdvancedDisplay="RequestId", AutoCreateRefTerm="RequestId"))
	void TriggerOperationCancelledWithData(const FBeamOperationHandle& Op, const FString& EventCode, const TScriptInterface<IBeamOperationEventData>& EventData, const int64& RequestId = -1000);

	/**
	 * @brief Call only within OnSuccess/OnError/OnComplete or FullResponse handlers when you wish to trigger an event that does not mean the operation is over. 
	 * @param Op The Operation whose event is being triggered.
	 * @param Type The type of the operation event being triggered.
	 * @param EventId The type of the sub-event being triggered.	 
	 * @param EventCode Arbitrary data for the event.	 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operations", meta=(AdvancedDisplay="RequestId", AutoCreateRefTerm="RequestId"))
	void TriggerOperationEvent(const FBeamOperationHandle& Op, const EBeamOperationEventType Type, FName EventId, const FString& EventCode, const int64& RequestId = -1000);

	/**
	 * @brief Call at any point before an operation is completed via the TriggerOperationSuccess|TriggerOperationError|TriggerOperationCancelled functions. 
	 * @param Op The Operation whose event is being triggered.
	 * @param Type The type of the operation event being triggered.
	 * @param EventId The type of the sub-event being triggered.	 
	 * @param EventCode A string describing the code for the event (sometimes can just be a raw string containing data for the event --- described on each operation's comments).
	 * @param EventData An optional object structure that has some arbitrary data associated with the event that might be useful for user-code.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operations", meta=(AdvancedDisplay="RequestId", AutoCreateRefTerm="RequestId"))
	void TriggerOperationEventWithData(const FBeamOperationHandle& Op, const EBeamOperationEventType Type, FName EventId, const FString& EventCode,
	                                   const TScriptInterface<IBeamOperationEventData> EventData, const int64& RequestId = -1000);

	/**
	 * @brief Triggers an operation event with the given parameters. 
	 * @param Op The Operation whose event is being triggered.
	 * @param Type The type of the operation event being triggered.
	 * @param EventId The type of the sub-event being triggered.
	 * @param UserSlots The user slots involved in triggering.
	 * @param EventCode Arbitrary data for the event.
	 * @param EventData
	 * @param CallingSystem The name of the system triggering the event.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operations")
	void TriggerOperationEventFull(const FBeamOperationHandle& Op, EBeamOperationEventType Type, FName EventId,
	                               const TArray<FUserSlot>& UserSlots, const FString& EventCode,
	                               const TScriptInterface<IBeamOperationEventData>& EventData, const FString& CallingSystem, int64 RequestId = -1);


	/**
	 * Queries the triggered events of any particular operation giving you back a subset of these events.
	 * Mostly used when waiting for several operations and then querying the results of them once all of them are done.
	 * 
	 * @param Op The operation to get the events from. 
	 * @param FilterType The EBeamOperationEventType we want to filter by. EBeamOperationEventType::OET_NONE means no filter will be applied and all types of events will be returned.
	 * @param FilterId The FBeamOperationEvent.EventId we want to filter by. NAME_All means no filter will be applied and all EventIds will be returned.  
	 * @param Events The filtered list of events.
	 * @return True, if the operation is still in memory. False, otherwise.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operations", meta=(ExpandBoolAsExecs="ReturnValue"))
	bool TryGetOperationEvents(const FBeamOperationHandle& Op, const EBeamOperationEventType& FilterType, const FName& FilterId, TArray<FBeamOperationEvent>& Events);

	/**
	 * Queries the triggered events of any particular operation giving you back the list of all EBeamOperationEventType::OET_SUCCESS events.
	 * Mostly used when waiting for several operations and then querying the results of them once all of them are done.
	 * 
	 * @param Op The operation to get the events from.	   
	 * @param Events The filtered list of events.
	 * @return True, if the operation is still in memory. False, otherwise.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operations", meta=(ExpandBoolAsExecs="ReturnValue"))
	bool TryGetOperationSuccesses(const FBeamOperationHandle& Op, TArray<FBeamOperationEvent>& Events);

	/**
	 * Queries the triggered events of any particular operation giving you back the list of all EBeamOperationEventType::OET_ERROR events.
	 * Mostly used when waiting for several operations and then querying the results of them once all of them are done.
	 * 
	 * @param Op The operation to get the events from.	   
	 * @param Events The filtered list of events.
	 * @return True, if the operation is still in memory. False, otherwise.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operations", meta=(ExpandBoolAsExecs="ReturnValue"))
	bool TryGetOperationErrors(const FBeamOperationHandle& Op, TArray<FBeamOperationEvent>& Events);

	/**
	 * Queries the triggered events of any particular operation giving you back the list of all EBeamOperationEventType::OET_CANCELLED events.
	 * Mostly used when waiting for several operations and then querying the results of them once all of them are done.
	 * 
	 * @param Op The operation to get the events from.	   
	 * @param Events The filtered list of events.
	 * @return True, if the operation is still in memory. False, otherwise.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operations", meta=(ExpandBoolAsExecs="ReturnValue"))
	bool TryGetOperationCancelations(const FBeamOperationHandle& Op, TArray<FBeamOperationEvent>& Events);

	/**
	 * Queries the triggered events of any particular operation giving you back the list of all EBeamOperationEventType::OET_SUCCESS events filtered by the given FilterId.
	 * Mostly used when waiting for several operations and then querying the results of them once all of them are done.
	 * 
	 * @param Op The operation to get the events from.	   
	 * @param FilterId The FBeamOperationEvent.EventId we want to filter by. NAME_All means no filter will be applied and all EventIds will be returned.  
	 * @param Events The filtered list of events.
	 * @return True, if the operation is still in memory. False, otherwise.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operations", meta=(ExpandBoolAsExecs="ReturnValue"))
	bool TryGetOperationSuccessesWithId(const FBeamOperationHandle& Op, FName FilterId, TArray<FBeamOperationEvent>& Events);

	/**
	 * Queries the triggered events of any particular operation giving you back the list of all EBeamOperationEventType::OET_ERROR events filtered by the given FilterId.
	 * Mostly used when waiting for several operations and then querying the results of them once all of them are done.
	 * 
	 * @param Op The operation to get the events from.	   
	 * @param FilterId The FBeamOperationEvent.EventId we want to filter by. NAME_All means no filter will be applied and all EventIds will be returned.  
	 * @param Events The filtered list of events.
	 * @return True, if the operation is still in memory. False, otherwise.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operations", meta=(ExpandBoolAsExecs="ReturnValue"))
	bool TryGetOperationErrorsWithId(const FBeamOperationHandle& Op, FName FilterId, TArray<FBeamOperationEvent>& Events);

	/**
	 * Queries the triggered events of any particular operation giving you back the list of all EBeamOperationEventType::OET_CANCELLED events filtered by the given FilterId.
	 * Mostly used when waiting for several operations and then querying the results of them once all of them are done.
	 * 
	 * @param Op The operation to get the events from.	   
	 * @param FilterId The FBeamOperationEvent.EventId we want to filter by. NAME_All means no filter will be applied and all EventIds will be returned.  
	 * @param Events The filtered list of events.
	 * @return True, if the operation is still in memory. False, otherwise.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operations", meta=(ExpandBoolAsExecs="ReturnValue"))
	bool TryGetOperationCancelationsWithId(const FBeamOperationHandle& Op, FName FilterId, TArray<FBeamOperationEvent>& Events);

	/**
	 * This is just a short-cut for the most-common-case for an operation (that only has its final Success/Error/Cancelled event). This will return you that event's Code and Data along with its type.
	 * If the operation has not yet emitted its final event, the return value here will be OET_NONE. 
	 * 
	 * @param Op The operation to get the event from.	   
	 * @param EventCode The FBeamOperationEvent.EventCode for the final emitted event of the operation.  
	 * @param EventData The FBeamOperationEvent.EventData for the last emitted event of the operation.
	 * @param OperationEventType OET_NONE, if the operation has not emitted its final event yet. OET_SUCCESS/OET_ERROR/OET_CANCELLED depending on what type was the final event.
	 * @return True if the event exist and false if the event don't exist
	*/
	UFUNCTION(BlueprintCallable, Category="Beam|Operations", meta=(ExpandEnumAsExecs="OperationEventType", ExpandBoolAsExecs="ReturnValue"))
	bool TryGetOperationResult(const FBeamOperationHandle& Op, FString& EventCode, TScriptInterface<IBeamOperationEventData>& EventData, TEnumAsByte<EBeamOperationEventType>& OperationEventType);

	/**
	 * Checks if the Operation exists and is not completed.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operations", meta=(ExpandBoolAsExecs="ReturnValue"))
	bool IsOperationActive(const FBeamOperationHandle& Op);

	/**
	 * Shortcut function call that returns an empty operation that is completed with success. 
	 */
	FBeamOperationHandle CPP_BeginSuccessfulOperation(const TArray<FUserSlot>& Participants, const FString& CallingSystem, FString Success, FBeamOperationEventHandlerCode OnEvent);

	/**
	 * Shortcut function call that returns an empty operation completed with an error error. 
	 */
	FBeamOperationHandle CPP_BeginErrorOperation(const TArray<FUserSlot>& Participants, const FString& CallingSystem, FString Error, FBeamOperationEventHandlerCode OnEvent);
};
