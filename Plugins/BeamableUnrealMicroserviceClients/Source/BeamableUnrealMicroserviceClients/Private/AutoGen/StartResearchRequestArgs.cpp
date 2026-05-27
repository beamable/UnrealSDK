
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/StartResearchRequestArgs.h"

#include "Misc/DefaultValueHelper.h"



void UStartResearchRequestArgs::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("itemInstanceId"), ItemInstanceId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("itemContentId"), ItemContentId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("projectContentId"), ProjectContentId, Serializer);
}

void UStartResearchRequestArgs::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("itemInstanceId"), ItemInstanceId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("itemContentId"), ItemContentId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("projectContentId"), ProjectContentId, Serializer);		
}

void UStartResearchRequestArgs::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("itemInstanceId"), Bag, ItemInstanceId);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("itemContentId"), Bag, ItemContentId);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("projectContentId"), Bag, ProjectContentId);
}



