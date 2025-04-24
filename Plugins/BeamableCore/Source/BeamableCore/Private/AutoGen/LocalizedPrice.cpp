
#include "BeamableCore/Public/AutoGen/LocalizedPrice.h"

#include "Misc/DefaultValueHelper.h"



void ULocalizedPrice::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("to"), To, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("price"), Price, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("priceLocalized"), PriceLocalized, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("priceLocalizedString"), PriceLocalizedString, Serializer);
}

void ULocalizedPrice::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("to"), To, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("price"), Price, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("priceLocalized"), PriceLocalized, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("priceLocalizedString"), PriceLocalizedString, Serializer);		
}

void ULocalizedPrice::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("to")), To);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("price")), Price);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("priceLocalized")), PriceLocalized);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("priceLocalizedString")), PriceLocalizedString);
}



