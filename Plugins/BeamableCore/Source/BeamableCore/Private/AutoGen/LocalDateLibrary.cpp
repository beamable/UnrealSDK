
#include "BeamableCore/Public/AutoGen/LocalDateLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString ULocalDateLibrary::LocalDateToJsonString(const ULocalDate* Serializable, const bool Pretty)
{
	FString Result = FString{};
	if(Pretty)
	{
		TUnrealPrettyJsonSerializer JsonSerializer = TJsonStringWriter<TPrettyJsonPrintPolicy<TCHAR>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();
	}
	else
	{
		TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();			
	}
	return Result;
}	

ULocalDate* ULocalDateLibrary::Make(bool bLeapYear, int32 DayOfYear, UIsoChronology* Chronology, FString DayOfWeek, int32 MonthValue, int32 DayOfMonth, int32 Year, UEra* Era, FString Month, UObject* Outer)
{
	auto Serializable = NewObject<ULocalDate>(Outer);
	Serializable->bLeapYear = bLeapYear;
	Serializable->DayOfYear = DayOfYear;
	Serializable->Chronology = Chronology;
	Serializable->DayOfWeek = DayOfWeek;
	Serializable->MonthValue = MonthValue;
	Serializable->DayOfMonth = DayOfMonth;
	Serializable->Year = Year;
	Serializable->Era = Era;
	Serializable->Month = Month;
	
	return Serializable;
}

void ULocalDateLibrary::Break(const ULocalDate* Serializable, bool& bLeapYear, int32& DayOfYear, UIsoChronology*& Chronology, FString& DayOfWeek, int32& MonthValue, int32& DayOfMonth, int32& Year, UEra*& Era, FString& Month)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bLeapYear = Serializable->bLeapYear;
		DayOfYear = Serializable->DayOfYear;
		Chronology = Serializable->Chronology;
		DayOfWeek = Serializable->DayOfWeek;
		MonthValue = Serializable->MonthValue;
		DayOfMonth = Serializable->DayOfMonth;
		Year = Serializable->Year;
		Era = Serializable->Era;
		Month = Serializable->Month;
	}
		
}

