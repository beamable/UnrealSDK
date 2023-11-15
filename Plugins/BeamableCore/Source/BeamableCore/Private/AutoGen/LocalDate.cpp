
#include "BeamableCore/Public/AutoGen/LocalDate.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void ULocalDate::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("leapYear"), bLeapYear);
	Serializer->WriteValue(TEXT("dayOfYear"), DayOfYear);
	UBeamJsonUtils::SerializeUObject<UIsoChronology*>("chronology", Chronology, Serializer);
	Serializer->WriteValue(TEXT("dayOfWeek"), DayOfWeek);
	Serializer->WriteValue(TEXT("monthValue"), MonthValue);
	Serializer->WriteValue(TEXT("dayOfMonth"), DayOfMonth);
	Serializer->WriteValue(TEXT("year"), Year);
	UBeamJsonUtils::SerializeUObject<UEra*>("era", Era, Serializer);
	Serializer->WriteValue(TEXT("month"), Month);
}

void ULocalDate::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("leapYear"), bLeapYear);
	Serializer->WriteValue(TEXT("dayOfYear"), DayOfYear);
	UBeamJsonUtils::SerializeUObject<UIsoChronology*>("chronology", Chronology, Serializer);
	Serializer->WriteValue(TEXT("dayOfWeek"), DayOfWeek);
	Serializer->WriteValue(TEXT("monthValue"), MonthValue);
	Serializer->WriteValue(TEXT("dayOfMonth"), DayOfMonth);
	Serializer->WriteValue(TEXT("year"), Year);
	UBeamJsonUtils::SerializeUObject<UEra*>("era", Era, Serializer);
	Serializer->WriteValue(TEXT("month"), Month);		
}

void ULocalDate::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	bLeapYear = Bag->GetBoolField(TEXT("leapYear"));
	DayOfYear = Bag->GetIntegerField(TEXT("dayOfYear"));
	UBeamJsonUtils::DeserializeUObject<UIsoChronology*>("chronology", Bag, Chronology, OuterOwner);
	DayOfWeek = Bag->GetStringField(TEXT("dayOfWeek"));
	MonthValue = Bag->GetIntegerField(TEXT("monthValue"));
	DayOfMonth = Bag->GetIntegerField(TEXT("dayOfMonth"));
	Year = Bag->GetIntegerField(TEXT("year"));
	UBeamJsonUtils::DeserializeUObject<UEra*>("era", Bag, Era, OuterOwner);
	Month = Bag->GetStringField(TEXT("month"));
}



