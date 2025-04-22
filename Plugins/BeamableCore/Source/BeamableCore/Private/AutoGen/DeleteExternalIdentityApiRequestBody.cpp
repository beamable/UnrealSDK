
#include "BeamableCore/Public/AutoGen/DeleteExternalIdentityApiRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UDeleteExternalIdentityApiRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("provider_service"), ProviderService, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("user_id"), UserId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("provider_namespace"), &ProviderNamespace, Serializer);
}

void UDeleteExternalIdentityApiRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("provider_service"), ProviderService, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("user_id"), UserId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("provider_namespace"), &ProviderNamespace, Serializer);		
}

void UDeleteExternalIdentityApiRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("provider_service")), ProviderService);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("user_id")), UserId);
	UBeamJsonUtils::DeserializeOptional<FString>("provider_namespace", Bag, ProviderNamespace, OuterOwner);
}



