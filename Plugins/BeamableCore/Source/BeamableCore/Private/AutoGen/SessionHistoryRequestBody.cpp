
#include "BeamableCore/Public/AutoGen/SessionHistoryRequestBody.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void USessionHistoryRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("dbid"), Dbid, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("month"), &Month, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("year"), &Year, Serializer);
}

void USessionHistoryRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("dbid"), Dbid, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("month"), &Month, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("year"), &Year, Serializer);		
}

void USessionHistoryRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("dbid")), Dbid);
	UBeamJsonUtils::DeserializeOptional<int32>("month", Bag, Month, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("year", Bag, Year, OuterOwner);
}



