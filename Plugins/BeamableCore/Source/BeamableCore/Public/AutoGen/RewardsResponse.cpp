
#include "AutoGen/RewardsResponse.h"
#include "Serialization/BeamJsonUtils.h"


void URewardsResponse ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UTournamentCurrencyReward*>(TEXT("rewardCurrencies"), RewardCurrencies, Serializer);
}

void URewardsResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UTournamentCurrencyReward*>(TEXT("rewardCurrencies"), RewardCurrencies, Serializer);		
}

void URewardsResponse ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UTournamentCurrencyReward*>(Bag->GetArrayField(TEXT("rewardCurrencies")), RewardCurrencies, OuterOwner);
}