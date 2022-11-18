
#include "AutoGen/ExternalIdentity.h"





void UExternalIdentity ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("providerAddress"), ProviderAddress);
	Serializer->WriteValue(TEXT("userId"), UserId);
}

void UExternalIdentity::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("providerAddress"), ProviderAddress);
	Serializer->WriteValue(TEXT("userId"), UserId);		
}

void UExternalIdentity ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	ProviderAddress = Bag->GetStringField(TEXT("providerAddress"));
	UserId = Bag->GetStringField(TEXT("userId"));
}