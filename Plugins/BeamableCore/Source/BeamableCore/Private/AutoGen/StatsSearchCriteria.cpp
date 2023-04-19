
#include "BeamableCore/Public/AutoGen/StatsSearchCriteria.h"
#include "Serialization/BeamJsonUtils.h"




void UStatsSearchCriteria::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("stat"), Stat);
	Serializer->WriteValue(TEXT("rel"), Rel);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("value"), &Value, Serializer);
}

void UStatsSearchCriteria::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("stat"), Stat);
	Serializer->WriteValue(TEXT("rel"), Rel);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("value"), &Value, Serializer);		
}

void UStatsSearchCriteria::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Stat = Bag->GetStringField(TEXT("stat"));
	Rel = Bag->GetStringField(TEXT("rel"));
	UBeamJsonUtils::DeserializeOptional<FString>("value", Bag, Value, OuterOwner);
}



