
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
	Id = Bag->GetStringField(TEXT("id"));
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("amount")), Amount);
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("originalAmount")), OriginalAmount);
}



