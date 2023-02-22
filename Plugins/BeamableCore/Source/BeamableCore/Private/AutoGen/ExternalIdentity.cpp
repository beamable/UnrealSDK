
#include "AutoGen/ExternalIdentity.h"





void UExternalIdentity::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("providerService"), ProviderService);
	Serializer->WriteValue(TEXT("userId"), UserId);
	Serializer->WriteValue(TEXT("providerNamespace"), ProviderNamespace);
}

void UExternalIdentity::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("providerService"), ProviderService);
	Serializer->WriteValue(TEXT("userId"), UserId);
	Serializer->WriteValue(TEXT("providerNamespace"), ProviderNamespace);		
}

void UExternalIdentity::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	ProviderService = Bag->GetStringField(TEXT("providerService"));
	UserId = Bag->GetStringField(TEXT("userId"));
	ProviderNamespace = Bag->GetStringField(TEXT("providerNamespace"));
}



