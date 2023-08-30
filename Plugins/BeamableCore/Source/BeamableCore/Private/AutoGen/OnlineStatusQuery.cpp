
#include "BeamableCore/Public/AutoGen/OnlineStatusQuery.h"
#include "Serialization/BeamJsonUtils.h"




void UOnlineStatusQuery::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("toManyRequests"), &bToManyRequests, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("playerIds"), &PlayerIds, Serializer);
}

void UOnlineStatusQuery::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("toManyRequests"), &bToManyRequests, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("playerIds"), &PlayerIds, Serializer);		
}

void UOnlineStatusQuery::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<bool>("toManyRequests", Bag, bToManyRequests, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("playerIds", Bag, PlayerIds, OuterOwner);
}



