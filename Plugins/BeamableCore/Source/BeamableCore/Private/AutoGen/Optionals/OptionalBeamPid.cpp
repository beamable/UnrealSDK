
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBeamPid.h"

FOptionalBeamPid::FOptionalBeamPid()
{
	Val = FBeamPid();
	IsSet = false;
}

FOptionalBeamPid::FOptionalBeamPid(FBeamPid Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalBeamPid::GetAddr() const { return &Val; }

void FOptionalBeamPid::Set(const void* Data)
{
	Val = *((FBeamPid*)Data);
	IsSet = true;
}