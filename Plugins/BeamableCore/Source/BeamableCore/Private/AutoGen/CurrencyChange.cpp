
#include "BeamableCore/Public/AutoGen/CurrencyChange.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UCurrencyChange::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("symbol"), Symbol);
	Serializer->WriteValue(TEXT("amount"), Amount);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("originalAmount"), &OriginalAmount, Serializer);
}

void UCurrencyChange::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("symbol"), Symbol);
	Serializer->WriteValue(TEXT("amount"), Amount);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("originalAmount"), &OriginalAmount, Serializer);		
}

void UCurrencyChange::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("symbol")), Symbol);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("amount")), Amount);
	UBeamJsonUtils::DeserializeOptional<int64>("originalAmount", Bag, OriginalAmount, OuterOwner);
}



