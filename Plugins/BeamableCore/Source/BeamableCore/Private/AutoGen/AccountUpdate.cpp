
#include "BeamableCore/Public/AutoGen/AccountUpdate.h"
#include "Serialization/BeamJsonUtils.h"




void UAccountUpdate::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("hasThirdPartyToken"), bHasThirdPartyToken, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("thirdParty"), &ThirdParty, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("country"), &Country, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("language"), &Language, Serializer);
	UBeamJsonUtils::SerializeOptional<UGamerTagAssociation*>(TEXT("gamerTagAssoc"), &GamerTagAssoc, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("token"), &Token, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("deviceId"), &DeviceId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("userName"), &UserName, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FBeamExternalIdentity>, FBeamExternalIdentity>(TEXT("external"), &External, Serializer);
}

void UAccountUpdate::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("hasThirdPartyToken"), bHasThirdPartyToken, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("thirdParty"), &ThirdParty, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("country"), &Country, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("language"), &Language, Serializer);
	UBeamJsonUtils::SerializeOptional<UGamerTagAssociation*>(TEXT("gamerTagAssoc"), &GamerTagAssoc, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("token"), &Token, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("deviceId"), &DeviceId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("userName"), &UserName, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FBeamExternalIdentity>, FBeamExternalIdentity>(TEXT("external"), &External, Serializer);		
}

void UAccountUpdate::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("hasThirdPartyToken")), bHasThirdPartyToken);
	UBeamJsonUtils::DeserializeOptional<FString>("thirdParty", Bag, ThirdParty, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("country", Bag, Country, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("language", Bag, Language, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UGamerTagAssociation*>("gamerTagAssoc", Bag, GamerTagAssoc, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("token", Bag, Token, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("deviceId", Bag, DeviceId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("userName", Bag, UserName, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FBeamExternalIdentity>, FBeamExternalIdentity>("external", Bag, External, OuterOwner);
}



