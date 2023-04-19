
#include "BeamableCore/Public/AutoGen/NewGameRequestBody.h"





void UNewGameRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("gameName"), GameName);
}

void UNewGameRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("gameName"), GameName);		
}

void UNewGameRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	GameName = Bag->GetStringField(TEXT("gameName"));
}



