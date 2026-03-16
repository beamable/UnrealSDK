
#include "BeamableCore/Public/AutoGen/AuthV2AuthResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UAuthV2AuthResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UAuthV2AuthResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("accessToken"), &AccessToken, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("refreshToken"), &RefreshToken, Serializer);
}

void UAuthV2AuthResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("accessToken"), &AccessToken, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("refreshToken"), &RefreshToken, Serializer);		
}

void UAuthV2AuthResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("accessToken", Bag, AccessToken, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("refreshToken", Bag, RefreshToken, OuterOwner);
}



