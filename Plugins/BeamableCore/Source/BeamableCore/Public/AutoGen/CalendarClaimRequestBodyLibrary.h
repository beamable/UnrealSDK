#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/CalendarClaimRequestBody.h"

#include "CalendarClaimRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UCalendarClaimRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Calendars|4 - Json", DisplayName="CalendarClaimRequestBody To JSON String")
	static FString CalendarClaimRequestBodyToJsonString(const UCalendarClaimRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Calendars|3 - Backend", DisplayName="Make CalendarClaimRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UCalendarClaimRequestBody* Make(FString Id, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Calendars|3 - Backend", DisplayName="Break CalendarClaimRequestBody", meta=(NativeBreakFunc))
	static void Break(const UCalendarClaimRequestBody* Serializable, FString& Id);
};