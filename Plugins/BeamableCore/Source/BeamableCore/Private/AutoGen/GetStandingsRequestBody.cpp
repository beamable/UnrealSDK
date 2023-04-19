
#include "BeamableCore/Public/AutoGen/GetStandingsRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UGetStandingsRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("tournamentId"), TournamentId);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("max"), &Max, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("focus"), &Focus, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("cycle"), &Cycle, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("from"), &From, Serializer);
}

void UGetStandingsRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("tournamentId"), TournamentId);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("max"), &Max, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("focus"), &Focus, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("cycle"), &Cycle, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("from"), &From, Serializer);		
}

void UGetStandingsRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	TournamentId = Bag->GetStringField(TEXT("tournamentId"));
	UBeamJsonUtils::DeserializeOptional<int32>("max", Bag, Max, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("focus", Bag, Focus, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("cycle", Bag, Cycle, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("from", Bag, From, OuterOwner);
}



