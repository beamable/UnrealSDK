
#include "BeamableCore/Public/AutoGen/ItemCreateRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UItemCreateRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("contentId"), ContentId, Serializer);
	UBeamJsonUtils::SerializeArray<UItemProperty*>(TEXT("properties"), Properties, Serializer);
}

void UItemCreateRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("contentId"), ContentId, Serializer);
	UBeamJsonUtils::SerializeArray<UItemProperty*>(TEXT("properties"), Properties, Serializer);		
}

void UItemCreateRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("contentId"), Bag, ContentId);
	UBeamJsonUtils::DeserializeArray<UItemProperty*>(TEXT("properties"), Bag, Properties, OuterOwner);
}



