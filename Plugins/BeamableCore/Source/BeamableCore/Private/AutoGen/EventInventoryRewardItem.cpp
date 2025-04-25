
#include "BeamableCore/Public/AutoGen/EventInventoryRewardItem.h"
#include "Serialization/BeamJsonUtils.h"




void UEventInventoryRewardItem::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("properties"), &Properties, Serializer);
}

void UEventInventoryRewardItem::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("properties"), &Properties, Serializer);		
}

void UEventInventoryRewardItem::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("id")), Id);
	UBeamJsonUtils::DeserializeOptional<TMap<FString, FString>, FString>("properties", Bag, Properties, OuterOwner);
}



