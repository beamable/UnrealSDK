
#include "BeamableCore/Public/AutoGen/JoinRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UJoinRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("tournamentId"), TournamentId);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("contentId"), &ContentId, Serializer);
}

void UJoinRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("tournamentId"), TournamentId);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("contentId"), &ContentId, Serializer);		
}

void UJoinRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	TournamentId = Bag->GetStringField(TEXT("tournamentId"));
	UBeamJsonUtils::DeserializeOptional<FString>("contentId", Bag, ContentId, OuterOwner);
}



