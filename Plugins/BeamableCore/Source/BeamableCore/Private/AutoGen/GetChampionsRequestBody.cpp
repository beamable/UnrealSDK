
#include "BeamableCore/Public/AutoGen/GetChampionsRequestBody.h"

#include "Misc/DefaultValueHelper.h"



void UGetChampionsRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("tournamentId"), TournamentId);
	Serializer->WriteValue(TEXT("cycles"), Cycles);
}

void UGetChampionsRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("tournamentId"), TournamentId);
	Serializer->WriteValue(TEXT("cycles"), Cycles);		
}

void UGetChampionsRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	TournamentId = Bag->GetStringField(TEXT("tournamentId"));
	Cycles = Bag->GetIntegerField(TEXT("cycles"));
}



