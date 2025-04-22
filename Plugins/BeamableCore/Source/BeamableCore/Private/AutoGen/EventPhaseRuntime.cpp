
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
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("name")), Name);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("startTime")), StartTime);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("endTime")), EndTime);
	UBeamJsonUtils::DeserializeArray<UEventRule*>(Bag->GetArrayField(TEXT("rules")), Rules, OuterOwner);
}



