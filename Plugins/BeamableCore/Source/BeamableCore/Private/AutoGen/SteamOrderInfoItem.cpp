
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
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("vat")), Vat);
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("amount")), Amount);
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("itemid")), Itemid);
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("qty")), Qty);
	Itemstatus = Bag->GetStringField(TEXT("itemstatus"));
}



