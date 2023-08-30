
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBeamContentId.h"

FOptionalBeamContentId::FOptionalBeamContentId()
{
	Val = FBeamContentId();
	IsSet = false;
}

FOptionalBeamContentId::FOptionalBeamContentId(FBeamContentId Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalBeamContentId::GetAddr() const { return &Val; }

void FOptionalBeamContentId::Set(const void* Data)
{
	Val = *((FBeamContentId*)Data);
	IsSet = true;
}