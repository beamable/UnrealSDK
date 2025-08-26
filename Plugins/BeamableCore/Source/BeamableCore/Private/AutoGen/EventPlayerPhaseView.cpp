
#include "BeamableCore/Public/AutoGen/EventPlayerPhaseView.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UEventPlayerPhaseView::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("name"), Name, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("durationSeconds"), DurationSeconds, Serializer);
	UBeamJsonUtils::SerializeArray<UEventRule*>(TEXT("rules"), Rules, Serializer);
}

void UEventPlayerPhaseView::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("name"), Name, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("durationSeconds"), DurationSeconds, Serializer);
	UBeamJsonUtils::SerializeArray<UEventRule*>(TEXT("rules"), Rules, Serializer);		
}

void UEventPlayerPhaseView::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("name"), Bag, Name);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("durationSeconds"), Bag, DurationSeconds);
	UBeamJsonUtils::DeserializeArray<UEventRule*>(TEXT("rules"), Bag, Rules, OuterOwner);
}



