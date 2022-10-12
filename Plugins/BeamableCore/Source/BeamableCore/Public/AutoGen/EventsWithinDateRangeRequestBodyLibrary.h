
#pragma once

#include "CoreMinimal.h"
#include "EventsWithinDateRangeRequestBody.h"

#include "EventsWithinDateRangeRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UEventsWithinDateRangeRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize EventsWithinDateRangeRequestBody To JSON String")
	static FString EventsWithinDateRangeRequestBodyToJsonString(const UEventsWithinDateRangeRequestBody* Serializable, const bool Pretty);		
};