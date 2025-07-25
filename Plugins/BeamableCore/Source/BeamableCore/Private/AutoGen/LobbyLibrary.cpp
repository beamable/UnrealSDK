
#include "BeamableCore/Public/AutoGen/LobbyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString ULobbyLibrary::LobbyToJsonString(const ULobby* Serializable, const bool Pretty)
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

ULobby* ULobbyLibrary::Make(FOptionalString LobbyId, FOptionalMatchType MatchType, FOptionalDateTime Created, FOptionalString Name, FOptionalString Description, FOptionalBeamGamerTag Host, FOptionalString Passcode, FOptionalLobbyRestriction Restriction, FOptionalInt32 MaxPlayers, FOptionalArrayOfLobbyPlayer Players, FOptionalMapOfString Data, UObject* Outer)
{
	auto Serializable = NewObject<ULobby>(Outer);
	Serializable->LobbyId = LobbyId;
	Serializable->MatchType = MatchType;
	Serializable->Created = Created;
	Serializable->Name = Name;
	Serializable->Description = Description;
	Serializable->Host = Host;
	Serializable->Passcode = Passcode;
	Serializable->Restriction = Restriction;
	Serializable->MaxPlayers = MaxPlayers;
	Serializable->Players = Players;
	Serializable->Data = Data;
	
	return Serializable;
}

void ULobbyLibrary::Break(const ULobby* Serializable, FOptionalString& LobbyId, FOptionalMatchType& MatchType, FOptionalDateTime& Created, FOptionalString& Name, FOptionalString& Description, FOptionalBeamGamerTag& Host, FOptionalString& Passcode, FOptionalLobbyRestriction& Restriction, FOptionalInt32& MaxPlayers, FOptionalArrayOfLobbyPlayer& Players, FOptionalMapOfString& Data)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		LobbyId = Serializable->LobbyId;
		MatchType = Serializable->MatchType;
		Created = Serializable->Created;
		Name = Serializable->Name;
		Description = Serializable->Description;
		Host = Serializable->Host;
		Passcode = Serializable->Passcode;
		Restriction = Serializable->Restriction;
		MaxPlayers = Serializable->MaxPlayers;
		Players = Serializable->Players;
		Data = Serializable->Data;
	}
		
}

