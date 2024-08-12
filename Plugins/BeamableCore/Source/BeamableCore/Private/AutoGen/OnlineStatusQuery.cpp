
#include "BeamableCore/Public/AutoGen/OnlineStatusQuery.h"
#include "Serialization/BeamJsonUtils.h"




void UOnlineStatusQuery::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("playerIds"), &PlayerIds, Serializer);
}

void UOnlineStatusQuery::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("playerIds"), &PlayerIds, Serializer);		
}

void UOnlineStatusQuery::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("playerIds", Bag, PlayerIds, OuterOwner);
}



