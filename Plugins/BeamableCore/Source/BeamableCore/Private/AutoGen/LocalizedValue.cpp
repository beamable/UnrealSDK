
#include "BeamableCore/Public/AutoGen/LocalizedValue.h"





void ULocalizedValue::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("language"), Language);
	Serializer->WriteValue(TEXT("value"), Value);
}

void ULocalizedValue::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("language"), Language);
	Serializer->WriteValue(TEXT("value"), Value);		
}

void ULocalizedValue::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("language")), Language);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("value")), Value);
}



