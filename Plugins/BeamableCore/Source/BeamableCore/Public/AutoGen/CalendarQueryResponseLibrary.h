
#pragma once

#include "CoreMinimal.h"
#include "CalendarQueryResponse.h"

#include "CalendarQueryResponseLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UCalendarQueryResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize CalendarQueryResponse To JSON String")
	static FString CalendarQueryResponseToJsonString(const UCalendarQueryResponse* Serializable, const bool Pretty);		
};