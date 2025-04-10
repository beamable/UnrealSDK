#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/KickRequestBody.h"

#include "KickRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UKickRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Groups|Utils|Json", DisplayName="KickRequestBody To JSON String")
	static FString KickRequestBodyToJsonString(const UKickRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Groups|Utils|Make/Break", DisplayName="Make KickRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="SubGroup, Outer", NativeMakeFunc))
	static UKickRequestBody* Make(int64 GamerTag, FOptionalInt64 SubGroup, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Groups|Utils|Make/Break", DisplayName="Break KickRequestBody", meta=(NativeBreakFunc))
	static void Break(const UKickRequestBody* Serializable, int64& GamerTag, FOptionalInt64& SubGroup);
};