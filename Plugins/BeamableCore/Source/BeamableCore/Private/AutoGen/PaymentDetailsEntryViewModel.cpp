
#include "BeamableCore/Public/AutoGen/PaymentDetailsEntryViewModel.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UPaymentDetailsEntryViewModel::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("reference"), Reference, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("name"), Name, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("quantity"), Quantity, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("sku"), Sku, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("price"), Price, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("gameplace"), Gameplace, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("providerProductId"), ProviderProductId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("subcategory"), &Subcategory, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("localPrice"), &LocalPrice, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("category"), &Category, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("localCurrency"), &LocalCurrency, Serializer);
}

void UPaymentDetailsEntryViewModel::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("reference"), Reference, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("name"), Name, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("quantity"), Quantity, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("sku"), Sku, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("price"), Price, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("gameplace"), Gameplace, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("providerProductId"), ProviderProductId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("subcategory"), &Subcategory, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("localPrice"), &LocalPrice, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("category"), &Category, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("localCurrency"), &LocalCurrency, Serializer);		
}

void UPaymentDetailsEntryViewModel::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("reference"), Bag, Reference);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("name"), Bag, Name);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("quantity"), Bag, Quantity);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("sku"), Bag, Sku);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("price"), Bag, Price);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("gameplace"), Bag, Gameplace);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("providerProductId"), Bag, ProviderProductId);
	UBeamJsonUtils::DeserializeOptional<FString>("subcategory", Bag, Subcategory, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("localPrice", Bag, LocalPrice, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("category", Bag, Category, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("localCurrency", Bag, LocalCurrency, OuterOwner);
}



