
#include "BeamableCore/Public/AutoGen/EventPhaseTime.h"
#include "Serialization/BeamJsonUtils.h"




void UEventPhaseTime::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("name"), Name);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("startTime"), &StartTime, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("endTime"), &EndTime, Serializer);
}

void UEventPhaseTime::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("name"), Name);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("startTime"), &StartTime, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("endTime"), &EndTime, Serializer);		
}

void UEventPhaseTime::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Name = Bag->GetStringField(TEXT("name"));
	UBeamJsonUtils::DeserializeOptional<int64>("startTime", Bag, StartTime, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("endTime", Bag, EndTime, OuterOwner);
}



