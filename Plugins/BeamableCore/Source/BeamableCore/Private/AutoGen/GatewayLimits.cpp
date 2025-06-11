
#include "BeamableCore/Public/AutoGen/GatewayLimits.h"

#include "Misc/DefaultValueHelper.h"



void UGatewayLimits::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("maxConcurrentRequests"), MaxConcurrentRequests, Serializer);
}

void UGatewayLimits::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("maxConcurrentRequests"), MaxConcurrentRequests, Serializer);		
}

void UGatewayLimits::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("maxConcurrentRequests")), MaxConcurrentRequests);
}



