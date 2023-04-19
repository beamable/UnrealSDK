
#include "BeamableCore/Public/AutoGen/ServiceLimits.h"
#include "Serialization/BeamJsonUtils.h"




void UServiceLimits::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<UBeamoLimits*>(TEXT("beamo"), &Beamo, Serializer);
	UBeamJsonUtils::SerializeOptional<UContentLimits*>(TEXT("content"), &Content, Serializer);
	UBeamJsonUtils::SerializeOptional<UGatewayLimits*>(TEXT("gateway"), &Gateway, Serializer);
}

void UServiceLimits::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<UBeamoLimits*>(TEXT("beamo"), &Beamo, Serializer);
	UBeamJsonUtils::SerializeOptional<UContentLimits*>(TEXT("content"), &Content, Serializer);
	UBeamJsonUtils::SerializeOptional<UGatewayLimits*>(TEXT("gateway"), &Gateway, Serializer);		
}

void UServiceLimits::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<UBeamoLimits*>("beamo", Bag, Beamo, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UContentLimits*>("content", Bag, Content, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UGatewayLimits*>("gateway", Bag, Gateway, OuterOwner);
}



