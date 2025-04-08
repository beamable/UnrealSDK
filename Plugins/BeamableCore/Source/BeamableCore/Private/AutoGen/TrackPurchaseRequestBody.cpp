
#include "BeamableCore/Public/AutoGen/TrackPurchaseRequestBody.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UTrackPurchaseRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("priceInLocalCurrency"), PriceInLocalCurrency);
	Serializer->WriteValue(TEXT("skuName"), SkuName);
	Serializer->WriteValue(TEXT("skuProductId"), SkuProductId);
	Serializer->WriteValue(TEXT("store"), Store);
	Serializer->WriteValue(TEXT("purchaseId"), PurchaseId);
	Serializer->WriteValue(TEXT("isoCurrencySymbol"), IsoCurrencySymbol);
	UBeamJsonUtils::SerializeArray<UItemCreateRequestBody*>(TEXT("obtainItems"), ObtainItems, Serializer);
	UBeamJsonUtils::SerializeArray<UCurrencyChange*>(TEXT("obtainCurrency"), ObtainCurrency, Serializer);
}

void UTrackPurchaseRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("priceInLocalCurrency"), PriceInLocalCurrency);
	Serializer->WriteValue(TEXT("skuName"), SkuName);
	Serializer->WriteValue(TEXT("skuProductId"), SkuProductId);
	Serializer->WriteValue(TEXT("store"), Store);
	Serializer->WriteValue(TEXT("purchaseId"), PurchaseId);
	Serializer->WriteValue(TEXT("isoCurrencySymbol"), IsoCurrencySymbol);
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



