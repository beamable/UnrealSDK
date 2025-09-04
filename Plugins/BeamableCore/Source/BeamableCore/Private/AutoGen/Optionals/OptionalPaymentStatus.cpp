
#include "BeamableCore/Public/AutoGen/Optionals/OptionalPaymentStatus.h"

FOptionalPaymentStatus::FOptionalPaymentStatus()
{
	Val = EBeamPaymentStatus();
	IsSet = false;
}

FOptionalPaymentStatus::FOptionalPaymentStatus(EBeamPaymentStatus Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalPaymentStatus::GetAddr() const { return &Val; }

void FOptionalPaymentStatus::Set(const void* Data)
{
	Val = *((EBeamPaymentStatus*)Data);
	IsSet = true;
}