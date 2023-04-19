
#include "BeamableCore/Public/AutoGen/JoinRequestBody.h"





void UJoinRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("tournamentId"), TournamentId);
}

void UJoinRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("tournamentId"), TournamentId);		
}

void UJoinRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	TournamentId = Bag->GetStringField(TEXT("tournamentId"));
}



