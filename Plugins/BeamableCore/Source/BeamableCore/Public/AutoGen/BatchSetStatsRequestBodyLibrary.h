
#pragma once

#include "CoreMinimal.h"
#include "BatchSetStatsRequestBody.h"

#include "BatchSetStatsRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UBatchSetStatsRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize BatchSetStatsRequestBody To JSON String")
	static FString BatchSetStatsRequestBodyToJsonString(const UBatchSetStatsRequestBody* Serializable, const bool Pretty);		
};