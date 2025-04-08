
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



