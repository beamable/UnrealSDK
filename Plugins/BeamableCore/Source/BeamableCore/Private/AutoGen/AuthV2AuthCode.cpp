
#include "BeamableCore/Public/AutoGen/AuthV2AuthCode.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"


void UAuthV2AuthCode::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UAuthV2AuthCode::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("code"), Code, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("accountId"), AccountId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("redirectUri"), RedirectUri, Serializer);
	UBeamJsonUtils::SerializeOptional<FDateTime>(TEXT("createdAt"), &CreatedAt, Serializer);
	UBeamJsonUtils::SerializeOptional<FDateTime>(TEXT("ttl"), &Ttl, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("scopes"), &Scopes, Serializer);
}

void UAuthV2AuthCode::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("code"), Code, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("accountId"), AccountId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("redirectUri"), RedirectUri, Serializer);
	UBeamJsonUtils::SerializeOptional<FDateTime>(TEXT("createdAt"), &CreatedAt, Serializer);
	UBeamJsonUtils::SerializeOptional<FDateTime>(TEXT("ttl"), &Ttl, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("scopes"), &Scopes, Serializer);		
}

void UAuthV2AuthCode::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("code"), Bag, Code);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("accountId"), Bag, AccountId);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("redirectUri"), Bag, RedirectUri);
	UBeamJsonUtils::DeserializeOptional<FDateTime>("createdAt", Bag, CreatedAt, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FDateTime>("ttl", Bag, Ttl, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("scopes", Bag, Scopes, OuterOwner);
}



