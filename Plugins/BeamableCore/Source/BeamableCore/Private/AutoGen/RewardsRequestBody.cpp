
#include "BeamableCore/Public/AutoGen/RewardsRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void URewardsRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("tournamentId"), &TournamentId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("contentId"), &ContentId, Serializer);
}

void URewardsRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("tournamentId"), &TournamentId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("contentId"), &ContentId, Serializer);		
}

void URewardsRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("tournamentId", Bag, TournamentId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("contentId", Bag, ContentId, OuterOwner);
}



