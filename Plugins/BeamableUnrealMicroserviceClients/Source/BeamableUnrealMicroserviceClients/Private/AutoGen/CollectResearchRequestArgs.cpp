
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/CollectResearchRequestArgs.h"

#include "Misc/DefaultValueHelper.h"



void UCollectResearchRequestArgs::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("itemInstanceId"), ItemInstanceId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("itemContentId"), ItemContentId, Serializer);
}

void UCollectResearchRequestArgs::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("itemInstanceId"), ItemInstanceId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("itemContentId"), ItemContentId, Serializer);		
}

void UCollectResearchRequestArgs::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("itemInstanceId"), Bag, ItemInstanceId);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("itemContentId"), Bag, ItemContentId);
}



