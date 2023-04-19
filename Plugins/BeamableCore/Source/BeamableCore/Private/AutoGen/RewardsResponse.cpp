
#include "BeamableCore/Public/AutoGen/RewardsResponse.h"
#include "Serialization/BeamJsonUtils.h"



void URewardsResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void URewardsResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UTournamentCurrencyReward*>(TEXT("rewardCurrencies"), RewardCurrencies, Serializer);
}

void URewardsResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UTournamentCurrencyReward*>(TEXT("rewardCurrencies"), RewardCurrencies, Serializer);		
}

void URewardsResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UTournamentCurrencyReward*>(Bag->GetArrayField(TEXT("rewardCurrencies")), RewardCurrencies, OuterOwner);
}



