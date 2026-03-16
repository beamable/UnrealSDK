
#include "BeamableCore/Public/AutoGen/AuthV2AuthCodeRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UAuthV2AuthCodeRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FBeamAccountId, FString>(TEXT("accountId"), &AccountId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("redirectUri"), &RedirectUri, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamCid, FString>(TEXT("customerId"), &CustomerId, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamPid, FString>(TEXT("realmId"), &RealmId, Serializer);
	UBeamJsonUtils::SerializeOptional<UAuthV2ContextInfo*>(TEXT("context"), &Context, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("scopes"), &Scopes, Serializer);
}

void UAuthV2AuthCodeRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FBeamAccountId, FString>(TEXT("accountId"), &AccountId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("redirectUri"), &RedirectUri, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamCid, FString>(TEXT("customerId"), &CustomerId, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamPid, FString>(TEXT("realmId"), &RealmId, Serializer);
	UBeamJsonUtils::SerializeOptional<UAuthV2ContextInfo*>(TEXT("context"), &Context, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("scopes"), &Scopes, Serializer);		
}

void UAuthV2AuthCodeRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FBeamAccountId, FString>("accountId", Bag, AccountId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("redirectUri", Bag, RedirectUri, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FBeamCid, FString>("customerId", Bag, CustomerId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FBeamPid, FString>("realmId", Bag, RealmId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UAuthV2ContextInfo*>("context", Bag, Context, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("scopes", Bag, Scopes, OuterOwner);
}



