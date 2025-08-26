
#include "BeamableCore/Public/AutoGen/LocalizedValue.h"





void ULocalizedValue::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("language"), Language, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("value"), Value, Serializer);
}

void ULocalizedValue::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("language"), Language, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("value"), Value, Serializer);		
}

void ULocalizedValue::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("language"), Bag, Language);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("value"), Bag, Value);
}



