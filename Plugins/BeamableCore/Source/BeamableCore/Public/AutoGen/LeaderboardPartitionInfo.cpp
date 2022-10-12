
#include "AutoGen/LeaderboardPartitionInfo.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"

void ULeaderboardPartitionInfo ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("playerId"), PlayerId);
	Serializer->WriteValue(TEXT("leaderboardId"), LeaderboardId);
	Serializer->WriteValue(TEXT("isEmpty"), bIsEmpty);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("partition"), &Partition, Serializer);
}

void ULeaderboardPartitionInfo::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("playerId"), PlayerId);
	Serializer->WriteValue(TEXT("leaderboardId"), LeaderboardId);
	Serializer->WriteValue(TEXT("isEmpty"), bIsEmpty);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("partition"), &Partition, Serializer);		
}

void ULeaderboardPartitionInfo ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("playerId")), PlayerId);
	LeaderboardId = Bag->GetStringField(TEXT("leaderboardId"));
	bIsEmpty = Bag->GetBoolField(TEXT("isEmpty"));
	UBeamJsonUtils::DeserializeOptional<int32>("partition", Bag, Partition, OuterOwner);
}