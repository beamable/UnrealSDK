
#include "BeamableCore/Public/AutoGen/EventGroupRewards.h"
#include "Serialization/BeamJsonUtils.h"




void UEventGroupRewards::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<UEventRewardContent*>, UEventRewardContent*>(TEXT("scoreRewards"), &ScoreRewards, Serializer);
}

void UEventGroupRewards::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<UEventRewardContent*>, UEventRewardContent*>(TEXT("scoreRewards"), &ScoreRewards, Serializer);		
}

void UEventGroupRewards::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<TArray<UEventRewardContent*>, UEventRewardContent*>("scoreRewards", Bag, ScoreRewards, OuterOwner);
}



