
#include "AutoGen/InventoryUpdateRequestBody.h"
#include "Serialization/BeamJsonUtils.h"


void UInventoryUpdateRequestBody ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TMap<FString, int64>, int64>(TEXT("currencies"), &Currencies, Serializer);
	Serializer->WriteValue(TEXT("empty"), bEmpty);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FArrayOfCurrencyProperty>, FArrayOfCurrencyProperty>(TEXT("currencyProperties"), &CurrencyProperties, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("currencyContentIds"), CurrencyContentIds, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("applyVipBonus"), &bApplyVipBonus, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("itemContentIds"), ItemContentIds, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UItemUpdateRequestBody*>, UItemUpdateRequestBody*>(TEXT("updateItems"), &UpdateItems, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UItemCreateRequestBody*>, UItemCreateRequestBody*>(TEXT("newItems"), &NewItems, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("transaction"), &Transaction, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UItemDeleteRequestBody*>, UItemDeleteRequestBody*>(TEXT("deleteItems"), &DeleteItems, Serializer);
}

void UInventoryUpdateRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TMap<FString, int64>, int64>(TEXT("currencies"), &Currencies, Serializer);
	Serializer->WriteValue(TEXT("empty"), bEmpty);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FArrayOfCurrencyProperty>, FArrayOfCurrencyProperty>(TEXT("currencyProperties"), &CurrencyProperties, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("currencyContentIds"), CurrencyContentIds, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("applyVipBonus"), &bApplyVipBonus, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("itemContentIds"), ItemContentIds, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UItemUpdateRequestBody*>, UItemUpdateRequestBody*>(TEXT("updateItems"), &UpdateItems, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UItemCreateRequestBody*>, UItemCreateRequestBody*>(TEXT("newItems"), &NewItems, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("transaction"), &Transaction, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UItemDeleteRequestBody*>, UItemDeleteRequestBody*>(TEXT("deleteItems"), &DeleteItems, Serializer);		
}

void UInventoryUpdateRequestBody ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<TMap<FString, int64>, int64>("currencies", Bag, Currencies, OuterOwner);
	bEmpty = Bag->GetBoolField(TEXT("empty"));
	UBeamJsonUtils::DeserializeOptional<TMap<FString, FArrayOfCurrencyProperty>, FArrayOfCurrencyProperty>("currencyProperties", Bag, CurrencyProperties, OuterOwner);
	UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("currencyContentIds")), CurrencyContentIds, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<bool>("applyVipBonus", Bag, bApplyVipBonus, OuterOwner);
	UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("itemContentIds")), ItemContentIds, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UItemUpdateRequestBody*>, UItemUpdateRequestBody*>("updateItems", Bag, UpdateItems, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UItemCreateRequestBody*>, UItemCreateRequestBody*>("newItems", Bag, NewItems, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("transaction", Bag, Transaction, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UItemDeleteRequestBody*>, UItemDeleteRequestBody*>("deleteItems", Bag, DeleteItems, OuterOwner);
}