
#include "BeamableCore/Public/AutoGen/AuthResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UAuthResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UAuthResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("accessToken"), &AccessToken, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("refreshToken"), &RefreshToken, Serializer);
}

void UAuthResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("accessToken"), &AccessToken, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("refreshToken"), &RefreshToken, Serializer);		
}

void UAuthResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("accessToken", Bag, AccessToken, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("refreshToken", Bag, RefreshToken, OuterOwner);
}



