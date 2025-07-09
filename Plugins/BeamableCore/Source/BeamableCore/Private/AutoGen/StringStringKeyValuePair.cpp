
#include "BeamableCore/Public/AutoGen/StringStringKeyValuePair.h"
#include "Serialization/BeamJsonUtils.h"




void UStringStringKeyValuePair::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("key"), &Key, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("value"), &Value, Serializer);
}

void UStringStringKeyValuePair::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("key"), &Key, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("value"), &Value, Serializer);		
}

void UStringStringKeyValuePair::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("key", Bag, Key, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("value", Bag, Value, OuterOwner);
}



