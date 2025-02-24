
#include "BeamableCore/Public/AutoGen/PasswordAuthRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UPasswordAuthRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("email"), &Email, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("password"), &Password, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("scope"), &Scope, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamCid, FString>(TEXT("customerId"), &CustomerId, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamPid, FString>(TEXT("realmId"), &RealmId, Serializer);
	UBeamJsonUtils::SerializeOptional<UContextInfo*>(TEXT("context"), &Context, Serializer);
}

void UPasswordAuthRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("email"), &Email, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("password"), &Password, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("scope"), &Scope, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamCid, FString>(TEXT("customerId"), &CustomerId, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamPid, FString>(TEXT("realmId"), &RealmId, Serializer);
	UBeamJsonUtils::SerializeOptional<UContextInfo*>(TEXT("context"), &Context, Serializer);		
}

void UPasswordAuthRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("email", Bag, Email, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("password", Bag, Password, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("scope", Bag, Scope, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FBeamCid, FString>("customerId", Bag, CustomerId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FBeamPid, FString>("realmId", Bag, RealmId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UContextInfo*>("context", Bag, Context, OuterOwner);
}



