
#include "BeamableCore/Public/AutoGen/ScheduleDefinition.h"
#include "Serialization/BeamJsonUtils.h"




void UScheduleDefinition::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<FString>(TEXT("dayOfWeek"), DayOfWeek, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("minute"), Minute, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("dayOfMonth"), DayOfMonth, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("year"), Year, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("hour"), Hour, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("second"), Second, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("month"), Month, Serializer);
}

void UScheduleDefinition::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<FString>(TEXT("dayOfWeek"), DayOfWeek, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("minute"), Minute, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("dayOfMonth"), DayOfMonth, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("year"), Year, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("hour"), Hour, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("second"), Second, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("month"), Month, Serializer);		
}

void UScheduleDefinition::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("dayOfWeek")), DayOfWeek, OuterOwner);
	UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("minute")), Minute, OuterOwner);
	UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("dayOfMonth")), DayOfMonth, OuterOwner);
	UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("year")), Year, OuterOwner);
	UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("hour")), Hour, OuterOwner);
	UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("second")), Second, OuterOwner);
	UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("month")), Month, OuterOwner);
}



