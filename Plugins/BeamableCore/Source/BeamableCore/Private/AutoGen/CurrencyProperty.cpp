
#include "BeamableCore/Public/AutoGen/CurrencyProperty.h"





void UCurrencyProperty::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("name"), Name);
	Serializer->WriteValue(TEXT("value"), Value);
}

void UCurrencyProperty::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("name"), Name);
	Serializer->WriteValue(TEXT("value"), Value);		
}

void UCurrencyProperty::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Name = Bag->GetStringField(TEXT("name"));
	Value = Bag->GetStringField(TEXT("value"));
}



