
#include "BeamableCore/Public/AutoGen/NewItemReward.h"
#include "Serialization/BeamJsonUtils.h"




void UNewItemReward::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("symbol"), Symbol);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("properties"), &Properties, Serializer);
}

void UNewItemReward::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("symbol"), Symbol);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("properties"), &Properties, Serializer);		
}

void UNewItemReward::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Symbol = Bag->GetStringField(TEXT("symbol"));
	UBeamJsonUtils::DeserializeOptional<TMap<FString, FString>, FString>("properties", Bag, Properties, OuterOwner);
}



