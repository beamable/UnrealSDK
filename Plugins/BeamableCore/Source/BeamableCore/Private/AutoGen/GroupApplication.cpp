
#include "BeamableCore/Public/AutoGen/GroupApplication.h"
#include "Serialization/BeamJsonUtils.h"




void UGroupApplication::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("subGroup"), &SubGroup, Serializer);
}

void UGroupApplication::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("subGroup"), &SubGroup, Serializer);		
}

void UGroupApplication::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<int64>("subGroup", Bag, SubGroup, OuterOwner);
}



