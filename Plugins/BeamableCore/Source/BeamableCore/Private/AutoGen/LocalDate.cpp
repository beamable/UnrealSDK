
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
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("leapYear")), bLeapYear);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("dayOfYear")), DayOfYear);
	UBeamJsonUtils::DeserializeUObject<UIsoChronology*>("chronology", Bag, Chronology, OuterOwner);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("dayOfWeek")), DayOfWeek);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("monthValue")), MonthValue);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("dayOfMonth")), DayOfMonth);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("year")), Year);
	UBeamJsonUtils::DeserializeUObject<UEra*>("era", Bag, Era, OuterOwner);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("month")), Month);
}



