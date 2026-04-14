
#include "BeamableCore/Public/AutoGen/TimeRange.h"
#include "Serialization/BeamJsonUtils.h"




void UTimeRange::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("from"), &From, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("to"), &To, Serializer);
}

void UTimeRange::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("from"), &From, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("to"), &To, Serializer);		
}

void UTimeRange::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<int64>("from", Bag, From, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("to", Bag, To, OuterOwner);
}



