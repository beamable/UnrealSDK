
#include "BeamableCore/Public/AutoGen/RegisterReq.h"





void URegisterReq::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("provider"), Provider, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("token"), Token, Serializer);
}

void URegisterReq::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("provider"), Provider, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("token"), Token, Serializer);		
}

void URegisterReq::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("provider"), Bag, Provider);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("token"), Bag, Token);
}



