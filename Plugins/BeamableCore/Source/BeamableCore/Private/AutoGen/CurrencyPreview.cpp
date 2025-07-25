
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
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("id"), Bag, Id);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("amount"), Bag, Amount);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("originalAmount"), Bag, OriginalAmount);
}



