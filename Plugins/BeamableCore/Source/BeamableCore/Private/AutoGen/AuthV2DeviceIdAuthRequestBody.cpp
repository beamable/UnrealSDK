
#include "BeamableCore/Public/AutoGen/AuthV2DeviceIdAuthRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UAuthV2DeviceIdAuthRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("deviceId"), &DeviceId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("scope"), &Scope, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamCid, FString>(TEXT("customerId"), &CustomerId, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamPid, FString>(TEXT("realmId"), &RealmId, Serializer);
	UBeamJsonUtils::SerializeOptional<UAuthV2ContextInfo*>(TEXT("context"), &Context, Serializer);
}

void UAuthV2DeviceIdAuthRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("deviceId"), &DeviceId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("scope"), &Scope, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamCid, FString>(TEXT("customerId"), &CustomerId, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamPid, FString>(TEXT("realmId"), &RealmId, Serializer);
	UBeamJsonUtils::SerializeOptional<UAuthV2ContextInfo*>(TEXT("context"), &Context, Serializer);		
}

void UAuthV2DeviceIdAuthRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("deviceId", Bag, DeviceId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("scope", Bag, Scope, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FBeamCid, FString>("customerId", Bag, CustomerId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FBeamPid, FString>("realmId", Bag, RealmId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UAuthV2ContextInfo*>("context", Bag, Context, OuterOwner);
}



