#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/KickRequestBody.h"

#include "KickRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UKickRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - KickRequestBody To JSON String")
	static FString KickRequestBodyToJsonString(const UKickRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make KickRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="SubGroup, Outer", NativeMakeFunc))
	static UKickRequestBody* Make(int64 GamerTag, FOptionalInt64 SubGroup, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break KickRequestBody", meta=(NativeBreakFunc))
	static void Break(const UKickRequestBody* Serializable, int64& GamerTag, FOptionalInt64& SubGroup);
};