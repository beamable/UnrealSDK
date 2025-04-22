
#include "BeamableCore/Public/AutoGen/Token.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"


void UToken::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UToken::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<int64>(TEXT("cid"), &Cid, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("token"), Token, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("type"), Type, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("created"), Created, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamGamerTag, int64>(TEXT("gamerTag"), &GamerTag, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamAccountId, int64>(TEXT("accountId"), &AccountId, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamPid, FString>(TEXT("pid"), &Pid, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("expiresMs"), &ExpiresMs, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("platform"), &Platform, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("device"), &Device, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("revoked"), &bRevoked, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("scopes"), &Scopes, Serializer);
}

void UToken::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<int64>(TEXT("cid"), &Cid, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("token"), Token, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("type"), Type, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("created"), Created, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamGamerTag, int64>(TEXT("gamerTag"), &GamerTag, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamAccountId, int64>(TEXT("accountId"), &AccountId, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamPid, FString>(TEXT("pid"), &Pid, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("expiresMs"), &ExpiresMs, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("platform"), &Platform, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("device"), &Device, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("revoked"), &bRevoked, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("scopes"), &Scopes, Serializer);		
}

void UToken::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeSemanticType<int64>(Bag->TryGetField(TEXT("cid")), Cid, OuterOwner);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("token")), Token);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("type")), Type);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("created")), Created);
	UBeamJsonUtils::DeserializeOptional<FBeamGamerTag, int64>("gamerTag", Bag, GamerTag, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FBeamAccountId, int64>("accountId", Bag, AccountId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FBeamPid, FString>("pid", Bag, Pid, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("expiresMs", Bag, ExpiresMs, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("platform", Bag, Platform, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("device", Bag, Device, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<bool>("revoked", Bag, bRevoked, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("scopes", Bag, Scopes, OuterOwner);
}



