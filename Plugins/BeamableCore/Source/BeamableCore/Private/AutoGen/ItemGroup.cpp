
#include "BeamableCore/Public/AutoGen/ItemGroup.h"
#include "Serialization/BeamJsonUtils.h"




void UItemGroup::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("id"), Id);
	UBeamJsonUtils::SerializeArray<UItem*>(TEXT("items"), Items, Serializer);
}

void UItemGroup::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("id"), Id);
	UBeamJsonUtils::SerializeArray<UItem*>(TEXT("items"), Items, Serializer);		
}

void UItemGroup::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Id = Bag->GetStringField(TEXT("id"));
	UBeamJsonUtils::DeserializeArray<UItem*>(Bag->GetArrayField(TEXT("items")), Items, OuterOwner);
}



