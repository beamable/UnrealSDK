
#include "BeamableCore/Public/AutoGen/LeaderboardGetMatchRequestBody.h"

#include "Misc/DefaultValueHelper.h"



void ULeaderboardGetMatchRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("poolSize"), PoolSize, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("windows"), Windows, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("windowSize"), WindowSize, Serializer);
}

void ULeaderboardGetMatchRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("poolSize"), PoolSize, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("windows"), Windows, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("windowSize"), WindowSize, Serializer);		
}

void ULeaderboardGetMatchRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("poolSize"), Bag, PoolSize);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("windows"), Bag, Windows);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("windowSize"), Bag, WindowSize);
}



