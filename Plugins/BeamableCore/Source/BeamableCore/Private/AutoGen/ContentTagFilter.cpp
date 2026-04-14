
#include "BeamableCore/Public/AutoGen/ContentTagFilter.h"
#include "Serialization/BeamJsonUtils.h"




void UContentTagFilter::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<FString>(TEXT("allOf"), AllOf, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("anyOf"), AnyOf, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("noneOf"), NoneOf, Serializer);
}

void UContentTagFilter::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<FString>(TEXT("allOf"), AllOf, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("anyOf"), AnyOf, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("noneOf"), NoneOf, Serializer);		
}

void UContentTagFilter::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<FString>(TEXT("allOf"), Bag, AllOf, OuterOwner);
	UBeamJsonUtils::DeserializeArray<FString>(TEXT("anyOf"), Bag, AnyOf, OuterOwner);
	UBeamJsonUtils::DeserializeArray<FString>(TEXT("noneOf"), Bag, NoneOf, OuterOwner);
}



