
#include "BeamableCore/Public/AutoGen/CreateFederatedGameServer.h"
#include "Serialization/BeamJsonUtils.h"




void UCreateFederatedGameServer::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FBeamContentId, FString>(TEXT("matchType"), &MatchType, Serializer);
}

void UCreateFederatedGameServer::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FBeamContentId, FString>(TEXT("matchType"), &MatchType, Serializer);		
}

void UCreateFederatedGameServer::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FBeamContentId, FString>("matchType", Bag, MatchType, OuterOwner);
}



