
#include "AutoGen/ExternalIdentityRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UExternalIdentityRequestBody ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("provider_address"), ProviderAddress);
	Serializer->WriteValue(TEXT("external_token"), ExternalToken);
	UBeamJsonUtils::SerializeOptional<UChallengeSolution*>(TEXT("challenge_solution"), &ChallengeSolution, Serializer);
}

void UExternalIdentityRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("provider_address"), ProviderAddress);
	Serializer->WriteValue(TEXT("external_token"), ExternalToken);
	UBeamJsonUtils::SerializeOptional<UChallengeSolution*>(TEXT("challenge_solution"), &ChallengeSolution, Serializer);		
}

void UExternalIdentityRequestBody ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	ProviderAddress = Bag->GetStringField(TEXT("provider_address"));
	ExternalToken = Bag->GetStringField(TEXT("external_token"));
	UBeamJsonUtils::DeserializeOptional<UChallengeSolution*>("challenge_solution", Bag, ChallengeSolution, OuterOwner);
}