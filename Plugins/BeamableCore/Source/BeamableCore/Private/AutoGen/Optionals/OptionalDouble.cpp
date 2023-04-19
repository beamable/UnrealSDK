
#include "BeamableCore/Public/AutoGen/Optionals/OptionalDouble.h"

FOptionalDouble::FOptionalDouble()
{
	Val = double();
	IsSet = false;
}

FOptionalDouble::FOptionalDouble(double Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalDouble::GetAddr() const { return &Val; }

void FOptionalDouble::Set(const void* Data)
{
	Val = *((double*)Data);
	IsSet = true;
}