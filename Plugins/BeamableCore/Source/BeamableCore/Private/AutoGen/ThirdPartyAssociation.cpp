
#include "BeamableCore/Public/AutoGen/ThirdPartyAssociation.h"
#include "Serialization/BeamJsonUtils.h"




void UThirdPartyAssociation::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("name"), Name);
	Serializer->WriteValue(TEXT("userAppId"), UserAppId);
	Serializer->WriteValue(TEXT("appId"), AppId);
	UBeamJsonUtils::SerializeMap<FString>(TEXT("meta"), Meta, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("email"), &Email, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("userBusinessId"), &UserBusinessId, Serializer);
}

void UThirdPartyAssociation::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("name"), Name);
	Serializer->WriteValue(TEXT("userAppId"), UserAppId);
	Serializer->WriteValue(TEXT("appId"), AppId);
	UBeamJsonUtils::SerializeMap<FString>(TEXT("meta"), Meta, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("email"), &Email, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("userBusinessId"), &UserBusinessId, Serializer);		
}

void UThirdPartyAssociation::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("name")), Name);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("userAppId")), UserAppId);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("appId")), AppId);
	UBeamJsonUtils::DeserializeMap<FString>(Bag->GetObjectField(TEXT("meta")), Meta, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("email", Bag, Email, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("userBusinessId", Bag, UserBusinessId, OuterOwner);
}



