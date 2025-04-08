
#include "BeamableCore/Public/AutoGen/CompletePurchaseRequestBody.h"

#include "Misc/DefaultValueHelper.h"



void UCompletePurchaseRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("txid"), Txid);
	Serializer->WriteValue(TEXT("receipt"), Receipt);
	Serializer->WriteValue(TEXT("priceInLocalCurrency"), PriceInLocalCurrency);
	Serializer->WriteValue(TEXT("isoCurrencySymbol"), IsoCurrencySymbol);
}

void UCompletePurchaseRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("txid"), Txid);
	Serializer->WriteValue(TEXT("receipt"), Receipt);
	Serializer->WriteValue(TEXT("priceInLocalCurrency"), PriceInLocalCurrency);
	Serializer->WriteValue(TEXT("isoCurrencySymbol"), IsoCurrencySymbol);		
}

void UCompletePurchaseRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("txid")), Txid);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("receipt")), Receipt);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("priceInLocalCurrency")), PriceInLocalCurrency);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("isoCurrencySymbol")), IsoCurrencySymbol);
}



