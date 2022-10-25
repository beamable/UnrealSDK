
#include "AutoGen/Token.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"

void UToken ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("cid"), Cid);
	Serializer->WriteValue(TEXT("token"), Token);
	Serializer->WriteValue(TEXT("type"), Type);
	Serializer->WriteValue(TEXT("created"), Created);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("gamerTag"), &GamerTag, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("accountId"), &AccountId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("pid"), &Pid, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("expiresMs"), &ExpiresMs, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("platform"), &Platform, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("device"), &Device, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("revoked"), &bRevoked, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("scopes"), &Scopes, Serializer);
}

void UToken::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("cid"), Cid);
	Serializer->WriteValue(TEXT("token"), Token);
	Serializer->WriteValue(TEXT("type"), Type);
	Serializer->WriteValue(TEXT("created"), Created);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("gamerTag"), &GamerTag, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("accountId"), &AccountId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("pid"), &Pid, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("expiresMs"), &ExpiresMs, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("platform"), &Platform, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("device"), &Device, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("revoked"), &bRevoked, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("scopes"), &Scopes, Serializer);		
}

void UToken ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("cid")), Cid);
	Token = Bag->GetStringField(TEXT("token"));
	Type = Bag->GetStringField(TEXT("type"));
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("created")), Created);
	UBeamJsonUtils::DeserializeOptional<int64>("gamerTag", Bag, GamerTag, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("accountId", Bag, AccountId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("pid", Bag, Pid, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("expiresMs", Bag, ExpiresMs, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("platform", Bag, Platform, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("device", Bag, Device, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<bool>("revoked", Bag, bRevoked, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("scopes", Bag, Scopes, OuterOwner);
}