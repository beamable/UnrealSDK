
#include "BeamableCore/Public/AutoGen/StatStringListEntry.h"





void UStatStringListEntry::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("k"), K);
	Serializer->WriteValue(TEXT("v"), V);
}

void UStatStringListEntry::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("k"), K);
	Serializer->WriteValue(TEXT("v"), V);		
}

void UStatStringListEntry::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("k")), K);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("v")), V);
}



