
#include "BeamableCore/Public/AutoGen/EventsWithinDateRangeRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UEventsWithinDateRangeRequestBodyLibrary::EventsWithinDateRangeRequestBodyToJsonString(const UEventsWithinDateRangeRequestBody* Serializable, const bool Pretty)
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

UEventsWithinDateRangeRequestBody* UEventsWithinDateRangeRequestBodyLibrary::Make(FOptionalString From, FOptionalString To, FOptionalString Query, FOptionalInt32 Limit, UObject* Outer)
{
	auto Serializable = NewObject<UEventsWithinDateRangeRequestBody>(Outer);
	Serializable->From = From;
	Serializable->To = To;
	Serializable->Query = Query;
	Serializable->Limit = Limit;
	
	return Serializable;
}

void UEventsWithinDateRangeRequestBodyLibrary::Break(const UEventsWithinDateRangeRequestBody* Serializable, FOptionalString& From, FOptionalString& To, FOptionalString& Query, FOptionalInt32& Limit)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		From = Serializable->From;
		To = Serializable->To;
		Query = Serializable->Query;
		Limit = Serializable->Limit;
	}
		
}

