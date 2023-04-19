
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
	K = Bag->GetStringField(TEXT("k"));
	V = Bag->GetStringField(TEXT("v"));
}



