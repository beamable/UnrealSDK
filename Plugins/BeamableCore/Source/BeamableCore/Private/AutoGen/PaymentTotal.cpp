
#include "BeamableCore/Public/AutoGen/PaymentTotal.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UPaymentTotal::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("totalRevenue"), TotalRevenue);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("currencyCode"), &CurrencyCode, Serializer);
}

void UPaymentTotal::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("totalRevenue"), TotalRevenue);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("currencyCode"), &CurrencyCode, Serializer);		
}

void UPaymentTotal::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("totalRevenue")), TotalRevenue);
	UBeamJsonUtils::DeserializeOptional<FString>("currencyCode", Bag, CurrencyCode, OuterOwner);
}



