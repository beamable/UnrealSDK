
#pragma once

#include "CoreMinimal.h"
#include "BatchReadStatsResponse.h"

#include "BatchReadStatsResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UBatchReadStatsResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize BatchReadStatsResponse To JSON String")
	static FString BatchReadStatsResponseToJsonString(const UBatchReadStatsResponse* Serializable, const bool Pretty);		
};