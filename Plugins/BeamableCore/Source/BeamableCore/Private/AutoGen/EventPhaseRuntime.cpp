
#include "BeamableCore/Public/AutoGen/EventPhaseRuntime.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UEventPhaseRuntime::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("name"), Name, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("startTime"), StartTime, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("endTime"), EndTime, Serializer);
	UBeamJsonUtils::SerializeArray<UEventRule*>(TEXT("rules"), Rules, Serializer);
}

void UEventPhaseRuntime::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("name"), Name, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("startTime"), StartTime, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("endTime"), EndTime, Serializer);
	UBeamJsonUtils::SerializeArray<UEventRule*>(TEXT("rules"), Rules, Serializer);		
}

void UEventPhaseRuntime::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("name"), Bag, Name);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("startTime"), Bag, StartTime);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("endTime"), Bag, EndTime);
	UBeamJsonUtils::DeserializeArray<UEventRule*>(TEXT("rules"), Bag, Rules, OuterOwner);
}



