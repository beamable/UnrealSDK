
#include "BeamableCore/Public/AutoGen/GetChampionsRequestBody.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UGetChampionsRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("tournamentId"), TournamentId);
	Serializer->WriteValue(TEXT("cycles"), Cycles);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("contentId"), &ContentId, Serializer);
}

void UGetChampionsRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("tournamentId"), TournamentId);
	Serializer->WriteValue(TEXT("cycles"), Cycles);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("contentId"), &ContentId, Serializer);		
}

void UGetChampionsRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	TournamentId = Bag->GetStringField(TEXT("tournamentId"));
	Cycles = Bag->GetIntegerField(TEXT("cycles"));
	UBeamJsonUtils::DeserializeOptional<FString>("contentId", Bag, ContentId, OuterOwner);
}



