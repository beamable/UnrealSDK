
#pragma once

#include "CoreMinimal.h"
#include "StatsSearchRequestBody.h"

#include "StatsSearchRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UStatsSearchRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize StatsSearchRequestBody To JSON String")
	static FString StatsSearchRequestBodyToJsonString(const UStatsSearchRequestBody* Serializable, const bool Pretty);		
};