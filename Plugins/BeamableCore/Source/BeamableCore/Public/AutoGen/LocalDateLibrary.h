#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/LocalDate.h"

#include "LocalDateLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API ULocalDateLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Session|Utils|Json", DisplayName="LocalDate To JSON String")
	static FString LocalDateToJsonString(const ULocalDate* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Session|Utils|Make/Break", DisplayName="Make LocalDate", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static ULocalDate* Make(bool bLeapYear, int32 DayOfYear, UIsoChronology* Chronology, FString DayOfWeek, int32 MonthValue, int32 DayOfMonth, int32 Year, UEra* Era, FString Month, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Session|Utils|Make/Break", DisplayName="Break LocalDate", meta=(NativeBreakFunc))
	static void Break(const ULocalDate* Serializable, bool& bLeapYear, int32& DayOfYear, UIsoChronology*& Chronology, FString& DayOfWeek, int32& MonthValue, int32& DayOfMonth, int32& Year, UEra*& Era, FString& Month);
};