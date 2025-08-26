
#include "BeamableCore/Public/AutoGen/ItemUpdateRequestBody.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UItemUpdateRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("contentId"), ContentId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
	UBeamJsonUtils::SerializeArray<UItemProperty*>(TEXT("properties"), Properties, Serializer);
}

void UItemUpdateRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("contentId"), ContentId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
	UBeamJsonUtils::SerializeArray<UItemProperty*>(TEXT("properties"), Properties, Serializer);		
}

void UItemUpdateRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("contentId"), Bag, ContentId);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("id"), Bag, Id);
	UBeamJsonUtils::DeserializeArray<UItemProperty*>(TEXT("properties"), Bag, Properties, OuterOwner);
}



