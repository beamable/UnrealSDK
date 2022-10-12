
#include "AutoGen/SteamOrderInfoResponse.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"

void USteamOrderInfoResponse ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("usstate"), Usstate);
	UBeamJsonUtils::SerializeArray<USteamOrderInfoItem*>(TEXT("items"), Items, Serializer);
	Serializer->WriteValue(TEXT("country"), Country);
	Serializer->WriteValue(TEXT("timecreated"), Timecreated);
	Serializer->WriteValue(TEXT("transid"), Transid);
	Serializer->WriteValue(TEXT("status"), Status);
	Serializer->WriteValue(TEXT("orderid"), Orderid);
	Serializer->WriteValue(TEXT("steamid"), Steamid);
	Serializer->WriteValue(TEXT("currency"), Currency);
	Serializer->WriteValue(TEXT("time"), Time);
}

void USteamOrderInfoResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("usstate"), Usstate);
	UBeamJsonUtils::SerializeArray<USteamOrderInfoItem*>(TEXT("items"), Items, Serializer);
	Serializer->WriteValue(TEXT("country"), Country);
	Serializer->WriteValue(TEXT("timecreated"), Timecreated);
	Serializer->WriteValue(TEXT("transid"), Transid);
	Serializer->WriteValue(TEXT("status"), Status);
	Serializer->WriteValue(TEXT("orderid"), Orderid);
	Serializer->WriteValue(TEXT("steamid"), Steamid);
	Serializer->WriteValue(TEXT("currency"), Currency);
	Serializer->WriteValue(TEXT("time"), Time);		
}

void USteamOrderInfoResponse ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Usstate = Bag->GetStringField(TEXT("usstate"));
	UBeamJsonUtils::DeserializeArray<USteamOrderInfoItem*>(Bag->GetArrayField(TEXT("items")), Items, OuterOwner);
	Country = Bag->GetStringField(TEXT("country"));
	Timecreated = Bag->GetStringField(TEXT("timecreated"));
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("transid")), Transid);
	Status = Bag->GetStringField(TEXT("status"));
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("orderid")), Orderid);
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("steamid")), Steamid);
	Currency = Bag->GetStringField(TEXT("currency"));
	Time = Bag->GetStringField(TEXT("time"));
}