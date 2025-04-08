
#include "BeamableCore/Public/AutoGen/DateRange.h"





void UDateRange::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("from"), From);
	Serializer->WriteValue(TEXT("to"), To);
}

void UDateRange::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("from"), From);
	Serializer->WriteValue(TEXT("to"), To);		
}

void UDateRange::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("from")), From);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("to")), To);
}



