
#include "BeamableCore/Public/AutoGen/BeamoLimits.h"

#include "Misc/DefaultValueHelper.h"



void UBeamoLimits::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("maxContainerSize"), MaxContainerSize, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("maxRunningContainersPerService"), MaxRunningContainersPerService, Serializer);
}

void UBeamoLimits::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("maxContainerSize"), MaxContainerSize, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("maxRunningContainersPerService"), MaxRunningContainersPerService, Serializer);		
}

void UBeamoLimits::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("maxContainerSize")), MaxContainerSize);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("maxRunningContainersPerService")), MaxRunningContainersPerService);
}



