
#include "BeamableCore/Public/AutoGen/ListTagsRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UListTagsRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("tagNameFilter"), &TagNameFilter, Serializer);
}

void UListTagsRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("tagNameFilter"), &TagNameFilter, Serializer);		
}

void UListTagsRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("tagNameFilter", Bag, TagNameFilter, OuterOwner);
}



