
#include "BeamableCore/Public/AutoGen/AccountAvailableRequestBody.h"





void UAccountAvailableRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("email"), Email);
}

void UAccountAvailableRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("email"), Email);		
}

void UAccountAvailableRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Email = Bag->GetStringField(TEXT("email"));
}



