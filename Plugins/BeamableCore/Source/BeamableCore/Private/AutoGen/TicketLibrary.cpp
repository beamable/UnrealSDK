
#include "BeamableCore/Public/AutoGen/TicketLibrary.h"

#include "CoreMinimal.h"


FString UTicketLibrary::TicketToJsonString(const UTicket* Serializable, const bool Pretty)
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

UTicket* UTicketLibrary::Make(FOptionalBool bWatchOnlineStatus, FOptionalString TicketId, FOptionalString Status, FOptionalString Created, FOptionalString Expires, FOptionalBeamContentId MatchType, FOptionalString MatchId, FOptionalString Team, FOptionalInt32 Priority, FOptionalString PartyId, FOptionalArrayOfString Players, FOptionalMapOfString StringProperties, FOptionalMapOfDouble NumberProperties, UObject* Outer)
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
	Serializable->Players = Players;
	Serializable->StringProperties = StringProperties;
	Serializable->NumberProperties = NumberProperties;
	
	return Serializable;
}

void UTicketLibrary::Break(const UTicket* Serializable, FOptionalBool& bWatchOnlineStatus, FOptionalString& TicketId, FOptionalString& Status, FOptionalString& Created, FOptionalString& Expires, FOptionalBeamContentId& MatchType, FOptionalString& MatchId, FOptionalString& Team, FOptionalInt32& Priority, FOptionalString& PartyId, FOptionalArrayOfString& Players, FOptionalMapOfString& StringProperties, FOptionalMapOfDouble& NumberProperties)
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
	Players = Serializable->Players;
	StringProperties = Serializable->StringProperties;
	NumberProperties = Serializable->NumberProperties;
		
}

