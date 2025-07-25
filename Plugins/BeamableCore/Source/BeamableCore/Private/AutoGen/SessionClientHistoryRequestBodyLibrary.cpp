
#include "BeamableCore/Public/AutoGen/SessionClientHistoryRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString USessionClientHistoryRequestBodyLibrary::SessionClientHistoryRequestBodyToJsonString(const USessionClientHistoryRequestBody* Serializable, const bool Pretty)
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

USessionClientHistoryRequestBody* USessionClientHistoryRequestBodyLibrary::Make(FOptionalInt32 Month, FOptionalInt32 Year, UObject* Outer)
{
	auto Serializable = NewObject<USessionClientHistoryRequestBody>(Outer);
	Serializable->Month = Month;
	Serializable->Year = Year;
	
	return Serializable;
}

void USessionClientHistoryRequestBodyLibrary::Break(const USessionClientHistoryRequestBody* Serializable, FOptionalInt32& Month, FOptionalInt32& Year)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Month = Serializable->Month;
		Year = Serializable->Year;
	}
		
}

