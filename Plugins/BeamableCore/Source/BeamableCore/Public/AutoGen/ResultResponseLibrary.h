#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ResultResponse.h"

#include "ResultResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UResultResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Json", DisplayName="ResultResponse To JSON String")
	static FString ResultResponseToJsonString(const UResultResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Backend", DisplayName="Make ResultResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UResultResponse* Make(bool bResult, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Backend", DisplayName="Break ResultResponse", meta=(NativeBreakFunc))
	static void Break(const UResultResponse* Serializable, bool& bResult);
};