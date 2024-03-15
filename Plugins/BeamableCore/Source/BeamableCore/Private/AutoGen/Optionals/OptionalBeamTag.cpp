
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBeamTag.h"

FOptionalBeamTag::FOptionalBeamTag()
{
	Val = FBeamTag();
	IsSet = false;
}

FOptionalBeamTag::FOptionalBeamTag(FBeamTag Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalBeamTag::GetAddr() const { return &Val; }

void FOptionalBeamTag::Set(const void* Data)
{
	Val = *((FBeamTag*)Data);
	IsSet = true;
}