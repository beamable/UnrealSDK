
#include "AutoGen/EventInventoryPendingRewards.h"
#include "Serialization/BeamJsonUtils.h"


void UEventInventoryPendingRewards ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("currencies"), &Currencies, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UItemCreateRequestBody*>, UItemCreateRequestBody*>(TEXT("items"), &Items, Serializer);
	Serializer->WriteValue(TEXT("empty"), bEmpty);
}

void UEventInventoryPendingRewards::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("currencies"), &Currencies, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UItemCreateRequestBody*>, UItemCreateRequestBody*>(TEXT("items"), &Items, Serializer);
	Serializer->WriteValue(TEXT("empty"), bEmpty);		
}

void UEventInventoryPendingRewards ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<TMap<FString, FString>, FString>("currencies", Bag, Currencies, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UItemCreateRequestBody*>, UItemCreateRequestBody*>("items", Bag, Items, OuterOwner);
	bEmpty = Bag->GetBoolField(TEXT("empty"));
}