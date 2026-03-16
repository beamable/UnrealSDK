
#include "BeamableCore/Public/AutoGen/AuthV2ListTokensResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UAuthV2ListTokensResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UAuthV2ListTokensResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<UAuthV2RefreshTokenResponse*>, UAuthV2RefreshTokenResponse*>(TEXT("tokens"), &Tokens, Serializer);
}

void UAuthV2ListTokensResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<UAuthV2RefreshTokenResponse*>, UAuthV2RefreshTokenResponse*>(TEXT("tokens"), &Tokens, Serializer);		
}

void UAuthV2ListTokensResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<TArray<UAuthV2RefreshTokenResponse*>, UAuthV2RefreshTokenResponse*>("tokens", Bag, Tokens, OuterOwner);
}



