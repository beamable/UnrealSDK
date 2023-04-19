
#include "BeamableCore/Public/AutoGen/Schedule.h"
#include "Serialization/BeamJsonUtils.h"




void USchedule::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("activeFrom"), ActiveFrom);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("description"), &Description, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("activeTo"), &ActiveTo, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("crons"), &Crons, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UScheduleDefinition*>, UScheduleDefinition*>(TEXT("definitions"), &Definitions, Serializer);
}

void USchedule::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("activeFrom"), ActiveFrom);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("description"), &Description, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("activeTo"), &ActiveTo, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("crons"), &Crons, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UScheduleDefinition*>, UScheduleDefinition*>(TEXT("definitions"), &Definitions, Serializer);		
}

void USchedule::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	ActiveFrom = Bag->GetStringField(TEXT("activeFrom"));
	UBeamJsonUtils::DeserializeOptional<FString>("description", Bag, Description, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("activeTo", Bag, ActiveTo, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("crons", Bag, Crons, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UScheduleDefinition*>, UScheduleDefinition*>("definitions", Bag, Definitions, OuterOwner);
}



