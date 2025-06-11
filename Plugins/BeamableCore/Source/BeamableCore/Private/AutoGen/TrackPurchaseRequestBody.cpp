
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
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("priceInLocalCurrency")), PriceInLocalCurrency);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("skuName")), SkuName);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("skuProductId")), SkuProductId);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("store")), Store);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("purchaseId")), PurchaseId);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("isoCurrencySymbol")), IsoCurrencySymbol);
	UBeamJsonUtils::DeserializeArray<UItemCreateRequestBody*>(Bag->GetArrayField(TEXT("obtainItems")), ObtainItems, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UCurrencyChange*>(Bag->GetArrayField(TEXT("obtainCurrency")), ObtainCurrency, OuterOwner);
}



