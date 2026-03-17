
#include "BeamableCore/Public/AutoGen/InventoryFiltersDTO.h"
#include "Serialization/BeamJsonUtils.h"




void UInventoryFiltersDTO::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<UTimeRange*>(TEXT("updatedAt"), &UpdatedAt, Serializer);
	UBeamJsonUtils::SerializeOptional<UTimeRange*>(TEXT("createdAt"), &CreatedAt, Serializer);
	UBeamJsonUtils::SerializeOptional<UContentTagFilter*>(TEXT("contentTagFilter"), &ContentTagFilter, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("proxyIds"), &ProxyIds, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UPropertyFilterDTO*>, UPropertyFilterDTO*>(TEXT("propertyFilters"), &PropertyFilters, Serializer);
}

void UInventoryFiltersDTO::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<UTimeRange*>(TEXT("updatedAt"), &UpdatedAt, Serializer);
	UBeamJsonUtils::SerializeOptional<UTimeRange*>(TEXT("createdAt"), &CreatedAt, Serializer);
	UBeamJsonUtils::SerializeOptional<UContentTagFilter*>(TEXT("contentTagFilter"), &ContentTagFilter, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("proxyIds"), &ProxyIds, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UPropertyFilterDTO*>, UPropertyFilterDTO*>(TEXT("propertyFilters"), &PropertyFilters, Serializer);		
}

void UInventoryFiltersDTO::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<UTimeRange*>("updatedAt", Bag, UpdatedAt, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UTimeRange*>("createdAt", Bag, CreatedAt, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UContentTagFilter*>("contentTagFilter", Bag, ContentTagFilter, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("proxyIds", Bag, ProxyIds, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UPropertyFilterDTO*>, UPropertyFilterDTO*>("propertyFilters", Bag, PropertyFilters, OuterOwner);
}



