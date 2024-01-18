
#include "BeamableCore/Public/AutoGen/MatchType.h"
#include "Serialization/BeamJsonUtils.h"




void UMatchType::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FBeamContentId, FString>(TEXT("id"), &Id, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("waitAfterMinReachedSecs"), &WaitAfterMinReachedSecs, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("maxWaitDurationSecs"), &MaxWaitDurationSecs, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("matchingIntervalSecs"), &MatchingIntervalSecs, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("federatedGameServerNamespace"), &FederatedGameServerNamespace, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UTeamContentProto*>, UTeamContentProto*>(TEXT("teams"), &Teams, Serializer);
}

void UMatchType::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FBeamContentId, FString>(TEXT("id"), &Id, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("waitAfterMinReachedSecs"), &WaitAfterMinReachedSecs, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("maxWaitDurationSecs"), &MaxWaitDurationSecs, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("matchingIntervalSecs"), &MatchingIntervalSecs, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("federatedGameServerNamespace"), &FederatedGameServerNamespace, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UTeamContentProto*>, UTeamContentProto*>(TEXT("teams"), &Teams, Serializer);		
}

void UMatchType::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FBeamContentId, FString>("id", Bag, Id, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("waitAfterMinReachedSecs", Bag, WaitAfterMinReachedSecs, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("maxWaitDurationSecs", Bag, MaxWaitDurationSecs, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("matchingIntervalSecs", Bag, MatchingIntervalSecs, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("federatedGameServerNamespace", Bag, FederatedGameServerNamespace, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UTeamContentProto*>, UTeamContentProto*>("teams", Bag, Teams, OuterOwner);
}



