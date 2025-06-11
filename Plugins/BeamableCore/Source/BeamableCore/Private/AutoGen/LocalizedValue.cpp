
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
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("language")), Language);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("value")), Value);
}



