
#include "BeamableCore/Public/AutoGen/CreateAccountWithCredsRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UCreateAccountWithCredsRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("username"), &Username, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("provider_namespace"), &ProviderNamespace, Serializer);
	UBeamJsonUtils::SerializeOptional<UChallengeSolution*>(TEXT("challenge_solution"), &ChallengeSolution, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("external_token"), &ExternalToken, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("provider_service"), &ProviderService, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("password"), &Password, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("initProperties"), &InitProperties, Serializer);
}

void UCreateAccountWithCredsRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("username"), &Username, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("provider_namespace"), &ProviderNamespace, Serializer);
	UBeamJsonUtils::SerializeOptional<UChallengeSolution*>(TEXT("challenge_solution"), &ChallengeSolution, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("external_token"), &ExternalToken, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("provider_service"), &ProviderService, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("password"), &Password, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("initProperties"), &InitProperties, Serializer);		
}

void UCreateAccountWithCredsRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("username", Bag, Username, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("provider_namespace", Bag, ProviderNamespace, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UChallengeSolution*>("challenge_solution", Bag, ChallengeSolution, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("external_token", Bag, ExternalToken, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("provider_service", Bag, ProviderService, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("password", Bag, Password, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TMap<FString, FString>, FString>("initProperties", Bag, InitProperties, OuterOwner);
}



