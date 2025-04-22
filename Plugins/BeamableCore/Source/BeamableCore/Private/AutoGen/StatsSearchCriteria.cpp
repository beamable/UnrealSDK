
#include "BeamableCore/Public/AutoGen/StatsSearchCriteria.h"
#include "Serialization/BeamJsonUtils.h"




void UStatsSearchCriteria::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("stat"), Stat, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("rel"), Rel, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("value"), &Value, Serializer);
}

void UStatsSearchCriteria::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("stat"), Stat, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("rel"), Rel, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("value"), &Value, Serializer);		
}

void UStatsSearchCriteria::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("stat")), Stat);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("rel")), Rel);
	UBeamJsonUtils::DeserializeOptional<FString>("value", Bag, Value, OuterOwner);
}



