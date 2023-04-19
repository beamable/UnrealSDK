
#include "BeamableCore/Public/AutoGen/LeaderboardDetailsRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void ULeaderboardDetailsRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("from"), &From, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("max"), &Max, Serializer);
}

void ULeaderboardDetailsRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("from"), &From, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("max"), &Max, Serializer);		
}

void ULeaderboardDetailsRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<int32>("from", Bag, From, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("max", Bag, Max, OuterOwner);
}



