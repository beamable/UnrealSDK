
#include "BeamableCore/Public/AutoGen/PropertyFilterDTO.h"
#include "Serialization/BeamJsonUtils.h"




void UPropertyFilterDTO::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("key"), Key, Serializer);
	UBeamJsonUtils::SerializeUObject<UPredicateDTO*>("predicate", Predicate, Serializer);
}

void UPropertyFilterDTO::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("key"), Key, Serializer);
	UBeamJsonUtils::SerializeUObject<UPredicateDTO*>("predicate", Predicate, Serializer);		
}

void UPropertyFilterDTO::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("key"), Bag, Key);
	UBeamJsonUtils::DeserializeUObject<UPredicateDTO*>("predicate", Bag, Predicate, OuterOwner);
}



