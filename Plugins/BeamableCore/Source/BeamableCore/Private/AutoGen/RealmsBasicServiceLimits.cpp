
#include "BeamableCore/Public/AutoGen/RealmsBasicServiceLimits.h"
#include "Serialization/BeamJsonUtils.h"




void URealmsBasicServiceLimits::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<URealmsBasicBeamoLimits*>(TEXT("beamo"), &Beamo, Serializer);
	UBeamJsonUtils::SerializeOptional<UContentLimits*>(TEXT("content"), &Content, Serializer);
	UBeamJsonUtils::SerializeOptional<UGatewayLimits*>(TEXT("gateway"), &Gateway, Serializer);
}

void URealmsBasicServiceLimits::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<URealmsBasicBeamoLimits*>(TEXT("beamo"), &Beamo, Serializer);
	UBeamJsonUtils::SerializeOptional<UContentLimits*>(TEXT("content"), &Content, Serializer);
	UBeamJsonUtils::SerializeOptional<UGatewayLimits*>(TEXT("gateway"), &Gateway, Serializer);		
}

void URealmsBasicServiceLimits::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<URealmsBasicBeamoLimits*>("beamo", Bag, Beamo, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UContentLimits*>("content", Bag, Content, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UGatewayLimits*>("gateway", Bag, Gateway, OuterOwner);
}



