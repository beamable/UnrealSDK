
#include "AutoGen/Token.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"

void UToken ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("revoked"), &bRevoked, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("gamerTag"), &GamerTag, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("scopes"), &Scopes, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("accountId"), &AccountId, Serializer);
	Serializer->WriteValue(TEXT("cid"), Cid);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("pid"), &Pid, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("expiresMs"), &ExpiresMs, Serializer);
	Serializer->WriteValue(TEXT("token"), Token);
	Serializer->WriteValue(TEXT("type"), Type);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("platform"), &Platform, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("device"), &Device, Serializer);
	Serializer->WriteValue(TEXT("created"), Created);
}

void UToken::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("revoked"), &bRevoked, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("gamerTag"), &GamerTag, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("scopes"), &Scopes, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("accountId"), &AccountId, Serializer);
	Serializer->WriteValue(TEXT("cid"), Cid);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("pid"), &Pid, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("expiresMs"), &ExpiresMs, Serializer);
	Serializer->WriteValue(TEXT("token"), Token);
	Serializer->WriteValue(TEXT("type"), Type);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("platform"), &Platform, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("device"), &Device, Serializer);
	Serializer->WriteValue(TEXT("created"), Created);		
}

void UToken ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<bool>("revoked", Bag, bRevoked, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("gamerTag", Bag, GamerTag, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("scopes", Bag, Scopes, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("accountId", Bag, AccountId, OuterOwner);
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("cid")), Cid);
	UBeamJsonUtils::DeserializeOptional<FString>("pid", Bag, Pid, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("expiresMs", Bag, ExpiresMs, OuterOwner);
	Token = Bag->GetStringField(TEXT("token"));
	Type = Bag->GetStringField(TEXT("type"));
	UBeamJsonUtils::DeserializeOptional<FString>("platform", Bag, Platform, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("device", Bag, Device, OuterOwner);
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("created")), Created);
}