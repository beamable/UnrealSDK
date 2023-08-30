
#include "BeamableCore/Public/AutoGen/Tag.h"
#include "Serialization/BeamJsonUtils.h"




void UTag::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("name"), &Name, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("value"), &Value, Serializer);
}

void UTag::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("name"), &Name, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("value"), &Value, Serializer);		
}

void UTag::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("name", Bag, Name, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("value", Bag, Value, OuterOwner);
}



