
#pragma once

#include "CoreMinimal.h"
#include "StatsResponse.h"

#include "StatsResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UStatsResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize StatsResponse To JSON String")
	static FString StatsResponseToJsonString(const UStatsResponse* Serializable, const bool Pretty);		
};