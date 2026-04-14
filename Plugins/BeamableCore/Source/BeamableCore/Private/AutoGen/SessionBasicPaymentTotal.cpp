
#include "BeamableCore/Public/AutoGen/SessionBasicPaymentTotal.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void USessionBasicPaymentTotal::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("totalRevenue"), TotalRevenue, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("currencyCode"), &CurrencyCode, Serializer);
}

void USessionBasicPaymentTotal::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("totalRevenue"), TotalRevenue, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("currencyCode"), &CurrencyCode, Serializer);		
}

void USessionBasicPaymentTotal::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("totalRevenue"), Bag, TotalRevenue);
	UBeamJsonUtils::DeserializeOptional<FString>("currencyCode", Bag, CurrencyCode, OuterOwner);
}



