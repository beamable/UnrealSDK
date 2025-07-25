
#include "BeamableCore/Public/AutoGen/BeamoV2StringStringKeyValuePair.h"
#include "Serialization/BeamJsonUtils.h"




void UBeamoV2StringStringKeyValuePair::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("key"), &Key, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("value"), &Value, Serializer);
}

void UBeamoV2StringStringKeyValuePair::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("key"), &Key, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("value"), &Value, Serializer);		
}

void UBeamoV2StringStringKeyValuePair::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("key", Bag, Key, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("value", Bag, Value, OuterOwner);
}



