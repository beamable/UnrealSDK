
#include "BeamableCore/Public/AutoGen/AuthV2LegacyAccessToken.h"
#include "Serialization/BeamJsonUtils.h"



void UAuthV2LegacyAccessToken::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UAuthV2LegacyAccessToken::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("revoked"), &bRevoked, Serializer);
	UBeamJsonUtils::SerializeOptional<FDateTime>(TEXT("ttl"), &Ttl, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("accountIdRaw"), &AccountIdRaw, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("cid"), &Cid, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("gamerTag"), &GamerTag, Serializer);
	UBeamJsonUtils::SerializeOptional<FDateTime>(TEXT("created"), &Created, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("type"), &Type, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("expiresMs"), &ExpiresMs, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("deviceId"), &DeviceId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("platform"), &Platform, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("token"), &Token, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("customerId"), &CustomerId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("gameId"), &GameId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("realmId"), &RealmId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("accountId"), &AccountId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("playerId"), &PlayerId, Serializer);
}

void UAuthV2LegacyAccessToken::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("revoked"), &bRevoked, Serializer);
	UBeamJsonUtils::SerializeOptional<FDateTime>(TEXT("ttl"), &Ttl, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("accountIdRaw"), &AccountIdRaw, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("cid"), &Cid, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("gamerTag"), &GamerTag, Serializer);
	UBeamJsonUtils::SerializeOptional<FDateTime>(TEXT("created"), &Created, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("type"), &Type, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("expiresMs"), &ExpiresMs, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("deviceId"), &DeviceId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("platform"), &Platform, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("token"), &Token, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("customerId"), &CustomerId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("gameId"), &GameId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("realmId"), &RealmId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("accountId"), &AccountId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("playerId"), &PlayerId, Serializer);		
}

void UAuthV2LegacyAccessToken::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<bool>("revoked", Bag, bRevoked, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FDateTime>("ttl", Bag, Ttl, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("accountIdRaw", Bag, AccountIdRaw, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("cid", Bag, Cid, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("gamerTag", Bag, GamerTag, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FDateTime>("created", Bag, Created, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("type", Bag, Type, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("expiresMs", Bag, ExpiresMs, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("deviceId", Bag, DeviceId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("platform", Bag, Platform, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("token", Bag, Token, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("customerId", Bag, CustomerId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("gameId", Bag, GameId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("realmId", Bag, RealmId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("accountId", Bag, AccountId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("playerId", Bag, PlayerId, OuterOwner);
}



