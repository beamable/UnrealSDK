#pragma once


#include "BeamableOSS.h"
#include "BeamOperationHandle.h"

#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamBaseResponseBodyInterface.h"

#include "BeamWaitHandle.generated.h"

// Forward declaration of beam backend so we can provide a useful API out of this struct
class UBeamBackend;

/**
 * @brief A wait-handle provided by the BeamRequestTracker system.
 * It keeps track of a group of requests, operations and other wait handles and allows you to react to when those requests are finished as a group. 
 */
USTRUCT(BlueprintType)
struct BEAMABLECORE_API FBeamWaitHandle
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	int64 WaitHandleId = -1;

	friend bool operator==(const FBeamWaitHandle& Lhs, const FBeamWaitHandle& RHS)
	{
		return Lhs.WaitHandleId == RHS.WaitHandleId;
	}

	friend bool operator!=(const FBeamWaitHandle& Lhs, const FBeamWaitHandle& RHS)
	{
		return !(Lhs == RHS);
	}
};

USTRUCT(BlueprintType)
struct BEAMABLECORE_API FBeamWaitCompleteEvent
{
	GENERATED_BODY()

	FBeamWaitHandle WaitHandle;

	UPROPERTY(BlueprintReadOnly)
	TArray<FBeamRequestContext> Contexts;

	UPROPERTY(BlueprintReadOnly)
	TArray<TScriptInterface<IBeamBaseRequestInterface>> Requests;

	UPROPERTY(BlueprintReadOnly)
	TArray<TScriptInterface<IBeamBaseResponseBodyInterface>> Responses;

	UPROPERTY(BlueprintReadOnly)
	TArray<FBeamErrorResponse> Errors;

	UPROPERTY(BlueprintReadOnly)
	TArray<FBeamOperationHandle> Operations;
};


DECLARE_DYNAMIC_DELEGATE_OneParam(FOnWaitComplete, FBeamWaitCompleteEvent, Evt);
DECLARE_DELEGATE_OneParam(FOnWaitCompleteCode, FBeamWaitCompleteEvent);


FORCEINLINE uint32 GetTypeHash(const FBeamWaitHandle& WaitHandle) { return GetTypeHash(WaitHandle.WaitHandleId); }

UCLASS(BlueprintType)
class BEAMABLECORE_API UBeamWaitState : public UObject
{
	GENERATED_BODY()

public:
	EBeamAsyncStatus Status;

	TArray<FBeamRequestId> RequestDependencies;
	TArray<FBeamOperationHandle> OperationDependencies;
	TArray<FBeamWaitHandle> WaitDependencies;

	/**
	 * @brief The Blueprint-based Handler for this Wait's Events.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FOnWaitComplete BlueprintHandler;

	FOnWaitCompleteCode CodeHandler;
};
