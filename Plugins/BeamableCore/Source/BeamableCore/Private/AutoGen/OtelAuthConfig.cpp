
#include "BeamableCore/Public/AutoGen/OtelAuthConfig.h"
#include "Serialization/BeamJsonUtils.h"



void UOtelAuthConfig::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UOtelAuthConfig::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("endpoint"), Endpoint, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("username"), Username, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("password"), Password, Serializer);
	UBeamJsonUtils::SerializeOptional<FDateTime>(TEXT("expiresAt"), &ExpiresAt, Serializer);
}

void UOtelAuthConfig::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("endpoint"), Endpoint, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("username"), Username, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("password"), Password, Serializer);
	UBeamJsonUtils::SerializeOptional<FDateTime>(TEXT("expiresAt"), &ExpiresAt, Serializer);		
}

void UOtelAuthConfig::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("endpoint"), Bag, Endpoint);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("username"), Bag, Username);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("password"), Bag, Password);
	UBeamJsonUtils::DeserializeOptional<FDateTime>("expiresAt", Bag, ExpiresAt, OuterOwner);
}



