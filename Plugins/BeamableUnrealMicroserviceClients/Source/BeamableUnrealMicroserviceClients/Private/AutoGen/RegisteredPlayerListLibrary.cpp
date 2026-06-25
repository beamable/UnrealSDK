
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/RegisteredPlayerListLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString URegisteredPlayerListLibrary::RegisteredPlayerListToJsonString(const URegisteredPlayerList* Serializable, const bool Pretty)
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

URegisteredPlayerList* URegisteredPlayerListLibrary::Make(FString Message, TArray<URegisteredPlayer*> Players, UObject* Outer)
{
	auto Serializable = NewObject<URegisteredPlayerList>(Outer);
	Serializable->Message = Message;
	Serializable->Players = Players;
	
	return Serializable;
}

void URegisteredPlayerListLibrary::Break(const URegisteredPlayerList* Serializable, FString& Message, TArray<URegisteredPlayer*>& Players)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Message = Serializable->Message;
		Players = Serializable->Players;
	}
		
}

