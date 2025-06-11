
#include "BeamableCore/Public/AutoGen/EventRewardContent.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UEventRewardContent::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("min"), Min, Serializer);
	UBeamJsonUtils::SerializeOptional<double>(TEXT("max"), &Max, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UEventInventoryRewardCurrency*>, UEventInventoryRewardCurrency*>(TEXT("currencies"), &Currencies, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UEventInventoryRewardItem*>, UEventInventoryRewardItem*>(TEXT("items"), &Items, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UEventRewardObtain*>, UEventRewardObtain*>(TEXT("obtain"), &Obtain, Serializer);
}

void UEventRewardContent::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("min"), Min, Serializer);
	UBeamJsonUtils::SerializeOptional<double>(TEXT("max"), &Max, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UEventInventoryRewardCurrency*>, UEventInventoryRewardCurrency*>(TEXT("currencies"), &Currencies, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UEventInventoryRewardItem*>, UEventInventoryRewardItem*>(TEXT("items"), &Items, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UEventRewardObtain*>, UEventRewardObtain*>(TEXT("obtain"), &Obtain, Serializer);		
}

void UEventRewardContent::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("min")), Min);
	UBeamJsonUtils::DeserializeOptional<double>("max", Bag, Max, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UEventInventoryRewardCurrency*>, UEventInventoryRewardCurrency*>("currencies", Bag, Currencies, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UEventInventoryRewardItem*>, UEventInventoryRewardItem*>("items", Bag, Items, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UEventRewardObtain*>, UEventRewardObtain*>("obtain", Bag, Obtain, OuterOwner);
}



