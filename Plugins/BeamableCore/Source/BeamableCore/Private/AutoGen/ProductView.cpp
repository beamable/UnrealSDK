
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
	LocalizedPrice = Bag->GetNumberField(TEXT("localizedPrice"));
	Sku = Bag->GetStringField(TEXT("sku"));
	Description = Bag->GetStringField(TEXT("description"));
	IsoCurrencyCode = Bag->GetStringField(TEXT("isoCurrencyCode"));
	LocalizedPriceString = Bag->GetStringField(TEXT("localizedPriceString"));
}



