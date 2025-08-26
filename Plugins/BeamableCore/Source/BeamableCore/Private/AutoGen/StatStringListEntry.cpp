
#include "BeamableCore/Public/AutoGen/StatStringListEntry.h"





void UStatStringListEntry::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("k"), K, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("v"), V, Serializer);
}

void UStatStringListEntry::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("k"), K, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("v"), V, Serializer);		
}

void UStatStringListEntry::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("k"), Bag, K);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("v"), Bag, V);
}



