
#include "BeamableCore/Public/AutoGen/NewGameRequestBody.h"





void UNewGameRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("gameName"), GameName, Serializer);
}

void UNewGameRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("gameName"), GameName, Serializer);		
}

void UNewGameRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("gameName")), GameName);
}



