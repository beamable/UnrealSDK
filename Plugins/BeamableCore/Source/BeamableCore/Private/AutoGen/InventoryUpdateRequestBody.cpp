
#include "BeamableCore/Public/AutoGen/InventoryUpdateRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UInventoryUpdateRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("empty"), bEmpty);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("currencyContentIds"), CurrencyContentIds, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("itemContentIds"), ItemContentIds, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("applyVipBonus"), &bApplyVipBonus, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("transaction"), &Transaction, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UItemUpdateRequestBody*>, UItemUpdateRequestBody*>(TEXT("updateItems"), &UpdateItems, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UItemCreateRequestBody*>, UItemCreateRequestBody*>(TEXT("newItems"), &NewItems, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UItemDeleteRequestBody*>, UItemDeleteRequestBody*>(TEXT("deleteItems"), &DeleteItems, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, int64>, int64>(TEXT("currencies"), &Currencies, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FArrayOfCurrencyProperty>, FArrayOfCurrencyProperty>(TEXT("currencyProperties"), &CurrencyProperties, Serializer);
}

void UInventoryUpdateRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("empty"), bEmpty);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("currencyContentIds"), CurrencyContentIds, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("itemContentIds"), ItemContentIds, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("applyVipBonus"), &bApplyVipBonus, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("transaction"), &Transaction, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UItemUpdateRequestBody*>, UItemUpdateRequestBody*>(TEXT("updateItems"), &UpdateItems, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UItemCreateRequestBody*>, UItemCreateRequestBody*>(TEXT("newItems"), &NewItems, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UItemDeleteRequestBody*>, UItemDeleteRequestBody*>(TEXT("deleteItems"), &DeleteItems, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, int64>, int64>(TEXT("currencies"), &Currencies, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FArrayOfCurrencyProperty>, FArrayOfCurrencyProperty>(TEXT("currencyProperties"), &CurrencyProperties, Serializer);		
}

void UInventoryUpdateRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	bEmpty = Bag->GetBoolField(TEXT("empty"));
	UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("currencyContentIds")), CurrencyContentIds, OuterOwner);
	UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("itemContentIds")), ItemContentIds, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<bool>("applyVipBonus", Bag, bApplyVipBonus, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("transaction", Bag, Transaction, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UItemUpdateRequestBody*>, UItemUpdateRequestBody*>("updateItems", Bag, UpdateItems, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UItemCreateRequestBody*>, UItemCreateRequestBody*>("newItems", Bag, NewItems, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UItemDeleteRequestBody*>, UItemDeleteRequestBody*>("deleteItems", Bag, DeleteItems, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TMap<FString, int64>, int64>("currencies", Bag, Currencies, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TMap<FString, FArrayOfCurrencyProperty>, FArrayOfCurrencyProperty>("currencyProperties", Bag, CurrencyProperties, OuterOwner);
}



