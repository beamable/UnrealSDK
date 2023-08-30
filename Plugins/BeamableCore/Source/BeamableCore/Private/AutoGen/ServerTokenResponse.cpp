
#include "BeamableCore/Public/AutoGen/ServerTokenResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UServerTokenResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UServerTokenResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("accessToken"), &AccessToken, Serializer);
}

void UServerTokenResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("accessToken"), &AccessToken, Serializer);		
}

void UServerTokenResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("accessToken", Bag, AccessToken, OuterOwner);
}



