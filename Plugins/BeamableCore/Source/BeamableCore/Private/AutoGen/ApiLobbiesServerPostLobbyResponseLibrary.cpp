
#include "BeamableCore/Public/AutoGen/ApiLobbiesServerPostLobbyResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UApiLobbiesServerPostLobbyResponseLibrary::ApiLobbiesServerPostLobbyResponseToJsonString(const UApiLobbiesServerPostLobbyResponse* Serializable, const bool Pretty)
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

UApiLobbiesServerPostLobbyResponse* UApiLobbiesServerPostLobbyResponseLibrary::Make(UObject* Outer)
{
	auto Serializable = NewObject<UApiLobbiesServerPostLobbyResponse>(Outer);
	
	return Serializable;
}



