
#include "BeamableCore/Public/AutoGen/BeamoV2DataPoint.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UBeamoV2DataPoint::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("value"), Value, Serializer);
	UBeamJsonUtils::SerializeOptional<FDateTime>(TEXT("timeStamp"), &TimeStamp, Serializer);
}

void UBeamoV2DataPoint::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("value"), Value, Serializer);
	UBeamJsonUtils::SerializeOptional<FDateTime>(TEXT("timeStamp"), &TimeStamp, Serializer);		
}

void UBeamoV2DataPoint::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("value")), Value);
	UBeamJsonUtils::DeserializeOptional<FDateTime>("timeStamp", Bag, TimeStamp, OuterOwner);
}



