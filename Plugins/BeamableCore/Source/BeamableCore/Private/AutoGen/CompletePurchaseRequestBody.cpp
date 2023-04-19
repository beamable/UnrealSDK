
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
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("txid")), Txid);
	Receipt = Bag->GetStringField(TEXT("receipt"));
	PriceInLocalCurrency = Bag->GetStringField(TEXT("priceInLocalCurrency"));
	IsoCurrencySymbol = Bag->GetStringField(TEXT("isoCurrencySymbol"));
}



