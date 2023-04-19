
#include "BeamableCore/Public/AutoGen/DeleteDevicesRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UDeleteDevicesRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("deviceIds"), &DeviceIds, Serializer);
}

void UDeleteDevicesRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("deviceIds"), &DeviceIds, Serializer);		
}

void UDeleteDevicesRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("deviceIds", Bag, DeviceIds, OuterOwner);
}



