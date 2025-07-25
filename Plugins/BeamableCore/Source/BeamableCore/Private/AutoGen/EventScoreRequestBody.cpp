
#include "BeamableCore/Public/AutoGen/EventScoreRequestBody.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UEventScoreRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("eventId"), EventId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("score"), Score, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("increment"), &bIncrement, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("stats"), &Stats, Serializer);
}

void UEventScoreRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("eventId"), EventId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("score"), Score, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("increment"), &bIncrement, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("stats"), &Stats, Serializer);		
}

void UEventScoreRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("eventId"), Bag, EventId);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("score"), Bag, Score);
	UBeamJsonUtils::DeserializeOptional<bool>("increment", Bag, bIncrement, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TMap<FString, FString>, FString>("stats", Bag, Stats, OuterOwner);
}



