
#include "BeamableCore/Public/AutoGen/ClientDataEntry.h"





void UClientDataEntry::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("name"), Name);
	Serializer->WriteValue(TEXT("value"), Value);
}

void UClientDataEntry::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("name"), Name);
	Serializer->WriteValue(TEXT("value"), Value);		
}

void UClientDataEntry::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Name = Bag->GetStringField(TEXT("name"));
	Value = Bag->GetStringField(TEXT("value"));
}



