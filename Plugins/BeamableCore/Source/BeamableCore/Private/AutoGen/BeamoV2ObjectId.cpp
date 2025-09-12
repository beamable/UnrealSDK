
#include "BeamableCore/Public/AutoGen/BeamoV2ObjectId.h"
#include "Serialization/BeamJsonUtils.h"




void UBeamoV2ObjectId::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("timestamp"), &Timestamp, Serializer);
	UBeamJsonUtils::SerializeOptional<FDateTime>(TEXT("creationTime"), &CreationTime, Serializer);
}

void UBeamoV2ObjectId::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("timestamp"), &Timestamp, Serializer);
	UBeamJsonUtils::SerializeOptional<FDateTime>(TEXT("creationTime"), &CreationTime, Serializer);		
}

void UBeamoV2ObjectId::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<int32>("timestamp", Bag, Timestamp, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FDateTime>("creationTime", Bag, CreationTime, OuterOwner);
}



