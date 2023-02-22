#pragma once

#include "CoreMinimal.h"
#include "UserSlots/UserSlot.h"
#include "BeamOperationHandle.generated.h"

/**
 * @brief An Operation Handle that can be used to add requests to an operation and to trigger it's completion (see BeamRequestTracker for more details).
 * The TLDR for an operation is that it is kinda like a "data-driven promise", as in, it solves the same problem a regular promise does but in a blueprint compatible way.
 */
USTRUCT(BlueprintType)
struct BEAMABLECORE_API FBeamOperationHandle
{
	GENERATED_BODY()

	FBeamOperationHandle() : OperationId(-1)
	{
	}

	FBeamOperationHandle(int64 Id) : OperationId(Id)
	{
	}

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Beam")
	/**
	 * @brief The OperationId. This is an per-session auto-increment that should not be persisted ever. 
	 */
	int64 OperationId;

	friend bool operator==(const FBeamOperationHandle& Lhs, const FBeamOperationHandle& RHS)
	{
		return Lhs.OperationId == RHS.OperationId;
	}

	friend bool operator!=(const FBeamOperationHandle& Lhs, const FBeamOperationHandle& RHS)
	{
		return !(Lhs == RHS);
	}
};

FORCEINLINE uint32 GetTypeHash(const FBeamOperationHandle& OperationHandle) { return GetTypeHash(OperationHandle.OperationId); }


/**
 * @brief The current state of an operation: it tracks its request dependencies, its participants and the expected number of requests.
 */
USTRUCT(BlueprintType)
struct FBeamOperationState
{
	GENERATED_BODY()

	static const int ONGOING = 0;
	static const int COMPLETE = 1;
	static const int CANCELED = 2;

	
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
	 * @brief The maximum number of Request Ids.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 MaximumRequestCount = -1;
};
