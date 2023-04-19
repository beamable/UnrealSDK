
#include "BeamableCore/Public/AutoGen/GetCatalogReq.h"
#include "Serialization/BeamJsonUtils.h"




void UGetCatalogReq::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("version"), &Version, Serializer);
}

void UGetCatalogReq::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("version"), &Version, Serializer);		
}

void UGetCatalogReq::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<int64>("version", Bag, Version, OuterOwner);
}



