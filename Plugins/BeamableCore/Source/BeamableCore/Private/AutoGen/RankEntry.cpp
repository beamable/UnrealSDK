
#include "BeamableCore/Public/AutoGen/RankEntry.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void URankEntry::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("rank"), Rank);
	Serializer->WriteValue(TEXT("gt"), Gt);
	UBeamJsonUtils::SerializeMap<int64>(TEXT("columns"), Columns, Serializer);
	UBeamJsonUtils::SerializeOptional<double>(TEXT("score"), &Score, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<URankEntryStat*>, URankEntryStat*>(TEXT("stats"), &Stats, Serializer);
}

void URankEntry::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("rank"), Rank);
	Serializer->WriteValue(TEXT("gt"), Gt);
	UBeamJsonUtils::SerializeMap<int64>(TEXT("columns"), Columns, Serializer);
	UBeamJsonUtils::SerializeOptional<double>(TEXT("score"), &Score, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<URankEntryStat*>, URankEntryStat*>(TEXT("stats"), &Stats, Serializer);		
}

void URankEntry::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("rank")), Rank);
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("gt")), Gt);
	UBeamJsonUtils::DeserializeMap<int64>(Bag->GetObjectField(TEXT("columns")), Columns, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<double>("score", Bag, Score, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<URankEntryStat*>, URankEntryStat*>("stats", Bag, Stats, OuterOwner);
}



