
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBool.h"

FOptionalBool::FOptionalBool()
{
	Val = bool();
	IsSet = false;
}

FOptionalBool::FOptionalBool(bool Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalBool::GetAddr() const { return &Val; }

void FOptionalBool::Set(const void* Data)
{
	Val = *((bool*)Data);
	IsSet = true;
}