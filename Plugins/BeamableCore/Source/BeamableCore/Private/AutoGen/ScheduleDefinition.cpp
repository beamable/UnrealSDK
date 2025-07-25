
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
	UBeamJsonUtils::DeserializeArray<FString>(TEXT("dayOfWeek"), Bag, DayOfWeek, OuterOwner);
	UBeamJsonUtils::DeserializeArray<FString>(TEXT("minute"), Bag, Minute, OuterOwner);
	UBeamJsonUtils::DeserializeArray<FString>(TEXT("dayOfMonth"), Bag, DayOfMonth, OuterOwner);
	UBeamJsonUtils::DeserializeArray<FString>(TEXT("year"), Bag, Year, OuterOwner);
	UBeamJsonUtils::DeserializeArray<FString>(TEXT("hour"), Bag, Hour, OuterOwner);
	UBeamJsonUtils::DeserializeArray<FString>(TEXT("second"), Bag, Second, OuterOwner);
	UBeamJsonUtils::DeserializeArray<FString>(TEXT("month"), Bag, Month, OuterOwner);
}



