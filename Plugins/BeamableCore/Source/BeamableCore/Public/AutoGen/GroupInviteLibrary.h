#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GroupInvite.h"

#include "GroupInviteLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGroupInviteLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Json", DisplayName="GroupInvite To JSON String")
	static FString GroupInviteToJsonString(const UGroupInvite* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Backend", DisplayName="Make GroupInvite", meta=(DefaultToSelf="Outer", AdvancedDisplay="SubGroup, bUseNewRewardsSystem, Outer", NativeMakeFunc))
	static UGroupInvite* Make(int64 GamerTag, FOptionalInt64 SubGroup, FOptionalBool bUseNewRewardsSystem, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Backend", DisplayName="Break GroupInvite", meta=(NativeBreakFunc))
	static void Break(const UGroupInvite* Serializable, int64& GamerTag, FOptionalInt64& SubGroup, FOptionalBool& bUseNewRewardsSystem);
};