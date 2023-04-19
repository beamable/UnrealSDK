
#include "BeamableCore/Public/AutoGen/AttachExternalIdentityApiRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UAttachExternalIdentityApiRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("provider_service"), ProviderService);
	Serializer->WriteValue(TEXT("external_token"), ExternalToken);
	UBeamJsonUtils::SerializeOptional<UChallengeSolution*>(TEXT("challenge_solution"), &ChallengeSolution, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("provider_namespace"), &ProviderNamespace, Serializer);
}

void UAttachExternalIdentityApiRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("provider_service"), ProviderService);
	Serializer->WriteValue(TEXT("external_token"), ExternalToken);
	UBeamJsonUtils::SerializeOptional<UChallengeSolution*>(TEXT("challenge_solution"), &ChallengeSolution, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("provider_namespace"), &ProviderNamespace, Serializer);		
}

void UAttachExternalIdentityApiRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	ProviderService = Bag->GetStringField(TEXT("provider_service"));
	ExternalToken = Bag->GetStringField(TEXT("external_token"));
	UBeamJsonUtils::DeserializeOptional<UChallengeSolution*>("challenge_solution", Bag, ChallengeSolution, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("provider_namespace", Bag, ProviderNamespace, OuterOwner);
}



