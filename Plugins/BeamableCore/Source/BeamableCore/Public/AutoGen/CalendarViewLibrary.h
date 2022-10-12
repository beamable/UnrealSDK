
#pragma once

#include "CoreMinimal.h"
#include "CalendarView.h"

#include "CalendarViewLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UCalendarViewLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize CalendarView To JSON String")
	static FString CalendarViewToJsonString(const UCalendarView* Serializable, const bool Pretty);		
};