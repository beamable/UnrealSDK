
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/BeamballMsUpdateFromDiscordResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UBeamballMsUpdateFromDiscordResponseLibrary::BeamballMsUpdateFromDiscordResponseToJsonString(const UBeamballMsUpdateFromDiscordResponse* Serializable, const bool Pretty)
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

UBeamballMsUpdateFromDiscordResponse* UBeamballMsUpdateFromDiscordResponseLibrary::Make(bool bValue, UObject* Outer)
{
	auto Serializable = NewObject<UBeamballMsUpdateFromDiscordResponse>(Outer);
	Serializable->bValue = bValue;
	
	return Serializable;
}

void UBeamballMsUpdateFromDiscordResponseLibrary::Break(const UBeamballMsUpdateFromDiscordResponse* Serializable, bool& bValue)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bValue = Serializable->bValue;
	}
		
}

