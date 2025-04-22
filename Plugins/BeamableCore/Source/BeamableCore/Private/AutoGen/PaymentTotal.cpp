
#include "BeamableCore/Public/AutoGen/PaymentTotal.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UPaymentTotal::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("totalRevenue"), TotalRevenue, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("currencyCode"), &CurrencyCode, Serializer);
}

void UPaymentTotal::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("totalRevenue"), TotalRevenue, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("currencyCode"), &CurrencyCode, Serializer);		
}

void UPaymentTotal::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("totalRevenue")), TotalRevenue);
	UBeamJsonUtils::DeserializeOptional<FString>("currencyCode", Bag, CurrencyCode, OuterOwner);
}



