
#include "BeamableCore/Public/AutoGen/EventPlayerPhaseView.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UEventPlayerPhaseView::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("name"), Name);
	Serializer->WriteValue(TEXT("durationSeconds"), DurationSeconds);
	UBeamJsonUtils::SerializeArray<UEventRule*>(TEXT("rules"), Rules, Serializer);
}

void UEventPlayerPhaseView::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("name"), Name);
	Serializer->WriteValue(TEXT("durationSeconds"), DurationSeconds);
	UBeamJsonUtils::SerializeArray<UEventRule*>(TEXT("rules"), Rules, Serializer);		
}

void UEventPlayerPhaseView::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Name = Bag->GetStringField(TEXT("name"));
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("durationSeconds")), DurationSeconds);
	UBeamJsonUtils::DeserializeArray<UEventRule*>(Bag->GetArrayField(TEXT("rules")), Rules, OuterOwner);
}



