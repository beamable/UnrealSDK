
#include "BeamableCore/Public/AutoGen/InventoryFiltersDTO.h"
#include "Serialization/BeamJsonUtils.h"




void UInventoryFiltersDTO::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<UContentTagFilter*>(TEXT("contentTagFilter"), &ContentTagFilter, Serializer);
	UBeamJsonUtils::SerializeOptional<UTimeRange*>(TEXT("createdAt"), &CreatedAt, Serializer);
	UBeamJsonUtils::SerializeOptional<UTimeRange*>(TEXT("updatedAt"), &UpdatedAt, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UPropertyFilterDTO*>, UPropertyFilterDTO*>(TEXT("properties"), &Properties, Serializer);
}

void UInventoryFiltersDTO::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<UContentTagFilter*>(TEXT("contentTagFilter"), &ContentTagFilter, Serializer);
	UBeamJsonUtils::SerializeOptional<UTimeRange*>(TEXT("createdAt"), &CreatedAt, Serializer);
	UBeamJsonUtils::SerializeOptional<UTimeRange*>(TEXT("updatedAt"), &UpdatedAt, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UPropertyFilterDTO*>, UPropertyFilterDTO*>(TEXT("properties"), &Properties, Serializer);		
}

void UInventoryFiltersDTO::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<UContentTagFilter*>("contentTagFilter", Bag, ContentTagFilter, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UTimeRange*>("createdAt", Bag, CreatedAt, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UTimeRange*>("updatedAt", Bag, UpdatedAt, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UPropertyFilterDTO*>, UPropertyFilterDTO*>("properties", Bag, Properties, OuterOwner);
}



