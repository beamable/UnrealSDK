
#include "BeamableCore/Public/AutoGen/Ticket.h"
#include "Serialization/BeamJsonUtils.h"



void UTicket::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UTicket::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("watchOnlineStatus"), &bWatchOnlineStatus, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("ticketId"), &TicketId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("status"), &Status, Serializer);
	UBeamJsonUtils::SerializeOptional<FDateTime>(TEXT("created"), &Created, Serializer);
	UBeamJsonUtils::SerializeOptional<FDateTime>(TEXT("expires"), &Expires, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamContentId, FString>(TEXT("matchType"), &MatchType, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("matchId"), &MatchId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("team"), &Team, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("priority"), &Priority, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("partyId"), &PartyId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("lobbyId"), &LobbyId, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FBeamGamerTag>, FBeamGamerTag, FString>(TEXT("players"), &Players, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FBeamTag>, FBeamTag>(TEXT("tags"), &Tags, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("stringProperties"), &StringProperties, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, double>, double>(TEXT("numberProperties"), &NumberProperties, Serializer);
}

void UTicket::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("watchOnlineStatus"), &bWatchOnlineStatus, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("ticketId"), &TicketId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("status"), &Status, Serializer);
	UBeamJsonUtils::SerializeOptional<FDateTime>(TEXT("created"), &Created, Serializer);
	UBeamJsonUtils::SerializeOptional<FDateTime>(TEXT("expires"), &Expires, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamContentId, FString>(TEXT("matchType"), &MatchType, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("matchId"), &MatchId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("team"), &Team, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("priority"), &Priority, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("partyId"), &PartyId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("lobbyId"), &LobbyId, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FBeamGamerTag>, FBeamGamerTag, FString>(TEXT("players"), &Players, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FBeamTag>, FBeamTag>(TEXT("tags"), &Tags, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("stringProperties"), &StringProperties, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, double>, double>(TEXT("numberProperties"), &NumberProperties, Serializer);		
}

void UTicket::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<bool>("watchOnlineStatus", Bag, bWatchOnlineStatus, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("ticketId", Bag, TicketId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("status", Bag, Status, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FDateTime>("created", Bag, Created, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FDateTime>("expires", Bag, Expires, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FBeamContentId, FString>("matchType", Bag, MatchType, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("matchId", Bag, MatchId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("team", Bag, Team, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("priority", Bag, Priority, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("partyId", Bag, PartyId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("lobbyId", Bag, LobbyId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FBeamGamerTag>, FBeamGamerTag, FString>("players", Bag, Players, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FBeamTag>, FBeamTag>("tags", Bag, Tags, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TMap<FString, FString>, FString>("stringProperties", Bag, StringProperties, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TMap<FString, double>, double>("numberProperties", Bag, NumberProperties, OuterOwner);
}



