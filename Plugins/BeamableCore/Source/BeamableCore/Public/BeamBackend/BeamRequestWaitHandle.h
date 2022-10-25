#pragma once

#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamBaseRequestInterface.h"

#include "BeamRequestWaitHandle.generated.h"

// Forward declaration of beam backend so we can provide a useful API out of this struct
class UBeamBackend;

UENUM(BlueprintType)
enum EWaitHandleMode { All, };

UDELEGATE()
DECLARE_DYNAMIC_DELEGATE_FourParams(FOnWaitComplete, const TArray<FBeamRequestContext>&, Contexts, const TArray<TScriptInterface<IBeamBaseRequestInterface>>&, Requests,
                                    const TArray<UObject*>&, Responses, const TArray<FBeamErrorResponse>&, Errors);


USTRUCT(BlueprintType)
struct FBeamRequestWaitHandle
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	int64 WaitHandleId;

	UPROPERTY()
	UBeamBackend* BeamBackend = nullptr;

	EWaitHandleMode Mode;
	EBeamRequestStatus Status;

	friend bool operator==(const FBeamRequestWaitHandle& Lhs, const FBeamRequestWaitHandle& RHS)
	{
		return Lhs.WaitHandleId == RHS.WaitHandleId
			&& Lhs.Mode == RHS.Mode;
	}

	friend bool operator!=(const FBeamRequestWaitHandle& Lhs, const FBeamRequestWaitHandle& RHS)
	{
		return !(Lhs == RHS);
	}
};

FORCEINLINE uint32 GetTypeHash(const FBeamRequestWaitHandle& WaitHandle) { return GetTypeHash(WaitHandle.WaitHandleId); }
