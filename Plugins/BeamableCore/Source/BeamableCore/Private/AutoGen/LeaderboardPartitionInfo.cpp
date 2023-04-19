
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
	Serializer->WriteValue(TEXT("isEmpty"), bIsEmpty);
	Serializer->WriteValue(TEXT("playerId"), PlayerId);
	Serializer->WriteValue(TEXT("leaderboardId"), LeaderboardId);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("partition"), &Partition, Serializer);
}

void ULeaderboardPartitionInfo::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("isEmpty"), bIsEmpty);
	Serializer->WriteValue(TEXT("playerId"), PlayerId);
	Serializer->WriteValue(TEXT("leaderboardId"), LeaderboardId);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("partition"), &Partition, Serializer);		
}

void ULeaderboardPartitionInfo::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	bIsEmpty = Bag->GetBoolField(TEXT("isEmpty"));
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("playerId")), PlayerId);
	LeaderboardId = Bag->GetStringField(TEXT("leaderboardId"));
	UBeamJsonUtils::DeserializeOptional<int32>("partition", Bag, Partition, OuterOwner);
}



