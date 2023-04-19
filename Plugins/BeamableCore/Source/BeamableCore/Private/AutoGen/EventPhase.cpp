
#include "BeamableCore/Public/AutoGen/EventPhase.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UEventPhase::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("name"), Name);
	Serializer->WriteValue(TEXT("duration_minutes"), DurationMinutes);
	Serializer->WriteValue(TEXT("durationMillis"), DurationMillis);
	Serializer->WriteValue(TEXT("durationSeconds"), DurationSeconds);
	UBeamJsonUtils::SerializeOptional<TArray<UEventRule*>, UEventRule*>(TEXT("rules"), &Rules, Serializer);
}

void UEventPhase::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("name"), Name);
	Serializer->WriteValue(TEXT("duration_minutes"), DurationMinutes);
	Serializer->WriteValue(TEXT("durationMillis"), DurationMillis);
	Serializer->WriteValue(TEXT("durationSeconds"), DurationSeconds);
	UBeamJsonUtils::SerializeOptional<TArray<UEventRule*>, UEventRule*>(TEXT("rules"), &Rules, Serializer);		
}

void UEventPhase::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Name = Bag->GetStringField(TEXT("name"));
	DurationMinutes = Bag->GetIntegerField(TEXT("duration_minutes"));
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("durationMillis")), DurationMillis);
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("durationSeconds")), DurationSeconds);
	UBeamJsonUtils::DeserializeOptional<TArray<UEventRule*>, UEventRule*>("rules", Bag, Rules, OuterOwner);
}



