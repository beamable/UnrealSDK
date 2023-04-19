
#include "BeamableCore/Public/AutoGen/EventPhaseRuntime.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UEventPhaseRuntime::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("name"), Name);
	Serializer->WriteValue(TEXT("startTime"), StartTime);
	Serializer->WriteValue(TEXT("endTime"), EndTime);
	UBeamJsonUtils::SerializeArray<UEventRule*>(TEXT("rules"), Rules, Serializer);
}

void UEventPhaseRuntime::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("name"), Name);
	Serializer->WriteValue(TEXT("startTime"), StartTime);
	Serializer->WriteValue(TEXT("endTime"), EndTime);
	UBeamJsonUtils::SerializeArray<UEventRule*>(TEXT("rules"), Rules, Serializer);		
}

void UEventPhaseRuntime::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Name = Bag->GetStringField(TEXT("name"));
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("startTime")), StartTime);
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("endTime")), EndTime);
	UBeamJsonUtils::DeserializeArray<UEventRule*>(Bag->GetArrayField(TEXT("rules")), Rules, OuterOwner);
}



