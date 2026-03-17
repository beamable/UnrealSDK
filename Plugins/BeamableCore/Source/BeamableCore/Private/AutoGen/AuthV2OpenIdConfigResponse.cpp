
#include "BeamableCore/Public/AutoGen/AuthV2OpenIdConfigResponse.h"




void UAuthV2OpenIdConfigResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UAuthV2OpenIdConfigResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("issuer"), Issuer, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("jwks_uri"), JwksUri, Serializer);
}

void UAuthV2OpenIdConfigResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("issuer"), Issuer, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("jwks_uri"), JwksUri, Serializer);		
}

void UAuthV2OpenIdConfigResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("issuer"), Bag, Issuer);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("jwks_uri"), Bag, JwksUri);
}



