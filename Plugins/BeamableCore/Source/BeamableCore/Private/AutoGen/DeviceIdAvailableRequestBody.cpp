
#include "BeamableCore/Public/AutoGen/DeviceIdAvailableRequestBody.h"





void UDeviceIdAvailableRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("deviceId"), DeviceId, Serializer);
}

void UDeviceIdAvailableRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("deviceId"), DeviceId, Serializer);		
}

void UDeviceIdAvailableRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("deviceId")), DeviceId);
}



