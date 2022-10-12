
#pragma once

#include "CoreMinimal.h"
#include "EventsInDateRangeResponse.h"

#include "EventsInDateRangeResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UEventsInDateRangeResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize EventsInDateRangeResponse To JSON String")
	static FString EventsInDateRangeResponseToJsonString(const UEventsInDateRangeResponse* Serializable, const bool Pretty);		
};