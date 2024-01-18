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
DECLARE_DELEGATE_RetVal(FBeamOperationHandle, FDelayedOperation)


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
	void GatherRequestIdsFromWaitHandle(const FBeamWaitHandle Handle, TArray<FBeamRequestId>& DependedOnRequests, TArray<FBeamOperationHandle>& DependedOnOperations) const;

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
	UFUNCTION(BlueprintCallable, Category="Beam|Waits", meta=(AutoCreateRefTerm="RequestContexts,Operations,Waits", BeamFlowFunction))
	FBeamWaitHandle WaitAll(const TArray<FBeamRequestContext>& RequestContexts, const TArray<FBeamOperationHandle>& Operations, const TArray<FBeamWaitHandle>& Waits, FOnWaitComplete OnComplete);

	/**
	 * @copybrief WaitAll
	 */
	FBeamWaitHandle CPP_WaitAll(const TArray<FBeamRequestContext>& RequestContexts, const TArray<FBeamOperationHandle>& Operations, const TArray<FBeamWaitHandle>& Waits, FOnWaitCompleteCode OnCompleteCode);

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
	bool IsWaitFailed(const FBeamWaitCompleteEvent& Evt) const;

	/**
	 * Returns TRUE if any of the Requests, Operations or Waits it depends on were cancelled.	 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Waits")
	bool IsAnyWaitCancelled(const FBeamWaitCompleteEvent& Evt) const;
	

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
	FBeamOperationHandle BeginOperation(const TArray<FUserSlot>& Participants, const FString& CallingSystem, FBeamOperationEventHandler OnEvent);

	/**
	 * @brief This begins an Operation.
	 * The returning OperationWaitHandle can be used to Wait on an entire chain of requests.
	 * @param Participants The list of all potential user slots that are participating in this operation.
	 * @param OnEvent An event handler to handle all potential events of this operation. 
	 * @return An Operation Handle you can use to enable callers to wait on the operation. 
	 */
	FBeamOperationHandle CPP_BeginOperation(const TArray<FUserSlot>& Participants, const FString& CallingSystem, FBeamOperationEventHandlerCode OnEvent);

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
	void TriggerOperationSuccess(const FBeamOperationHandle& Op, const FString& EventData, const int64& RequestId = -1000);

	/**
	 * @brief Call only within OnSuccess/OnError/OnComplete or FullResponse handlers when the operation is completed and ended with an error. 	 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operations", meta=(AdvancedDisplay="RequestId", AutoCreateRefTerm="RequestId"))
	void TriggerOperationError(const FBeamOperationHandle& Op, const FString& EventData, const int64& RequestId = -1000);

	/**
	 * @brief Call only within OnSuccess/OnError/OnComplete or FullResponse handlers when the operation is completed and was cancelled by the user.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operations", meta=(AdvancedDisplay="RequestId", AutoCreateRefTerm="RequestId"))
	void TriggerOperationCancelled(const FBeamOperationHandle& Op, const FString& EventData, const int64& RequestId = -1000);


	/**
	 * @brief Call only within OnSuccess/OnError/OnComplete or FullResponse handlers when you wish to trigger an event that does not mean the operation is over. 
	 * @param Op The Operation whose event is being triggered.
	 * @param Type The type of the operation event being triggered.
	 * @param SubEvent The type of the sub-event being triggered.	 
	 * @param EventData Arbitrary data for the event.	 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operations", meta=(AdvancedDisplay="RequestId", AutoCreateRefTerm="RequestId"))
	void TriggerOperationEvent(const FBeamOperationHandle& Op, const EBeamOperationEventType Type, FName SubEvent, const FString& EventData, const int64& RequestId = -1000);

	/**
	 * @brief Triggers an operation event with the given parameters. 
	 * @param Op The Operation whose event is being triggered.
	 * @param Type The type of the operation event being triggered.
	 * @param SubEvent The type of the sub-event being triggered.
	 * @param UserSlots The user slots involved in triggering.
	 * @param EventData Arbitrary data for the event.
	 * @param CallingSystem The name of the system triggering the event.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operations")
	void TriggerOperationEventFull(const FBeamOperationHandle& Op, const EBeamOperationEventType Type, FName SubEvent, const TArray<FUserSlot>& UserSlots, const FString& EventData,
	                               const FString&              CallingSystem, const int64        RequestId = -1);
};
