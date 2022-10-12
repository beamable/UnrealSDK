
#include "AutoGen/RankEntry.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"

void URankEntry ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<URankEntryStat*>, URankEntryStat*>(TEXT("stats"), &Stats, Serializer);
	Serializer->WriteValue(TEXT("rank"), Rank);
	UBeamJsonUtils::SerializeOptional<double>(TEXT("score"), &Score, Serializer);
	UBeamJsonUtils::SerializeMap<int64>(TEXT("columns"), Columns, Serializer);
	Serializer->WriteValue(TEXT("gt"), Gt);
}

void URankEntry::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<URankEntryStat*>, URankEntryStat*>(TEXT("stats"), &Stats, Serializer);
	Serializer->WriteValue(TEXT("rank"), Rank);
	UBeamJsonUtils::SerializeOptional<double>(TEXT("score"), &Score, Serializer);
	UBeamJsonUtils::SerializeMap<int64>(TEXT("columns"), Columns, Serializer);
	Serializer->WriteValue(TEXT("gt"), Gt);		
}

void URankEntry ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<TArray<URankEntryStat*>, URankEntryStat*>("stats", Bag, Stats, OuterOwner);
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("rank")), Rank);
	UBeamJsonUtils::DeserializeOptional<double>("score", Bag, Score, OuterOwner);
	UBeamJsonUtils::DeserializeMap<int64>(Bag->GetObjectField(TEXT("columns")), Columns, OuterOwner);
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("gt")), Gt);
}