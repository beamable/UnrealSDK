
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
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("endTimeMs")), EndTimeMs);
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("startTimeMs")), StartTimeMs);
	Score = Bag->GetNumberField(TEXT("score"));
	Cycle = Bag->GetIntegerField(TEXT("cycle"));
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("playerId")), PlayerId);
}



