
#include "BeamableCore/Public/AutoGen/CompletePurchaseRequestBody.h"

#include "Misc/DefaultValueHelper.h"



void UCompletePurchaseRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("txid"), Txid, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("receipt"), Receipt, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("priceInLocalCurrency"), PriceInLocalCurrency, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("isoCurrencySymbol"), IsoCurrencySymbol, Serializer);
}

void UCompletePurchaseRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("txid"), Txid, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("receipt"), Receipt, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("priceInLocalCurrency"), PriceInLocalCurrency, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("isoCurrencySymbol"), IsoCurrencySymbol, Serializer);		
}

void UCompletePurchaseRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("txid"), Bag, Txid);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("receipt"), Bag, Receipt);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("priceInLocalCurrency"), Bag, PriceInLocalCurrency);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("isoCurrencySymbol"), Bag, IsoCurrencySymbol);
}



