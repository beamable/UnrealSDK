
#include "BeamableCore/Public/AutoGen/ItemProperty.h"





void UItemProperty::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("name"), Name);
	Serializer->WriteValue(TEXT("value"), Value);
}

void UItemProperty::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("name"), Name);
	Serializer->WriteValue(TEXT("value"), Value);		
}

void UItemProperty::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Name = Bag->GetStringField(TEXT("name"));
	Value = Bag->GetStringField(TEXT("value"));
}



