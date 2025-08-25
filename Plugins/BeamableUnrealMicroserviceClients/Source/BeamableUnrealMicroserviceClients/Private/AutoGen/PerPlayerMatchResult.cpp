
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/PerPlayerMatchResult.h"

#include "Misc/DefaultValueHelper.h"



void UPerPlayerMatchResult::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("Won"), bWon, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("RankEarned"), RankEarned, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("CoinsEarned"), CoinsEarned, Serializer);
}

void UPerPlayerMatchResult::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("Won"), bWon, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("RankEarned"), RankEarned, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("CoinsEarned"), CoinsEarned, Serializer);		
}

void UPerPlayerMatchResult::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("Won"), Bag, bWon);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("RankEarned"), Bag, RankEarned);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("CoinsEarned"), Bag, CoinsEarned);
}



