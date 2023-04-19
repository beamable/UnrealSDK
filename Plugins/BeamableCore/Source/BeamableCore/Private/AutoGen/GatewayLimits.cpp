
#include "BeamableCore/Public/AutoGen/GatewayLimits.h"

#include "Misc/DefaultValueHelper.h"



void UGatewayLimits::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("maxConcurrentRequests"), MaxConcurrentRequests);
}

void UGatewayLimits::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("maxConcurrentRequests"), MaxConcurrentRequests);		
}

void UGatewayLimits::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	MaxConcurrentRequests = Bag->GetIntegerField(TEXT("maxConcurrentRequests"));
}



