
#include "BeamableCore/Public/AutoGen/TicketReservationRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UTicketReservationRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("watchOnlineStatus"), &bWatchOnlineStatus, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("maxWaitDurationSecs"), &MaxWaitDurationSecs, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("team"), &Team, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FBeamGamerTag>, FBeamGamerTag, FString>(TEXT("players"), &Players, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FBeamContentId>, FBeamContentId, FString>(TEXT("matchTypes"), &MatchTypes, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FBeamTag>, FBeamTag>(TEXT("tags"), &Tags, Serializer);
}

void UTicketReservationRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("watchOnlineStatus"), &bWatchOnlineStatus, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("maxWaitDurationSecs"), &MaxWaitDurationSecs, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("team"), &Team, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FBeamGamerTag>, FBeamGamerTag, FString>(TEXT("players"), &Players, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FBeamContentId>, FBeamContentId, FString>(TEXT("matchTypes"), &MatchTypes, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FBeamTag>, FBeamTag>(TEXT("tags"), &Tags, Serializer);		
}

void UTicketReservationRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<bool>("watchOnlineStatus", Bag, bWatchOnlineStatus, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("maxWaitDurationSecs", Bag, MaxWaitDurationSecs, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("team", Bag, Team, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FBeamGamerTag>, FBeamGamerTag, FString>("players", Bag, Players, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FBeamContentId>, FBeamContentId, FString>("matchTypes", Bag, MatchTypes, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FBeamTag>, FBeamTag>("tags", Bag, Tags, OuterOwner);
}



