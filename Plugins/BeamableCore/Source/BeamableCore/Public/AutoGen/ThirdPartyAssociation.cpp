
#include "AutoGen/ThirdPartyAssociation.h"
#include "Serialization/BeamJsonUtils.h"


void UThirdPartyAssociation ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("name"), Name);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("email"), &Email, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("userBusinessId"), &UserBusinessId, Serializer);
	Serializer->WriteValue(TEXT("userAppId"), UserAppId);
	UBeamJsonUtils::SerializeMap<FString>(TEXT("meta"), Meta, Serializer);
	Serializer->WriteValue(TEXT("appId"), AppId);
}

void UThirdPartyAssociation::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("name"), Name);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("email"), &Email, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("userBusinessId"), &UserBusinessId, Serializer);
	Serializer->WriteValue(TEXT("userAppId"), UserAppId);
	UBeamJsonUtils::SerializeMap<FString>(TEXT("meta"), Meta, Serializer);
	Serializer->WriteValue(TEXT("appId"), AppId);		
}

void UThirdPartyAssociation ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Name = Bag->GetStringField(TEXT("name"));
	UBeamJsonUtils::DeserializeOptional<FString>("email", Bag, Email, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("userBusinessId", Bag, UserBusinessId, OuterOwner);
	UserAppId = Bag->GetStringField(TEXT("userAppId"));
	UBeamJsonUtils::DeserializeMap<FString>(Bag->GetObjectField(TEXT("meta")), Meta, OuterOwner);
	AppId = Bag->GetStringField(TEXT("appId"));
}