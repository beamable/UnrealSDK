
#include "BeamableCore/Public/AutoGen/OptionalJsonNodeWrapper.h"
#include "Serialization/BeamJsonUtils.h"




void UOptionalJsonNodeWrapper::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("node"), &Node, Serializer);
}

void UOptionalJsonNodeWrapper::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("node"), &Node, Serializer);		
}

void UOptionalJsonNodeWrapper::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("node", Bag, Node, OuterOwner);
}



