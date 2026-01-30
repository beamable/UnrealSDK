
#include "BeamableCore/Public/AutoGen/ItemPropertiesDelta.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UItemPropertiesDelta::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("contentId"), ContentId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("itemId"), ItemId, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, UPropertyDelta*>, UPropertyDelta*>(TEXT("properties"), &Properties, Serializer);
}

void UItemPropertiesDelta::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("contentId"), ContentId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("itemId"), ItemId, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, UPropertyDelta*>, UPropertyDelta*>(TEXT("properties"), &Properties, Serializer);		
}

void UItemPropertiesDelta::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("contentId"), Bag, ContentId);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("itemId"), Bag, ItemId);
	UBeamJsonUtils::DeserializeOptional<TMap<FString, UPropertyDelta*>, UPropertyDelta*>("properties", Bag, Properties, OuterOwner);
}



