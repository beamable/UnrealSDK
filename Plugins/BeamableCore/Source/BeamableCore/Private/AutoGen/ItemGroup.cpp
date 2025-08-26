
#include "BeamableCore/Public/AutoGen/ItemGroup.h"
#include "Serialization/BeamJsonUtils.h"




void UItemGroup::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
	UBeamJsonUtils::SerializeArray<UItem*>(TEXT("items"), Items, Serializer);
}

void UItemGroup::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
	UBeamJsonUtils::SerializeArray<UItem*>(TEXT("items"), Items, Serializer);		
}

void UItemGroup::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("id"), Bag, Id);
	UBeamJsonUtils::DeserializeArray<UItem*>(TEXT("items"), Bag, Items, OuterOwner);
}



