
#include "BeamableCore/Public/AutoGen/ProductView.h"

#include "Misc/DefaultValueHelper.h"



void UProductView::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("localizedPrice"), LocalizedPrice, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("sku"), Sku, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("description"), Description, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("isoCurrencyCode"), IsoCurrencyCode, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("localizedPriceString"), LocalizedPriceString, Serializer);
}

void UProductView::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("localizedPrice"), LocalizedPrice, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("sku"), Sku, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("description"), Description, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("isoCurrencyCode"), IsoCurrencyCode, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("localizedPriceString"), LocalizedPriceString, Serializer);		
}

void UProductView::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("localizedPrice"), Bag, LocalizedPrice);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("sku"), Bag, Sku);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("description"), Bag, Description);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("isoCurrencyCode"), Bag, IsoCurrencyCode);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("localizedPriceString"), Bag, LocalizedPriceString);
}



