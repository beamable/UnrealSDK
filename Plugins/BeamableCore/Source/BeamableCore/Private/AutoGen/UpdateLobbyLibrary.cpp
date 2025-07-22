
#include "BeamableCore/Public/AutoGen/UpdateLobbyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UUpdateLobbyLibrary::UpdateLobbyToJsonString(const UUpdateLobby* Serializable, const bool Pretty)
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

UUpdateLobby* UUpdateLobbyLibrary::Make(FOptionalString Name, FOptionalString Description, FOptionalLobbyRestriction Restriction, FOptionalBeamContentId MatchType, FOptionalInt32 MaxPlayers, FOptionalString NewHost, FOptionalUpdateData Data, UObject* Outer)
{
	auto Serializable = NewObject<UUpdateLobby>(Outer);
	Serializable->Name = Name;
	Serializable->Description = Description;
	Serializable->Restriction = Restriction;
	Serializable->MatchType = MatchType;
	Serializable->MaxPlayers = MaxPlayers;
	Serializable->NewHost = NewHost;
	Serializable->Data = Data;
	
	return Serializable;
}

void UUpdateLobbyLibrary::Break(const UUpdateLobby* Serializable, FOptionalString& Name, FOptionalString& Description, FOptionalLobbyRestriction& Restriction, FOptionalBeamContentId& MatchType, FOptionalInt32& MaxPlayers, FOptionalString& NewHost, FOptionalUpdateData& Data)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Name = Serializable->Name;
		Description = Serializable->Description;
		Restriction = Serializable->Restriction;
		MatchType = Serializable->MatchType;
		MaxPlayers = Serializable->MaxPlayers;
		NewHost = Serializable->NewHost;
		Data = Serializable->Data;
	}
		
}

