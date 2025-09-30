
#include "BeamableCore/Public/AutoGen/ServicePlanActorServiceLimits.h"
#include "Serialization/BeamJsonUtils.h"




void UServicePlanActorServiceLimits::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<UServicePlanActorBeamoLimits*>(TEXT("beamo"), &Beamo, Serializer);
}

void UServicePlanActorServiceLimits::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<UServicePlanActorBeamoLimits*>(TEXT("beamo"), &Beamo, Serializer);		
}

void UServicePlanActorServiceLimits::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<UServicePlanActorBeamoLimits*>("beamo", Bag, Beamo, OuterOwner);
}



