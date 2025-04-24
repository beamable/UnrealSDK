
#include "BeamableCore/Public/AutoGen/GetLogsUrlHeader.h"





void UGetLogsUrlHeader::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("key"), Key, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("value"), Value, Serializer);
}

void UGetLogsUrlHeader::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("key"), Key, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("value"), Value, Serializer);		
}

void UGetLogsUrlHeader::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("key")), Key);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("value")), Value);
}



