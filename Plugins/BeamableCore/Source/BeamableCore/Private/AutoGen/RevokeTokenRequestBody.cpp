
#include "BeamableCore/Public/AutoGen/RevokeTokenRequestBody.h"





void URevokeTokenRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("token"), Token);
}

void URevokeTokenRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("token"), Token);		
}

void URevokeTokenRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Token = Bag->GetStringField(TEXT("token"));
}



