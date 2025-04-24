
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
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("poolSize")), PoolSize);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("windows")), Windows);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("windowSize")), WindowSize);
}



