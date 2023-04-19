
#include "BeamableCore/Public/AutoGen/UpdatePlayerStatusRequestBody.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UUpdatePlayerStatusRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("playerId"), PlayerId);
	Serializer->WriteValue(TEXT("tournamentId"), TournamentId);
	UBeamJsonUtils::SerializeUObject<UPlayerStatusUpdate*>("update", Update, Serializer);
}

void UUpdatePlayerStatusRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("playerId"), PlayerId);
	Serializer->WriteValue(TEXT("tournamentId"), TournamentId);
	UBeamJsonUtils::SerializeUObject<UPlayerStatusUpdate*>("update", Update, Serializer);		
}

void UUpdatePlayerStatusRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("playerId")), PlayerId);
	TournamentId = Bag->GetStringField(TEXT("tournamentId"));
	UBeamJsonUtils::DeserializeUObject<UPlayerStatusUpdate*>("update", Bag, Update, OuterOwner);
}



