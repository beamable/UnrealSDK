
#include "BeamableCore/Public/AutoGen/EventsInDateRangeResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UEventsInDateRangeResponseLibrary::EventsInDateRangeResponseToJsonString(const UEventsInDateRangeResponse* Serializable, const bool Pretty)
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

UEventsInDateRangeResponse* UEventsInDateRangeResponseLibrary::Make(TArray<UEventDateRanges*> EventInDateRange, UObject* Outer)
{
	auto Serializable = NewObject<UEventsInDateRangeResponse>(Outer);
	Serializable->EventInDateRange = EventInDateRange;
	
	return Serializable;
}

void UEventsInDateRangeResponseLibrary::Break(const UEventsInDateRangeResponse* Serializable, TArray<UEventDateRanges*>& EventInDateRange)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		EventInDateRange = Serializable->EventInDateRange;
	}
		
}

