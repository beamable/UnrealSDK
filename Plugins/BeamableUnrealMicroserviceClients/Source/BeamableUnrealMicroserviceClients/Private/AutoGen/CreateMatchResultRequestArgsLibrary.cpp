
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/CreateMatchResultRequestArgsLibrary.h"

#include "CoreMinimal.h"


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

UCreateMatchResultRequestArgs* UCreateMatchResultRequestArgsLibrary::Make(FString LobbyId, UObject* Outer)
{
	auto Serializable = NewObject<UCreateMatchResultRequestArgs>(Outer);
	Serializable->LobbyId = LobbyId;
	
	return Serializable;
}

void UCreateMatchResultRequestArgsLibrary::Break(const UCreateMatchResultRequestArgs* Serializable, FString& LobbyId)
{
	LobbyId = Serializable->LobbyId;
		
}

