
#include "BeamableCore/Public/AutoGen/RankEntry.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void URankEntry::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("rank"), Rank, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("gt"), Gt, Serializer);
	UBeamJsonUtils::SerializeMap<int64>(TEXT("columns"), Columns, Serializer);
	UBeamJsonUtils::SerializeOptional<double>(TEXT("score"), &Score, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<URankEntryStat*>, URankEntryStat*>(TEXT("stats"), &Stats, Serializer);
}

void URankEntry::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("rank"), Rank, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("gt"), Gt, Serializer);
	UBeamJsonUtils::SerializeMap<int64>(TEXT("columns"), Columns, Serializer);
	UBeamJsonUtils::SerializeOptional<double>(TEXT("score"), &Score, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<URankEntryStat*>, URankEntryStat*>(TEXT("stats"), &Stats, Serializer);		
}

void URankEntry::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("rank"), Bag, Rank);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("gt"), Bag, Gt);
	UBeamJsonUtils::DeserializeMap<int64>(TEXT("columns"), Bag, Columns, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<double>("score", Bag, Score, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<URankEntryStat*>, URankEntryStat*>("stats", Bag, Stats, OuterOwner);
}



