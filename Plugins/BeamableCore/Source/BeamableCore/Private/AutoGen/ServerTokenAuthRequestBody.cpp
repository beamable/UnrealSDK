
#include "BeamableCore/Public/AutoGen/ServerTokenAuthRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UServerTokenAuthRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("clientId"), &ClientId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("clientSecret"), &ClientSecret, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamCid, FString>(TEXT("customerId"), &CustomerId, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamPid, FString>(TEXT("realmId"), &RealmId, Serializer);
}

void UServerTokenAuthRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("clientId"), &ClientId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("clientSecret"), &ClientSecret, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamCid, FString>(TEXT("customerId"), &CustomerId, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamPid, FString>(TEXT("realmId"), &RealmId, Serializer);		
}

void UServerTokenAuthRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("clientId", Bag, ClientId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("clientSecret", Bag, ClientSecret, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FBeamCid, FString>("customerId", Bag, CustomerId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FBeamPid, FString>("realmId", Bag, RealmId, OuterOwner);
}



