
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
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("vat")), Vat);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("amount")), Amount);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("itemid")), Itemid);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("qty")), Qty);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("itemstatus")), Itemstatus);
}



