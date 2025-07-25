
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/CreateMatchResultRequestArgsLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UCreateMatchResultRequestArgsLibrary::CreateMatchResultRequestArgsToJsonString(const UCreateMatchResultRequestArgs* Serializable, const bool Pretty)
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

UCreateMatchResultRequestArgs* UCreateMatchResultRequestArgsLibrary::Make(int64 UserId, FString LobbyId, UObject* Outer)
{
	auto Serializable = NewObject<UCreateMatchResultRequestArgs>(Outer);
	Serializable->UserId = UserId;
	Serializable->LobbyId = LobbyId;
	
	return Serializable;
}

void UCreateMatchResultRequestArgsLibrary::Break(const UCreateMatchResultRequestArgs* Serializable, int64& UserId, FString& LobbyId)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		UserId = Serializable->UserId;
		LobbyId = Serializable->LobbyId;
	}
		
}

