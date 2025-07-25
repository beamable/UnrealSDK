
#include "BeamableCore/Public/AutoGen/CalendarQueryResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UCalendarQueryResponseLibrary::CalendarQueryResponseToJsonString(const UCalendarQueryResponse* Serializable, const bool Pretty)
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

UCalendarQueryResponse* UCalendarQueryResponseLibrary::Make(TArray<UCalendarView*> Calendars, UObject* Outer)
{
	auto Serializable = NewObject<UCalendarQueryResponse>(Outer);
	Serializable->Calendars = Calendars;
	
	return Serializable;
}

void UCalendarQueryResponseLibrary::Break(const UCalendarQueryResponse* Serializable, TArray<UCalendarView*>& Calendars)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Calendars = Serializable->Calendars;
	}
		
}

