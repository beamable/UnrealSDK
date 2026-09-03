
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/DeviceList.h"
#include "Serialization/BeamJsonUtils.h"



void UDeviceList::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UDeviceList::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UDeviceInfo*>(TEXT("devices"), Devices, Serializer);
}

void UDeviceList::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UDeviceInfo*>(TEXT("devices"), Devices, Serializer);		
}

void UDeviceList::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UDeviceInfo*>(TEXT("devices"), Bag, Devices, OuterOwner);
}



