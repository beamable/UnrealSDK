
#include "BeamableCore/Public/AutoGen/AttachExternalIdentityApiRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UAttachExternalIdentityApiRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("provider_service"), ProviderService, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("external_token"), ExternalToken, Serializer);
	UBeamJsonUtils::SerializeOptional<UChallengeSolution*>(TEXT("challenge_solution"), &ChallengeSolution, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("provider_namespace"), &ProviderNamespace, Serializer);
}

void UAttachExternalIdentityApiRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("provider_service"), ProviderService, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("external_token"), ExternalToken, Serializer);
	UBeamJsonUtils::SerializeOptional<UChallengeSolution*>(TEXT("challenge_solution"), &ChallengeSolution, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("provider_namespace"), &ProviderNamespace, Serializer);		
}

void UAttachExternalIdentityApiRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("provider_service")), ProviderService);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("external_token")), ExternalToken);
	UBeamJsonUtils::DeserializeOptional<UChallengeSolution*>("challenge_solution", Bag, ChallengeSolution, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("provider_namespace", Bag, ProviderNamespace, OuterOwner);
}



