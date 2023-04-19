
#include "BeamableCore/Public/AutoGen/BeamoLimits.h"

#include "Misc/DefaultValueHelper.h"



void UBeamoLimits::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("maxContainerSize"), MaxContainerSize);
	Serializer->WriteValue(TEXT("maxRunningContainersPerService"), MaxRunningContainersPerService);
}

void UBeamoLimits::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("maxContainerSize"), MaxContainerSize);
	Serializer->WriteValue(TEXT("maxRunningContainersPerService"), MaxRunningContainersPerService);		
}

void UBeamoLimits::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	MaxContainerSize = Bag->GetStringField(TEXT("maxContainerSize"));
	MaxRunningContainersPerService = Bag->GetIntegerField(TEXT("maxRunningContainersPerService"));
}



