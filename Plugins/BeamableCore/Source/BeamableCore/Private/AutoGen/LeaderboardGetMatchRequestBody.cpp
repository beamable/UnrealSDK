
#include "BeamableCore/Public/AutoGen/LeaderboardGetMatchRequestBody.h"

#include "Misc/DefaultValueHelper.h"



void ULeaderboardGetMatchRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("poolSize"), PoolSize);
	Serializer->WriteValue(TEXT("windows"), Windows);
	Serializer->WriteValue(TEXT("windowSize"), WindowSize);
}

void ULeaderboardGetMatchRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("poolSize"), PoolSize);
	Serializer->WriteValue(TEXT("windows"), Windows);
	Serializer->WriteValue(TEXT("windowSize"), WindowSize);		
}

void ULeaderboardGetMatchRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("poolSize")), PoolSize);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("windows")), Windows);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("windowSize")), WindowSize);
}



