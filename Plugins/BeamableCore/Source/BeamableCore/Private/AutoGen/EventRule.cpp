
#include "BeamableCore/Public/AutoGen/EventRule.h"





void UEventRule::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("rule"), Rule, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("value"), Value, Serializer);
}

void UEventRule::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("rule"), Rule, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("value"), Value, Serializer);		
}

void UEventRule::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("rule"), Bag, Rule);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("value"), Bag, Value);
}



