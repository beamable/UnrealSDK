#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BeamableCore/Public/AutoGen/GroupInvite.h"

#include "GroupInviteLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGroupInviteLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - GroupInvite To JSON String")
	static FString GroupInviteToJsonString(const UGroupInvite* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make GroupInvite", meta=(DefaultToSelf="Outer", AdvancedDisplay="SubGroup, bUseNewRewardsSystem, Outer", NativeMakeFunc))
	static UGroupInvite* Make(int64 GamerTag, FOptionalInt64 SubGroup, FOptionalBool bUseNewRewardsSystem, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break GroupInvite", meta=(NativeBreakFunc))
	static void Break(const UGroupInvite* Serializable, int64& GamerTag, FOptionalInt64& SubGroup, FOptionalBool& bUseNewRewardsSystem);
};