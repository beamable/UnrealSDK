#pragma once

#include "CoreMinimal.h"
#include "BeamOperationHandle.h"
#include "BeamWaitHandle.h"
#include "UserSlots/UserSlot.h"

#include "BeamOperation.generated.h"


/**
 * @brief Operations can trigger arbitrary events over the course of their execution (which are exposed to blueprints).
 * Every event has a general classification: is it an success, error or cancellation? This enum answers that question.
 */
UENUM(BlueprintType)
enum EBeamOperationEventType
{
	OET_NONE      = 0 UMETA(Hidden),
	OET_SUCCESS   = 1 << 0,
	OET_ERROR     = 1 << 1,
	OET_CANCELLED = 1 << 2,
};

BEAMABLECORE_API ENUM_CLASS_FLAGS(EBeamOperationEventType);

UINTERFACE()
class UBeamOperationEventData : public UInterface
{
	GENERATED_BODY()
};

class IBeamOperationEventData
{
	GENERATED_BODY()

public:
	
};

/**
 * @brief An Operation event.
 * These can be triggered from BP or CPP (see UBeamRequestTracker::TriggerOperationEventFull and others) so that users can respond to a point in the operation.
 * The most common use case for these are wrapping a sequence of request that client code only cares about when it's done or if any of the sub-requests failed.
 * Other advanced use cases may include: an operation that exposes custom events based on processed data it gets out of the requests its making or
 * a long running intermittent operation that runs every once in a while (keep in mind that all requests associated with an operation will not be released from memory until the op completes).
 * 
 * There are more things you can do with this and we have a base custom blueprint node you can leverage to expose this in a very simple way to Blueprints (see UK2BeamNode_Operation). 
 */
USTRUCT(BlueprintType)
struct BEAMABLECORE_API FBeamOperationEvent
{
	GENERATED_BODY()
	/**
	 * @brief The owner operation. This is mostly here for testing. 
	 */
	UPROPERTY(BlueprintReadOnly, AdvancedDisplay)
	FBeamOperationHandle OwnerHandle;

	/**
	 * @brief The event type of this event.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Beam")
	TEnumAsByte<EBeamOperationEventType> EventType = EBeamOperationEventType::OET_SUCCESS;

	/**
	 * @brief If this event is being called from inside a Request's response handler, we pass in that Request's Id so users can check for number of attempts among other things.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Beam")
	int64 RequestId = -1;

	/**
	 * @brief An operation-specific id describing the type of the event that happened.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Beam")
	FName EventId = NAME_None;

	/**
	 * @brief The Beamable Runtime System where the Operation event originated.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Beam")
	FString System;

	/**
	 * @brief An Error Code string. In some very rare cases, this might just be some arbitrary string data that can be passed on by the event.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Beam")
	FString EventCode;

	/**
	 * @brief An event data object that may or may not exist for each emitted event.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Beam")
	TScriptInterface<IBeamOperationEventData> EventData;
};


DECLARE_DYNAMIC_DELEGATE_OneParam(FBeamOperationEventHandler, FBeamOperationEvent, OperationEvent);

DECLARE_DELEGATE_OneParam(FBeamOperationEventHandlerCode, FBeamOperationEvent);

/**
 * @brief The current state of an operation: it tracks its request dependencies, its participants and the expected number of requests.
 */
UCLASS(BlueprintType)
class BEAMABLECORE_API UBeamOperationState : public UObject
{
	GENERATED_BODY()

public:
	static const int ONGOING  = 0;
	static const int COMPLETE_SUCCESS = 1;
	static const int COMPLETE_FAILURE = 2;
	static const int CANCELLED = 3;

	/**
	 * @brief Whether or not this operation is ongoing, complete or cancelled.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int Status = ONGOING;

	/**
	 * @brief The name of subsystem that owns this operation. Mostly for debugging purposes. 
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString CallingSystem;

	/**
	 * @brief The list of requests that were made during this operation.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<int64> DependentRequests;

	/**
	 * @brief The list of user slots that are participating in this operation.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FUserSlot> DependentUserSlots;

	/**
	 * @brief The list of user slots that are participating in this operation.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FBeamWaitHandle> WaitedBy;
	
	/**
	 * @brief The Blueprint-based Handler for this Operation's Events.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FBeamOperationEventHandler BlueprintHandler;

	/**
	 * @brief The Code-based Handler for this Operation's Events.
	 */	
	FBeamOperationEventHandlerCode CodeHandler;

	/**
	 * List of events that were triggered by this operation.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FBeamOperationEvent> TriggeredEvents;
};
