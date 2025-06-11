
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
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("endTimeMs")), EndTimeMs);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("startTimeMs")), StartTimeMs);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("score")), Score);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("cycle")), Cycle);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("playerId")), PlayerId);
}



