

#include "AutoGen/Optionals/OptionalArrayOfWebhookRewardLibrary.h"

FOptionalArrayOfWebhookReward UOptionalArrayOfWebhookRewardLibrary::MakeOptional(TArray<UWebhookReward*> Value)
{
	FOptionalArrayOfWebhookReward Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfWebhookReward UOptionalArrayOfWebhookRewardLibrary::Conv_OptionalFromValue(TArray<UWebhookReward*> Value)
{
	FOptionalArrayOfWebhookReward Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfWebhookRewardLibrary::HasValue(const FOptionalArrayOfWebhookReward& Optional, TArray<UWebhookReward*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UWebhookReward*> UOptionalArrayOfWebhookRewardLibrary::GetOptionalValue(const FOptionalArrayOfWebhookReward& Optional, TArray<UWebhookReward*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

