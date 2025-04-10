#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/DisbandRequestBody.h"

#include "DisbandRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UDisbandRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Groups|4 - Json", DisplayName="DisbandRequestBody To JSON String")
	static FString DisbandRequestBodyToJsonString(const UDisbandRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Groups|3 - Backend", DisplayName="Make DisbandRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="SubGroup, Outer", NativeMakeFunc))
	static UDisbandRequestBody* Make(FOptionalInt64 SubGroup, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Groups|3 - Backend", DisplayName="Break DisbandRequestBody", meta=(NativeBreakFunc))
	static void Break(const UDisbandRequestBody* Serializable, FOptionalInt64& SubGroup);
};