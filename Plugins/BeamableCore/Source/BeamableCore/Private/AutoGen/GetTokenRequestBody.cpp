
#include "BeamableCore/Public/AutoGen/GetTokenRequestBody.h"





void UGetTokenRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("token"), Token);
}

void UGetTokenRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("token"), Token);		
}

void UGetTokenRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Token = Bag->GetStringField(TEXT("token"));
}



