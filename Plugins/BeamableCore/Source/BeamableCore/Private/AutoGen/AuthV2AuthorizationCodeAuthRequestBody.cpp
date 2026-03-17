
#include "BeamableCore/Public/AutoGen/AuthV2AuthorizationCodeAuthRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UAuthV2AuthorizationCodeAuthRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("clientId"), &ClientId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("code"), &Code, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("redirectUri"), &RedirectUri, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("scope"), &Scope, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamCid, FString>(TEXT("customerId"), &CustomerId, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamPid, FString>(TEXT("realmId"), &RealmId, Serializer);
	UBeamJsonUtils::SerializeOptional<UAuthV2ContextInfo*>(TEXT("context"), &Context, Serializer);
}

void UAuthV2AuthorizationCodeAuthRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("clientId"), &ClientId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("code"), &Code, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("redirectUri"), &RedirectUri, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("scope"), &Scope, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamCid, FString>(TEXT("customerId"), &CustomerId, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamPid, FString>(TEXT("realmId"), &RealmId, Serializer);
	UBeamJsonUtils::SerializeOptional<UAuthV2ContextInfo*>(TEXT("context"), &Context, Serializer);		
}

void UAuthV2AuthorizationCodeAuthRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("clientId", Bag, ClientId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("code", Bag, Code, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("redirectUri", Bag, RedirectUri, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("scope", Bag, Scope, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FBeamCid, FString>("customerId", Bag, CustomerId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FBeamPid, FString>("realmId", Bag, RealmId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UAuthV2ContextInfo*>("context", Bag, Context, OuterOwner);
}



