
#include "BeamableCore/Public/AutoGen/LocalizedPrice.h"

#include "Misc/DefaultValueHelper.h"



void ULocalizedPrice::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("to"), To);
	Serializer->WriteValue(TEXT("price"), Price);
	Serializer->WriteValue(TEXT("priceLocalized"), PriceLocalized);
	Serializer->WriteValue(TEXT("priceLocalizedString"), PriceLocalizedString);
}

void ULocalizedPrice::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("to"), To);
	Serializer->WriteValue(TEXT("price"), Price);
	Serializer->WriteValue(TEXT("priceLocalized"), PriceLocalized);
	Serializer->WriteValue(TEXT("priceLocalizedString"), PriceLocalizedString);		
}

void ULocalizedPrice::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("to")), To);
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("price")), Price);
	PriceLocalized = Bag->GetNumberField(TEXT("priceLocalized"));
	PriceLocalizedString = Bag->GetStringField(TEXT("priceLocalizedString"));
}



