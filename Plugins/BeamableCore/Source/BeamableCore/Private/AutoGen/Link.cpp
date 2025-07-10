
#include "BeamableCore/Public/AutoGen/Link.h"
#include "Serialization/BeamJsonUtils.h"




void ULink::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("href"), &Href, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("rel"), &Rel, Serializer);
}

void ULink::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("href"), &Href, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("rel"), &Rel, Serializer);		
}

void ULink::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("href", Bag, Href, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("rel", Bag, Rel, OuterOwner);
}



