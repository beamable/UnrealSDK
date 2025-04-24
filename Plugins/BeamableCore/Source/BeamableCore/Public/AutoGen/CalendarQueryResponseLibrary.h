#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/CalendarQueryResponse.h"

#include "CalendarQueryResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UCalendarQueryResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Calendars|Utils|Json", DisplayName="CalendarQueryResponse To JSON String")
	static FString CalendarQueryResponseToJsonString(const UCalendarQueryResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Calendars|Utils|Make/Break", DisplayName="Make CalendarQueryResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UCalendarQueryResponse* Make(TArray<UCalendarView*> Calendars, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Calendars|Utils|Make/Break", DisplayName="Break CalendarQueryResponse", meta=(NativeBreakFunc))
	static void Break(const UCalendarQueryResponse* Serializable, TArray<UCalendarView*>& Calendars);
};