
#include "AutoGen/TrackPurchaseRequestBody.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"

void UTrackPurchaseRequestBody ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("priceInLocalCurrency"), PriceInLocalCurrency);
	Serializer->WriteValue(TEXT("skuName"), SkuName);
	Serializer->WriteValue(TEXT("skuProductId"), SkuProductId);
	Serializer->WriteValue(TEXT("store"), Store);
	UBeamJsonUtils::SerializeArray<UItemCreateRequestBody*>(TEXT("obtainItems"), ObtainItems, Serializer);
	UBeamJsonUtils::SerializeArray<UCurrencyChange*>(TEXT("obtainCurrency"), ObtainCurrency, Serializer);
	Serializer->WriteValue(TEXT("purchaseId"), PurchaseId);
	Serializer->WriteValue(TEXT("isoCurrencySymbol"), IsoCurrencySymbol);
}

void UTrackPurchaseRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("priceInLocalCurrency"), PriceInLocalCurrency);
	Serializer->WriteValue(TEXT("skuName"), SkuName);
	Serializer->WriteValue(TEXT("skuProductId"), SkuProductId);
	Serializer->WriteValue(TEXT("store"), Store);
	UBeamJsonUtils::SerializeArray<UItemCreateRequestBody*>(TEXT("obtainItems"), ObtainItems, Serializer);
	UBeamJsonUtils::SerializeArray<UCurrencyChange*>(TEXT("obtainCurrency"), ObtainCurrency, Serializer);
	Serializer->WriteValue(TEXT("purchaseId"), PurchaseId);
	Serializer->WriteValue(TEXT("isoCurrencySymbol"), IsoCurrencySymbol);		
}

void UTrackPurchaseRequestBody ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	PriceInLocalCurrency = Bag->GetNumberField(TEXT("priceInLocalCurrency"));
	SkuName = Bag->GetStringField(TEXT("skuName"));
	SkuProductId = Bag->GetStringField(TEXT("skuProductId"));
	Store = Bag->GetStringField(TEXT("store"));
	UBeamJsonUtils::DeserializeArray<UItemCreateRequestBody*>(Bag->GetArrayField(TEXT("obtainItems")), ObtainItems, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UCurrencyChange*>(Bag->GetArrayField(TEXT("obtainCurrency")), ObtainCurrency, OuterOwner);
	PurchaseId = Bag->GetStringField(TEXT("purchaseId"));
	IsoCurrencySymbol = Bag->GetStringField(TEXT("isoCurrencySymbol"));
}