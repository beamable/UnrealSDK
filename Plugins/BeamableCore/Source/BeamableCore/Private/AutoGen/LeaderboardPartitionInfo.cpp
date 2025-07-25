
#include "BeamableCore/Public/AutoGen/LeaderboardPartitionInfo.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"


void ULeaderboardPartitionInfo::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void ULeaderboardPartitionInfo::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("isEmpty"), bIsEmpty, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("playerId"), PlayerId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("leaderboardId"), LeaderboardId, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("partition"), &Partition, Serializer);
}

void ULeaderboardPartitionInfo::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("isEmpty"), bIsEmpty, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("playerId"), PlayerId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("leaderboardId"), LeaderboardId, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("partition"), &Partition, Serializer);		
}

void ULeaderboardPartitionInfo::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("isEmpty"), Bag, bIsEmpty);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("playerId"), Bag, PlayerId);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("leaderboardId"), Bag, LeaderboardId);
	UBeamJsonUtils::DeserializeOptional<int32>("partition", Bag, Partition, OuterOwner);
}



