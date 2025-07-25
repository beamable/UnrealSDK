
#include "BeamableCore/Public/AutoGen/CreateLobbyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UCreateLobbyLibrary::CreateLobbyToJsonString(const UCreateLobby* Serializable, const bool Pretty)
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

UCreateLobby* UCreateLobbyLibrary::Make(FOptionalString Name, FOptionalString Description, FOptionalLobbyRestriction Restriction, FOptionalBeamContentId MatchType, FOptionalInt32 PasscodeLength, FOptionalInt32 MaxPlayers, FOptionalArrayOfBeamTag PlayerTags, FOptionalMapOfString Data, UObject* Outer)
{
	auto Serializable = NewObject<UCreateLobby>(Outer);
	Serializable->Name = Name;
	Serializable->Description = Description;
	Serializable->Restriction = Restriction;
	Serializable->MatchType = MatchType;
	Serializable->PasscodeLength = PasscodeLength;
	Serializable->MaxPlayers = MaxPlayers;
	Serializable->PlayerTags = PlayerTags;
	Serializable->Data = Data;
	
	return Serializable;
}

void UCreateLobbyLibrary::Break(const UCreateLobby* Serializable, FOptionalString& Name, FOptionalString& Description, FOptionalLobbyRestriction& Restriction, FOptionalBeamContentId& MatchType, FOptionalInt32& PasscodeLength, FOptionalInt32& MaxPlayers, FOptionalArrayOfBeamTag& PlayerTags, FOptionalMapOfString& Data)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Name = Serializable->Name;
		Description = Serializable->Description;
		Restriction = Serializable->Restriction;
		MatchType = Serializable->MatchType;
		PasscodeLength = Serializable->PasscodeLength;
		MaxPlayers = Serializable->MaxPlayers;
		PlayerTags = Serializable->PlayerTags;
		Data = Serializable->Data;
	}
		
}

