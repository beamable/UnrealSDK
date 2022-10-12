
#include "AutoGen/EventPhase.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"

void UEventPhase ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("name"), Name);
	Serializer->WriteValue(TEXT("duration_minutes"), DurationMinutes);
	Serializer->WriteValue(TEXT("durationMillis"), DurationMillis);
	UBeamJsonUtils::SerializeOptional<TArray<UEventRule*>, UEventRule*>(TEXT("rules"), &Rules, Serializer);
	Serializer->WriteValue(TEXT("durationSeconds"), DurationSeconds);
}

void UEventPhase::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("name"), Name);
	Serializer->WriteValue(TEXT("duration_minutes"), DurationMinutes);
	Serializer->WriteValue(TEXT("durationMillis"), DurationMillis);
	UBeamJsonUtils::SerializeOptional<TArray<UEventRule*>, UEventRule*>(TEXT("rules"), &Rules, Serializer);
	Serializer->WriteValue(TEXT("durationSeconds"), DurationSeconds);		
}

void UEventPhase ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Name = Bag->GetStringField(TEXT("name"));
	DurationMinutes = Bag->GetIntegerField(TEXT("duration_minutes"));
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("durationMillis")), DurationMillis);
	UBeamJsonUtils::DeserializeOptional<TArray<UEventRule*>, UEventRule*>("rules", Bag, Rules, OuterOwner);
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("durationSeconds")), DurationSeconds);
}