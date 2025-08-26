
#include "BeamableCore/Public/AutoGen/DateRange.h"





void UDateRange::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("from"), From, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("to"), To, Serializer);
}

void UDateRange::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("from"), From, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("to"), To, Serializer);		
}

void UDateRange::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("from"), Bag, From);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("to"), Bag, To);
}



