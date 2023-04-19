
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfWebhookReward.h"

FOptionalArrayOfWebhookReward::FOptionalArrayOfWebhookReward()
{
	Val = TArray<UWebhookReward*>();
	IsSet = false;
}

FOptionalArrayOfWebhookReward::FOptionalArrayOfWebhookReward(TArray<UWebhookReward*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfWebhookReward::GetAddr() const { return &Val; }

void FOptionalArrayOfWebhookReward::Set(const void* Data)
{
	Val = *((TArray<UWebhookReward*>*)Data);
	IsSet = true;
}