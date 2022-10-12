
#pragma once

#include "CoreMinimal.h"
#include "DateRange.h"

#include "DateRangeLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UDateRangeLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize DateRange To JSON String")
	static FString DateRangeToJsonString(const UDateRange* Serializable, const bool Pretty);		
};