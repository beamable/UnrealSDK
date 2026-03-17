
#include "BeamableCore/Public/AutoGen/AuthV2RevokeRefreshTokensRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UAuthV2RevokeRefreshTokensRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<FString>(TEXT("tokens"), Tokens, Serializer);
}

void UAuthV2RevokeRefreshTokensRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<FString>(TEXT("tokens"), Tokens, Serializer);		
}

void UAuthV2RevokeRefreshTokensRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<FString>(TEXT("tokens"), Bag, Tokens, OuterOwner);
}



