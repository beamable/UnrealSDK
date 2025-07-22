
#include "BeamableCore/Public/AutoGen/OnlineStatusResponsesLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UOnlineStatusResponsesLibrary::OnlineStatusResponsesToJsonString(const UOnlineStatusResponses* Serializable, const bool Pretty)
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

UOnlineStatusResponses* UOnlineStatusResponsesLibrary::Make(TArray<UPlayerOnlineStatusResponse*> Players, UObject* Outer)
{
	auto Serializable = NewObject<UOnlineStatusResponses>(Outer);
	Serializable->Players = Players;
	
	return Serializable;
}

void UOnlineStatusResponsesLibrary::Break(const UOnlineStatusResponses* Serializable, TArray<UPlayerOnlineStatusResponse*>& Players)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Players = Serializable->Players;
	}
		
}

