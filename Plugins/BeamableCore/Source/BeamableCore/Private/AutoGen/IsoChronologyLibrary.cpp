
#include "BeamableCore/Public/AutoGen/IsoChronologyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UIsoChronologyLibrary::IsoChronologyToJsonString(const UIsoChronology* Serializable, const bool Pretty)
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

UIsoChronology* UIsoChronologyLibrary::Make(FString CalendarType, FString Id, UObject* Outer)
{
	auto Serializable = NewObject<UIsoChronology>(Outer);
	Serializable->CalendarType = CalendarType;
	Serializable->Id = Id;
	
	return Serializable;
}

void UIsoChronologyLibrary::Break(const UIsoChronology* Serializable, FString& CalendarType, FString& Id)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		CalendarType = Serializable->CalendarType;
		Id = Serializable->Id;
	}
		
}

