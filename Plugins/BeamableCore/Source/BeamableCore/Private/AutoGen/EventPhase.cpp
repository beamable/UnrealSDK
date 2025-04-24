
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
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("name")), Name);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("duration_minutes")), DurationMinutes);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("durationMillis")), DurationMillis);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("durationSeconds")), DurationSeconds);
	UBeamJsonUtils::DeserializeOptional<TArray<UEventRule*>, UEventRule*>("rules", Bag, Rules, OuterOwner);
}



