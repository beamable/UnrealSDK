
#include "BeamableCore/Public/AutoGen/Link.h"





void ULink::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("href"), Href);
	Serializer->WriteValue(TEXT("rel"), Rel);
}

void ULink::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("href"), Href);
	Serializer->WriteValue(TEXT("rel"), Rel);		
}

void ULink::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("href")), Href);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("rel")), Rel);
}



