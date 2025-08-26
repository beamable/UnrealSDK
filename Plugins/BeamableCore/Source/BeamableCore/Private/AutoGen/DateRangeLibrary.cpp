
#include "BeamableCore/Public/AutoGen/DateRangeLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UDateRangeLibrary::DateRangeToJsonString(const UDateRange* Serializable, const bool Pretty)
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

UDateRange* UDateRangeLibrary::Make(FString From, FString To, UObject* Outer)
{
	auto Serializable = NewObject<UDateRange>(Outer);
	Serializable->From = From;
	Serializable->To = To;
	
	return Serializable;
}

void UDateRangeLibrary::Break(const UDateRange* Serializable, FString& From, FString& To)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		From = Serializable->From;
		To = Serializable->To;
	}
		
}

