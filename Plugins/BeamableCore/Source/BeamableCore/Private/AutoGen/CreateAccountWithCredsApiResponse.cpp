
#include "BeamableCore/Public/AutoGen/CreateAccountWithCredsApiResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UCreateAccountWithCredsApiResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UCreateAccountWithCredsApiResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<UAccountPlayerView*>(TEXT("account"), &Account, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("challenge_token"), &ChallengeToken, Serializer);
	UBeamJsonUtils::SerializeOptional<UTokenResponse*>(TEXT("token"), &Token, Serializer);
}

void UCreateAccountWithCredsApiResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<UAccountPlayerView*>(TEXT("account"), &Account, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("challenge_token"), &ChallengeToken, Serializer);
	UBeamJsonUtils::SerializeOptional<UTokenResponse*>(TEXT("token"), &Token, Serializer);		
}

void UCreateAccountWithCredsApiResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<UAccountPlayerView*>("account", Bag, Account, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("challenge_token", Bag, ChallengeToken, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UTokenResponse*>("token", Bag, Token, OuterOwner);
}



