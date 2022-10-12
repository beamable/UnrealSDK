
#pragma once

#include "CoreMinimal.h"
#include "BatchReadStatsRequestBody.h"

#include "BatchReadStatsRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UBatchReadStatsRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize BatchReadStatsRequestBody To JSON String")
	static FString BatchReadStatsRequestBodyToJsonString(const UBatchReadStatsRequestBody* Serializable, const bool Pretty);		
};