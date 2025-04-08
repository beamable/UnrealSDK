
#include "BeamableCore/Public/AutoGen/ChampionScore.h"

#include "Misc/DefaultValueHelper.h"



void UChampionScore::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("endTimeMs"), EndTimeMs);
	Serializer->WriteValue(TEXT("startTimeMs"), StartTimeMs);
	Serializer->WriteValue(TEXT("score"), Score);
	Serializer->WriteValue(TEXT("cycle"), Cycle);
	Serializer->WriteValue(TEXT("playerId"), PlayerId);
}

void UChampionScore::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("endTimeMs"), EndTimeMs);
	Serializer->WriteValue(TEXT("startTimeMs"), StartTimeMs);
	Serializer->WriteValue(TEXT("score"), Score);
	Serializer->WriteValue(TEXT("cycle"), Cycle);
	Serializer->WriteValue(TEXT("playerId"), PlayerId);		
}

void UChampionScore::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("endTimeMs")), EndTimeMs);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("startTimeMs")), StartTimeMs);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("score")), Score);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("cycle")), Cycle);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("playerId")), PlayerId);
}



