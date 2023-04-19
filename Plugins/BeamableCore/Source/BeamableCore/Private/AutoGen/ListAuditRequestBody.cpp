
#include "BeamableCore/Public/AutoGen/ListAuditRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UListAuditRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("providerid"), &Providerid, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("provider"), &Provider, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("state"), &State, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("txid"), &Txid, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("player"), &Player, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("start"), &Start, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("limit"), &Limit, Serializer);
}

void UListAuditRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("providerid"), &Providerid, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("provider"), &Provider, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("state"), &State, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("txid"), &Txid, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("player"), &Player, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("start"), &Start, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("limit"), &Limit, Serializer);		
}

void UListAuditRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("providerid", Bag, Providerid, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("provider", Bag, Provider, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("state", Bag, State, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("txid", Bag, Txid, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("player", Bag, Player, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("start", Bag, Start, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("limit", Bag, Limit, OuterOwner);
}



