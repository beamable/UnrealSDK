
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/BeamballMsProcessMatchResultResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UBeamballMsProcessMatchResultResponseLibrary::BeamballMsProcessMatchResultResponseToJsonString(const UBeamballMsProcessMatchResultResponse* Serializable, const bool Pretty)
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

UBeamballMsProcessMatchResultResponse* UBeamballMsProcessMatchResultResponseLibrary::Make(TMap<FString, FString> Value, UObject* Outer)
{
	auto Serializable = NewObject<UBeamballMsProcessMatchResultResponse>(Outer);
	Serializable->Value = Value;
	
	return Serializable;
}

void UBeamballMsProcessMatchResultResponseLibrary::Break(const UBeamballMsProcessMatchResultResponse* Serializable, TMap<FString, FString>& Value)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Value = Serializable->Value;
	}
		
}

