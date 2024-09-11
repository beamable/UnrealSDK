
#include "BeamableCore/Public/AutoGen/LeaderboardListRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void ULeaderboardListRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("includePartitions"), &bIncludePartitions, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("skip"), &Skip, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("limit"), &Limit, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("prefix"), &Prefix, Serializer);
}

void ULeaderboardListRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("includePartitions"), &bIncludePartitions, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("skip"), &Skip, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("limit"), &Limit, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("prefix"), &Prefix, Serializer);		
}

void ULeaderboardListRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<bool>("includePartitions", Bag, bIncludePartitions, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("skip", Bag, Skip, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("limit", Bag, Limit, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("prefix", Bag, Prefix, OuterOwner);
}



