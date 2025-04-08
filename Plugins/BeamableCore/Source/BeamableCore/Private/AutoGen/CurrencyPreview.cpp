
#include "BeamableCore/Public/AutoGen/CurrencyPreview.h"

#include "Misc/DefaultValueHelper.h"



void UCurrencyPreview::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("id"), Id);
	Serializer->WriteValue(TEXT("amount"), Amount);
	Serializer->WriteValue(TEXT("originalAmount"), OriginalAmount);
}

void UCurrencyPreview::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("id"), Id);
	Serializer->WriteValue(TEXT("amount"), Amount);
	Serializer->WriteValue(TEXT("originalAmount"), OriginalAmount);		
}

void UCurrencyPreview::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("id")), Id);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("amount")), Amount);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("originalAmount")), OriginalAmount);
}



