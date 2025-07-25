
#include "BeamableCore/Public/AutoGen/LocalDate.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void ULocalDate::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("leapYear"), bLeapYear, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("dayOfYear"), DayOfYear, Serializer);
	UBeamJsonUtils::SerializeUObject<UIsoChronology*>("chronology", Chronology, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("dayOfWeek"), DayOfWeek, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("monthValue"), MonthValue, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("dayOfMonth"), DayOfMonth, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("year"), Year, Serializer);
	UBeamJsonUtils::SerializeUObject<UEra*>("era", Era, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("month"), Month, Serializer);
}

void ULocalDate::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("leapYear"), bLeapYear, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("dayOfYear"), DayOfYear, Serializer);
	UBeamJsonUtils::SerializeUObject<UIsoChronology*>("chronology", Chronology, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("dayOfWeek"), DayOfWeek, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("monthValue"), MonthValue, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("dayOfMonth"), DayOfMonth, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("year"), Year, Serializer);
	UBeamJsonUtils::SerializeUObject<UEra*>("era", Era, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("month"), Month, Serializer);		
}

void ULocalDate::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("leapYear"), Bag, bLeapYear);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("dayOfYear"), Bag, DayOfYear);
	UBeamJsonUtils::DeserializeUObject<UIsoChronology*>("chronology", Bag, Chronology, OuterOwner);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("dayOfWeek"), Bag, DayOfWeek);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("monthValue"), Bag, MonthValue);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("dayOfMonth"), Bag, DayOfMonth);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("year"), Bag, Year);
	UBeamJsonUtils::DeserializeUObject<UEra*>("era", Bag, Era, OuterOwner);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("month"), Bag, Month);
}



