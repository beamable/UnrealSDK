#pragma once

#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamBaseRequestInterface.h"

#include "BeamWaitHandle.generated.h"

// Forward declaration of beam backend so we can provide a useful API out of this struct
class UBeamBackend;

UENUM(BlueprintType)
enum EWaitHandleMode { All, };

UDELEGATE()
DECLARE_DYNAMIC_DELEGATE_FourParams(FOnWaitComplete, const TArray<FBeamRequestContext>&, Contexts, const TArray<TScriptInterface<IBeamBaseRequestInterface>>&, Requests,
                                    const TArray<UObject*>&, Responses, const TArray<FBeamErrorResponse>&, Errors);

DECLARE_DELEGATE_FourParams(FOnWaitCompleteCode, const TArray<FBeamRequestContext>&, const TArray<TScriptInterface<IBeamBaseRequestInterface>>&, const TArray<UObject*>&,
                            const TArray<FBeamErrorResponse>&);


/**
 * @brief A wait-handle provided by the BeamRequestTracker system.
 * It keeps track of a group of requests, operations and other wait handles and allows you to react to when those requests are finished as a group. 
 */
USTRUCT(BlueprintType)
struct FBeamWaitHandle
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	int64 WaitHandleId = -1;

	UPROPERTY()
	UBeamBackend* BeamBackend = nullptr;

	EWaitHandleMode Mode;
	EBeamAsyncStatus Status;

	friend bool operator==(const FBeamWaitHandle& Lhs, const FBeamWaitHandle& RHS)
	{
		return Lhs.WaitHandleId == RHS.WaitHandleId
			&& Lhs.Mode == RHS.Mode;
	}

	friend bool operator!=(const FBeamWaitHandle& Lhs, const FBeamWaitHandle& RHS)
	{
		return !(Lhs == RHS);
	}
};

FORCEINLINE uint32 GetTypeHash(const FBeamWaitHandle& WaitHandle) { return GetTypeHash(WaitHandle.WaitHandleId); }
