
#include "BeamableCore/Public/AutoGen/Optionals/OptionalOrderDirection.h"

FOptionalOrderDirection::FOptionalOrderDirection()
{
	Val = EBeamOrderDirection();
	IsSet = false;
}

FOptionalOrderDirection::FOptionalOrderDirection(EBeamOrderDirection Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalOrderDirection::GetAddr() const { return &Val; }

void FOptionalOrderDirection::Set(const void* Data)
{
	Val = *((EBeamOrderDirection*)Data);
	IsSet = true;
}