#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BatchSetStatsRequestBody.h"

#include "BatchSetStatsRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBatchSetStatsRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - BatchSetStatsRequestBody To JSON String")
	static FString BatchSetStatsRequestBodyToJsonString(const UBatchSetStatsRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make BatchSetStatsRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UBatchSetStatsRequestBody* Make(TArray<UStatUpdateRequestBody*> Updates, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break BatchSetStatsRequestBody", meta=(NativeBreakFunc))
	static void Break(const UBatchSetStatsRequestBody* Serializable, TArray<UStatUpdateRequestBody*>& Updates);
};