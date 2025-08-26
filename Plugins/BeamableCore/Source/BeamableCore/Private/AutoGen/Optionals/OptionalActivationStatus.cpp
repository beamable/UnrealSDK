
#include "BeamableCore/Public/AutoGen/Optionals/OptionalActivationStatus.h"

FOptionalActivationStatus::FOptionalActivationStatus()
{
	Val = EBeamActivationStatus();
	IsSet = false;
}

FOptionalActivationStatus::FOptionalActivationStatus(EBeamActivationStatus Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalActivationStatus::GetAddr() const { return &Val; }

void FOptionalActivationStatus::Set(const void* Data)
{
	Val = *((EBeamActivationStatus*)Data);
	IsSet = true;
}