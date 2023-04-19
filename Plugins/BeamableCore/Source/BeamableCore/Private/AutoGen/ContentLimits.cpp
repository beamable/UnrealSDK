
#include "BeamableCore/Public/AutoGen/ContentLimits.h"
#include "Serialization/BeamJsonUtils.h"




void UContentLimits::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("maxDistinctContentIds"), &MaxDistinctContentIds, Serializer);
}

void UContentLimits::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("maxDistinctContentIds"), &MaxDistinctContentIds, Serializer);		
}

void UContentLimits::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<int32>("maxDistinctContentIds", Bag, MaxDistinctContentIds, OuterOwner);
}



