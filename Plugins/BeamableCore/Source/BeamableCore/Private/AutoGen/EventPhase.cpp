
#include "BeamableCore/Public/AutoGen/EventPhase.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UEventPhase::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("name"), Name, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("duration_minutes"), DurationMinutes, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("durationMillis"), DurationMillis, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("durationSeconds"), DurationSeconds, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UEventRule*>, UEventRule*>(TEXT("rules"), &Rules, Serializer);
}

void UEventPhase::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("name"), Name, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("duration_minutes"), DurationMinutes, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("durationMillis"), DurationMillis, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("durationSeconds"), DurationSeconds, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UEventRule*>, UEventRule*>(TEXT("rules"), &Rules, Serializer);		
}

void UEventPhase::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("name"), Bag, Name);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("duration_minutes"), Bag, DurationMinutes);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("durationMillis"), Bag, DurationMillis);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("durationSeconds"), Bag, DurationSeconds);
	UBeamJsonUtils::DeserializeOptional<TArray<UEventRule*>, UEventRule*>("rules", Bag, Rules, OuterOwner);
}



