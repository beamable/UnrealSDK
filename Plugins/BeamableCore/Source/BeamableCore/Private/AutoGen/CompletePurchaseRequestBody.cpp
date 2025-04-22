
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
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("txid")), Txid);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("receipt")), Receipt);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("priceInLocalCurrency")), PriceInLocalCurrency);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("isoCurrencySymbol")), IsoCurrencySymbol);
}



