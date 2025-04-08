
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
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("to")), To);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("price")), Price);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("priceLocalized")), PriceLocalized);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("priceLocalizedString")), PriceLocalizedString);
}



