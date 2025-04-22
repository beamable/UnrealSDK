
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
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("k")), K);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("v")), V);
}



