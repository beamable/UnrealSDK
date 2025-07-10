
#include "BeamableCore/Public/AutoGen/Optionals/OptionalFederationType.h"

FOptionalFederationType::FOptionalFederationType()
{
	Val = EBeamFederationType();
	IsSet = false;
}

FOptionalFederationType::FOptionalFederationType(EBeamFederationType Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalFederationType::GetAddr() const { return &Val; }

void FOptionalFederationType::Set(const void* Data)
{
	Val = *((EBeamFederationType*)Data);
	IsSet = true;
}