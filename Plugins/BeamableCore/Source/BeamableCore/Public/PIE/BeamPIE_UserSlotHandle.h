#pragma once

#include "UserSlots/UserSlot.h"
#include "BeamPIE_UserSlotHandle.generated.h"

USTRUCT(BlueprintType)
struct BEAMABLECORE_API FBeamPIE_UserSlotHandle
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 PIEIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FUserSlot Slot = FUserSlot{};

	friend bool operator==(const FBeamPIE_UserSlotHandle& Lhs, const FBeamPIE_UserSlotHandle& RHS)
	{
		return Lhs.Slot == RHS.Slot && Lhs.PIEIndex == RHS.PIEIndex;
	}

	friend bool operator!=(const FBeamPIE_UserSlotHandle& Lhs, const FBeamPIE_UserSlotHandle& RHS)
	{
		return !(Lhs == RHS);
	}
};

FORCEINLINE uint32 GetTypeHash(const FBeamPIE_UserSlotHandle& Context) { return HashCombine(GetTypeHash(Context.Slot), GetTypeHash(Context.PIEIndex)); }
