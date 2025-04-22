
#include "BeamableCore/Public/AutoGen/TokenResponse.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"


void UTokenResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UTokenResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("expires_in"), ExpiresIn, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("token_type"), TokenType, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("access_token"), &AccessToken, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("refresh_token"), &RefreshToken, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("challenge_token"), &ChallengeToken, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("scopes"), &Scopes, Serializer);
}

void UTokenResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("expires_in"), ExpiresIn, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("token_type"), TokenType, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("access_token"), &AccessToken, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("refresh_token"), &RefreshToken, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("challenge_token"), &ChallengeToken, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("scopes"), &Scopes, Serializer);		
}

void UTokenResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("expires_in")), ExpiresIn);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("token_type")), TokenType);
	UBeamJsonUtils::DeserializeOptional<FString>("access_token", Bag, AccessToken, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("refresh_token", Bag, RefreshToken, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("challenge_token", Bag, ChallengeToken, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("scopes", Bag, Scopes, OuterOwner);
}



