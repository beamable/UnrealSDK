
#include "BeamableCore/Public/AutoGen/CalendarQueryResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UCalendarQueryResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UCalendarQueryResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UCalendarView*>(TEXT("calendars"), Calendars, Serializer);
}

void UCalendarQueryResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UCalendarView*>(TEXT("calendars"), Calendars, Serializer);		
}

void UCalendarQueryResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UCalendarView*>(Bag->GetArrayField(TEXT("calendars")), Calendars, OuterOwner);
}



