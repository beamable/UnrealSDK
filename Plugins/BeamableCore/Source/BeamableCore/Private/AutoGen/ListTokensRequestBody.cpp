
#include "BeamableCore/Public/AutoGen/ListTokensRequestBody.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UListTokensRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("pageSize"), PageSize);
	Serializer->WriteValue(TEXT("page"), Page);
	Serializer->WriteValue(TEXT("gamerTagOrAccountId"), GamerTagOrAccountId);
	UBeamJsonUtils::SerializeOptional<FBeamCid, int64>(TEXT("cid"), &Cid, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamPid, FString>(TEXT("pid"), &Pid, Serializer);
}

void UListTokensRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("pageSize"), PageSize);
	Serializer->WriteValue(TEXT("page"), Page);
	Serializer->WriteValue(TEXT("gamerTagOrAccountId"), GamerTagOrAccountId);
	UBeamJsonUtils::SerializeOptional<FBeamCid, int64>(TEXT("cid"), &Cid, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamPid, FString>(TEXT("pid"), &Pid, Serializer);		
}

void UListTokensRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("pageSize")), PageSize);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("page")), Page);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("gamerTagOrAccountId")), GamerTagOrAccountId);
	UBeamJsonUtils::DeserializeOptional<FBeamCid, int64>("cid", Bag, Cid, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FBeamPid, FString>("pid", Bag, Pid, OuterOwner);
}



