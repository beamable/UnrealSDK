
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

UProcessMatchResultRequestArgs* UProcessMatchResultRequestArgsLibrary::Make(FString LobbyId, TArray<UBeamballTeamInfo*> TeamInfos, UObject* Outer)
{
	auto Serializable = NewObject<UProcessMatchResultRequestArgs>(Outer);
	Serializable->LobbyId = LobbyId;
	Serializable->TeamInfos = TeamInfos;
	
	return Serializable;
}

void UProcessMatchResultRequestArgsLibrary::Break(const UProcessMatchResultRequestArgs* Serializable, FString& LobbyId, TArray<UBeamballTeamInfo*>& TeamInfos)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		LobbyId = Serializable->LobbyId;
		TeamInfos = Serializable->TeamInfos;
	}
		
}

