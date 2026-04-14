
#include "BeamableCore/Public/AutoGen/RealmsBasicNewGameRequestBody.h"





void URealmsBasicNewGameRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("gameName"), GameName, Serializer);
}

void URealmsBasicNewGameRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("gameName"), GameName, Serializer);		
}

void URealmsBasicNewGameRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("gameName"), Bag, GameName);
}



