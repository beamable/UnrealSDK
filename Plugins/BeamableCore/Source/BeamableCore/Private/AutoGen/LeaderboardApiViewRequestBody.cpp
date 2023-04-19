
#include "BeamableCore/Public/AutoGen/LeaderboardApiViewRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void ULeaderboardApiViewRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("friends"), &bFriends, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("guild"), &bGuild, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("max"), &Max, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("focus"), &Focus, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("from"), &From, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("outlier"), &Outlier, Serializer);
}

void ULeaderboardApiViewRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("friends"), &bFriends, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("guild"), &bGuild, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("max"), &Max, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("focus"), &Focus, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("from"), &From, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("outlier"), &Outlier, Serializer);		
}

void ULeaderboardApiViewRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<bool>("friends", Bag, bFriends, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<bool>("guild", Bag, bGuild, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("max", Bag, Max, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("focus", Bag, Focus, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("from", Bag, From, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("outlier", Bag, Outlier, OuterOwner);
}



