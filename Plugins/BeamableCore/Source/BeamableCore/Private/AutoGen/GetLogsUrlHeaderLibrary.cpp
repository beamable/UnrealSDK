
#include "BeamableCore/Public/AutoGen/GetLogsUrlHeaderLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGetLogsUrlHeaderLibrary::GetLogsUrlHeaderToJsonString(const UGetLogsUrlHeader* Serializable, const bool Pretty)
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

UGetLogsUrlHeader* UGetLogsUrlHeaderLibrary::Make(FString Key, FString Value, UObject* Outer)
{
	auto Serializable = NewObject<UGetLogsUrlHeader>(Outer);
	Serializable->Key = Key;
	Serializable->Value = Value;
	
	return Serializable;
}

void UGetLogsUrlHeaderLibrary::Break(const UGetLogsUrlHeader* Serializable, FString& Key, FString& Value)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Key = Serializable->Key;
		Value = Serializable->Value;
	}
		
}

