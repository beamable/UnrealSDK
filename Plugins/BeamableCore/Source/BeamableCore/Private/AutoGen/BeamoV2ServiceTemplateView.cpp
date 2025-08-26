
#include "BeamableCore/Public/AutoGen/BeamoV2ServiceTemplateView.h"
#include "Serialization/BeamJsonUtils.h"




void UBeamoV2ServiceTemplateView::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("id"), &Id, Serializer);
}

void UBeamoV2ServiceTemplateView::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("id"), &Id, Serializer);		
}

void UBeamoV2ServiceTemplateView::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("id", Bag, Id, OuterOwner);
}



