
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBeamGamerTag.h"

FOptionalBeamGamerTag::FOptionalBeamGamerTag()
{
	Val = FBeamGamerTag();
	IsSet = false;
}

FOptionalBeamGamerTag::FOptionalBeamGamerTag(FBeamGamerTag Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalBeamGamerTag::GetAddr() const { return &Val; }

void FOptionalBeamGamerTag::Set(const void* Data)
{
	Val = *((FBeamGamerTag*)Data);
	IsSet = true;
}