
#include "BeamableCore/Public/AutoGen/ProductView.h"

#include "Misc/DefaultValueHelper.h"



void UProductView::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("localizedPrice"), LocalizedPrice);
	Serializer->WriteValue(TEXT("sku"), Sku);
	Serializer->WriteValue(TEXT("description"), Description);
	Serializer->WriteValue(TEXT("isoCurrencyCode"), IsoCurrencyCode);
	Serializer->WriteValue(TEXT("localizedPriceString"), LocalizedPriceString);
}

void UProductView::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("localizedPrice"), LocalizedPrice);
	Serializer->WriteValue(TEXT("sku"), Sku);
	Serializer->WriteValue(TEXT("description"), Description);
	Serializer->WriteValue(TEXT("isoCurrencyCode"), IsoCurrencyCode);
	Serializer->WriteValue(TEXT("localizedPriceString"), LocalizedPriceString);		
}

void UProductView::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("localizedPrice")), LocalizedPrice);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("sku")), Sku);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("description")), Description);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("isoCurrencyCode")), IsoCurrencyCode);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("localizedPriceString")), LocalizedPriceString);
}



