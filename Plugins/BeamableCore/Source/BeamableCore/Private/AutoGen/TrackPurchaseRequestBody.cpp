
#include "BeamableCore/Public/AutoGen/TrackPurchaseRequestBody.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UTrackPurchaseRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("priceInLocalCurrency"), PriceInLocalCurrency, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("skuName"), SkuName, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("skuProductId"), SkuProductId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("store"), Store, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("purchaseId"), PurchaseId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("isoCurrencySymbol"), IsoCurrencySymbol, Serializer);
	UBeamJsonUtils::SerializeArray<UItemCreateRequestBody*>(TEXT("obtainItems"), ObtainItems, Serializer);
	UBeamJsonUtils::SerializeArray<UCurrencyChange*>(TEXT("obtainCurrency"), ObtainCurrency, Serializer);
}

void UTrackPurchaseRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("priceInLocalCurrency"), PriceInLocalCurrency, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("skuName"), SkuName, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("skuProductId"), SkuProductId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("store"), Store, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("purchaseId"), PurchaseId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("isoCurrencySymbol"), IsoCurrencySymbol, Serializer);
	UBeamJsonUtils::SerializeArray<UItemCreateRequestBody*>(TEXT("obtainItems"), ObtainItems, Serializer);
	UBeamJsonUtils::SerializeArray<UCurrencyChange*>(TEXT("obtainCurrency"), ObtainCurrency, Serializer);		
}

void UTrackPurchaseRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("priceInLocalCurrency"), Bag, PriceInLocalCurrency);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("skuName"), Bag, SkuName);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("skuProductId"), Bag, SkuProductId);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("store"), Bag, Store);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("purchaseId"), Bag, PurchaseId);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("isoCurrencySymbol"), Bag, IsoCurrencySymbol);
	UBeamJsonUtils::DeserializeArray<UItemCreateRequestBody*>(TEXT("obtainItems"), Bag, ObtainItems, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UCurrencyChange*>(TEXT("obtainCurrency"), Bag, ObtainCurrency, OuterOwner);
}



