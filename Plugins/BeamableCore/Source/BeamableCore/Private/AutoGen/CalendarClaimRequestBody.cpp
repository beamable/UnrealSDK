
#include "BeamableCore/Public/AutoGen/CalendarClaimRequestBody.h"





void UCalendarClaimRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("id"), Id);
}

void UCalendarClaimRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("id"), Id);		
}

void UCalendarClaimRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Id = Bag->GetStringField(TEXT("id"));
}



