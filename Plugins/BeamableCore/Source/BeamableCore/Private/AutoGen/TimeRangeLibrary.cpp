
#include "BeamableCore/Public/AutoGen/TimeRangeLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UTimeRangeLibrary::TimeRangeToJsonString(const UTimeRange* Serializable, const bool Pretty)
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

UTimeRange* UTimeRangeLibrary::Make(FOptionalInt64 From, FOptionalInt64 To, UObject* Outer)
{
	auto Serializable = NewObject<UTimeRange>(Outer);
	Serializable->From = From;
	Serializable->To = To;
	
	return Serializable;
}

void UTimeRangeLibrary::Break(const UTimeRange* Serializable, FOptionalInt64& From, FOptionalInt64& To)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		From = Serializable->From;
		To = Serializable->To;
	}
		
}

