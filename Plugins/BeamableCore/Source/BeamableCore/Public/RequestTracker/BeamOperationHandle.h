#pragma once

#include "CoreMinimal.h"
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


