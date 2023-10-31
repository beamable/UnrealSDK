
#include "BeamableCore/Public/AutoGen/SessionClientHistoryRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void USessionClientHistoryRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("month"), &Month, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("year"), &Year, Serializer);
}

void USessionClientHistoryRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("month"), &Month, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("year"), &Year, Serializer);		
}

void USessionClientHistoryRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<int32>("month", Bag, Month, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("year", Bag, Year, OuterOwner);
}



