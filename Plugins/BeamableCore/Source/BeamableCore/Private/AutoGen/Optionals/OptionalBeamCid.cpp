
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBeamCid.h"

FOptionalBeamCid::FOptionalBeamCid()
{
	Val = FBeamCid();
	IsSet = false;
}

FOptionalBeamCid::FOptionalBeamCid(FBeamCid Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalBeamCid::GetAddr() const { return &Val; }

void FOptionalBeamCid::Set(const void* Data)
{
	Val = *((FBeamCid*)Data);
	IsSet = true;
}