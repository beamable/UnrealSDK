
#include "BeamableCore/Public/AutoGen/DataPoint.h"





void UDataPoint::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("timestamp"), Timestamp);
	Serializer->WriteValue(TEXT("value"), Value);
}

void UDataPoint::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("timestamp"), Timestamp);
	Serializer->WriteValue(TEXT("value"), Value);		
}

void UDataPoint::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Timestamp = Bag->GetStringField(TEXT("timestamp"));
	Value = Bag->GetStringField(TEXT("value"));
}



