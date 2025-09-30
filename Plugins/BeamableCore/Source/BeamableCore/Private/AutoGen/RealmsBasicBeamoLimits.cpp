
#include "BeamableCore/Public/AutoGen/RealmsBasicBeamoLimits.h"

#include "Misc/DefaultValueHelper.h"



void URealmsBasicBeamoLimits::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("maxContainerSize"), MaxContainerSize, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("maxRunningContainersPerService"), MaxRunningContainersPerService, Serializer);
}

void URealmsBasicBeamoLimits::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("maxContainerSize"), MaxContainerSize, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("maxRunningContainersPerService"), MaxRunningContainersPerService, Serializer);		
}

void URealmsBasicBeamoLimits::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("maxContainerSize"), Bag, MaxContainerSize);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("maxRunningContainersPerService"), Bag, MaxRunningContainersPerService);
}



