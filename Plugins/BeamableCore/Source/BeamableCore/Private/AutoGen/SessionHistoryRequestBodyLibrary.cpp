
#include "BeamableCore/Public/AutoGen/SessionHistoryRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString USessionHistoryRequestBodyLibrary::SessionHistoryRequestBodyToJsonString(const USessionHistoryRequestBody* Serializable, const bool Pretty)
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

USessionHistoryRequestBody* USessionHistoryRequestBodyLibrary::Make(int64 Dbid, FOptionalInt32 Month, FOptionalInt32 Year, UObject* Outer)
{
	auto Serializable = NewObject<USessionHistoryRequestBody>(Outer);
	Serializable->Dbid = Dbid;
	Serializable->Month = Month;
	Serializable->Year = Year;
	
	return Serializable;
}

void USessionHistoryRequestBodyLibrary::Break(const USessionHistoryRequestBody* Serializable, int64& Dbid, FOptionalInt32& Month, FOptionalInt32& Year)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Dbid = Serializable->Dbid;
		Month = Serializable->Month;
		Year = Serializable->Year;
	}
		
}

