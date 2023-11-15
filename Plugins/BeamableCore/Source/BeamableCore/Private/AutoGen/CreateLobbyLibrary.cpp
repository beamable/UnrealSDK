
#include "BeamableCore/Public/AutoGen/CreateLobbyLibrary.h"

#include "CoreMinimal.h"


FString UCreateLobbyLibrary::CreateLobbyToJsonString(const UCreateLobby* Serializable, const bool Pretty)
{
	FString Result = FString{};
	if(Pretty)
	{
		TUnrealPrettyJsonSerializer JsonSerializer = TJsonStringWriter<TPrettyJsonPrintPolicy<wchar_t>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();
	}
	else
	{
		TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();			
	}
	return Result;
}	

UCreateLobby* UCreateLobbyLibrary::Make(FOptionalBool bHasRestriction, FOptionalString Name, FOptionalString Description, FOptionalLobbyRestriction Restriction, FOptionalBeamContentId MatchType, FOptionalInt32 PasscodeLength, FOptionalInt32 MaxPlayers, FOptionalArrayOfTag PlayerTags, UObject* Outer)
{
	auto Serializable = NewObject<UCreateLobby>(Outer);
	Serializable->bHasRestriction = bHasRestriction;
	Serializable->Name = Name;
	Serializable->Description = Description;
	Serializable->Restriction = Restriction;
	Serializable->MatchType = MatchType;
	Serializable->PasscodeLength = PasscodeLength;
	Serializable->MaxPlayers = MaxPlayers;
	Serializable->PlayerTags = PlayerTags;
	
	return Serializable;
}

void UCreateLobbyLibrary::Break(const UCreateLobby* Serializable, FOptionalBool& bHasRestriction, FOptionalString& Name, FOptionalString& Description, FOptionalLobbyRestriction& Restriction, FOptionalBeamContentId& MatchType, FOptionalInt32& PasscodeLength, FOptionalInt32& MaxPlayers, FOptionalArrayOfTag& PlayerTags)
{
	bHasRestriction = Serializable->bHasRestriction;
	Name = Serializable->Name;
	Description = Serializable->Description;
	Restriction = Serializable->Restriction;
	MatchType = Serializable->MatchType;
	PasscodeLength = Serializable->PasscodeLength;
	MaxPlayers = Serializable->MaxPlayers;
	PlayerTags = Serializable->PlayerTags;
		
}

