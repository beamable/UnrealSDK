
#include "BeamableCore/Public/AutoGen/ItemDeleteRequestBody.h"

#include "Misc/DefaultValueHelper.h"



void UItemDeleteRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("contentId"), ContentId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
}

void UItemDeleteRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("contentId"), ContentId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);		
}

void UItemDeleteRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("contentId"), Bag, ContentId);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("id"), Bag, Id);
}



