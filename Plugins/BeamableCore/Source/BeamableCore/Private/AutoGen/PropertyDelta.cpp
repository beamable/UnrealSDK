
#include "BeamableCore/Public/AutoGen/PropertyDelta.h"
#include "Serialization/BeamJsonUtils.h"




void UPropertyDelta::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("before"), &Before, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("after"), &After, Serializer);
}

void UPropertyDelta::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("before"), &Before, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("after"), &After, Serializer);		
}

void UPropertyDelta::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("before", Bag, Before, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("after", Bag, After, OuterOwner);
}



