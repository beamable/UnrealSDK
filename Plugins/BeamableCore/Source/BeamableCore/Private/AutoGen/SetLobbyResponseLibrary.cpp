
#include "BeamableCore/Public/AutoGen/SetLobbyResponseLibrary.h"

#include "CoreMinimal.h"


FString USetLobbyResponseLibrary::SetLobbyResponseToJsonString(const USetLobbyResponse* Serializable, const bool Pretty)
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

USetLobbyResponse* USetLobbyResponseLibrary::Make(FOptionalString LobbyId, UObject* Outer)
{
	auto Serializable = NewObject<USetLobbyResponse>(Outer);
	Serializable->LobbyId = LobbyId;
	
	return Serializable;
}

void USetLobbyResponseLibrary::Break(const USetLobbyResponse* Serializable, FOptionalString& LobbyId)
{
	LobbyId = Serializable->LobbyId;
		
}

