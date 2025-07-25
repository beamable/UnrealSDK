
#include "BeamableCore/Public/AutoGen/TicketLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UTicketLibrary::TicketToJsonString(const UTicket* Serializable, const bool Pretty)
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

UTicket* UTicketLibrary::Make(FOptionalBool bWatchOnlineStatus, FOptionalString TicketId, FOptionalString Status, FOptionalDateTime Created, FOptionalDateTime Expires, FOptionalBeamContentId MatchType, FOptionalString MatchId, FOptionalString Team, FOptionalInt32 Priority, FOptionalString PartyId, FOptionalString LobbyId, FOptionalArrayOfBeamGamerTag Players, FOptionalArrayOfBeamTag Tags, FOptionalMapOfString StringProperties, FOptionalMapOfDouble NumberProperties, UObject* Outer)
{
	auto Serializable = NewObject<UTicket>(Outer);
	Serializable->bWatchOnlineStatus = bWatchOnlineStatus;
	Serializable->TicketId = TicketId;
	Serializable->Status = Status;
	Serializable->Created = Created;
	Serializable->Expires = Expires;
	Serializable->MatchType = MatchType;
	Serializable->MatchId = MatchId;
	Serializable->Team = Team;
	Serializable->Priority = Priority;
	Serializable->PartyId = PartyId;
	Serializable->LobbyId = LobbyId;
	Serializable->Players = Players;
	Serializable->Tags = Tags;
	Serializable->StringProperties = StringProperties;
	Serializable->NumberProperties = NumberProperties;
	
	return Serializable;
}

void UTicketLibrary::Break(const UTicket* Serializable, FOptionalBool& bWatchOnlineStatus, FOptionalString& TicketId, FOptionalString& Status, FOptionalDateTime& Created, FOptionalDateTime& Expires, FOptionalBeamContentId& MatchType, FOptionalString& MatchId, FOptionalString& Team, FOptionalInt32& Priority, FOptionalString& PartyId, FOptionalString& LobbyId, FOptionalArrayOfBeamGamerTag& Players, FOptionalArrayOfBeamTag& Tags, FOptionalMapOfString& StringProperties, FOptionalMapOfDouble& NumberProperties)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bWatchOnlineStatus = Serializable->bWatchOnlineStatus;
		TicketId = Serializable->TicketId;
		Status = Serializable->Status;
		Created = Serializable->Created;
		Expires = Serializable->Expires;
		MatchType = Serializable->MatchType;
		MatchId = Serializable->MatchId;
		Team = Serializable->Team;
		Priority = Serializable->Priority;
		PartyId = Serializable->PartyId;
		LobbyId = Serializable->LobbyId;
		Players = Serializable->Players;
		Tags = Serializable->Tags;
		StringProperties = Serializable->StringProperties;
		NumberProperties = Serializable->NumberProperties;
	}
		
}

