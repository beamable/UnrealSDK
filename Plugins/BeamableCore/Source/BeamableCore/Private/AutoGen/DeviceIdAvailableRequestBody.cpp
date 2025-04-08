
#include "BeamableCore/Public/AutoGen/DeviceIdAvailableRequestBody.h"





void UDeviceIdAvailableRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("deviceId"), DeviceId);
}

void UDeviceIdAvailableRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("deviceId"), DeviceId);		
}

void UDeviceIdAvailableRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("deviceId")), DeviceId);
}



