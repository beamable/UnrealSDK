
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
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("usstate")), Usstate);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("country")), Country);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("timecreated")), Timecreated);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("transid")), Transid);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("status")), Status);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("orderid")), Orderid);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("steamid")), Steamid);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("currency")), Currency);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("time")), Time);
	UBeamJsonUtils::DeserializeArray<USteamOrderInfoItem*>(Bag->GetArrayField(TEXT("items")), Items, OuterOwner);
}



