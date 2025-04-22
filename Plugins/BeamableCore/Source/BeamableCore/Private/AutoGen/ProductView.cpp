
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
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("localizedPrice")), LocalizedPrice);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("sku")), Sku);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("description")), Description);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("isoCurrencyCode")), IsoCurrencyCode);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("localizedPriceString")), LocalizedPriceString);
}



