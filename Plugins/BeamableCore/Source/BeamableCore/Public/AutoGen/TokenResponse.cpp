
#include "AutoGen/TokenResponse.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"

void UTokenResponse ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("access_token"), AccessToken);
	Serializer->WriteValue(TEXT("expires_in"), ExpiresIn);
	Serializer->WriteValue(TEXT("refresh_token"), RefreshToken);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("scopes"), &Scopes, Serializer);
	Serializer->WriteValue(TEXT("token_type"), TokenType);
}

void UTokenResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("access_token"), AccessToken);
	Serializer->WriteValue(TEXT("expires_in"), ExpiresIn);
	Serializer->WriteValue(TEXT("refresh_token"), RefreshToken);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("scopes"), &Scopes, Serializer);
	Serializer->WriteValue(TEXT("token_type"), TokenType);		
}

void UTokenResponse ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	AccessToken = Bag->GetStringField(TEXT("access_token"));
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("expires_in")), ExpiresIn);
	RefreshToken = Bag->GetStringField(TEXT("refresh_token"));
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("scopes", Bag, Scopes, OuterOwner);
	TokenType = Bag->GetStringField(TEXT("token_type"));
}