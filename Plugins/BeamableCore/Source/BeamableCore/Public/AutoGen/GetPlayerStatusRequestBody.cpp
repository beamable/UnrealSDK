
#include "AutoGen/GetPlayerStatusRequestBody.h"
#include "Serialization/BeamJsonUtils.h"


void UGetPlayerStatusRequestBody ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("tournamentId"), &TournamentId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("contentId"), &ContentId, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("hasUnclaimedRewards"), &bHasUnclaimedRewards, Serializer);
}

void UGetPlayerStatusRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("tournamentId"), &TournamentId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("contentId"), &ContentId, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("hasUnclaimedRewards"), &bHasUnclaimedRewards, Serializer);		
}

void UGetPlayerStatusRequestBody ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("tournamentId", Bag, TournamentId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("contentId", Bag, ContentId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<bool>("hasUnclaimedRewards", Bag, bHasUnclaimedRewards, OuterOwner);
}