
#include "BeamableCore/Public/AutoGen/AdminGetPlayerStatusRequestBody.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UAdminGetPlayerStatusRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("playerId"), PlayerId, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("hasUnclaimedRewards"), &bHasUnclaimedRewards, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("tournamentId"), &TournamentId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("contentId"), &ContentId, Serializer);
}

void UAdminGetPlayerStatusRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("playerId"), PlayerId, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("hasUnclaimedRewards"), &bHasUnclaimedRewards, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("tournamentId"), &TournamentId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("contentId"), &ContentId, Serializer);		
}

void UAdminGetPlayerStatusRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("playerId")), PlayerId);
	UBeamJsonUtils::DeserializeOptional<bool>("hasUnclaimedRewards", Bag, bHasUnclaimedRewards, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("tournamentId", Bag, TournamentId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("contentId", Bag, ContentId, OuterOwner);
}



