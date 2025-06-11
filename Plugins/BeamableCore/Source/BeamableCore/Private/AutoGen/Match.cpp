
#include "BeamableCore/Public/AutoGen/Match.h"
#include "Serialization/BeamJsonUtils.h"



void UMatch::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UMatch::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("matchId"), &MatchId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("status"), &Status, Serializer);
	UBeamJsonUtils::SerializeOptional<FDateTime>(TEXT("created"), &Created, Serializer);
	UBeamJsonUtils::SerializeOptional<UMatchType*>(TEXT("matchType"), &MatchType, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UTeam*>, UTeam*>(TEXT("teams"), &Teams, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UTicket*>, UTicket*>(TEXT("tickets"), &Tickets, Serializer);
}

void UMatch::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("matchId"), &MatchId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("status"), &Status, Serializer);
	UBeamJsonUtils::SerializeOptional<FDateTime>(TEXT("created"), &Created, Serializer);
	UBeamJsonUtils::SerializeOptional<UMatchType*>(TEXT("matchType"), &MatchType, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UTeam*>, UTeam*>(TEXT("teams"), &Teams, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UTicket*>, UTicket*>(TEXT("tickets"), &Tickets, Serializer);		
}

void UMatch::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("matchId", Bag, MatchId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("status", Bag, Status, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FDateTime>("created", Bag, Created, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UMatchType*>("matchType", Bag, MatchType, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UTeam*>, UTeam*>("teams", Bag, Teams, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UTicket*>, UTicket*>("tickets", Bag, Tickets, OuterOwner);
}



