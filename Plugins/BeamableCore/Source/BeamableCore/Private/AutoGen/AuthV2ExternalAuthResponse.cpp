
#include "BeamableCore/Public/AutoGen/AuthV2ExternalAuthResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UAuthV2ExternalAuthResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UAuthV2ExternalAuthResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("hasAccessToken"), &bHasAccessToken, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("hasChallengeToken"), &bHasChallengeToken, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("hasExpiresInMs"), &bHasExpiresInMs, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("hasRefreshToken"), &bHasRefreshToken, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("accessToken"), &AccessToken, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("refreshToken"), &RefreshToken, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("challengeToken"), &ChallengeToken, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("expiresInMs"), &ExpiresInMs, Serializer);
}

void UAuthV2ExternalAuthResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("hasAccessToken"), &bHasAccessToken, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("hasChallengeToken"), &bHasChallengeToken, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("hasExpiresInMs"), &bHasExpiresInMs, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("hasRefreshToken"), &bHasRefreshToken, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("accessToken"), &AccessToken, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("refreshToken"), &RefreshToken, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("challengeToken"), &ChallengeToken, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("expiresInMs"), &ExpiresInMs, Serializer);		
}

void UAuthV2ExternalAuthResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<bool>("hasAccessToken", Bag, bHasAccessToken, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<bool>("hasChallengeToken", Bag, bHasChallengeToken, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<bool>("hasExpiresInMs", Bag, bHasExpiresInMs, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<bool>("hasRefreshToken", Bag, bHasRefreshToken, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("accessToken", Bag, AccessToken, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("refreshToken", Bag, RefreshToken, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("challengeToken", Bag, ChallengeToken, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("expiresInMs", Bag, ExpiresInMs, OuterOwner);
}



