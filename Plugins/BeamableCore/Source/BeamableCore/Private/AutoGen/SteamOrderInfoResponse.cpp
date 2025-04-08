
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
	Serializer->WriteValue(TEXT("usstate"), Usstate);
	Serializer->WriteValue(TEXT("country"), Country);
	Serializer->WriteValue(TEXT("timecreated"), Timecreated);
	Serializer->WriteValue(TEXT("transid"), Transid);
	Serializer->WriteValue(TEXT("status"), Status);
	Serializer->WriteValue(TEXT("orderid"), Orderid);
	Serializer->WriteValue(TEXT("steamid"), Steamid);
	Serializer->WriteValue(TEXT("currency"), Currency);
	Serializer->WriteValue(TEXT("time"), Time);
	UBeamJsonUtils::SerializeArray<USteamOrderInfoItem*>(TEXT("items"), Items, Serializer);
}

void USteamOrderInfoResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("usstate"), Usstate);
	Serializer->WriteValue(TEXT("country"), Country);
	Serializer->WriteValue(TEXT("timecreated"), Timecreated);
	Serializer->WriteValue(TEXT("transid"), Transid);
	Serializer->WriteValue(TEXT("status"), Status);
	Serializer->WriteValue(TEXT("orderid"), Orderid);
	Serializer->WriteValue(TEXT("steamid"), Steamid);
	Serializer->WriteValue(TEXT("currency"), Currency);
	Serializer->WriteValue(TEXT("time"), Time);
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



