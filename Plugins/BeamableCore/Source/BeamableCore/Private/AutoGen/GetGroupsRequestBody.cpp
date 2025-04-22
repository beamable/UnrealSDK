
#include "BeamableCore/Public/AutoGen/GetGroupsRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UGetGroupsRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("tournamentId"), TournamentId, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("max"), &Max, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("focus"), &Focus, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("cycle"), &Cycle, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("from"), &From, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("contentId"), &ContentId, Serializer);
}

void UGetGroupsRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("tournamentId"), TournamentId, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("max"), &Max, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("focus"), &Focus, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("cycle"), &Cycle, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("from"), &From, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("contentId"), &ContentId, Serializer);		
}

void UGetGroupsRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("tournamentId")), TournamentId);
	UBeamJsonUtils::DeserializeOptional<int32>("max", Bag, Max, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("focus", Bag, Focus, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("cycle", Bag, Cycle, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("from", Bag, From, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("contentId", Bag, ContentId, OuterOwner);
}



