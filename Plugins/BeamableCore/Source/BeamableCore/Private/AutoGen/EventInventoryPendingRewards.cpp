
#include "BeamableCore/Public/AutoGen/EventInventoryPendingRewards.h"
#include "Serialization/BeamJsonUtils.h"




void UEventInventoryPendingRewards::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("empty"), bEmpty);
	UBeamJsonUtils::SerializeOptional<TArray<UItemCreateRequestBody*>, UItemCreateRequestBody*>(TEXT("items"), &Items, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("currencies"), &Currencies, Serializer);
}

void UEventInventoryPendingRewards::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("empty"), bEmpty);
	UBeamJsonUtils::SerializeOptional<TArray<UItemCreateRequestBody*>, UItemCreateRequestBody*>(TEXT("items"), &Items, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("currencies"), &Currencies, Serializer);		
}

void UEventInventoryPendingRewards::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	bEmpty = Bag->GetBoolField(TEXT("empty"));
	UBeamJsonUtils::DeserializeOptional<TArray<UItemCreateRequestBody*>, UItemCreateRequestBody*>("items", Bag, Items, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TMap<FString, FString>, FString>("currencies", Bag, Currencies, OuterOwner);
}



