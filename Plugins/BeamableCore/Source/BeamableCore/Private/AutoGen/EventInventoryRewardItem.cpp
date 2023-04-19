
#include "BeamableCore/Public/AutoGen/EventInventoryRewardItem.h"
#include "Serialization/BeamJsonUtils.h"




void UEventInventoryRewardItem::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("id"), Id);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("properties"), &Properties, Serializer);
}

void UEventInventoryRewardItem::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("id"), Id);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("properties"), &Properties, Serializer);		
}

void UEventInventoryRewardItem::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Id = Bag->GetStringField(TEXT("id"));
	UBeamJsonUtils::DeserializeOptional<TMap<FString, FString>, FString>("properties", Bag, Properties, OuterOwner);
}



