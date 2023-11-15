#pragma once

#include "CoreMinimal.h"
#include "BeamOperationHandle.h"
#include "UserSlots/UserSlot.h"

#include "BeamOperation.generated.h"


/**
 * @brief Operations can trigger arbitrary events over the course of their execution (which are exposed to blueprints).
 * Every event has a general classification: is it an success, error or cancellation? This enum answers that question.
 */
UENUM(BlueprintType)
enum EBeamOperationEventType
{
	OET_NONE = 0 UMETA(Hidden),
	OET_SUCCESS = 1 << 0,
	OET_ERROR = 1 << 1,
	OET_CANCELLED = 1 << 2,
};

BEAMABLECORE_API ENUM_CLASS_FLAGS(EBeamOperationEventType);

/**
 * @brief Every event an Operation trigger has a sub type. The default sub-type is "Final" meaning the operation:
 * completed with a success OR it completed with an error OR it completed because it was cancelled. 
 *
 * This is just a byte in the FBeamOperationEvent struct so you can declare your custom enumerations that are specific to an operation and leverage that instead.
 * If you don't want to specify a custom one, use this one whenever asked for the subtype.
 *
 * Just keep in mind that 0 is a reserved value that means the operation is over. Also, you must add the MetaData flags indicating which SubType values are available for each Type value:
 *  - OperationSuccessSubEvents="Final,OtherSuccessSubEvent" 
 *  - OperationErrorSubEvents="Final,OtherErrorSubEvent"
 *  - OperationCancelledSubEvents="Final,OtherCancelledSubEvent" *
 *
 *  Unless you are making a very specific operation, you can use "EventA,EventB,EventC" declarations for sub-events and map them to their parsed structs.
 */
UENUM(BlueprintType, meta=(OperationSuccessSubEvents="Final,EventA,EventB,EventC", OperationErrorSubEvents="Final,EventA,EventB,EventC", OperationCancelledSubEvents="Final,EventA,EventB,EventC"))
enum EDefaultOperationEventSubType
{
	Final = 0 UMETA(Tooltip="It is the final event of the operation. No more events will be issued later."),
	EventA = 1 UMETA(Tooltip="It is another event in the operation. More events can be issued later. Here to make it unnecessary to create enums for operations that want to send unnamed events."),
	EventB = 2 UMETA(Tooltip="It is another event in the operation. More events can be issued later. Here to make it unnecessary to create enums for operations that want to send unnamed events."),
	EventC = 3 UMETA(Tooltip="It is another event in the operation. More events can be issued later. Here to make it unnecessary to create enums for operations that want to send unnamed events."),
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
	 * @brief An code indicating the an operation-specific type of the event that happened. It is the value of an operation-specific Enum.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Beam")
	uint8 EventSubTypeCode = 0;

	/**
	 * @brief The Beamable Runtime System where the Operation event originated.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Beam")
	FString System;

	/**
	 * @brief An error string or some arbitrary string data that can be passed on by the event
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Beam")
	FString EventData;

	/**
	 * @brief The owner operation. This is mostly here for testing. 
	 */
	UPROPERTY(BlueprintReadOnly, AdvancedDisplay)
	FBeamOperationHandle OwnerHandle;
};


DECLARE_DYNAMIC_DELEGATE_TwoParams(FBeamOperationEventHandler, const TArray<FUserSlot>&, UserSlots, FBeamOperationEvent, OperationEvent);

DECLARE_DELEGATE_TwoParams(FBeamOperationEventHandlerCode, const TArray<FUserSlot>&, FBeamOperationEvent);
