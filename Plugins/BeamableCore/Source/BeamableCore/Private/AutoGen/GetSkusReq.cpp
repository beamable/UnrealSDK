
#include "BeamableCore/Public/AutoGen/GetSkusReq.h"
#include "Serialization/BeamJsonUtils.h"




void UGetSkusReq::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("version"), &Version, Serializer);
}

void UGetSkusReq::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("version"), &Version, Serializer);		
}

void UGetSkusReq::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<int64>("version", Bag, Version, OuterOwner);
}



