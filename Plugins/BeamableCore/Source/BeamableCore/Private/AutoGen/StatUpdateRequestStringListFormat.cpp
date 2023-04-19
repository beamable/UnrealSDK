
#include "BeamableCore/Public/AutoGen/StatUpdateRequestStringListFormat.h"
#include "Serialization/BeamJsonUtils.h"




void UStatUpdateRequestStringListFormat::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<UStatStringListEntry*>, UStatStringListEntry*>(TEXT("set"), &Set, Serializer);
}

void UStatUpdateRequestStringListFormat::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<UStatStringListEntry*>, UStatStringListEntry*>(TEXT("set"), &Set, Serializer);		
}

void UStatUpdateRequestStringListFormat::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<TArray<UStatStringListEntry*>, UStatStringListEntry*>("set", Bag, Set, OuterOwner);
}



