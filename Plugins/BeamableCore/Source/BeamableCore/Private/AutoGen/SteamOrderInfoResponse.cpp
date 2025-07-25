
#include "BeamableCore/Public/AutoGen/SteamOrderInfoResponse.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"


void USteamOrderInfoResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void USteamOrderInfoResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("usstate"), Usstate, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("country"), Country, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("timecreated"), Timecreated, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("transid"), Transid, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("status"), Status, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("orderid"), Orderid, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("steamid"), Steamid, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("currency"), Currency, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("time"), Time, Serializer);
	UBeamJsonUtils::SerializeArray<USteamOrderInfoItem*>(TEXT("items"), Items, Serializer);
}

void USteamOrderInfoResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("usstate"), Usstate, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("country"), Country, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("timecreated"), Timecreated, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("transid"), Transid, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("status"), Status, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("orderid"), Orderid, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("steamid"), Steamid, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("currency"), Currency, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("time"), Time, Serializer);
	UBeamJsonUtils::SerializeArray<USteamOrderInfoItem*>(TEXT("items"), Items, Serializer);		
}

void USteamOrderInfoResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("usstate"), Bag, Usstate);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("country"), Bag, Country);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("timecreated"), Bag, Timecreated);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("transid"), Bag, Transid);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("status"), Bag, Status);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("orderid"), Bag, Orderid);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("steamid"), Bag, Steamid);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("currency"), Bag, Currency);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("time"), Bag, Time);
	UBeamJsonUtils::DeserializeArray<USteamOrderInfoItem*>(TEXT("items"), Bag, Items, OuterOwner);
}



