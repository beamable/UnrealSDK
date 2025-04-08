#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BatchSetStatsRequestBody.h"

#include "BatchSetStatsRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBatchSetStatsRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Json", DisplayName="BatchSetStatsRequestBody To JSON String")
	static FString BatchSetStatsRequestBodyToJsonString(const UBatchSetStatsRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Backend", DisplayName="Make BatchSetStatsRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UBatchSetStatsRequestBody* Make(TArray<UStatUpdateRequestBody*> Updates, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Backend", DisplayName="Break BatchSetStatsRequestBody", meta=(NativeBreakFunc))
	static void Break(const UBatchSetStatsRequestBody* Serializable, TArray<UStatUpdateRequestBody*>& Updates);
};