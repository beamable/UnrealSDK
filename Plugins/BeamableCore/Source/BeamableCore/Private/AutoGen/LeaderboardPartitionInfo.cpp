
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
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("isEmpty")), bIsEmpty);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("playerId")), PlayerId);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("leaderboardId")), LeaderboardId);
	UBeamJsonUtils::DeserializeOptional<int32>("partition", Bag, Partition, OuterOwner);
}



