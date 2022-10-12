
#pragma once

#include "CoreMinimal.h"
#include "StatsSearchCriteria.h"

#include "StatsSearchCriteriaLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UStatsSearchCriteriaLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize StatsSearchCriteria To JSON String")
	static FString StatsSearchCriteriaToJsonString(const UStatsSearchCriteria* Serializable, const bool Pretty);		
};