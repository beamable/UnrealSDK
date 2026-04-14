
#include "BeamableCore/Public/AutoGen/ContextInfo.h"





void UContextInfo::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("platform"), Platform, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("device"), Device, Serializer);
}

void UContextInfo::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("platform"), Platform, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("device"), Device, Serializer);		
}

void UContextInfo::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("platform"), Bag, Platform);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("device"), Bag, Device);
}



