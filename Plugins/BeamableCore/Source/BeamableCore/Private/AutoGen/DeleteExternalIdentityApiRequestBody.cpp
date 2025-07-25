
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
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("provider_service"), Bag, ProviderService);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("user_id"), Bag, UserId);
	UBeamJsonUtils::DeserializeOptional<FString>("provider_namespace", Bag, ProviderNamespace, OuterOwner);
}



