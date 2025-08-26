
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/ProcessMatchResultRequestArgsLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UProcessMatchResultRequestArgsLibrary::ProcessMatchResultRequestArgsToJsonString(const UProcessMatchResultRequestArgs* Serializable, const bool Pretty)
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

UProcessMatchResultRequestArgs* UProcessMatchResultRequestArgsLibrary::Make(FString WinnerId, FString LobbyId, UObject* Outer)
{
	auto Serializable = NewObject<UProcessMatchResultRequestArgs>(Outer);
	Serializable->WinnerId = WinnerId;
	Serializable->LobbyId = LobbyId;
	
	return Serializable;
}

void UProcessMatchResultRequestArgsLibrary::Break(const UProcessMatchResultRequestArgs* Serializable, FString& WinnerId, FString& LobbyId)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		WinnerId = Serializable->WinnerId;
		LobbyId = Serializable->LobbyId;
	}
		
}

