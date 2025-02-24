
#include "BeamableCore/Public/AutoGen/GuestAuthRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UGuestAuthRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("scope"), &Scope, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamCid, FString>(TEXT("customerId"), &CustomerId, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamPid, FString>(TEXT("realmId"), &RealmId, Serializer);
	UBeamJsonUtils::SerializeOptional<UContextInfo*>(TEXT("context"), &Context, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("initProperties"), &InitProperties, Serializer);
}

void UGuestAuthRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("scope"), &Scope, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamCid, FString>(TEXT("customerId"), &CustomerId, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamPid, FString>(TEXT("realmId"), &RealmId, Serializer);
	UBeamJsonUtils::SerializeOptional<UContextInfo*>(TEXT("context"), &Context, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("initProperties"), &InitProperties, Serializer);		
}

void UGuestAuthRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("scope", Bag, Scope, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FBeamCid, FString>("customerId", Bag, CustomerId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FBeamPid, FString>("realmId", Bag, RealmId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UContextInfo*>("context", Bag, Context, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TMap<FString, FString>, FString>("initProperties", Bag, InitProperties, OuterOwner);
}



