
#include "BeamableCore/Public/AutoGen/EventRule.h"





void UEventRule::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("rule"), Rule);
	Serializer->WriteValue(TEXT("value"), Value);
}

void UEventRule::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("rule"), Rule);
	Serializer->WriteValue(TEXT("value"), Value);		
}

void UEventRule::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("rule")), Rule);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("value")), Value);
}



