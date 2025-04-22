
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
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("name")), Name);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("durationSeconds")), DurationSeconds);
	UBeamJsonUtils::DeserializeArray<UEventRule*>(Bag->GetArrayField(TEXT("rules")), Rules, OuterOwner);
}



