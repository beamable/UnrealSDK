
#include "BeamableCore/Public/AutoGen/GetLogsUrlHeader.h"





void UGetLogsUrlHeader::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("key"), Key);
	Serializer->WriteValue(TEXT("value"), Value);
}

void UGetLogsUrlHeader::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("key"), Key);
	Serializer->WriteValue(TEXT("value"), Value);		
}

void UGetLogsUrlHeader::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("key")), Key);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("value")), Value);
}



