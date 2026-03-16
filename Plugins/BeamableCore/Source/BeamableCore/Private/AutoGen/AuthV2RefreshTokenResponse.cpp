
#include "BeamableCore/Public/AutoGen/AuthV2RefreshTokenResponse.h"
#include "Serialization/BeamJsonUtils.h"




void UAuthV2RefreshTokenResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("token"), &Token, Serializer);
	UBeamJsonUtils::SerializeOptional<FDateTime>(TEXT("created"), &Created, Serializer);
}

void UAuthV2RefreshTokenResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("token"), &Token, Serializer);
	UBeamJsonUtils::SerializeOptional<FDateTime>(TEXT("created"), &Created, Serializer);		
}

void UAuthV2RefreshTokenResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("token", Bag, Token, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FDateTime>("created", Bag, Created, OuterOwner);
}



