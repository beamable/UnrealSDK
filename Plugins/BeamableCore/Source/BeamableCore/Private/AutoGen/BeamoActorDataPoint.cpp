
#include "BeamableCore/Public/AutoGen/BeamoActorDataPoint.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UBeamoActorDataPoint::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("value"), Value, Serializer);
	UBeamJsonUtils::SerializeOptional<FDateTime>(TEXT("timeStamp"), &TimeStamp, Serializer);
}

void UBeamoActorDataPoint::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("value"), Value, Serializer);
	UBeamJsonUtils::SerializeOptional<FDateTime>(TEXT("timeStamp"), &TimeStamp, Serializer);		
}

void UBeamoActorDataPoint::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("value")), Value);
	UBeamJsonUtils::DeserializeOptional<FDateTime>("timeStamp", Bag, TimeStamp, OuterOwner);
}



