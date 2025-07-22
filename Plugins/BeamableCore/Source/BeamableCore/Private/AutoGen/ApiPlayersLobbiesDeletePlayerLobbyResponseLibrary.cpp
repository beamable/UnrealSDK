
#include "BeamableCore/Public/AutoGen/ApiPlayersLobbiesDeletePlayerLobbyResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UApiPlayersLobbiesDeletePlayerLobbyResponseLibrary::ApiPlayersLobbiesDeletePlayerLobbyResponseToJsonString(const UApiPlayersLobbiesDeletePlayerLobbyResponse* Serializable, const bool Pretty)
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

UApiPlayersLobbiesDeletePlayerLobbyResponse* UApiPlayersLobbiesDeletePlayerLobbyResponseLibrary::Make(UObject* Outer)
{
	auto Serializable = NewObject<UApiPlayersLobbiesDeletePlayerLobbyResponse>(Outer);
	
	return Serializable;
}



