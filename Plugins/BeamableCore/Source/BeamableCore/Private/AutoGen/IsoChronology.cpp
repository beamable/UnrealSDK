
#include "BeamableCore/Public/AutoGen/IsoChronology.h"





void UIsoChronology::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("calendarType"), CalendarType);
	Serializer->WriteValue(TEXT("id"), Id);
}

void UIsoChronology::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("calendarType"), CalendarType);
	Serializer->WriteValue(TEXT("id"), Id);		
}

void UIsoChronology::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	CalendarType = Bag->GetStringField(TEXT("calendarType"));
	Id = Bag->GetStringField(TEXT("id"));
}



