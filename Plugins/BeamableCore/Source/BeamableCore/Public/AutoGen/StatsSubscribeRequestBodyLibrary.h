
#pragma once

#include "CoreMinimal.h"
#include "StatsSubscribeRequestBody.h"

#include "StatsSubscribeRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UStatsSubscribeRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize StatsSubscribeRequestBody To JSON String")
	static FString StatsSubscribeRequestBodyToJsonString(const UStatsSubscribeRequestBody* Serializable, const bool Pretty);		
};