
#include "BeamableCore/Public/AutoGen/Link.h"





void ULink::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("href"), Href, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("rel"), Rel, Serializer);
}

void ULink::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("href"), Href, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("rel"), Rel, Serializer);		
}

void ULink::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("href"), Bag, Href);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("rel"), Bag, Rel);
}



