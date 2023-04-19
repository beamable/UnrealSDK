
#include "BeamableCore/Public/AutoGen/Optionals/OptionalSendNotification.h"

FOptionalSendNotification::FOptionalSendNotification()
{
	Val = nullptr;
	IsSet = false;
}

FOptionalSendNotification::FOptionalSendNotification(USendNotification* Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalSendNotification::GetAddr() const { return &Val; }

void FOptionalSendNotification::Set(const void* Data)
{
	Val = *((USendNotification**)Data);
	IsSet = true;
}