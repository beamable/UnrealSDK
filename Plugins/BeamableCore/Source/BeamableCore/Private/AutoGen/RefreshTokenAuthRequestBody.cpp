
#include "BeamableCore/Public/AutoGen/RefreshTokenAuthRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void URefreshTokenAuthRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("refreshToken"), &RefreshToken, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamCid, FString>(TEXT("customerId"), &CustomerId, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamPid, FString>(TEXT("realmId"), &RealmId, Serializer);
	UBeamJsonUtils::SerializeOptional<UContextInfo*>(TEXT("context"), &Context, Serializer);
}

void URefreshTokenAuthRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("refreshToken"), &RefreshToken, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamCid, FString>(TEXT("customerId"), &CustomerId, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamPid, FString>(TEXT("realmId"), &RealmId, Serializer);
	UBeamJsonUtils::SerializeOptional<UContextInfo*>(TEXT("context"), &Context, Serializer);		
}

void URefreshTokenAuthRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("refreshToken", Bag, RefreshToken, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FBeamCid, FString>("customerId", Bag, CustomerId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FBeamPid, FString>("realmId", Bag, RealmId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UContextInfo*>("context", Bag, Context, OuterOwner);
}



