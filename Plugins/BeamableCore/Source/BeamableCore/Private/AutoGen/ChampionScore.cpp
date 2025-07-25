
#include "BeamableCore/Public/AutoGen/ChampionScore.h"

#include "Misc/DefaultValueHelper.h"



void UChampionScore::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("endTimeMs"), EndTimeMs, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("startTimeMs"), StartTimeMs, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("score"), Score, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("cycle"), Cycle, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("playerId"), PlayerId, Serializer);
}

void UChampionScore::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("endTimeMs"), EndTimeMs, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("startTimeMs"), StartTimeMs, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("score"), Score, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("cycle"), Cycle, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("playerId"), PlayerId, Serializer);		
}

void UChampionScore::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("endTimeMs"), Bag, EndTimeMs);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("startTimeMs"), Bag, StartTimeMs);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("score"), Bag, Score);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("cycle"), Bag, Cycle);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("playerId"), Bag, PlayerId);
}



