
#pragma once

#include "CoreMinimal.h"
#include "EventDateRanges.h"

#include "EventDateRangesLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UEventDateRangesLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize EventDateRanges To JSON String")
	static FString EventDateRangesToJsonString(const UEventDateRanges* Serializable, const bool Pretty);		
};