
#pragma once

#include "CoreMinimal.h"
#include "CalendarClaimRequestBody.h"

#include "CalendarClaimRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UCalendarClaimRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize CalendarClaimRequestBody To JSON String")
	static FString CalendarClaimRequestBodyToJsonString(const UCalendarClaimRequestBody* Serializable, const bool Pretty);		
};