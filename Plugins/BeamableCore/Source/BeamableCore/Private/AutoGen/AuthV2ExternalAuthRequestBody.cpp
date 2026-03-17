
#include "BeamableCore/Public/AutoGen/AuthV2ExternalAuthRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UAuthV2ExternalAuthRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("hasProviderNamespace"), &bHasProviderNamespace, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("provider"), &Provider, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("providerNamespace"), &ProviderNamespace, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("token"), &Token, Serializer);
	UBeamJsonUtils::SerializeOptional<UAuthV2ChallengeSolution*>(TEXT("challengeSolution"), &ChallengeSolution, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("scope"), &Scope, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamCid, FString>(TEXT("customerId"), &CustomerId, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamPid, FString>(TEXT("realmId"), &RealmId, Serializer);
	UBeamJsonUtils::SerializeOptional<UAuthV2ContextInfo*>(TEXT("context"), &Context, Serializer);
}

void UAuthV2ExternalAuthRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("hasProviderNamespace"), &bHasProviderNamespace, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("provider"), &Provider, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("providerNamespace"), &ProviderNamespace, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("token"), &Token, Serializer);
	UBeamJsonUtils::SerializeOptional<UAuthV2ChallengeSolution*>(TEXT("challengeSolution"), &ChallengeSolution, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("scope"), &Scope, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamCid, FString>(TEXT("customerId"), &CustomerId, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamPid, FString>(TEXT("realmId"), &RealmId, Serializer);
	UBeamJsonUtils::SerializeOptional<UAuthV2ContextInfo*>(TEXT("context"), &Context, Serializer);		
}

void UAuthV2ExternalAuthRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<bool>("hasProviderNamespace", Bag, bHasProviderNamespace, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("provider", Bag, Provider, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("providerNamespace", Bag, ProviderNamespace, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("token", Bag, Token, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UAuthV2ChallengeSolution*>("challengeSolution", Bag, ChallengeSolution, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("scope", Bag, Scope, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FBeamCid, FString>("customerId", Bag, CustomerId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FBeamPid, FString>("realmId", Bag, RealmId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UAuthV2ContextInfo*>("context", Bag, Context, OuterOwner);
}



