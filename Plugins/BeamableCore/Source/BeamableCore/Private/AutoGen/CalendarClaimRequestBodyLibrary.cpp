
#include "BeamableCore/Public/AutoGen/CalendarClaimRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UCalendarClaimRequestBodyLibrary::CalendarClaimRequestBodyToJsonString(const UCalendarClaimRequestBody* Serializable, const bool Pretty)
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

UCalendarClaimRequestBody* UCalendarClaimRequestBodyLibrary::Make(FString Id, UObject* Outer)
{
	auto Serializable = NewObject<UCalendarClaimRequestBody>(Outer);
	Serializable->Id = Id;
	
	return Serializable;
}

void UCalendarClaimRequestBodyLibrary::Break(const UCalendarClaimRequestBody* Serializable, FString& Id)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Id = Serializable->Id;
	}
		
}

