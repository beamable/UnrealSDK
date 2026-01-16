
#include "BeamableCore/Public/AutoGen/TransactionDetails.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UTransactionDetails::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("priceCents"), PriceCents, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("sku"), Sku, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("providerProductId"), ProviderProductId, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("quantity"), &Quantity, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("name"), &Name, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("reference"), &Reference, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("gamePlace"), &GamePlace, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("category"), &Category, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("subcategory"), &Subcategory, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("localCurrency"), &LocalCurrency, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("localPrice"), &LocalPrice, Serializer);
}

void UTransactionDetails::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("priceCents"), PriceCents, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("sku"), Sku, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("providerProductId"), ProviderProductId, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("quantity"), &Quantity, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("name"), &Name, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("reference"), &Reference, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("gamePlace"), &GamePlace, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("category"), &Category, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("subcategory"), &Subcategory, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("localCurrency"), &LocalCurrency, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("localPrice"), &LocalPrice, Serializer);		
}

void UTransactionDetails::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("priceCents"), Bag, PriceCents);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("sku"), Bag, Sku);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("providerProductId"), Bag, ProviderProductId);
	UBeamJsonUtils::DeserializeOptional<int32>("quantity", Bag, Quantity, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("name", Bag, Name, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("reference", Bag, Reference, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("gamePlace", Bag, GamePlace, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("category", Bag, Category, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("subcategory", Bag, Subcategory, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("localCurrency", Bag, LocalCurrency, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("localPrice", Bag, LocalPrice, OuterOwner);
}



