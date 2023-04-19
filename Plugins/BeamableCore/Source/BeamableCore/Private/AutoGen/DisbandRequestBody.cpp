
#include "BeamableCore/Public/AutoGen/DisbandRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UDisbandRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("subGroup"), &SubGroup, Serializer);
}

void UDisbandRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("subGroup"), &SubGroup, Serializer);		
}

void UDisbandRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<int64>("subGroup", Bag, SubGroup, OuterOwner);
}



