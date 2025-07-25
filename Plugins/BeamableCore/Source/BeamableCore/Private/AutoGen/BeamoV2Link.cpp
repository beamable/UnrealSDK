
#include "BeamableCore/Public/AutoGen/BeamoV2Link.h"
#include "Serialization/BeamJsonUtils.h"




void UBeamoV2Link::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("href"), &Href, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("rel"), &Rel, Serializer);
}

void UBeamoV2Link::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("href"), &Href, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("rel"), &Rel, Serializer);		
}

void UBeamoV2Link::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("href", Bag, Href, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("rel", Bag, Rel, OuterOwner);
}



