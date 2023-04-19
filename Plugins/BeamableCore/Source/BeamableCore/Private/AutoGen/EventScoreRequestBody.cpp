
#include "BeamableCore/Public/AutoGen/EventScoreRequestBody.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UEventScoreRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("eventId"), EventId);
	Serializer->WriteValue(TEXT("score"), Score);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("increment"), &bIncrement, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("stats"), &Stats, Serializer);
}

void UEventScoreRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("eventId"), EventId);
	Serializer->WriteValue(TEXT("score"), Score);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("increment"), &bIncrement, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("stats"), &Stats, Serializer);		
}

void UEventScoreRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	EventId = Bag->GetStringField(TEXT("eventId"));
	Score = Bag->GetNumberField(TEXT("score"));
	UBeamJsonUtils::DeserializeOptional<bool>("increment", Bag, bIncrement, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TMap<FString, FString>, FString>("stats", Bag, Stats, OuterOwner);
}



