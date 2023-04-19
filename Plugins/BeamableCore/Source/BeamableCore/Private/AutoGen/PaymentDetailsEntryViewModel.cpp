
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
	Reference = Bag->GetStringField(TEXT("reference"));
	Name = Bag->GetStringField(TEXT("name"));
	Quantity = Bag->GetIntegerField(TEXT("quantity"));
	Sku = Bag->GetStringField(TEXT("sku"));
	Price = Bag->GetIntegerField(TEXT("price"));
	Gameplace = Bag->GetStringField(TEXT("gameplace"));
	ProviderProductId = Bag->GetStringField(TEXT("providerProductId"));
	UBeamJsonUtils::DeserializeOptional<FString>("subcategory", Bag, Subcategory, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("localPrice", Bag, LocalPrice, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("category", Bag, Category, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("localCurrency", Bag, LocalCurrency, OuterOwner);
}



