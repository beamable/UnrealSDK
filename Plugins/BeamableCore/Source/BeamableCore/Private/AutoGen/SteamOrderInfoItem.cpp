
#include "BeamableCore/Public/AutoGen/SteamOrderInfoItem.h"

#include "Misc/DefaultValueHelper.h"



void USteamOrderInfoItem::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("vat"), Vat);
	Serializer->WriteValue(TEXT("amount"), Amount);
	Serializer->WriteValue(TEXT("itemid"), Itemid);
	Serializer->WriteValue(TEXT("qty"), Qty);
	Serializer->WriteValue(TEXT("itemstatus"), Itemstatus);
}

void USteamOrderInfoItem::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("vat"), Vat);
	Serializer->WriteValue(TEXT("amount"), Amount);
	Serializer->WriteValue(TEXT("itemid"), Itemid);
	Serializer->WriteValue(TEXT("qty"), Qty);
	Serializer->WriteValue(TEXT("itemstatus"), Itemstatus);		
}

void USteamOrderInfoItem::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("vat")), Vat);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("amount")), Amount);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("itemid")), Itemid);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("qty")), Qty);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("itemstatus")), Itemstatus);
}



