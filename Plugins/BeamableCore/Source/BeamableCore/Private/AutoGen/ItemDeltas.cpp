
#include "BeamableCore/Public/AutoGen/ItemDeltas.h"
#include "Serialization/BeamJsonUtils.h"




void UItemDeltas::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UItemPropertiesDelta*>(TEXT("created"), Created, Serializer);
	UBeamJsonUtils::SerializeArray<UItemPropertiesDelta*>(TEXT("updated"), Updated, Serializer);
	UBeamJsonUtils::SerializeArray<UItemPropertiesDelta*>(TEXT("deleted"), Deleted, Serializer);
}

void UItemDeltas::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UItemPropertiesDelta*>(TEXT("created"), Created, Serializer);
	UBeamJsonUtils::SerializeArray<UItemPropertiesDelta*>(TEXT("updated"), Updated, Serializer);
	UBeamJsonUtils::SerializeArray<UItemPropertiesDelta*>(TEXT("deleted"), Deleted, Serializer);		
}

void UItemDeltas::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UItemPropertiesDelta*>(TEXT("created"), Bag, Created, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UItemPropertiesDelta*>(TEXT("updated"), Bag, Updated, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UItemPropertiesDelta*>(TEXT("deleted"), Bag, Deleted, OuterOwner);
}



