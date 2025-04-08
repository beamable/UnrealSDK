
#include "BeamableCore/Public/AutoGen/PaymentDetailsEntryViewModel.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UPaymentDetailsEntryViewModel::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("reference"), Reference);
	Serializer->WriteValue(TEXT("name"), Name);
	Serializer->WriteValue(TEXT("quantity"), Quantity);
	Serializer->WriteValue(TEXT("sku"), Sku);
	Serializer->WriteValue(TEXT("price"), Price);
	Serializer->WriteValue(TEXT("gameplace"), Gameplace);
	Serializer->WriteValue(TEXT("providerProductId"), ProviderProductId);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("subcategory"), &Subcategory, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("localPrice"), &LocalPrice, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("category"), &Category, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("localCurrency"), &LocalCurrency, Serializer);
}

void UPaymentDetailsEntryViewModel::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("reference"), Reference);
	Serializer->WriteValue(TEXT("name"), Name);
	Serializer->WriteValue(TEXT("quantity"), Quantity);
	Serializer->WriteValue(TEXT("sku"), Sku);
	Serializer->WriteValue(TEXT("price"), Price);
	Serializer->WriteValue(TEXT("gameplace"), Gameplace);
	Serializer->WriteValue(TEXT("providerProductId"), ProviderProductId);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("subcategory"), &Subcategory, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("localPrice"), &LocalPrice, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("category"), &Category, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("localCurrency"), &LocalCurrency, Serializer);		
}

void UPaymentDetailsEntryViewModel::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("reference")), Reference);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("name")), Name);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("quantity")), Quantity);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("sku")), Sku);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("price")), Price);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("gameplace")), Gameplace);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("providerProductId")), ProviderProductId);
	UBeamJsonUtils::DeserializeOptional<FString>("subcategory", Bag, Subcategory, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("localPrice", Bag, LocalPrice, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("category", Bag, Category, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("localCurrency", Bag, LocalCurrency, OuterOwner);
}



