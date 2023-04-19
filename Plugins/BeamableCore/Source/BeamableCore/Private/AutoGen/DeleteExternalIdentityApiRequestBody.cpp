
#include "BeamableCore/Public/AutoGen/DeleteExternalIdentityApiRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UDeleteExternalIdentityApiRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("provider_service"), ProviderService);
	Serializer->WriteValue(TEXT("user_id"), UserId);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("provider_namespace"), &ProviderNamespace, Serializer);
}

void UDeleteExternalIdentityApiRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("provider_service"), ProviderService);
	Serializer->WriteValue(TEXT("user_id"), UserId);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("provider_namespace"), &ProviderNamespace, Serializer);		
}

void UDeleteExternalIdentityApiRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	ProviderService = Bag->GetStringField(TEXT("provider_service"));
	UserId = Bag->GetStringField(TEXT("user_id"));
	UBeamJsonUtils::DeserializeOptional<FString>("provider_namespace", Bag, ProviderNamespace, OuterOwner);
}



