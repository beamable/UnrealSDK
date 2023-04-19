
#include "BeamableCore/Public/AutoGen/MetadataPair.h"





void UMetadataPair::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("key"), Key);
	Serializer->WriteValue(TEXT("value"), Value);
}

void UMetadataPair::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("key"), Key);
	Serializer->WriteValue(TEXT("value"), Value);		
}

void UMetadataPair::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Key = Bag->GetStringField(TEXT("key"));
	Value = Bag->GetStringField(TEXT("value"));
}



