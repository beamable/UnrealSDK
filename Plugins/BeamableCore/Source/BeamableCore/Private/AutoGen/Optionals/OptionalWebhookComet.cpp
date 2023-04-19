
#include "BeamableCore/Public/AutoGen/Optionals/OptionalWebhookComet.h"

FOptionalWebhookComet::FOptionalWebhookComet()
{
	Val = nullptr;
	IsSet = false;
}

FOptionalWebhookComet::FOptionalWebhookComet(UWebhookComet* Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalWebhookComet::GetAddr() const { return &Val; }

void FOptionalWebhookComet::Set(const void* Data)
{
	Val = *((UWebhookComet**)Data);
	IsSet = true;
}