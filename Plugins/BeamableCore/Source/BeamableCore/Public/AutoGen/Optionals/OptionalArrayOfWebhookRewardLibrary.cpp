

#include "OptionalArrayOfWebhookRewardLibrary.h"

FOptionalArrayOfWebhookReward UOptionalArrayOfWebhookRewardLibrary::MakeOptionalArrayOfWebhookReward(TArray<UWebhookReward*> Value)
{
	FOptionalArrayOfWebhookReward Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfWebhookReward UOptionalArrayOfWebhookRewardLibrary::Conv_OptionalArrayOfWebhookRewardFromValue(TArray<UWebhookReward*> Value)
{
	FOptionalArrayOfWebhookReward Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

