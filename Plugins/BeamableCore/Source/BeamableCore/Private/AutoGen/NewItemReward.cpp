
#include "BeamableCore/Public/AutoGen/NewItemReward.h"
#include "Serialization/BeamJsonUtils.h"




void UNewItemReward::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("symbol"), Symbol, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("properties"), &Properties, Serializer);
}

void UNewItemReward::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("symbol"), Symbol, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("properties"), &Properties, Serializer);		
}

void UNewItemReward::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("symbol"), Bag, Symbol);
	UBeamJsonUtils::DeserializeOptional<TMap<FString, FString>, FString>("properties", Bag, Properties, OuterOwner);
}



