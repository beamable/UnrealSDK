
#include "AutoGen/Schedule.h"
#include "Serialization/BeamJsonUtils.h"


void USchedule ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("description"), &Description, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("crons"), &Crons, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("activeTo"), &ActiveTo, Serializer);
	Serializer->WriteValue(TEXT("activeFrom"), ActiveFrom);
	UBeamJsonUtils::SerializeOptional<TArray<UScheduleDefinition*>, UScheduleDefinition*>(TEXT("definitions"), &Definitions, Serializer);
}

void USchedule::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("description"), &Description, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("crons"), &Crons, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("activeTo"), &ActiveTo, Serializer);
	Serializer->WriteValue(TEXT("activeFrom"), ActiveFrom);
	UBeamJsonUtils::SerializeOptional<TArray<UScheduleDefinition*>, UScheduleDefinition*>(TEXT("definitions"), &Definitions, Serializer);		
}

void USchedule ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("description", Bag, Description, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("crons", Bag, Crons, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("activeTo", Bag, ActiveTo, OuterOwner);
	ActiveFrom = Bag->GetStringField(TEXT("activeFrom"));
	UBeamJsonUtils::DeserializeOptional<TArray<UScheduleDefinition*>, UScheduleDefinition*>("definitions", Bag, Definitions, OuterOwner);
}