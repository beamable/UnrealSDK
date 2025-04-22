
#include "BeamableCore/Public/AutoGen/CurrencyPreview.h"

#include "Misc/DefaultValueHelper.h"



void UCurrencyPreview::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("amount"), Amount, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("originalAmount"), OriginalAmount, Serializer);
}

void UCurrencyPreview::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("amount"), Amount, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("originalAmount"), OriginalAmount, Serializer);		
}

void UCurrencyPreview::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("id")), Id);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("amount")), Amount);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("originalAmount")), OriginalAmount);
}



