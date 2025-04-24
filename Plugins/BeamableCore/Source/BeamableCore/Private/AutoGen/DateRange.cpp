
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
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("from")), From);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("to")), To);
}



