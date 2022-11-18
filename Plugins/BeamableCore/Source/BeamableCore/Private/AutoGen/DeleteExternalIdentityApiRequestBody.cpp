
#include "AutoGen/DeleteExternalIdentityApiRequestBody.h"





void UDeleteExternalIdentityApiRequestBody ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("provider_address"), ProviderAddress);
	Serializer->WriteValue(TEXT("user_id"), UserId);
}

void UDeleteExternalIdentityApiRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("provider_address"), ProviderAddress);
	Serializer->WriteValue(TEXT("user_id"), UserId);		
}

void UDeleteExternalIdentityApiRequestBody ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	ProviderAddress = Bag->GetStringField(TEXT("provider_address"));
	UserId = Bag->GetStringField(TEXT("user_id"));
}