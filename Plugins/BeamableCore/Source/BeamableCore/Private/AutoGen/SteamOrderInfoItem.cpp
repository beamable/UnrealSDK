
#include "BeamableCore/Public/AutoGen/SteamOrderInfoItem.h"

#include "Misc/DefaultValueHelper.h"



void USteamOrderInfoItem::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("vat"), Vat, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("amount"), Amount, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("itemid"), Itemid, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("qty"), Qty, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("itemstatus"), Itemstatus, Serializer);
}

void USteamOrderInfoItem::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("vat"), Vat, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("amount"), Amount, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("itemid"), Itemid, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("qty"), Qty, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("itemstatus"), Itemstatus, Serializer);		
}

void USteamOrderInfoItem::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("vat"), Bag, Vat);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("amount"), Bag, Amount);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("itemid"), Bag, Itemid);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("qty"), Bag, Qty);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("itemstatus"), Bag, Itemstatus);
}



